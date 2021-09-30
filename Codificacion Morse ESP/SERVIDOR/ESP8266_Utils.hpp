
void ConnectWiFi_STA(bool useStaticIP = false)
{
  Serial.println("");
  WiFi.mode(WIFI_STA);
  if (useStaticIP) WiFi.config(ip, gateway, subnet);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Conexion Wifi...
  Serial.print("Conectando a ");
  Serial.print(WIFI_SSID);
  // Bucle de conexion
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  // Conexion exitosa
  Serial.println();
  Serial.print("Connectado! Direccion IP: ");
  Serial.println(WiFi.localIP());
}

void ConnectWiFi_AP(bool useStaticIP = false)
{
  Serial.println("");
  WiFi.mode(WIFI_AP);
  while (!WiFi.softAP(WIFI_SSID, WIFI_PASS))
  {
    Serial.println(".");
    delay(100);
  }
  if (useStaticIP) WiFi.softAPConfig(ip, gateway, subnet);

  Serial.println("");
  Serial.print("Iniciado AP:\t");
  Serial.println(WIFI_SSID);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
}
