- 구조
모터 드라이버 D-SUB(9P)-Female - D-SUB(9P)-Male - USB to RS485 컨버터 - 노트북(ubuntu 18.04)

- Serial 연결 상태
모터 드라이버 8. RS-485 A+ ↔ USB to RS485 컨버터 TX+ (D+)
모터 드라이버 9. RS-485 B- ↔ USB to RS485 컨버터 TX- (D-)

USB to RS485 컨버터 TX- (D-) ↔ USB to RS485 컨버터 RX-
USB to RS485 컨버터 TX+ (D+) ↔ USB to RS485 컨버터 RX+

- comfile (build)
gcc -o bldc_control main.c rs485_set.c motor_control.c -Wall

- run
./bldc_control
