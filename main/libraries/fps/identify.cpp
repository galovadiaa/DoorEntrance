void IdentifyFinger() {

if (fps.IsPressFinger())
  {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    
    if (id <200)
    {
      Serial.print("Verified ID:");
      Serial.println(id);
    }
    else
    {
      Serial.println("Finger not found");
    }
  }
  else
  {
    Serial.println("Please press finger");
  }
  delay(100);
}
