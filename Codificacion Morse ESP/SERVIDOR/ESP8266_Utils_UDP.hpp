
boolean ConnectUDP() {
  Serial.println();
  Serial.println("Starting UDP");
  // in UDP error, block execution
  if (UDP.begin(localPort) != 1)
  {
    Serial.println("Connection failed");
    while (true) {
      delay(1000);
    }
  }
  Serial.println("UDP successful");
}

void SendUDP_ACK()
{
  UDP.beginPacket(UDP.remoteIP(), remotePort);
  UDP.write("ACK");
  UDP.endPacket();
}
void SendUDP_Packet(String content)
{
  UDP.beginPacket(UDP.remoteIP(), remotePort);
  UDP.write(content.c_str());
  UDP.endPacket();
}
