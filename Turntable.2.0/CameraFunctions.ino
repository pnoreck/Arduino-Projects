
// Pin of the camera remote
const short cameraPin = 6;


void initializeCamera() {
    pinMode(cameraPin, OUTPUT);
}

/**
   Press the remote control and make a picture
*/
void takePicture() {
  delay(200);
  digitalWrite(cameraPin, HIGH);
  delay(500);
  digitalWrite(cameraPin, LOW);
  delay(500);
}
