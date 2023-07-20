int IdentifyFinger(){
  if (fps.IsPressFinger())
    {
      fps.CaptureFinger(false);      
      int id = fps.Identify1_N();
      
      if (id < 200)
      {
        return id;
      }
      else {  } // finger not found
    }
    else {  } // please press finger
  delay(100);

  return -1;
}
