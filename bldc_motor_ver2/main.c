#include <stdio.h>
#include <unistd.h>
#include "rs485.h"
#include "motor_control.h"

int main() {
    int fd = InitRS485();
    if (fd == -1) return -1;
    
    /*
    int rpm = 50;  // RPM 설정

    ResetAlarm(fd);

    GetMotorStatus(fd);

    SetServoOn(fd);

    printf("Setting Motor Speed to %d RPM\n", rpm);
    SetMotorSpeed(fd, rpm);
    sleep(1);
    ReceiveResponse(fd);
    */
    
    ResetAlarm(fd);
    sleep(1);

    ReceiveResponse(fd);

    // SetDriverOn(fd);
    ForceCommunicationMode(fd);
    sleep(1);

    ReceiveResponse(fd);

    BrakeOff(fd);
    sleep(1);

    ReceiveResponse(fd);

    SetServoOn(fd);
    sleep(1);

    ReceiveResponse(fd);

    ReadAlarmStatus(fd);   // 알람 상태 읽기 (필요시)
    sleep(1);

    ReceiveResponse(fd);

    Set1000RPM(fd);
    sleep(1);

    // 응답 확인
    ReceiveResponse(fd);

    close(fd);
    return 0;
}