/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#include "../../../../inc/MarlinConfigPre.h"

#if HAS_TFT_LVGL_UI

#include "../../../../MarlinCore.h"
#include "../../../../gcode/queue.h"
#include "../../../../libs/buzzer.h"

#include "draw_ready_print.h"
#include "draw_set.h"
#include "lv_conf.h"
#include "draw_ui.h"
#include "pic_manager.h"

static lv_obj_t * scr;
extern lv_group_t*  g;
static lv_obj_t *buttonBuzz;
static lv_obj_t *label_buzz; 

#define ID_S_WIFI         1
#define ID_S_FAN          2
#define ID_S_ABOUT        3
#define ID_S_CONTINUE     4
#define ID_S_LANGUAGE     5
#define ID_S_MACHINE_PARA 6
#define ID_S_EEPROM_SET   7
#define ID_S_MORE       	8
#define ID_S_RETURN       9
#define ID_S_BUZZER				10

static int32_t repeat_time;
static uint16_t repeat_event_id;

void set_repeat_ops(){
	if (ABS(systick_uptime_millis - repeat_time) < 500)
		return;
	
	switch (repeat_event_id) {
		case ID_S_BUZZER:
			queue.inject_P(PSTR("M500"));
			break;
	}
	repeat_event_id=0;
}

static void event_handler(lv_obj_t * obj, lv_event_t event) {
  #if ENABLED(USE_WIFI_FUNCTION)
    char buf[6] = { 0 };
  #endif
  switch (obj->mks_obj_id) {
		case ID_S_BUZZER:
			if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
				if (buzzer.onoff == 0)
					buzzer.onoff = 1;
				else
					buzzer.onoff = 0;
				disp_buzz_onoff();
       	repeat_time = systick_uptime_millis; 
        repeat_event_id = ID_S_BUZZER;
      }
			break;
    case ID_S_FAN:
      if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
        lv_clear_set();
        lv_draw_fan();
      }
      break;
    case ID_S_ABOUT:
      if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
        lv_clear_set();
        lv_draw_about();
      }
      break;
    case ID_S_CONTINUE:

      break;
		case ID_S_MORE:
      #if ENABLED(CUSTOM_USER_MENUS)
        if (event == LV_EVENT_CLICKED) {
          // nothing to do
        }
        else if (event == LV_EVENT_RELEASED) {
          lv_clear_set();
          lv_draw_more();
        }
      #endif
      break;	
    case ID_S_LANGUAGE:
      if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
        lv_clear_set();
        lv_draw_language();
      }
      break;
    case ID_S_MACHINE_PARA:
      if (event == LV_EVENT_CLICKED) {

      }
      else if (event == LV_EVENT_RELEASED) {
        lv_clear_set();
        lv_draw_machine_para();
      }
      break;
    case ID_S_EEPROM_SET:
      if (event == LV_EVENT_CLICKED) {

      }
      else if (event == LV_EVENT_RELEASED) {
        lv_clear_set();
        lv_draw_eeprom_settings();
      }
      break;
    case ID_S_RETURN:
      if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
        lv_clear_set();
        lv_draw_ready_print();
      }
      break;
    #if ENABLED(USE_WIFI_FUNCTION)
      case ID_S_WIFI:
        if (event == LV_EVENT_CLICKED) {

        }
        else if (event == LV_EVENT_RELEASED) {
        if (gCfgItems.wifi_mode_sel == STA_MODEL) {
          if (wifi_link_state == WIFI_CONNECTED) {
            last_disp_state = SET_UI;
            lv_clear_set();
            lv_draw_wifi();
          }
          else {
            if (uiCfg.command_send == 1) {
              buf[0] = 0xA5;
              buf[1] = 0x07;
              buf[2] = 0x00;
              buf[3] = 0x00;
              buf[4] = 0xFC;
              raw_send_to_wifi(buf, 5);

              last_disp_state = SET_UI;
              lv_clear_set();
              lv_draw_wifi_list();
            }
            else {
              last_disp_state = SET_UI;
              lv_clear_set();
              lv_draw_dialog(WIFI_ENABLE_TIPS);
            }
          }
        }
        else {
          last_disp_state = SET_UI;
          lv_clear_set();
          lv_draw_wifi();
        }
      }
      break;
    #endif
  }
}

