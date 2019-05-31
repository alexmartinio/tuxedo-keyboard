/*
* tuxedo_keyboard.h
*
* Copyright (C) 2018 TUXEDO Computers GmbH <tux@tuxedocomputers.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef _TUXEDO_KEYBOARD_H
#define _TUXEDO_KEYBOARD_H

#define DRIVER_NAME "tuxedo_keyboard"
#define pr_fmt(fmt) DRIVER_NAME ": " fmt

#include <linux/list.h>
#include <linux/platform_device.h>
#include <linux/module.h>

#define __TUXEDO_PR(lvl, fmt, ...) do { pr_##lvl(fmt, ##__VA_ARGS__); } while (0)
#define TUXEDO_INFO(fmt, ...) __TUXEDO_PR(info, fmt, ##__VA_ARGS__)
#define TUXEDO_ERROR(fmt, ...) __TUXEDO_PR(err, fmt, ##__VA_ARGS__)
#define TUXEDO_DEBUG(fmt, ...) __TUXEDO_PR(debug, "[%s:%u] " fmt, __func__, __LINE__, ##__VA_ARGS__)

#define BRIGHTNESS_MIN                  0
#define BRIGHTNESS_MAX                  255
#define BRIGHTNESS_DEFAULT              BRIGHTNESS_MAX

#define KB_MODE_DEFAULT                 0	// CUSTOM Mode

#define CLEVO_EVENT_GUID                "ABBC0F6B-8EA1-11D1-00A0-C90629100000"
#define CLEVO_EMAIL_GUID                "ABBC0F6C-8EA1-11D1-00A0-C90629100000"
#define CLEVO_GET_GUID                  "ABBC0F6D-8EA1-11D1-00A0-C90629100000"

#define REGION_LEFT                     0xF0000000
#define REGION_CENTER                   0xF1000000
#define REGION_RIGHT                    0xF2000000
#define REGION_EXTRA                    0xF3000000

#define KEYBOARD_BRIGHTNESS             0xF4000000

#define COLOR_BLACK                     0x000000
#define COLOR_RED                       0xFF0000
#define COLOR_GREEN                     0x00FF00
#define COLOR_BLUE                      0x0000FF
#define COLOR_YELLOW                    0xFFFF00
#define COLOR_MAGENTA                   0xFF00FF
#define COLOR_CYAN                      0x00FFFF
#define COLOR_WHITE                     0xFFFFFF

#define KB_COLOR_DEFAULT                COLOR_BLUE	// Default Color Blue
#define DEFAULT_MODE                    0

// Method IDs for CLEVO_GET
#define GET_EVENT                       0x01
#define GET_AP                          0x46
#define SET_KB_LED                      0x67

// WMI Codes
#define WMI_CODE_DECREASE_BACKLIGHT     0x81
#define WMI_CODE_INCREASE_BACKLIGHT     0x82
#define WMI_CODE_NEXT_MODE              0x83
#define WMI_CODE_TOGGLE_STATE           0x9F

#define STEP_BRIGHTNESS_STEP            25

// Module Parameter Values
//static bool 



// Param Validators
static int mode_validator(const char *val, const struct kernel_param *kp);
static const struct kernel_param_ops param_ops_mode_ops = {
	.set = mode_validator,
	.get = param_get_int,
};

static int brightness_validator(const char *val, const struct kernel_param *kp);
static const struct kernel_param_ops param_ops_brightness_ops = {
	.set = brightness_validator,
	.get = param_get_int,
};

// Params Variables
static uint param_color_left = KB_COLOR_DEFAULT;
module_param_named(color_left, param_color_left, uint, S_IRUSR);
MODULE_PARM_DESC(color_left, "Color for the Left Section");

static uint param_color_center = KB_COLOR_DEFAULT;
module_param_named(color_center, param_color_center, uint, S_IRUSR);
MODULE_PARM_DESC(color_center, "Color for the Center Section");

static uint param_color_right = KB_COLOR_DEFAULT;
module_param_named(color_right, param_color_right, uint, S_IRUSR);
MODULE_PARM_DESC(color_right, "Color for the Right Right");

static uint param_color_extra = KB_COLOR_DEFAULT;
module_param_named(color_extra, param_color_extra, uint, S_IRUSR);
MODULE_PARM_DESC(color_extra, "Color for the Extra Section");

static ushort param_mode = DEFAULT_MODE;
module_param_cb(mode, &param_ops_mode_ops, &param_mode, S_IRUSR);
MODULE_PARM_DESC(mode, "Set the mode");

static ushort param_brightness = BRIGHTNESS_DEFAULT;
module_param_cb(brightness, &param_ops_brightness_ops, &param_brightness,
		S_IRUSR);
MODULE_PARM_DESC(brightness, "Set the Keyboard Brightness");

static bool param_state = true;
module_param_named(state, param_state, bool, S_IRUSR);
MODULE_PARM_DESC(state,
		 "Set the State of the Keyboard TRUE = ON | FALSE = OFF");

// Sysfs device Attributes
static DEVICE_ATTR(state, 0644, show_state_fs, set_state_fs);
static DEVICE_ATTR(color_left, 0644, show_color_left_fs, set_color_left_fs);
static DEVICE_ATTR(color_center, 0644, show_color_center_fs,
		   set_color_center_fs);
static DEVICE_ATTR(color_right, 0644, show_color_right_fs, set_color_right_fs);
static DEVICE_ATTR(color_extra, 0644, show_color_extra_fs, set_color_extra_fs);
static DEVICE_ATTR(brightness, 0644, show_brightness_fs, set_brightness_fs);
static DEVICE_ATTR(mode, 0644, show_mode_fs, set_mode_fs);
static DEVICE_ATTR(extra, 0444, show_hasextra_fs, NULL);

#endif
