/*
Copyright (C) 2013-2014 Ladislas de Toldi <ladislas at weareleka dot com> and Leka <http://weareleka.com>

This file is part of Moti, a spherical robotic smart toy for autistic children.

Moti is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Moti is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Moti. If not, see <http://www.gnu.org/licenses/>.
*/

#include <Arduino.h>
#include "Serial.h"

/**
 * @file Serial.cpp
 * @author Ladislas de Toldi & Flavien Raynaud
 * @version 1.0
 */

uint8_t readByte(void) {
    while (!Serial.available());

    return (uint8_t)Serial.read();
}

uint16_t readTwoBytes(void) {
    uint8_t first = readByte();
    uint8_t second = readByte();

    return ((uint16_t)first << 8) + (uint16_t)second;
}

READ_COMMAND readCommand(void) {
    READ_COMMAND cmd;

    cmd.type = COMMAND_NONE;

    while (!Serial.available());

    if (readByte() == 42) {
        uint8_t actionByte = readByte();

        if (actionByte > 0x03)
            return cmd;

        cmd.type = (COMMAND_TYPE)actionByte;

        switch (cmd.type) {
        case COMMAND_GO:
            if (readByte() == 1)
                cmd.cmd.go.direction = FORWARD;
            else
                cmd.cmd.go.direction = BACKWARD;

            cmd.cmd.go.speed = readByte();
            cmd.cmd.go.duration = readTwoBytes();
            break;

        case COMMAND_SPIN:
            cmd.cmd.spin.rotation = (Rotation)readByte();
            cmd.cmd.spin.speed = readByte();
            cmd.cmd.spin.angle = readTwoBytes();
            break;

        case COMMAND_STOP:
            break;

        case COMMAND_FADE:
            cmd.cmd.fade.indicator = (LedIndicator)readByte();
            cmd.cmd.fade.startR = readByte();
            cmd.cmd.fade.startG = readByte();
            cmd.cmd.fade.startB = readByte();
            cmd.cmd.fade.endR = readByte();
            cmd.cmd.fade.endG = readByte();
            cmd.cmd.fade.endB = readByte();
            cmd.cmd.fade.duration = readTwoBytes();
        }
    }
    else
        return readCommand();

    return cmd;
}
