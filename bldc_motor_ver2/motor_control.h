#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

// void ResetAlarm(int fd);
// void GetMotorStatus(int fd);
// void SetServoOn(int fd);
// void SetMotorSpeed(int fd, int rpm);
// void ReceiveResponse(int fd);

// 하드 코딩 전용 함수
// void SetDriverOn(int fd);
void ForceCommunicationMode(int fd);
void ResetAlarm(int fd);
void BrakeOff(int fd);
void SetServoOn(int fd);
void ReadAlarmStatus(int fd);
void Set1000RPM(int fd);
void ReceiveResponse(int fd);

#endif
