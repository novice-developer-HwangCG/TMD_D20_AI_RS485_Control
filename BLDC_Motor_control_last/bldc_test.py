import serial
import struct
import time

def calc_crc(data):
    crc = 0xFFFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            lsb = crc & 0x0001
            crc >>= 1
            if lsb:
                crc ^= 0xA001
    return crc.to_bytes(2, byteorder='little')  # Low byte first

def send_packet(ser, packet):
    ser.write(packet)
    time.sleep(0.05)
    if ser.in_waiting:
        response = ser.read(ser.in_waiting)
        print("[RESPONSE]", response.hex())
        return response
    return b''

if __name__ == "__main__":
    # === Serial Port 설정 ===
    ser = serial.Serial('/dev/ttyUSB0', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=1)

    try:
        print("==== Servo ON ====")
        servo_on_cmd = bytes.fromhex("01 06 00 78 00 01 C8 13")
        send_packet(ser, servo_on_cmd)

        time.sleep(0.5)

        print("==== Set Speed 1000rpm (CW) ====")
        speed_1000_cmd = bytes.fromhex("01 06 00 79 03 E8 58 AD")
        send_packet(ser, speed_1000_cmd)

        time.sleep(1)

        print("==== Read Current Speed ====")
        read_speed_cmd = bytes.fromhex("01 04 00 03 00 01 C1 CA")
        response = send_packet(ser, read_speed_cmd)
        if len(response) >= 5:
            speed_val = struct.unpack('>h', response[3:5])[0]
            print(f"[INFO] Current Speed: {speed_val} rpm")

        # === 사용자 입력 대기 ===
        input("motor on, stop key is Enter")

        print("==== Set Speed to 0rpm ====")
        stop_cmd = bytes.fromhex("01 06 00 79 00 00 58 13")
        send_packet(ser, stop_cmd)

        print("==== Servo OFF ====")
        servo_off_cmd = bytes.fromhex("01 06 00 78 00 00 09 D3")
        send_packet(ser, servo_off_cmd)

    finally:
        ser.close()
