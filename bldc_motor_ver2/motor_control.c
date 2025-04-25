#include <stdio.h>
#include <unistd.h>
#include "rs485.h"
#include "motor_control.h"

#define SLAVE_ID 0x01

/*
void ResetAlarm(int fd) {
    unsigned char packet[8] = {0x01, 0x06, 0x00, 0x78, 0x02, 0x01};
    unsigned short crc = CalculateCRC16(packet, 6);
    packet[6] = crc & 0xFF;
    packet[7] = (crc >> 8) & 0xFF;

    SendRS485(fd, packet, 8);
}

void GetMotorStatus(int fd) {
    unsigned char packet[8] = {0x01, 0x03, 0x00, 0x78, 0x00, 0x01};
    unsigned short crc = CalculateCRC16(packet, 6);
    packet[6] = crc & 0xFF;
    packet[7] = (crc >> 8) & 0xFF;

    SendRS485(fd, packet, 8);
    sleep(1);
    ReceiveResponse(fd);
}

void SetServoOn(int fd) {
    unsigned char packet[8] = {0x01, 0x06, 0x00, 0x78, 0x00, 0x01};
    unsigned short crc = CalculateCRC16(packet, 6);
    packet[6] = crc & 0xFF;
    packet[7] = (crc >> 8) & 0xFF;

    SendRS485(fd, packet, 8);
}

// 속도 설정 함수 (MODBUS RTU 프로토콜)
void SetMotorSpeed(int fd, int rpm) {
    unsigned char packet[8];
    unsigned short crc;

    packet[0] = SLAVE_ID;       // Slave Address
    packet[1] = 0x06;           // Function Code (Write Single Register)
    packet[2] = 0x00;           // Register Address High Byte (속도 설정)
    packet[3] = 0x79;           // Register Address Low Byte
    packet[4] = (rpm >> 8) & 0xFF; // Data High Byte 
    packet[5] = rpm & 0xFF;        // Data Low Byte

    crc = CalculateCRC16(packet, 6);
    packet[6] = crc & 0xFF;     // CRC Low Byte
    packet[7] = (crc >> 8) & 0xFF; // CRC High Byte

    SendRS485(fd, packet, 8);
}
*/

// 하드 코딩 전용 함수 
void SetDriverOn(int fd) {
    unsigned char packet[8] = {0x01, 0x06, 0x00, 0x78, 0x00, 0x01, 0xC8, 0x13};
    SendRS485(fd, packet, 8);
    printf("Driver ON\n");
}

void ForceCommunicationMode(int fd) {
    unsigned char packet[8] = {0x01, 0x06, 0x00, 0x17, 0x00, 0x01, 0xF8, 0x02};
    SendRS485(fd, packet, 8);
    printf("Forced Communication Mode Set\n");
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
void ReceiveResponse(int fd) {
    unsigned char buffer[10];
    int bytes_read = ReceiveRS485(fd, buffer, sizeof(buffer));

    if (bytes_read > 0) {
        printf("Received Data: ");
        for (int i = 0; i < bytes_read; i++) {
            printf("%02X ", buffer[i]);
        }
        printf("\n");
    } else {
        printf("No response received.\n");
    }
}