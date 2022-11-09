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
#include "draw_ready_print.h"
#include "draw_set.h"
#include "lv_conf.h"
//#include "../lvgl/src/lv_objx/lv_imgbtn.h"
//#include "../lvgl/src/lv_objx/lv_img.h"
//#include "../lvgl/src/lv_core/lv_disp.h"
//#include "../lvgl/src/lv_core/lv_refr.h"
#include "draw_ui.h"
#include "../../../../gcode/queue.h"

#if ENABLED(BLTOUCH)
#include "../../../../feature/bltouch.h"
#endif

extern lv_group_t * g;
static lv_obj_t * scr;

static lv_obj_t *buttonCustom1;
static lv_obj_t * labelCustom1;
static lv_obj_t *buttonCustom2;
static lv_obj_t * labelCustom2;
static lv_obj_t *buttonCustom3;
static lv_obj_t * labelCustom3;
static lv_obj_t *buttonCustom4;
static lv_obj_t * labelCustom4;
static lv_obj_t *buttonCustom5;
static lv_obj_t * labelCustom5;
static lv_obj_t *buttonCustom6;
static lv_obj_t * labelCustom6;

#define ID_3DTOUCH_RESET   	1
#define ID_3DTOUCH_TEST   	2
#define ID_3DTOUCH_DEPLOY   3
#define ID_3DTOUCH_STOW   	4
#define ID_3DTOUCH_ONOFF   	5
#define ID_3DTOUCH_PARA   	6
#define ID_3DTOUCH_RETURN   7

static int32_t repeat_time;
static uint16_t repeat_event_id;

void more_repeat_ops(){
	if (ABS(systick_uptime_millis - repeat_time) < 500)
		return;
	
	switch (repeat_event_id) {
		case ID_3DTOUCH_RESET:
			  if(bltouch.enable_state) bltouch._reset();
			break;
		case ID_3DTOUCH_TEST:
			if(bltouch.enable_state) bltouch._selftest();
			break;
		case ID_3DTOUCH_DEPLOY:
			if(bltouch.enable_state)	bltouch._deploy();
			break;
		case ID_3DTOUCH_STOW:
			 if(bltouch.enable_state) bltouch._stow();
			 break;
	}
	repeat_event_id=0;
}

static void event_handler(lv_obj_t * obj, lv_event_t event) {
  switch (obj->mks_obj_id) {
    case ID_3DTOUCH_RESET:
      if (event == LV_EVENT_CLICKED) {
      }
      else if (event == LV_EVENT_RELEASED) {
				repeat_time = systick_uptime_millis; 
				repeat_event_id = ID_3DTOUCH_RESET;
      }
      break;
    case ID_3DTOUCH_TEST:
      if (event == LV_EVENT_CLICKED) {
      }
      else if (event == LV_EVENT_RELEASED) {
				repeat_time = systick_uptime_millis; 
				repeat_event_id = ID_3DTOUCH_TEST;
      }
      break;
    case ID_3DTOUCH_DEPLOY:
      if (event == LV_EVENT_CLICKED) {
      }
      else if (event == LV_EVENT_RELEASED) {
				repeat_time = systick_uptime_millis; 
				repeat_event_id = ID_3DTOUCH_DEPLOY;
      }
      break;
    case ID_3DTOUCH_STOW:
      if (event == LV_EVENT_CLICKED) {
      }
      else if (event == LV_EVENT_RELEASED) {
				repeat_time = systick_uptime_millis; 
				repeat_event_id = ID_3DTOUCH_STOW;
      }
      break;
    case ID_3DTOUCH_ONOFF:
      if (event == LV_EVENT_CLICKED) {
      }
      else if (event == LV_EVENT_RELEASED) {
				if (gCfgItems.multiple_language != 0) {
					bltouch.switch_flag = 1;
					if (bltouch.enable_state == 0)
						bltouch.enable_state = 1;
					else
						bltouch.enable_state = 0;
				}
				queue.inject_P(PSTR(USER_GCODE_5));
      }
      break;
    case ID_3DTOUCH_PARA:
      if (event == LV_EVENT_CLICKED) {
      }
      else if (event == LV_EVENT_RELEASED) {
          lv_clear_more();
        	lv_draw_auto_level_offset_settings();
      }
      break;
    case ID_3DTOUCH_RETURN:
      if (event == LV_EVENT_CLICKED) {
      }
      else if (event == LV_EVENT_RELEASED) {
        lv_clear_more();
				draw_return_ui();
      }
      break;
  }
}

