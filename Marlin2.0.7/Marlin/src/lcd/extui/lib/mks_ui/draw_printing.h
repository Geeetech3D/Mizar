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
#pragma once

#ifdef __cplusplus
  extern "C" { /* C-declarations for C++ */
#endif

#define IDLE        0
#define WORKING     1
#define PAUSING     2
#define PAUSED      3
#define REPRINTING  4
#define REPRINTED   5
#define RESUMING    6
#define STOP        7

extern void lv_draw_printing(void);
extern void lv_clear_printing();
extern void disp_ext_temp();
extern void disp_bed_temp();
extern void disp_fan_speed();
extern void disp_print_time();
extern void disp_fan_Zpos();
extern void reset_print_time();
extern void start_print_time();
extern void stop_print_time();
extern void setProBarRate();
extern void disp_move_Speed();
extern void disp_extru_Speed();
extern void disp_print_state();

//extern void disp_temp_ready_print();
#ifdef __cplusplus
  } /* C-declarations for C++ */
#endif
