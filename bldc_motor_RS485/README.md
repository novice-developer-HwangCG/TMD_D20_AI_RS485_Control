- Serial 연결 상태
모터 드라이버 A+ ↔ RS485 컨버터 TX+ (D+)
모터 드라이버 B- ↔ RS485 컨버터 TX- (D-)

RS485 컨버터 TX- (D-) ↔ RS485 컨버터 RX-
RS485 컨버터 TX+ (D+) ↔ RS485 컨버터 RX+

- comfile (build)
gcc -o bldc_control_ver3 main.c rs485_set.c motor_control.c -Wall

- run
./bldc_control_ver2
./bldc_control_ver3
