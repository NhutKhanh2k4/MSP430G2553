#include <SPI.h>

volatile byte receivedData = 0; // Biến lưu trữ dữ liệu nhận từ Master
volatile byte dataToSend = 0; // Dữ liệu gửi lại cho Master

void setup() {
  pinMode(MISO, OUTPUT); // Đặt chân MISO là ngõ ra

  // Bắt đầu SPI ở chế độ Slave
  SPCR |= _BV(SPE);

  // Gắn hàm ngắt nhận SPI
  SPI.attachInterrupt();

  Serial.begin(9600); // Khởi động Serial để debug
}

ISR(SPI_STC_vect) {
  receivedData = SPDR; // Đọc dữ liệu từ thanh ghi SPI
  //dataToSend = receivedData + 1; // Gửi lại dữ liệu đã nhận cộng thêm 1
  SPDR = receivedData;   // Gửi dữ liệu trở lại Master
}

void loop() {
  // In dữ liệu nhận được ra Serial để debug
  Serial.print("RX: ");
  Serial.print(receivedData, HEX);
  Serial.print("  |  ");
  Serial.print("TX:  ");
  Serial.println(dataToSend, HEX);
  
  delay(500); // Đợi một khoảng thời gian để tránh spam cổng Serial
}
