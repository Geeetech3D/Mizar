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

#include "lv_conf.h"
#include "draw_ui.h"

#include "../../../../MarlinCore.h"
#include "../../../../module/temperature.h"

static lv_obj_t * scr;
extern lv_group_t*  g;
static lv_obj_t *buttoType, *buttonStep;
static lv_obj_t *labelType;
static lv_obj_t *labelStep;
static lv_obj_t * tempText1;

#define ID_H_ADD    1
#define ID_H_DEC    2
#define ID_H_TYPE   3
#define ID_H_STEP   4
#define ID_H_OFF    5
#define ID_H_RETURN 6

static void event_handler(lv_obj_t * obj, lv_event_t event) {
  switch (obj->mks_obj_id) {
    case ID_H_ADD:
      if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
        if (uiCfg.curTempType == 0) {
          thermalManager.temp_hotend[uiCfg.curSprayerChoose].target += uiCfg.stepHeat;
          if (uiCfg.curSprayerChoose == 0) {
            if ((int)thermalManager.temp_hotend[uiCfg.curSprayerChoose].target > (HEATER_0_MAXTEMP - (WATCH_TEMP_INCREASE + TEMP_HYSTERESIS + 1))) {
              thermalManager.temp_hotend[uiCfg.curSprayerChoose].target = (float)HEATER_0_MAXTEMP - (WATCH_TEMP_INCREASE + TEMP_HYSTERESIS + 1);
            }
          }
          #if !defined(SINGLENOZZLE) && HAS_MULTI_EXTRUDER
            else if ((int)thermalManager.temp_hotend[uiCfg.curSprayerChoose].target > (HEATER_1_MAXTEMP - (WATCH_TEMP_INCREASE + TEMP_HYSTERESIS + 1))) {
              thermalManager.temp_hotend[uiCfg.curSprayerChoose].target = (float)HEATER_1_MAXTEMP - (WATCH_TEMP_INCREASE + TEMP_HYSTERESIS + 1);
            }
          #endif
          thermalManager.start_watching_hotend(uiCfg.curSprayerChoose);
        }
        #if HAS_HEATED_BED
          else {
            thermalManager.temp_bed.target += uiCfg.stepHeat;
            if ((int)thermalManager.temp_bed.target > BED_MAXTEMP - (WATCH_BED_TEMP_INCREASE + TEMP_BED_HYSTERESIS + 1)) {
              thermalManager.temp_bed.target = (float)BED_MAXTEMP - (WATCH_BED_TEMP_INCREASE + TEMP_BED_HYSTERESIS + 1);
            }
            thermalManager.start_watching_bed();
          }
        #endif
        disp_desire_temp();
      }
      break;
    case ID_H_DEC:
      if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
        if (uiCfg.curTempType == 0) {
          if ((int)thermalManager.temp_hotend[uiCfg.curSprayerChoose].target > uiCfg.stepHeat) {
            thermalManager.temp_hotend[uiCfg.curSprayerChoose].target -= uiCfg.stepHeat;
          }
          else {
            thermalManager.temp_hotend[uiCfg.curSprayerChoose].target = (float)0;
          }
          thermalManager.start_watching_hotend(uiCfg.curSprayerChoose);
        }
        #if HAS_HEATED_BED
          else {
            if ((int)thermalManager.temp_bed.target > uiCfg.stepHeat) {
              thermalManager.temp_bed.target -= uiCfg.stepHeat;
            }
            else {
              thermalManager.temp_bed.target = (float)0;
            }
            thermalManager.start_watching_bed();
          }
        #endif
        disp_desire_temp();
      }

      break;
    case ID_H_TYPE:
      if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
        if (uiCfg.curTempType == 0) {
          if (ENABLED(HAS_MULTI_EXTRUDER)) {
            if (uiCfg.curSprayerChoose == 0) {
              uiCfg.curSprayerChoose = 1;
            }
            else if (uiCfg.curSprayerChoose == 1) {
              if (TEMP_SENSOR_BED != 0) {
                uiCfg.curTempType = 1;
              }
              else {
                uiCfg.curTempType      = 0;
                uiCfg.curSprayerChoose = 0;
              }
            }
          }
          else if (uiCfg.curSprayerChoose == 0) {
            if (TEMP_SENSOR_BED != 0)
              uiCfg.curTempType = 1;
            else
              uiCfg.curTempType = 0;
          }
        }
        else if (uiCfg.curTempType == 1) {
          uiCfg.curSprayerChoose = 0;
          uiCfg.curTempType      = 0;
        }
				#if ENABLED(HAS_UI_BUTTEN_TYPE)
        disp_temp_type();
				#endif
      }
      break;
    case ID_H_STEP:
      if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
        switch (uiCfg.stepHeat) {
          case  1: uiCfg.stepHeat =  5; break;
          case  5: uiCfg.stepHeat = 10; break;
          case 10: uiCfg.stepHeat =  1; break;
          default: break;
        }
        disp_step_heat();
      }
      break;
    case ID_H_OFF:
      if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
        if (uiCfg.curTempType == 0) {
          thermalManager.temp_hotend[uiCfg.curSprayerChoose].target = (float)0;
          thermalManager.start_watching_hotend(uiCfg.curSprayerChoose);
        }
        #if HAS_HEATED_BED
          else {
            thermalManager.temp_bed.target = (float)0;
            thermalManager.start_watching_bed();
          }
        #endif
        disp_desire_temp();
      }
      break;
    case ID_H_RETURN:
      if (event == LV_EVENT_CLICKED) {
        // nothing to do
      }
      else if (event == LV_EVENT_RELEASED) {
        clear_cur_ui();
        draw_return_ui();
      }
      break;
  }
}

