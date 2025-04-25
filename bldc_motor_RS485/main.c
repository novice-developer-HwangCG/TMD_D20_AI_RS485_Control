#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include "rs485.h"
#include "motor_control.h"

int main() {
    int fd = InitRS485();
    if (fd == -1) return -1;

    tcflush(fd, TCIFLUSH);
    ResetAlarm(fd);
    usleep(100000);
    ReceiveResponseWithLabel(fd, "ResetAlarm");

    tcflush(fd, TCIFLUSH);
    SetDriverOn(fd);
    usleep(100000);
    ReceiveResponseWithLabel(fd, "SetDriverOn");

    tcflush(fd, TCIFLUSH);
    SetServoOn(fd);
    usleep(100000);
    ReceiveResponseWithLabel(fd, "SetServoOn");

    tcflush(fd, TCIFLUSH);
    BrakeOff(fd);
    usleep(100000);
    ReceiveResponseWithLabel(fd, "BrakeOff");

    tcflush(fd, TCIFLUSH);
    Set1000RPM(fd);
    usleep(100000);
    ReceiveResponseWithLabel(fd, "Set1000RPM");

    tcflush(fd, TCIFLUSH);
    ReadAlarmStatus(fd);
    usleep(100000);
    ReceiveResponseWithLabel(fd, "ReadAlarmStatus");

    close(fd);
    return 0;
}