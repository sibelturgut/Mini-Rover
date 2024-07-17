#include <IRremote.h>
#include <NewPing.h>

const int ir_remote_pin = A2;
const int sonar_trigger_pin = 12;
const int sonar_echo_pin = 11;
const int max_distance = 500

String last_move = "";
NewPing sonar(sonar_trigger_pin, sonar_echo_pin, max_distance);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("IR activating...");
  IrReceiver.begin(ir_remote_pin, true);
  Serial.println("IR activated");

}

void loop() {
  // put your main code here, to run repeatedly:

  unsigned int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance); // Print the distance on the Serial Monitor
  Serial.println(" cm");
  if (IrReceiver.decode()) {
    Serial.println(IrReceiver.decodedIRData.decodedRawData); 

    if (IrReceiver.decodedIRData.decodedRawData == 3877175040) {
      // move forward
      last_move = "forward";
    } else if (IrReceiver.decodedIRData.decodedRawData == 2774204160) {
      // move right
      last_move = "right";
    } else if (IrReceiver.decodedIRData.decodedRawData == 4144561920) {
      // move left
      last_move = "left";
    } else if (IrReceiver.decodedIRData.decodedRawData == 2907897600) {
      // move backwards
      last_move = "backwards";
    } else if (IrReceiver.decodedIRData.decodedRawData == 3810328320) {
      last_move = "stop";
    }
    // No need to check for zero or unexpected values here, just keep the previous `last_move`

    Serial.println(last_move);
    IrReceiver.resume();
  }

  delay(500);
}
