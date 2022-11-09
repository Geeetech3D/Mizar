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

#include "../gcode.h"
#include "../../MarlinCore.h"

#if ENABLED(BLTOUCH)
  #include "../../feature/bltouch.h"
#endif

#if ENABLED(PLATFORM_M997_SUPPORT)

/**
 * M997: Perform in-application firmware update
 */
void GcodeSuite::M997() {
	#if ENABLED(BLTOUCH_MENU_OPTION)
	if(bltouch.switch_flag)
	{
		bltouch.switch_flag = 0;
		#if ENABLED(USER_CMD_5_ENABLE)
		kill(USER_DESC_5);
		#endif
	}
	#endif

  flashFirmware(parser.intval('S'));
}

#endif