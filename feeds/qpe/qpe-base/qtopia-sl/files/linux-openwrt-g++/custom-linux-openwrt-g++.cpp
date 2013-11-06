/**********************************************************************
** Copyright (C) 2000-2005 Trolltech AS.  All rights reserved.
**
** This file is part of the Qtopia Environment.
** 
** This program is free software; you can redistribute it and/or modify it
** under the terms of the GNU General Public License as published by the
** Free Software Foundation; either version 2 of the License, or (at your
** option) any later version.
** 
** A copy of the GNU GPL license version 2 is included in this package as 
** LICENSE.GPL.
**
** This program is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
** See the GNU General Public License for more details.
**
** In addition, as a special exception Trolltech gives permission to link
** the code of this program with Qtopia applications copyrighted, developed
** and distributed by Trolltech under the terms of the Qtopia Personal Use
** License Agreement. You must comply with the GNU General Public License
** in all respects for all of the code used other than the applications
** licensed under the Qtopia Personal Use License Agreement. If you modify
** this file, you may extend this exception to your version of the file,
** but you are not obligated to do so. If you do not wish to do so, delete
** this exception statement from your version.
** 
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

#include "qtopia/power.h"

int qpe_sysBrightnessSteps()
{
    return 255;
}

#include <stdio.h>
#include <stdlib.h>
#include <qfile.h>

void qpe_setBrightness(int bright)
{
	QFile OneWireInfo("/proc/driver/one-wire-info");
	if (!OneWireInfo.open(IO_ReadOnly)) {
		return;
	}
	char Info[256 + 1];
	memset(Info, 0, sizeof Info);
	if (OneWireInfo.readLine(&Info[0], 256) <= 0) {
		return;
	}
	unsigned int lcd_type, firmwire_ver;
	if (sscanf(Info, "%u%u", &lcd_type, &firmwire_ver) != 2) {
		return;
	}
	if (lcd_type == 0) {
		return;
	}
	//printf("lcd_type, firewire: %u %u\n", lcd_type, firmwire_ver);
	char bright_str[20];
	if (bright < 0) {
		bright = 0;
	} else if (bright > 255) {
		bright = 255;
	}

	int min_v = 1, max_v = 127;
	if (lcd_type == 1) {
		min_v = 20;
	}
	if (bright > 0) {
		bright = (127.0 - min_v) / 254 * (bright - 1) + 0.5 + min_v;
	}

	sprintf(bright_str, "%u", bright);
	QFile BacklightOnewireDevice("/dev/backlight-1wire");
	if (!BacklightOnewireDevice.open(IO_WriteOnly)) {
		return;
	}
	BacklightOnewireDevice.writeBlock(bright_str, strlen(bright_str));
	
	//printf("qpe_setBrightness: %d\n", bright);
}

void PowerStatusManager::getStatus()
{
    int ac, bs, bf, pc, sec;
    if ( getProcApmStatus( ac, bs, bf, pc, sec ) ) {
	ps->percentRemain = pc;
	ps->secsRemain = sec;
	ps->percentAccurate = TRUE;
    } else {
	ps->percentRemain = 100;
	ps->secsRemain = -1;
	ps->percentAccurate = FALSE;
    }
}
