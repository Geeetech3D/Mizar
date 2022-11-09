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

//****************俄语***************************//
#define TOOL_TEXT_RU                    "инструмент"
#define PREHEAT_TEXT_RU                 " нагрев"
#define MOVE_TEXT_RU                    "движение"
#define HOME_TEXT_RU                    "домой"
#define PRINT_TEXT_RU                   " печать"
#define EXTRUDE_TEXT_RU                 "экструзия"
#define LEVELING_TEXT_RU                "уровень"
#define AUTO_LEVELING_TEXT_RU           "aвто"
#define SET_TEXT_RU                     "настройки"
#define MORE_TEXT_RU                    "3DTouch"//"больше"

#define ADD_TEXT_RU                     "добавить"
#define DEC_TEXT_RU                     "уменьшить"
#define EXTRUDER_1_TEXT_RU              "экструдер"
#define EXTRUDER_2_TEXT_RU              "экструдер2"
#define HEATBED_TEXT_RU                 "стол"
#define TEXT_1C_RU                      "1℃"
#define TEXT_5C_RU                      "5℃"
#define TEXT_10C_RU                     "10℃"
#define CLOSE_TEXT_RU                   "выкл"

#define TITLE_HANDEHEAT_RU							"вручн"
#define CUS_PREHEAT_RU									"вручн"
#define BAS_PREHEAT_RU									"ABS"
#define PLA_PREHEAT_RU									"PLA"

#define BACK_TEXT_RU                    "назад"

#define TOOL_PREHEAT_RU                 "нагрев"
#define TOOL_EXTRUDE_RU                 "экструзия"
#define TOOL_MOVE_RU                    "движение"
#define TOOL_HOME_RU                    "домой"
#define TOOL_LEVELING_RU                "уровень"
#define TOOL_AUTO_LEVELING_RU           "aвто"
#define TOOL_FILAMENT_RU                "замена"
#define TOOL_MORE_RU                    "3DTouch"//"больше"

#define AXIS_X_ADD_TEXT_RU              "X+"
#define AXIS_X_DEC_TEXT_RU              "X-"
#define AXIS_Y_ADD_TEXT_RU              "Y+"
#define AXIS_Y_DEC_TEXT_RU              "Y-"
#define AXIS_Z_ADD_TEXT_RU              "Z+"
#define AXIS_Z_DEC_TEXT_RU              "Z-"
#define TEXT_01MM_RU                    "0.1mm"
#define TEXT_1MM_RU                     "1mm"
#define TEXT_10MM_RU                    "10mm"

#define HOME_X_TEXT_RU                  "X"
#define HOME_Y_TEXT_RU                  "Y"
#define HOME_Z_TEXT_RU                  "Z"
#define HOME_ALL_TEXT_RU                "Home"
#define HOME_STOPMOVE_RU                "Quickstop"

#define PAGE_UP_TEXT_RU                 "вверх"
#define PAGE_DOWN_TEXT_RU               "вниз"

#define EXTRUDER_IN_TEXT_RU             "втянуть"
#define EXTRUDER_OUT_TEXT_RU            "выдавить"
#define EXTRUDE_1MM_TEXT_RU             "1mm"
#define EXTRUDE_5MM_TEXT_RU             "5mm"
#define EXTRUDE_10MM_TEXT_RU            "10mm"
#define EXTRUDE_LOW_SPEED_TEXT_RU       "мин"
#define EXTRUDE_MEDIUM_SPEED_TEXT_RU    "сред"
#define EXTRUDE_HIGH_SPEED_TEXT_RU      "выс"

#define LEVELING_POINT1_TEXT_RU         "1точка"
#define LEVELING_POINT2_TEXT_RU         "2точка"
#define LEVELING_POINT3_TEXT_RU         "3точка"
#define LEVELING_POINT4_TEXT_RU         "4точка"
#define LEVELING_POINT5_TEXT_RU         "5точка"

#define FILESYS_TEXT_RU                 "система"
#define WIFI_TEXT_RU                    "WiFi"
#define FAN_TEXT_RU                     "вентилятор"
#define ABOUT_TEXT_RU                   "инфо"
#define BREAK_POINT_TEXT_RU             "продолжить"
#define FILAMENT_TEXT_RU                "замена"
#define LANGUAGE_TEXT_RU                "язык"
#define MOTOR_OFF_TEXT_RU               "отклмотор"
#define MOTOR_OFF_XY_TEXT_RU            "Off-XY"
#define SHUTDOWN_TEXT_RU                "выключение"
#define MACHINE_PARA_RU                 "конфиг"
#define EEPROM_SETTINGS_RU              "Eeprom Set"
#define BUZZER_RU												"пищик"

