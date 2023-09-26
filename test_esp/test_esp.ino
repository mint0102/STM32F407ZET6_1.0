/*
  ESP8266 CheckFlashConfig by Markus Sattler

  This sketch tests if the EEPROM settings of the IDE match to the Hardware

*/

void setup(void) {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {
  // Kiểm tra nếu có dữ liệu được gửi đến từ Serial
  if (Serial.available() > 0) {
    // Đọc dữ liệu từ Serial và lưu vào biến inputString
    uint8_t input = Serial.read();

    // Nếu chuỗi nhận được là "A," thì gửi chuỗi "B" như phản hồi
    if (input == 'A') {
      Serial.print("B"); // Gửi chuỗi "B" qua Serial
      digitalWrite(2, LOW);  // Turn the LED off by making the voltage HIGH
    }
  }
}