#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

void SetDriverOn(int fd);
void ResetAlarm(int fd);
void BrakeOff(int fd);
void SetServoOn(int fd);
void ReadAlarmStatus(int fd);
void Set1000RPM(int fd);
void ReceiveResponseWithLabel(int fd, const char* commandLabel);

#endif