#define U_DISK_TEXT_RU                  "U диск"
#define SD_CARD_TEXT_RU                 "SD диск"
#define WIFI_NAME_TEXT_RU               "WiFi: "
#define WIFI_KEY_TEXT_RU                "пароль: "
#define WIFI_IP_TEXT_RU                 "IP: "
#define WIFI_AP_TEXT_RU                 "режим: AP"
#define WIFI_STA_TEXT_RU                "режим: STA"
#define WIFI_CONNECTED_TEXT_RU          "подключен"
#define WIFI_DISCONNECTED_TEXT_RU       "не подключен"
#define WIFI_EXCEPTION_TEXT_RU          "исключение"
#define WIFI_RECONNECT_TEXT_RU          "Reconnect"
#define CLOUD_TEXT_RU                   "облако"
#define CLOUD_BIND_RU                   "соединён"
#define CLOUD_UNBIND_RU                 "не соединён"
#define CLOUD_UNBINDING_RU              "Unbinding"
#define CLOUD_DISCONNECTED_RU           "Disconnected"
#define CLOUD_UNBINDED_RU               "Unbinded"
#define CLOUD_BINDED_RU                 "Binded"
#define CLOUD_DISABLE_RU                "Disable"

#define FAN_ADD_TEXT_RU                 "добавить"
#define FAN_DEC_TEXT_RU                 "уменьшить"
#define FAN_OPEN_TEXT_RU                "100%"
#define FAN_HALF_TEXT_RU                "50%"
#define FAN_CLOSE_TEXT_RU               "откл"
#define FAN_TIPS1_TEXT_RU               "вентилятор"
#define FAN_TIPS2_TEXT_RU               "вентилятор\nоткл"

#define FILAMENT_IN_TEXT_RU             "втянуть"
#define FILAMENT_OUT_TEXT_RU            "выдавить"
#define FILAMENT_EXT0_TEXT_RU           "экструдер1"
#define FILAMENT_EXT1_TEXT_RU           "экструдер2"
#define FILAMENT_HEAT_TEXT_RU           "нагрев"
#define FILAMENT_STOP_TEXT_RU           "стоп"
//#define FILAMENT_CHANGE_TEXT_RU           "замена"
#define FILAMENT_TIPS2_TEXT_RU          "T:"
#define FILAMENT_TIPS3_TEXT_RU          "втянуть..."
#define FILAMENT_TIPS4_TEXT_RU          "вядавить..."
#define FILAMENT_TIPS5_TEXT_RU          "Низкая температура, \nнеобходим нагрев"
#define FILAMENT_TIPS6_TEXT_RU          "завершено"

#if 0
  #define FILAMENT_REPLAYS_IDLE_TEXT_RU                 "Please click <втянуть> or <выдавить> \nto replace filament!"
  #define FILAMENT_CHANGE_TEXT_RU                       "Please click <втянуть> or <выдавить>,\nAfter pinter pause."
  #define FILAMENT_DIALOG_LOAD_HEAT_TIPS_RU             "Heating up the nozzle,please wait..."
  #define FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_RU           "Heating up the nozzle,please wait..."
  #define FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_RU         "Heat completed,please load filament to extruder,and click <да> for start loading."
  #define FILAMENT_DIALOG_LOAD_CONFIRM2_TIPS_RU         "Please load filament to extruder,and click <да> for start loading."
  #define FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_RU        "Heat completed,please click <да> for start unloading.!"
  #define FILAMENT_DIALOG_LOADING_TIPS_RU               "Is loading ,please wait!"
  #define FILAMENT_DIALOG_UNLOADING_TIPS_RU             "Is unloading,please wait!"
  #define FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_RU         "Load filament completed,click <да> for return!"
  #define FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_RU       "Unload filament completed,click <да> for return!"
#endif
#define FILAMENT_CHANGE_TEXT_RU                       "Please click <Load> \nor <unload>,After \npinter pause."
#define FILAMENT_DIALOG_LOAD_HEAT_TIPS_RU             "Heating up the nozzle,\nplease wait..."
#define FILAMENT_DIALOG_UNLOAD_HEAT_TIPS_RU           "Heating up the nozzle,\nplease wait..."
#define FILAMENT_DIALOG_LOAD_CONFIRM1_TIPS_RU         "Heat completed,please load filament \nto extruder,and click <confirm> \nfor start loading."
#define FILAMENT_DIALOG_LOAD_CONFIRM2_TIPS_RU         "Please load filament to extruder,\nand click <confirm> for start loading."
#define FILAMENT_DIALOG_UNLOAD_CONFIRM_TIPS_RU        "Heat completed,please \nclick <confirm> for start unloading.!"
#define FILAMENT_DIALOG_LOADING_TIPS_RU               "Is loading ,please wait!"
#define FILAMENT_DIALOG_UNLOADING_TIPS_RU             "Is unloading,please wait!"
#define FILAMENT_DIALOG_LOAD_COMPLETE_TIPS_RU         "Load filament completed,\nclick <confirm> for return!"
#define FILAMENT_DIALOG_UNLOAD_COMPLETE_TIPS_RU       "Unload filament completed,\nclick <confirm> for return!"


#define PRE_HEAT_EXT_TEXT_RU                "E"
#define PRE_HEAT_BED_TEXT_RU                "стол"

#define FILE_LOADING_RU                     "загрузка......"
#if 0
  #define NO_FILE_AND_CHECK_RU                "Файлы не найдены! Вставьте SD-карту или диск U!"
#endif
#define NO_FILE_AND_CHECK_RU                "нет файла,попробуйте ещё раз!"

#define NO_FILE_RU                          "нет файла!"

#define EXTRUDER_TEMP_TEXT_RU               "температура"
#define EXTRUDER_E_LENGTH1_TEXT_RU          "экструзия1"
#define EXTRUDER_E_LENGTH2_TEXT_RU          "экструзия2"
#define EXTRUDER_E_LENGTH3_TEXT_RU          "экструзия3"
#define EXTERDE_TEMP_WARN_TEXT_RU						"Сопло не нагрето \n       Нагрев... "

#define ABOUT_TYPE_TEXT_RU                  "Type: "
#define ABOUT_VERSION_TEXT_RU               "Firmware: "
#define ABOUT_WIFI_TEXT_RU                  "WiFi: "

#define PRINTING_OPERATION_RU               "управление"
#define PRINTING_PAUSE_RU                   "пауза"
#define PRINTING_TEMP_RU                    "темп"
#define PRINTING_CHANGESPEED_RU             "скорости"
#define PRINTING_RESUME_RU                  "возобновить"
#define PRINTING_STOP_RU                    "стоп"
#define PRINTING_MORE_RU                    "больше"
#define PRINTING_EXTRUDER_RU                "экстр"
#define PRINTING_MOVE_RU                    "движение"
#define PRINTING_WAIT_RU										"Wait"

#define EXTRUDER_SPEED_RU                   "экстр"
#define MOVE_SPEED_RU                       "движ"
#define EXTRUDER_SPEED_STATE_RU             "скорость экстр"
#define MOVE_SPEED_STATE_RU                 "скорость движ"
#define STEP_1PERCENT_RU                    "1%"
#define STEP_5PERCENT_RU                    "5%"
#define STEP_10PERCENT_RU                   "10%"

#define TITLE_READYPRINT_RU                 "готов к"
#define TITLE_PREHEAT_RU                    "движение"
#define TITLE_MOVE_RU                       "движение"
#define TITLE_HOME_RU                       "Home"
#define TITLE_EXTRUDE_RU                    "экструзия"
#define TITLE_LEVELING_RU                   "уровень"
#define TITLE_SET_RU                        "настройки"
#define TITLE_MORE_RU                       "3DTouch"//"больше"
#define TITLE_CHOOSEFILE_RU                 "файла"
#define TITLE_PRINTING_RU                   "печать"
#define TITLE_OPERATION_RU                  "управление"
#define TITLE_ADJUST_RU                     "регулировать"
#define TITLE_WIRELESS_RU                   "Wireless"
#define TITLE_FILAMENT_RU                   "замена"
#define TITLE_ABOUT_RU                      "инфо"
#define TITLE_FAN_RU                        "вентилятор"
#define TITLE_LANGUAGE_RU                   "язык"
#define TITLE_PAUSE_RU                      "пауза"
#define TITLE_CHANGESPEED_RU                "скорости"
#define TILE_TOOL_RU                        "инструмент"
#define TITLE_CLOUD_TEXT_RU                 "Cloud"
#define TITLE_DIALOG_CONFIRM_RU             "Confirm"
#define TITLE_FILESYS_RU                    "FileSys"

#define AUTO_SHUTDOWN_RU                    "авто-откл"
#define MANUAL_SHUTDOWN_RU                  "ручн-откл"

#define DIALOG_CONFIRM_RU                   "да"//"подтвердить"
#define DIALOG_CANCLE_RU                    "отмена"
#define DIALOG_OK_RU                        "да"
#define DIALOG_RESET_RU                     "сброс"
#define DIALOG_RETRY_RU                     "повтор"
#define DIALOG_DISABLE_RU                   "запретить"
#define DIALOG_PRINT_MODEL_RU               "печать модели?"
#define DIALOG_CANCEL_PRINT_RU              "стоп?"
#define DIALOG_STOP_RU                      "стоп"
#define DIALOG_REPRINT_FROM_BREAKPOINT_RU   "продолжить?"
//#define DIALOG_UNBIND_PRINTER_RU          "разрыв?"
#define DIALOG_ERROR_TIPS1_RU               "ошибка:нет файла, попробуйте ещё раз."
#define DIALOG_ERROR_TIPS2_RU               "ошибка:сбой передачи. установите скорость \nпередачи данных как на плате управления!"
#define DIALOG_ERROR_TIPS3_RU               "ошибка: имя файла слишком длинное!"
#define DIALOG_CLOSE_MACHINE_RU             "Closing machine......"
#define DIALOG_UNBIND_PRINTER_RU            "Unbind the printer?"
#define DIALOG_FILAMENT_NO_PRESS_RU         "Filament detection switch is not pressed"
#define DIALOG_PRINT_FINISH_RU              "Печать завершена!"
#define DIALOG_PRINT_TIME_RU                "Время печати: "
#define DIALOG_REPRINT_RU                   "Print again"
#define DIALOG_WIFI_ENABLE_TIPS_RU          "The wifi module is being configured,\nplease wait a moment....."

#define MESSAGE_PAUSING_RU            "Стоянка..."
#define MESSAGE_CHANGING_RU           "Подождите, пока начнется смена филамента"
#define MESSAGE_UNLOAD_RU             "Дождитесь выгрузки нити"
#define MESSAGE_WAITING_RU            "Нажмите кнопку,чтобы возобновить печать"
#define MESSAGE_INSERT_RU             "Вставьте нить и нажмите кнопку,чтобы продолжить"
#define MESSAGE_LOAD_RU               "Дождитесь загрузки нити"
#define MESSAGE_PURGE_RU              "Дождитесь чистки нити"
#define MESSAGE_RESUME_RU             "Подождите,пока печать возобновится ..."
#define MESSAGE_HEAT_RU               "Нажмите кнопку, чтобы нагреть форсунку"
#define MESSAGE_HEATING_RU            "Подогрев форсунки Пожалуйста, подождите ..."
#define MESSAGE_OPTION_RU             "Очистить больше или продолжить печать?"
#define MESSAGE_PURGE_MORE_RU         "чистка"
#define MESSAGE_CONTINUE_PRINT_RU     "Распечатать"
#define EEPROM_SETTINGS_TITLE_RU      "Настройки EEPROM"
#define EEPROM_SETTINGS_STORE_RU      "Сохранение настроек в EEPROM"
#define EEPROM_SETTINGS_READ_RU       "Чтение настроек из EEPROM"
#define EEPROM_SETTINGS_REVERT_RU     "Восстановить заводские настройки по умолчанию"

#define EEPROM_STORE_TIPS_RU          "Сохранить настройки в EEPROM?"
#define EEPROM_READ_TIPS_RU           "Читать настройки из EEPROM?"
#define EEPROM_REVERT_TIPS_RU         "Revert settings to factory defaults?"

#define MORE_CUSTOM1_TEXT_RU  "Сброс"
#define MORE_CUSTOM2_TEXT_RU  "Самопроверка"
#define MORE_CUSTOM3_TEXT_RU  "Развернуть"
#define MORE_CUSTOM4_TEXT_RU  "Отозвать"
#define MORE_CUSTOM5_TEXT_RU  "Выкл"
#define MORE_CUSTOM6_TEXT_RU  "Вкл"
#define MORE_CUSTOM7_TEXT_RU  USER_DESC_7