void lv_draw_handHeat(void) {
  lv_obj_t *buttonAdd, *buttonDec;
  lv_obj_t *buttonOff, *buttonBack;

  if (disp_state_stack._disp_state[disp_state_stack._disp_index] != HAND_HEAT_UI) {
    disp_state_stack._disp_index++;
    disp_state_stack._disp_state[disp_state_stack._disp_index] = HAND_HEAT_UI;
  }
  disp_state = HAND_HEAT_UI;

  scr = lv_obj_create(NULL, NULL);

  lv_obj_set_style(scr, &tft_style_scr);
  lv_scr_load(scr);
  lv_obj_clean(scr);

  lv_obj_t * title = lv_label_create(scr, NULL);
  lv_obj_set_style(title, &tft_style_label_rel);
  lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
  lv_label_set_text(title, creat_title_text());

  lv_refr_now(lv_refr_get_disp_refreshing());

  // Create image buttons
  buttonAdd  = lv_imgbtn_create(scr, NULL);
  buttonDec  = lv_imgbtn_create(scr, NULL);
	#if ENABLED(HAS_UI_BUTTEN_TYPE)
  buttoType  = lv_imgbtn_create(scr, NULL);
	#endif
  buttonStep = lv_imgbtn_create(scr, NULL);
  buttonOff  = lv_imgbtn_create(scr, NULL);
  buttonBack = lv_imgbtn_create(scr, NULL);

	// when printing, disable buttonoff
	if(printingIsActive() || printingIsPaused()) 
		lv_obj_set_hidden(buttonOff, 1);
	else
		lv_obj_set_hidden(buttonOff, 0);
	
  lv_obj_set_event_cb_mks(buttonAdd, event_handler, ID_H_ADD, NULL, 0);
  lv_imgbtn_set_src(buttonAdd, LV_BTN_STATE_REL, "F:/bmp_Add.bin");
  lv_imgbtn_set_src(buttonAdd, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
  lv_imgbtn_set_style(buttonAdd, LV_BTN_STATE_PR, &tft_style_label_pre);
  lv_imgbtn_set_style(buttonAdd, LV_BTN_STATE_REL, &tft_style_label_rel);
  lv_obj_clear_protect(buttonAdd, LV_PROTECT_FOLLOW);

  #if 1
    lv_obj_set_event_cb_mks(buttonDec, event_handler, ID_H_DEC, NULL, 0);
    lv_imgbtn_set_src(buttonDec, LV_BTN_STATE_REL, "F:/bmp_Dec.bin");
    lv_imgbtn_set_src(buttonDec, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
    lv_imgbtn_set_style(buttonDec, LV_BTN_STATE_PR, &tft_style_label_pre);
    lv_imgbtn_set_style(buttonDec, LV_BTN_STATE_REL, &tft_style_label_rel);

		#if ENABLED(HAS_UI_BUTTEN_TYPE)
    lv_obj_set_event_cb_mks(buttoType, event_handler, ID_H_TYPE, NULL, 0);
    lv_imgbtn_set_style(buttoType, LV_BTN_STATE_PR, &tft_style_label_pre);
    lv_imgbtn_set_style(buttoType, LV_BTN_STATE_REL, &tft_style_label_rel);
		#endif
		
    lv_obj_set_event_cb_mks(buttonStep, event_handler, ID_H_STEP, NULL, 0);
    lv_imgbtn_set_style(buttonStep, LV_BTN_STATE_PR, &tft_style_label_pre);
    lv_imgbtn_set_style(buttonStep, LV_BTN_STATE_REL, &tft_style_label_rel);

    lv_obj_set_event_cb_mks(buttonOff, event_handler, ID_H_OFF, NULL, 0);
    lv_imgbtn_set_src(buttonOff, LV_BTN_STATE_REL, "F:/bmp_cool.bin");
    lv_imgbtn_set_src(buttonOff, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
    lv_imgbtn_set_style(buttonOff, LV_BTN_STATE_PR, &tft_style_label_pre);
    lv_imgbtn_set_style(buttonOff, LV_BTN_STATE_REL, &tft_style_label_rel);

    lv_obj_set_event_cb_mks(buttonBack, event_handler, ID_H_RETURN, NULL, 0);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, "F:/bmp_return.bin");
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
    lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
    lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);
  #endif

	#if ENABLED(HAS_UI_BUTTEN_TYPE)
  lv_obj_set_pos(buttonAdd, INTERVAL_V, titleHeight);
  lv_obj_set_pos(buttonDec, BTN_X_PIXEL * 3 + INTERVAL_V * 4, titleHeight);
  lv_obj_set_pos(buttoType, INTERVAL_V, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
  lv_obj_set_pos(buttonStep, BTN_X_PIXEL + INTERVAL_V * 2, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
  lv_obj_set_pos(buttonOff, BTN_X_PIXEL * 2 + INTERVAL_V * 3, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
  lv_obj_set_pos(buttonBack, BTN_X_PIXEL * 3 + INTERVAL_V * 4, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
	#else
	lv_obj_set_pos(buttonAdd, INTERVAL_V, titleHeight);
  lv_obj_set_pos(buttonDec, BTN_X_PIXEL * 3 + INTERVAL_V * 4, titleHeight);
  lv_obj_set_pos(buttonStep, INTERVAL_V, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
  lv_obj_set_pos(buttonOff, BTN_X_PIXEL + INTERVAL_V * 2, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
  lv_obj_set_pos(buttonBack, BTN_X_PIXEL * 3 + INTERVAL_V * 4, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
	#endif

  // Create labels on the image buttons
  lv_btn_set_layout(buttonAdd, LV_LAYOUT_OFF);
  lv_btn_set_layout(buttonDec, LV_LAYOUT_OFF);
	#if ENABLED(HAS_UI_BUTTEN_TYPE)
  lv_btn_set_layout(buttoType, LV_LAYOUT_OFF);
	#endif
  lv_btn_set_layout(buttonStep, LV_LAYOUT_OFF);
  lv_btn_set_layout(buttonOff, LV_LAYOUT_OFF);
  lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);

  lv_obj_t *labelAdd = lv_label_create(buttonAdd, NULL);
  lv_obj_t *labelDec = lv_label_create(buttonDec, NULL);
	#if ENABLED(HAS_UI_BUTTEN_TYPE)
  labelType = lv_label_create(buttoType, NULL);
	#endif
  labelStep = lv_label_create(buttonStep, NULL);
  lv_obj_t *labelOff   = lv_label_create(buttonOff, NULL);
  lv_obj_t *label_Back = lv_label_create(buttonBack, NULL);

  if (gCfgItems.multiple_language != 0) {
    lv_label_set_text(labelAdd, preheat_menu.add);
    lv_obj_align(labelAdd, buttonAdd, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

    lv_label_set_text(labelDec, preheat_menu.dec);
    lv_obj_align(labelDec, buttonDec, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

    lv_label_set_text(labelOff, preheat_menu.off);
    lv_obj_align(labelOff, buttonOff, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);

    lv_label_set_text(label_Back, common_menu.text_back);
    lv_obj_align(label_Back, buttonBack, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
  }

  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) {
      lv_group_add_obj(g, buttonAdd);
      lv_group_add_obj(g, buttonDec);
			#if ENABLED(HAS_UI_BUTTEN_TYPE)
      lv_group_add_obj(g, buttoType);
			#endif
      lv_group_add_obj(g, buttonStep);
      lv_group_add_obj(g, buttonOff);
      lv_group_add_obj(g, buttonBack);
    }
  #endif

	#if ENABLED(HAS_UI_BUTTEN_TYPE)
  disp_temp_type();
	#endif
  disp_step_heat();

  tempText1 = lv_label_create(scr, NULL);
  lv_obj_set_style(tempText1, &tft_style_label_rel);
  disp_desire_temp();
}

#if ENABLED(HAS_UI_BUTTEN_TYPE)
void disp_temp_type() {
  if (uiCfg.curTempType == 0) {
    if (uiCfg.curSprayerChoose == 1) {
    lv_imgbtn_set_src(buttoType, LV_BTN_STATE_REL, "F:/bmp_extru2.bin");
      lv_imgbtn_set_src(buttoType, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
      if (gCfgItems.multiple_language != 0) {
        lv_label_set_text(labelType, preheat_menu.ext2);
        lv_obj_align(labelType, buttoType, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
      }
    }
    else {
    lv_imgbtn_set_src(buttoType, LV_BTN_STATE_REL, "F:/bmp_extru1.bin");
      lv_imgbtn_set_src(buttoType, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
      if (gCfgItems.multiple_language != 0) {
        lv_label_set_text(labelType, preheat_menu.ext1);
        lv_obj_align(labelType, buttoType, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
      }
    }

  }
  else {
  lv_imgbtn_set_src(buttoType, LV_BTN_STATE_REL, "F:/bmp_bed.bin");
      lv_imgbtn_set_src(buttoType, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
    if (gCfgItems.multiple_language != 0) {
      lv_label_set_text(labelType, preheat_menu.hotbed);
      lv_obj_align(labelType, buttoType, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
    }
  }
}
#endif

void disp_desire_temp() {
  char buf[20] = {0};

  public_buf_l[0] = '\0';

  if (uiCfg.curTempType == 0) {
    if (uiCfg.curSprayerChoose < 1)
      strcat(public_buf_l, preheat_menu.ext1);
    else
      strcat(public_buf_l, preheat_menu.ext2);
    sprintf(buf, preheat_menu.value_state, (int)thermalManager.temp_hotend[uiCfg.curSprayerChoose].celsius,  (int)thermalManager.temp_hotend[uiCfg.curSprayerChoose].target);
  }
  #if HAS_HEATED_BED
    else {
      strcat(public_buf_l, preheat_menu.hotbed);
      sprintf(buf, preheat_menu.value_state, (int)thermalManager.temp_bed.celsius,  (int)thermalManager.temp_bed.target);
    }
  #endif
  strcat_P(public_buf_l, PSTR(": "));
  strcat(public_buf_l, buf);
  lv_label_set_text(tempText1, public_buf_l);
  lv_obj_align(tempText1, NULL, LV_ALIGN_CENTER, 0, -50);
}

void disp_step_heat() {
  if (uiCfg.stepHeat == 1) {
    lv_imgbtn_set_src(buttonStep, LV_BTN_STATE_REL, "F:/bmp_step1_degree.bin");
    lv_imgbtn_set_src(buttonStep, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
  }
  else if (uiCfg.stepHeat == 5) {
    lv_imgbtn_set_src(buttonStep, LV_BTN_STATE_REL, "F:/bmp_step5_degree.bin");
    lv_imgbtn_set_src(buttonStep, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
  }
  else if (uiCfg.stepHeat == 10) {
    lv_imgbtn_set_src(buttonStep, LV_BTN_STATE_REL, "F:/bmp_step10_degree.bin");
    lv_imgbtn_set_src(buttonStep, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
  }

  if (gCfgItems.multiple_language != 0) {
    if (uiCfg.stepHeat == 1) {
      lv_label_set_text(labelStep, preheat_menu.step_1c);
      lv_obj_align(labelStep, buttonStep, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
    }
    else if (uiCfg.stepHeat == 5) {
      lv_label_set_text(labelStep, preheat_menu.step_5c);
      lv_obj_align(labelStep, buttonStep, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
    }
    else if (uiCfg.stepHeat == 10) {
      lv_label_set_text(labelStep, preheat_menu.step_10c);
      lv_obj_align(labelStep, buttonStep, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
    }
  }
}

void lv_clear_handHeat() {
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) lv_group_remove_all_objs(g);
  #endif
  lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI
