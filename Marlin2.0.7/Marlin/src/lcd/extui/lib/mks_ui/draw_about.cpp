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
//#include "../lvgl/src/lv_objx/lv_imgbtn.h"
//#include "../lvgl/src/lv_objx/lv_img.h"
//#include "../lvgl/src/lv_core/lv_disp.h"
//#include "../lvgl/src/lv_core/lv_refr.h"

#include "../../../../MarlinCore.h"
#include "../../../../module/temperature.h"

extern lv_group_t * g;
static lv_obj_t * scr;
static lv_obj_t *baud_rate, *hw_version, *machine_size;
static lv_obj_t *fw_version, *board, *marlin_version; 

#define ID_A_RETURN   1

static void event_handler(lv_obj_t * obj, lv_event_t event) {
  switch (obj->mks_obj_id) {
    case ID_A_RETURN:
      if (event == LV_EVENT_CLICKED) {
        // do nothing
      }
      else if (event == LV_EVENT_RELEASED) {
        clear_cur_ui();
        draw_return_ui();
      }
      break;
  }
}

void lv_draw_about(void) {
  lv_obj_t *buttonBack, *label_Back;
  if (disp_state_stack._disp_state[disp_state_stack._disp_index] != ABOUT_UI) {
    disp_state_stack._disp_index++;
    disp_state_stack._disp_state[disp_state_stack._disp_index] = ABOUT_UI;
  }
  disp_state = ABOUT_UI;

  scr = lv_obj_create(NULL, NULL);

  lv_obj_set_style(scr, &tft_style_scr);
  lv_scr_load(scr);
  lv_obj_clean(scr);

  lv_obj_t * title = lv_label_create(scr, NULL);
  lv_obj_set_style(title, &tft_style_label_rel);
  lv_obj_set_pos(title, TITLE_XPOS, TITLE_YPOS);
  lv_label_set_text(title, creat_title_text());

  lv_refr_now(lv_refr_get_disp_refreshing());

  // Create an Image button
  buttonBack = lv_imgbtn_create(scr, NULL);

  #if 1
    lv_obj_set_event_cb_mks(buttonBack, event_handler, ID_A_RETURN, NULL, 0);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, "F:/bmp_return.bin");
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, "F:/bmp_clear.bin");
    lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_label_pre);
    lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_label_rel);
    #if HAS_ROTARY_ENCODER
      if (gCfgItems.encoder_enable) lv_group_add_obj(g, buttonBack);
    #endif
  #endif

  lv_obj_set_pos(buttonBack, BTN_X_PIXEL * 3 + INTERVAL_V * 4, BTN_Y_PIXEL + INTERVAL_H + titleHeight);
  lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);

  // Create a label on the image button
  label_Back = lv_label_create(buttonBack, NULL);

  if (gCfgItems.multiple_language != 0) {
    lv_label_set_text(label_Back, common_menu.text_back);
    lv_obj_align(label_Back, buttonBack, LV_ALIGN_IN_BOTTOM_MID, 0, BUTTON_TEXT_Y_OFFSET);
  }

	machine_size = lv_label_create(scr, NULL);
  lv_obj_set_style(machine_size, &tft_style_label_rel);
  lv_label_set_text(machine_size, "Machine Size:220x220x260mm");
  lv_obj_align(machine_size, NULL, LV_ALIGN_IN_LEFT_MID, ABOUT_ALIGN_XPOS, 70);

  baud_rate = lv_label_create(scr, NULL);
  lv_obj_set_style(baud_rate, &tft_style_label_rel);
  lv_label_set_text(baud_rate, "Baud Rate:250000");
  lv_obj_align(baud_rate, NULL, LV_ALIGN_IN_LEFT_MID, ABOUT_ALIGN_XPOS, 40);

  hw_version = lv_label_create(scr, NULL);
  lv_obj_set_style(hw_version, &tft_style_label_rel);
  lv_label_set_text(hw_version, "Hardware:" USER_HARDWARE_VERSION);
  lv_obj_align(hw_version, NULL, LV_ALIGN_IN_LEFT_MID, ABOUT_ALIGN_XPOS, 10);

  fw_version = lv_label_create(scr, NULL);
  lv_obj_set_style(fw_version, &tft_style_label_rel);
  lv_label_set_text(fw_version, "Firmware:" USER_FIRMWARE_VERSION);
  lv_obj_align(fw_version, NULL, LV_ALIGN_IN_LEFT_MID, ABOUT_ALIGN_XPOS, -20);

  board = lv_label_create(scr, NULL);
  lv_obj_set_style(board, &tft_style_label_rel);
  lv_label_set_text(board, "Board:" BOARD_INFO_NAME);
  lv_obj_align(board, NULL, LV_ALIGN_IN_LEFT_MID, ABOUT_ALIGN_XPOS, -50);

	marlin_version = lv_label_create(scr, NULL);
  lv_obj_set_style(marlin_version, &tft_style_label_rel);
  lv_label_set_text(marlin_version, "Marlin:" SHORT_BUILD_VERSION);
  lv_obj_align(marlin_version, NULL, LV_ALIGN_IN_LEFT_MID, ABOUT_ALIGN_XPOS, -80);
}

void lv_clear_about() {
  #if HAS_ROTARY_ENCODER
    if (gCfgItems.encoder_enable) lv_group_remove_all_objs(g);
  #endif
  lv_obj_del(scr);
}

#endif // HAS_TFT_LVGL_UI
