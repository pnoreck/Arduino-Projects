

/**
   Press the remote control and make a picture
*/
void makePicture() {
  digitalWrite(cameraPin, HIGH);
  delay(500);
  digitalWrite(cameraPin, LOW);
}