void lv_draw_more(void) {
  lv_obj_t *buttonBack;

  if (disp_state_stack._disp_state[disp_state_stack._disp_index] != MORE_UI) {
    disp_state_stack._disp_index++;
    disp_state_stack._disp_state[disp_state_stack._disp_index] = MORE_UI;
  }
  disp_state = MORE_UI;

  scr = lv_obj_create(NULL, NULL);
  #if ENABLED(BLTOUCH_MENU_OPTION)
  bltouch.switch_flag = 0;
  #endif

  //static lv_style_t tool_style;

  lv_obj_set_style(scr, &tft_style_scr);
  lv_scr_load(scr);
  lv_obj_clean(scr);

  lv_obj_t * title = lv_label_create(scr, NULL);
  lv_obj_set_style(title, &tft_style_label_rel);
  lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
  lv_label_set_text(title, creat_title_text());

  lv_refr_now(lv_refr_get_disp_refreshing());

  /*Create an Image button and label*/
  buttonCustom1 = lv_imgbtn_create(scr, NULL);
  lv_obj_set_event_cb_mks(buttonCustom1, event_handler,ID_3DTOUCH_RESET, NULL,0);
  lv_imgbtn_set_src(buttonCustom1, LV_BTN_STATE_REL, "F:/bmp_3dtouch_reset.bin");
  lv_imgbtn_set_src(buttonCustom1, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
  lv_imgbtn_set_style(buttonCustom1, LV_BTN_STATE_PR, &tft_style_label_pre);
  lv_imgbtn_set_style(buttonCustom1, LV_BTN_STATE_REL, &tft_style_label_rel);
  lv_obj_set_pos(buttonCustom1, INTERVAL_V, titleHeight);
  lv_btn_set_layout(buttonCustom1, LV_LAYOUT_OFF);
  labelCustom1 = lv_label_create(buttonCustom1, NULL);

  buttonCustom2 = lv_imgbtn_create(scr, NULL);
  lv_obj_set_event_cb_mks(buttonCustom2, event_handler, ID_3DTOUCH_TEST, NULL, 0);
  lv_imgbtn_set_src(buttonCustom2, LV_BTN_STATE_REL, "F:/bmp_3dtouch_test.bin");
  lv_imgbtn_set_src(buttonCustom2, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
  lv_imgbtn_set_style(buttonCustom2, LV_BTN_STATE_PR, &tft_style_label_pre);
  lv_imgbtn_set_style(buttonCustom2, LV_BTN_STATE_REL, &tft_style_label_rel);
  lv_obj_set_pos(buttonCustom2, BTN_X_PIXEL + INTERVAL_V * 2, titleHeight);
  lv_btn_set_layout(buttonCustom2, LV_LAYOUT_OFF);
  labelCustom2 = lv_label_create(buttonCustom2, NULL);

  buttonCustom3 = lv_imgbtn_create(scr, NULL);
  lv_obj_set_event_cb_mks(buttonCustom3, event_handler, ID_3DTOUCH_DEPLOY, NULL, 0);
  lv_imgbtn_set_src(buttonCustom3, LV_BTN_STATE_REL, "F:/bmp_3dtouch_deploy.bin");
  lv_imgbtn_set_src(buttonCustom3, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
  lv_imgbtn_set_style(buttonCustom3, LV_BTN_STATE_PR, &tft_style_label_pre);
  lv_imgbtn_set_style(buttonCustom3, LV_BTN_STATE_REL, &tft_style_label_rel);
  lv_obj_set_pos(buttonCustom3, BTN_X_PIXEL * 2 + INTERVAL_V * 3, titleHeight);
  lv_btn_set_layout(buttonCustom3, LV_LAYOUT_OFF);
  labelCustom3 = lv_label_create(buttonCustom3, NULL);

  buttonCustom4 = lv_imgbtn_create(scr, NULL);
  lv_obj_set_event_cb_mks(buttonCustom4, event_handler, ID_3DTOUCH_STOW, NULL, 0);
  lv_imgbtn_set_src(buttonCustom4, LV_BTN_STATE_REL, "F:/bmp_3dtouch_stow.bin");
  lv_imgbtn_set_src(buttonCustom4, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
  lv_imgbtn_set_style(buttonCustom4, LV_BTN_STATE_PR, &tft_style_label_pre);
  lv_imgbtn_set_style(buttonCustom4, LV_BTN_STATE_REL, &tft_style_label_rel);
  lv_obj_set_pos(buttonCustom4, BTN_X_PIXEL * 3 + INTERVAL_V * 4, titleHeight);
  lv_btn_set_layout(buttonCustom4, LV_LAYOUT_OFF);
  labelCustom4 = lv_label_create(buttonCustom4, NULL);

  buttonCustom5 = lv_imgbtn_create(scr, NULL);
  lv_obj_set_event_cb_mks(buttonCustom5, event_handler,ID_3DTOUCH_ONOFF, NULL,0);
	if (bltouch.enable_state == 0)
  {
  	lv_imgbtn_set_src(buttonCustom5, LV_BTN_STATE_REL, "F:/bmp_3dtouch_off.bin");
  	lv_imgbtn_set_src(buttonCustom5, LV_BTN_STATE_PR, "F:/bmp_3dtouch_off.bin");
	}else{
		lv_imgbtn_set_src(buttonCustom5, LV_BTN_STATE_REL, "F:/bmp_3dtouch_on.bin");
  	lv_imgbtn_set_src(buttonCustom5, LV_BTN_STATE_PR, "F:/bmp_3dtouch_on.bin");
	}
  lv_imgbtn_set_style(buttonCustom5, LV_BTN_STATE_PR, &tft_style_label_pre);
  lv_imgbtn_set_style(buttonCustom5, LV_BTN_STATE_REL, &tft_style_label_rel);
  lv_obj_set_pos(buttonCustom5, INTERVAL_V, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
  lv_btn_set_layout(buttonCustom5, LV_LAYOUT_OFF);
  labelCustom5 = lv_label_create(buttonCustom5, NULL);

	if(bltouch.enable_state){
	  buttonCustom6 = lv_imgbtn_create(scr, NULL);
	  lv_obj_set_event_cb_mks(buttonCustom6, event_handler,ID_3DTOUCH_PARA, NULL,0);
		lv_imgbtn_set_src(buttonCustom6, LV_BTN_STATE_REL, "F:/bmp_machine_para.bin");
	  lv_imgbtn_set_src(buttonCustom6, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
	  lv_imgbtn_set_style(buttonCustom6, LV_BTN_STATE_PR, &tft_style_label_pre);
	  lv_imgbtn_set_style(buttonCustom6, LV_BTN_STATE_REL, &tft_style_label_rel);
	  lv_obj_set_pos(buttonCustom6, BTN_X_PIXEL + INTERVAL_V * 2, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
	  lv_btn_set_layout(buttonCustom6, LV_LAYOUT_OFF);
	  labelCustom6 = lv_label_create(buttonCustom6, NULL);
	}
	
  buttonBack = lv_imgbtn_create(scr, NULL);
  lv_obj_set_event_cb_mks(buttonBack, event_handler,ID_3DTOUCH_RETURN, NULL,0);
  lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, "F:/bmp_return.bin");
  lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
  lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
  lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);
  lv_obj_set_pos(buttonBack, BTN_X_PIXEL * 3 + INTERVAL_V * 4, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
  lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);
  lv_obj_t * label_Back = lv_label_create(buttonBack, NULL);


  if (gCfgItems.multiple_language != 0) {
    lv_label_set_text(labelCustom1, more_menu.BLTouch_Reset);
    lv_obj_align(labelCustom1, buttonCustom1, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

    lv_label_set_text(labelCustom2, more_menu.BLTouch_Test);
    lv_obj_align(labelCustom2, buttonCustom2, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

    lv_label_set_text(labelCustom3, more_menu.BLTouch_Deploy);
    lv_obj_align(labelCustom3, buttonCustom3, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

    lv_label_set_text(labelCustom4, more_menu.BLTouch_Stow);
    lv_obj_align(labelCustom4, buttonCustom4, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

  	if (bltouch.enable_state == 0)
    	lv_label_set_text(labelCustom5, more_menu.BLTouch_Off);
  	else
    	lv_label_set_text(labelCustom5, more_menu.BLTouch_On);
    lv_obj_align(labelCustom5, buttonCustom5, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

		if(bltouch.enable_state){
    	lv_label_set_text(labelCustom6, set_menu.machine_para);
    	lv_obj_align(labelCustom6, buttonCustom6, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
		}
		
    lv_label_set_text(label_Back, common_menu.text_back);
    lv_obj_align(label_Back, buttonBack, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
  }

  #if BUTTONS_EXIST(EN1, EN2, ENC)
	if (gCfgItems.encoder_enable == true) {
    lv_group_add_obj(g, buttonCustom1);
    lv_group_add_obj(g, buttonCustom2);
    lv_group_add_obj(g, buttonCustom3);
    lv_group_add_obj(g, buttonCustom4);
    lv_group_add_obj(g, buttonCustom5);
    lv_group_add_obj(g, buttonCustom6);
		lv_group_add_obj(g, buttonBack);
	}
  #endif // BUTTONS_EXIST(EN1, EN2, ENC)
}

void lv_clear_more() {
	#if BUTTONS_EXIST(EN1, EN2, ENC)
	if (gCfgItems.encoder_enable == true) {
		lv_group_remove_all_objs(g);
	}
  #endif // BUTTONS_EXIST(EN1, EN2, ENC)
	lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI
