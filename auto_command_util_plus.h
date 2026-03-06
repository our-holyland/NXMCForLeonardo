#include "switch_controller_plus.h"

#pragma once

void pushButton(Button button, int delay_after_pushing_msec, int loop_num = 1);
void pushButton2(Button button, int pushing_time_msec, int delay_after_pushing_msec, int loop_num = 1);
void pushHatButton(Hat button, int delay_after_pushing_msec, int loop_num = 1);
void pushHatButtonContinuous(Hat button, int pushing_time_msec);
void tiltJoystick(int lx_per, int ly_per, int rx_per, int ry_per, int tilt_time_msec, int delay_after_tilt_msec);
void sendReportOnly(USB_JoystickReport_Input_t t_joystickInputData);

void UseLStick(LS Lstick, int tilt_time_msec, int delay_after_tilt_msec);
void UseRStick(RS Rstick, int tilt_time_msec, int delay_after_tilt_msec);
void TiltLeftStick(int direction_deg, double power, int holdtime, int delaytime);
