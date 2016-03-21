void setup()  
{
  Serial.begin(9600);
  Serial3.begin(9600);
  //*B1M33H20T28F30#
  delay(5000);
    Serial3.println("B1M33H20T28F30#");
 }
// http://smartnodes.in/swc/update_bin.php?methane_level=6&humidity=6&temp=6&fill_level=6&bin_number=6
 //*B1M33H20T28F30#
 //http://smartnodes.in/swc/update_bin.php?methane_level=33&humidity=20&temp=28&fill_level=30bin_number=1
void loop() // run over and over
{
  if (Serial3.available())
    Serial.write(Serial3.read());
  if (Serial.available())
    Serial3.write(Serial.read());
}