void lv_draw_set(void) {
  lv_obj_t *buttonFan, *buttonAbout;
  lv_obj_t *buttonBack;
	#if ENABLED(CUSTOM_USER_MENUS)
    lv_obj_t *buttonMore;
  #endif
  #if HAS_LANG_SELECT_SCREEN
    lv_obj_t *buttonLanguage;
  #endif
	#ifdef HAS_UI_MACHINE_PARA
  lv_obj_t *buttonMachinePara;
  lv_obj_t *buttonEepromSet;
	#endif
  #if ENABLED(USE_WIFI_FUNCTION)
    lv_obj_t *buttonWifi;
  #endif

  if (disp_state_stack._disp_state[disp_state_stack._disp_index] != SET_UI) {
    disp_state_stack._disp_index++;
    disp_state_stack._disp_state[disp_state_stack._disp_index] = SET_UI;
  }
  disp_state = SET_UI;

  scr = lv_obj_create(NULL, NULL);

  //static lv_style_t tool_style;

  lv_obj_set_style(scr, &tft_style_scr);
  lv_scr_load(scr);
  lv_obj_clean(scr);

  lv_obj_t * title = lv_label_create(scr, NULL);
  lv_obj_set_style(title, &tft_style_label_rel);
  lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
  lv_label_set_text(title, creat_title_text());

  lv_refr_now(lv_refr_get_disp_refreshing());

  // Create image buttons
  #ifdef HAS_UI_MACHINE_PARA
  buttonEepromSet   = lv_imgbtn_create(scr, NULL);
	#endif
  //buttonWifi      = lv_imgbtn_create(scr, NULL);
  buttonFan         = lv_imgbtn_create(scr, NULL);
  buttonAbout       = lv_imgbtn_create(scr, NULL);
  //buttonContinue  = lv_imgbtn_create(scr, NULL);
  
	#ifdef HAS_UI_MACHINE_PARA
  buttonMachinePara = lv_imgbtn_create(scr, NULL);
	#endif
  #if HAS_LANG_SELECT_SCREEN
    buttonLanguage  = lv_imgbtn_create(scr, NULL);
  #endif
  #if ENABLED(USE_WIFI_FUNCTION)
  	buttonWifi        = lv_imgbtn_create(scr, NULL);
  #endif
	#if ENABLED(CUSTOM_USER_MENUS)
    buttonMore    = lv_imgbtn_create(scr, NULL);
  #endif
  buttonBack        = lv_imgbtn_create(scr, NULL);
	buttonBuzz				= lv_imgbtn_create(scr, NULL);

	#ifdef HAS_UI_MACHINE_PARA
  lv_obj_set_event_cb_mks(buttonEepromSet, event_handler, ID_S_EEPROM_SET, NULL, 0);
  lv_imgbtn_set_src(buttonEepromSet, LV_BTN_STATE_REL, "F:/bmp_eeprom_settings.bin");
  lv_imgbtn_set_src(buttonEepromSet, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
  lv_imgbtn_set_style(buttonEepromSet, LV_BTN_STATE_PR, &tft_style_label_pre);
  lv_imgbtn_set_style(buttonEepromSet, LV_BTN_STATE_REL, &tft_style_label_rel);
	#endif
	
  #if 1
    lv_obj_set_event_cb_mks(buttonFan, event_handler, ID_S_FAN, NULL, 0);
    lv_imgbtn_set_src(buttonFan, LV_BTN_STATE_REL, "F:/bmp_fan.bin");
    lv_imgbtn_set_src(buttonFan, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
    lv_imgbtn_set_style(buttonFan, LV_BTN_STATE_PR, &tft_style_label_pre);
    lv_imgbtn_set_style(buttonFan, LV_BTN_STATE_REL, &tft_style_label_rel);

    lv_obj_set_event_cb_mks(buttonAbout, event_handler, ID_S_ABOUT, NULL, 0);
    lv_imgbtn_set_src(buttonAbout, LV_BTN_STATE_REL, "F:/bmp_about.bin");
    lv_imgbtn_set_src(buttonAbout, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
    lv_imgbtn_set_style(buttonAbout, LV_BTN_STATE_PR, &tft_style_label_pre);
    lv_imgbtn_set_style(buttonAbout, LV_BTN_STATE_REL, &tft_style_label_rel);

		#ifdef HAS_UI_MACHINE_PARA
    lv_obj_set_event_cb_mks(buttonMachinePara, event_handler, ID_S_MACHINE_PARA, NULL, 0);
    lv_imgbtn_set_src(buttonMachinePara, LV_BTN_STATE_REL, "F:/bmp_machine_para.bin");
    lv_imgbtn_set_src(buttonMachinePara, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
    lv_imgbtn_set_style(buttonMachinePara, LV_BTN_STATE_PR, &tft_style_label_pre);
    lv_imgbtn_set_style(buttonMachinePara, LV_BTN_STATE_REL, &tft_style_label_rel);
		#endif

    #if HAS_LANG_SELECT_SCREEN
      lv_obj_set_event_cb_mks(buttonLanguage, event_handler, ID_S_LANGUAGE, NULL, 0);
      lv_imgbtn_set_src(buttonLanguage, LV_BTN_STATE_REL, "F:/bmp_language.bin");
      lv_imgbtn_set_src(buttonLanguage, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
      lv_imgbtn_set_style(buttonLanguage, LV_BTN_STATE_PR, &tft_style_label_pre);
      lv_imgbtn_set_style(buttonLanguage, LV_BTN_STATE_REL, &tft_style_label_rel);
    #endif

    #if ENABLED(USE_WIFI_FUNCTION)
      lv_obj_set_event_cb_mks(buttonWifi, event_handler,ID_S_WIFI,NULL,0);
      lv_imgbtn_set_src(buttonWifi, LV_BTN_STATE_REL, "F:/bmp_wifi.bin");
      lv_imgbtn_set_src(buttonWifi, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
      lv_imgbtn_set_style(buttonWifi, LV_BTN_STATE_PR, &tft_style_label_pre);
      lv_imgbtn_set_style(buttonWifi, LV_BTN_STATE_REL, &tft_style_label_rel);
    #endif

		#if ENABLED(CUSTOM_USER_MENUS)
			lv_obj_set_event_cb_mks(buttonMore, event_handler,ID_S_MORE,NULL,0);
			lv_imgbtn_set_src(buttonMore, LV_BTN_STATE_REL, "F:/bmp_3dtouch.bin");
			lv_imgbtn_set_src(buttonMore, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
			lv_imgbtn_set_style(buttonMore, LV_BTN_STATE_PR, &tft_style_label_pre);
			lv_imgbtn_set_style(buttonMore, LV_BTN_STATE_REL, &tft_style_label_rel);
		#endif

    lv_obj_set_event_cb_mks(buttonBuzz, event_handler, ID_S_BUZZER,NULL , 0);
    lv_imgbtn_set_style(buttonBuzz, LV_BTN_STATE_PR, &tft_style_label_pre);
    lv_imgbtn_set_style(buttonBuzz, LV_BTN_STATE_REL, &tft_style_label_rel);

		lv_obj_set_event_cb_mks(buttonBack, event_handler, ID_S_RETURN,NULL , 0);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, "F:/bmp_return.bin");
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
    lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
    lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);

  #endif // if 1

  /*lv_obj_set_pos(buttonWifi,INTERVAL_V,titleHeight);
  lv_obj_set_pos(buttonFan,BTN_X_PIXEL+INTERVAL_V*2,titleHeight);
  lv_obj_set_pos(buttonAbout,BTN_X_PIXEL*2+INTERVAL_V*3,titleHeight);
  lv_obj_set_pos(buttonContinue,BTN_X_PIXEL*3+INTERVAL_V*4,titleHeight);
  lv_obj_set_pos(buttonLanguage,BTN_X_PIXEL+INTERVAL_V*2,BTN_Y_PIXEL+INTERVAL_H+titleHeight);
  lv_obj_set_pos(buttonBack,BTN_X_PIXEL*3+INTERVAL_V*4, BTN_Y_PIXEL+INTERVAL_H+titleHeight);*/

	#ifdef HAS_UI_MACHINE_PARA
	  //lv_obj_set_pos(buttonWifi,INTERVAL_V,titleHeight);
	  lv_obj_set_pos(buttonEepromSet, INTERVAL_V, titleHeight);
	  lv_obj_set_pos(buttonFan, BTN_X_PIXEL + INTERVAL_V * 2, titleHeight);
	  lv_obj_set_pos(buttonAbout, BTN_X_PIXEL * 2 + INTERVAL_V * 3, titleHeight);
	  //lv_obj_set_pos(buttonContinue,BTN_X_PIXEL*3+INTERVAL_V*4,titleHeight);
		lv_obj_set_pos(buttonMachinePara, INTERVAL_V, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
		#if HAS_LANG_SELECT_SCREEN
	    lv_obj_set_pos(buttonLanguage, BTN_X_PIXEL + INTERVAL_V * 2, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
	  #endif
	#else
		lv_obj_set_pos(buttonFan, INTERVAL_V, titleHeight);
		#if ENABLED(CUSTOM_USER_MENUS)
	  lv_obj_set_pos(buttonMore , BTN_X_PIXEL + INTERVAL_V * 2, titleHeight);
		#endif
		#if HAS_LANG_SELECT_SCREEN
	  lv_obj_set_pos(buttonLanguage, BTN_X_PIXEL * 2 + INTERVAL_V * 3, titleHeight);
		#endif
		lv_obj_set_pos(buttonBuzz, BTN_X_PIXEL * 3 + INTERVAL_V * 4, titleHeight);
		lv_obj_set_pos(buttonAbout, INTERVAL_V, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
	#endif
  
  #if ENABLED(USE_WIFI_FUNCTION)
    lv_obj_set_pos(buttonWifi,BTN_X_PIXEL*2+INTERVAL_V*3,BTN_Y_PIXEL+INTERVAL_H+titleHeight);
  #endif
	
  lv_obj_set_pos(buttonBack, BTN_X_PIXEL * 3 + INTERVAL_V * 4, BTN_Y_PIXEL + INTERVAL_H + titleHeight);

  /// Create labels on the buttons
  //lv_btn_set_layout(buttonWifi, LV_LAYOUT_OFF);
  #ifdef HAS_UI_MACHINE_PARA
  lv_btn_set_layout(buttonEepromSet, LV_LAYOUT_OFF);
	#endif
  lv_btn_set_layout(buttonFan, LV_LAYOUT_OFF);
  lv_btn_set_layout(buttonAbout, LV_LAYOUT_OFF);
  //lv_btn_set_layout(buttonContinue, LV_LAYOUT_OFF);
	#ifdef HAS_UI_MACHINE_PARA
  lv_btn_set_layout(buttonMachinePara, LV_LAYOUT_OFF);
	#endif
  #if HAS_LANG_SELECT_SCREEN
    lv_btn_set_layout(buttonLanguage, LV_LAYOUT_OFF);
  #endif
  #if ENABLED(USE_WIFI_FUNCTION)
    lv_btn_set_layout(buttonWifi, LV_LAYOUT_OFF);
  #endif
	#if ENABLED(CUSTOM_USER_MENUS)
    lv_btn_set_layout(buttonMore, LV_LAYOUT_OFF);
	#endif
  lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonBuzz, LV_LAYOUT_OFF);

  //lv_obj_t *labelWifi= lv_label_create(buttonWifi, NULL);
  #ifdef HAS_UI_MACHINE_PARA
  lv_obj_t *label_EepromSet   = lv_label_create(buttonEepromSet, NULL);
	#endif
  lv_obj_t *labelFan          = lv_label_create(buttonFan, NULL);
  lv_obj_t *label_About       = lv_label_create(buttonAbout, NULL);
  //lv_obj_t *label_Continue  = lv_label_create(buttonContinue, NULL);
	#ifdef HAS_UI_MACHINE_PARA
  lv_obj_t *label_MachinePara = lv_label_create(buttonMachinePara, NULL);
	#endif
  #if HAS_LANG_SELECT_SCREEN
    lv_obj_t *label_Language  = lv_label_create(buttonLanguage, NULL);
  #endif
  #if ENABLED(USE_WIFI_FUNCTION)
    lv_obj_t *label_Wifi      = lv_label_create(buttonWifi, NULL);
  #endif
	#if ENABLED(CUSTOM_USER_MENUS)
    lv_obj_t * label_More   = lv_label_create(buttonMore, NULL);
	#endif
  lv_obj_t *label_Back        = lv_label_create(buttonBack, NULL);
	label_buzz				= lv_label_create(buttonBuzz, NULL);

  if (gCfgItems.multiple_language != 0) {
		#ifdef HAS_UI_MACHINE_PARA
    lv_label_set_text(label_EepromSet, set_menu.eepromSet);
    lv_obj_align(label_EepromSet, buttonEepromSet, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
		#endif

    lv_label_set_text(labelFan, set_menu.fan);
    lv_obj_align(labelFan, buttonFan, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

    lv_label_set_text(label_About, set_menu.about);
    lv_obj_align(label_About, buttonAbout, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);		

		#ifdef HAS_UI_MACHINE_PARA
    lv_label_set_text(label_MachinePara, set_menu.machine_para);
    lv_obj_align(label_MachinePara, buttonMachinePara, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
		#endif
		
    #if HAS_LANG_SELECT_SCREEN
      lv_label_set_text(label_Language, set_menu.language);
      lv_obj_align(label_Language, buttonLanguage, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
    #endif

    #if ENABLED(USE_WIFI_FUNCTION)
      lv_label_set_text(label_Wifi, set_menu.wifi);
      lv_obj_align(label_Wifi, buttonWifi, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
    #endif

		#if ENABLED(CUSTOM_USER_MENUS)
      lv_label_set_text(label_More, tool_menu.more);
      lv_obj_align(label_More, buttonMore, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
		#endif

		lv_label_set_text(label_Back, common_menu.text_back);
    lv_obj_align(label_Back, buttonBack, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
  }

	disp_buzz_onoff();
	
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) {
      lv_group_add_obj(g, buttonFan);
      lv_group_add_obj(g, buttonAbout);
			#ifdef HAS_UI_MACHINE_PARA
				lv_group_add_obj(g, buttonEepromSet);
      	lv_group_add_obj(g, buttonMachinePara);
			#endif
      lv_group_add_obj(g, buttonLanguage);
      #if ENABLED(USE_WIFI_FUNCTION)
        lv_group_add_obj(g, buttonWifi);
      #endif
			#if ENABLED(CUSTOM_USER_MENUS)
      	lv_group_add_obj(g, buttonMore);
			#endif
      lv_group_add_obj(g, buttonBack);
    }
  #endif
}

void disp_buzz_onoff() {
  if (buzzer.onoff == 1) {  
		lv_imgbtn_set_src(buttonBuzz, LV_BTN_STATE_REL, "F:/bmp_buzz_on.bin");
    lv_imgbtn_set_src(buttonBuzz, LV_BTN_STATE_PR, "F:/bmp_buzz_on.bin");
  }else{
		lv_imgbtn_set_src(buttonBuzz, LV_BTN_STATE_REL, "F:/bmp_buzz_off.bin");
  	lv_imgbtn_set_src(buttonBuzz, LV_BTN_STATE_PR, "F:/bmp_buzz_off.bin");
	}
	if (gCfgItems.multiple_language != 0) {
		lv_label_set_text(label_buzz, set_menu.buzzer);
		lv_obj_align(label_buzz, buttonBuzz, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
	}
}

void lv_clear_set() {
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) lv_group_remove_all_objs(g);
  #endif
  lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI
