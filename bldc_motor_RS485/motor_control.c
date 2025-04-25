#include <stdio.h>
#include <unistd.h>
#include "rs485.h"
#include "motor_control.h"

#define SLAVE_ID 0x01

void SetDriverOn(int fd) {
    unsigned char packet[8] = {0x01, 0x06, 0x00, 0x78, 0x00, 0x01, 0xC8, 0x13};
    SendRS485(fd, packet, 8);
    printf("Driver ON\n");
}

// 알람 리셋
void ResetAlarm(int fd) {
    unsigned char packet[8] = {0x01, 0x06, 0x00, 0x78, 0x02, 0x01, 0xC9, 0x73};
    SendRS485(fd, packet, 8);
    printf("Reset Alarm\n");
}

void BrakeOff(int fd) {
    unsigned char packet[8] = {0x01, 0x06, 0x00, 0x78, 0x01, 0x00, 0x08, 0x43};
    SendRS485(fd, packet, 8);
    printf("Brake OFF\n");
}

// 서보 ON
void SetServoOn(int fd) {
    unsigned char packet[8] = {0x01, 0x06, 0x00, 0x78, 0x00, 0x01, 0xC8, 0x13};
    SendRS485(fd, packet, 8);
    printf("Set Servo ON\n");
}

// 알람 상태 읽기
void ReadAlarmStatus(int fd) {
    unsigned char packet[8] = {0x01, 0x04, 0x00, 0x01, 0x00, 0x01, 0x60, 0x0A};
    SendRS485(fd, packet, 8);
    printf("Request Alarm Status\n");
}

// 1000RPM 세팅
void Set1000RPM(int fd) {
    unsigned char packet[8] = {0x01, 0x06, 0x00, 0x79, 0x03, 0xE8, 0x58, 0xAD};
    SendRS485(fd, packet, 8);
    printf("Set 1000 RPM\n");
}

// 응답 수신 함수
void ReceiveResponseWithLabel(int fd, const char* commandLabel) {
    unsigned char buf[256];
    int len = read(fd, buf, sizeof(buf));

    printf("Response for %s:\n", commandLabel);

    if (len <= 0) {
        printf("    No response received.\n\n");
        return;
    }

    printf("    Received Data (%d bytes): ", len);
    for (int i = 0; i < len; i++) {
        printf("%02X ", buf[i]);
    }
    printf("\n");

    // 패턴 해석
    if (buf[0] == 0x01 && buf[1] == 0x06) {
        if (buf[2] == 0x00 && buf[3] == 0x78)
            printf("  ↪ Echo: SetServoOn / ResetAlarm / Brake / DriverOn\n");
        else if (buf[2] == 0x00 && buf[3] == 0x79)
            printf("  ↪ Echo: SetSpeed\n");
        else if (buf[2] == 0x00 && buf[3] == 0x17)
            printf("  ↪ Echo: SetCommunicationMode\n");
    } else if (buf[1] == 0x04) {
        printf("  ↪ Read register response (likely Alarm or Speed)\n");
    } else {
        printf("    Unknown or delayed response\n");
    }

    printf("\n");
}
