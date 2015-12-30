/**
 * This file is part of Weather Sensor Reading Library.
 *
 * Copyright (C) 2014 Ulrich Eckhardt
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * This is a test program, showing the usage of the library
 */
 
 // usare: gcc -o main_wsread main_wsread.c bmp085.c -lbcm2835 -lrt 
 
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "bmp085.h"

int main(int argc, char *argv[])
{
    float temp = 0.0;
    float pressure = 0.0;
    float sealvl;

    if (!bcm2835_init()) {
        fprintf(stderr, "bcm2835_init failed\n");
        return false;
    }
    /*
     * readBmp085 returns TRUE if data is successfully read
     */
    if (readBmp085(BMP085_HIGH_RESOLUTION, &temp, &pressure)) {
        /*
         * The pressure sensor is located approximately 150 meters over
         * sea level
         */
        sealvl = convertToSeaLevel(pressure, 150.0);

        printf("BMP085 Temp=%1.1f° Pressure %1.2fhPa Sea level %1.2fhPa\n",
                temp, pressure, sealvl);
    } else {
        printf("Can not access the BMP085\n");
    }

    bcm2835_close();
    return (0);
}
