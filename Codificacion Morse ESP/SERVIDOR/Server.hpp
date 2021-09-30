AsyncWebServer server(80);
#include "Codificar.hpp"
void handleFormText(AsyncWebServerRequest *request)
{
  String MiText = request->arg("miText");
  char Buf[250];
  MiText.toCharArray(Buf, 250);
  Serial.print("MiText:\t");
  Serial.println(MiText);
  Serial.println(CodificacionMorse(Buf));
//  ConnectUDP();
//  SendUDP_Packet(MiText);
  //String response = "<a href='/'> Go Back </a>";
  //request->send(200, "text/html", response);

  request->redirect("/");
}

void InitServer()
{
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

  server.on("/SetText", HTTP_POST, handleFormText);

  server.onNotFound([](AsyncWebServerRequest * request) {
    request->send(400, "text/plain", "Not found");
  });

  server.begin();
  Serial.println("HTTP server started");
}
