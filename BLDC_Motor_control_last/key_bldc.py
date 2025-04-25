import serial
import struct
import time
import sys
import termios
import tty

def calc_crc(data):
    crc = 0xFFFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            lsb = crc & 0x0001
            crc >>= 1
            if lsb:
                crc ^= 0xA001
    return crc.to_bytes(2, byteorder='little')

def send_packet(ser, packet):
    ser.write(packet)
    time.sleep(0.05)
    if ser.in_waiting:
        response = ser.read(ser.in_waiting)
        print("[RESPONSE]", response.hex())
        return response
    return b''

def get_key():
    fd = sys.stdin.fileno()
    old = termios.tcgetattr(fd)
    try:
        tty.setraw(sys.stdin.fileno())
        key = sys.stdin.read(1)
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old)
    return key

def make_speed_packet(rpm):
    # rpm: int, 음수면 CCW
    rpm = rpm & 0xFFFF  # convert to unsigned
    packet = struct.pack('>B B H H', 0x01, 0x06, 0x0079, rpm)
    return packet + calc_crc(packet)

def read_current_speed(ser):
    print("==== Read Current Speed ====")
    read_speed_cmd = bytes.fromhex("01 04 00 03 00 01 C1 CA")
    response = send_packet(ser, read_speed_cmd)
    if len(response) >= 5:
        speed_val = struct.unpack('>h', response[3:5])[0]
        print(f"[INFO] Current Speed: {speed_val} rpm")
    else:
        print("[WARN] No valid speed response received.")

if __name__ == "__main__":
    ser = serial.Serial('/dev/ttyUSB0', baudrate=115200, bytesize=8, parity='N', stopbits=1, timeout=1)

    try:
        print("==== Servo ON ====")
        send_packet(ser, bytes.fromhex("01 06 00 78 00 01 C8 13"))

        print("control ('w'=forward, 's'=정지, 'x'=forward, 'a'=turn left, 'd'=turtn right, 'q'=quit)")

        while True:
            key = get_key()
            if key == 'w':
                print("forward (1000rpm)")
                packet = make_speed_packet(1000)
            elif key == 'x':
                print("backward (-1000rpm)")
                packet = make_speed_packet(-1000)
            elif key == 's':
                print("stop")
                packet = make_speed_packet(0)
            elif key == 'a':
                print("turn left (감속 500rpm)")
                packet = make_speed_packet(500)
            elif key == 'd':
                print("turtn right (역회전 -500rpm)")
                packet = make_speed_packet(-500)
            elif key == 'q':
                print("quit")
                break
            else:
                continue
            send_packet(ser, packet)
            read_current_speed(ser)

        print("==== Servo OFF ====")
        send_packet(ser, bytes.fromhex("01 06 00 78 00 00 09 D3"))

    finally:
        ser.close()
