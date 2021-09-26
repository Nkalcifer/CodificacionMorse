#include <WiFi.h>
#include <WiFiUdp.h>
#include <LiquidCrystal_I2C.h>

/* Nombre y contraseña de la red WiFi */
// Credenciales WIFI
#define WIFI_SSID "CDE-PUENTES"
#define WIFI_PASS "Puentes9496"

// Dirección IP a la que enviar datos UDP.
// puede ser la dirección IP del servidor o
// una dirección de transmisión de red
// aquí está la dirección de transmisión
const char * udpAddress = "192.168.1.100";
const int UDP_PORT = 4210;
char reply[] = "Paquete Recibido!";

//Abecedarios
char *codigosMorse[] = {".-", "-...", "-.-.", "-..",
                        ".", "..-.", "--.", "....", "..",
                        ".---", "-.-", ".-..", "--", "-.",
                        "---", ".--.", "--.-", ".-.", "...",
                        "-", "..-", "...-", ".--", "-..-",
                        "-.--", "--..", "-----", ".----", "..---",
                        "...--", "....-", ".....", "-....", "--...",
                        "---..", "----.", ".-.-.-", "--..--", "---...",
                        "..--..", ".----.", "-....-", "-..-.", ".--.-.",
                        "-...-", ".-..-.", "-.-.--", "--.--",
                       };
char *simbolosAscii[] = {"A", "B", "C", "D",
                         "E", "F", "G", "H", "I",
                         "J", "K", "L", "M", "N",
                         "O", "P", "Q", "R", "S",
                         "T", "U", "V", "W", "X",
                         "Y", "Z", "0", "1", "2",
                         "3", "4", "5", "6", "7",
                         "8", "9", ".", ",", ":",
                         "?", "'", "-", "/", "@",
                         "=", "\"", "!", " ",
                        };

//instancia UDP
WiFiUDP UDP;
// si no conoce su dirección de visualización, ejecute un boceto de escáner I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Variables y Constantes
char messageRecived[255];
char messageDecodified[255];
char packet[255];
String cadena = "";
const int NUMERO_CODIGOS = sizeof(codigosMorse) / sizeof(codigosMorse[0]);
// Funcion para imprimir Escroll
void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i = 0; i < lcdColumns; i++) {
    message = " " + message;
  }
  message = message + " ";
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(100);
  }
}


int buscarIndiceDeMorse(char *codigo) {
  for (int x = 0; x < NUMERO_CODIGOS; x++) {
    if (strcmp(codigosMorse[x], codigo) == 0) {
      return x;
    }
  }
  return -1;
}

int buscarIndiceDeAscii(char signo) {
  // Convertir char a string
  char cadenaTemporal[2];
  cadenaTemporal[0] = signo;
  cadenaTemporal[1] = '\0';
  for (int x = 0; x < NUMERO_CODIGOS; x++) {
    if (strcmp(simbolosAscii[x], cadenaTemporal) == 0) {
      return x;
    }
  }
  return -1;
}




void setup() {

  Serial.begin(115200);
  //Connect to the WiFi network
  // Inicio WiFi
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
  // Inicio escucha UDP
  UDP.begin(UDP_PORT);
  Serial.print("Escuchando UDP en Puerto: ");
  Serial.println(UDP_PORT);

  // Inicializa LCD
  lcd.init();
  // encender la luz de fondo de la pantalla LCD
  lcd.backlight();
}

void loop() {
  // Si se recibe un paquete...
  int packetSize = UDP.parsePacket();
  if (packetSize) {
    Serial.print("Paquete Recibido! Tamaño: ");
    Serial.println(packetSize);
    int len = UDP.read(packet, packetSize);
    if (len > 0)
    {
      packet[len] = '\0';
    }
    Serial.print("Paquete Recibido: ");
    Serial.println(packet);
    int i = 0;
    while (reply[i] != 0) 
    UDP.write((uint8_t)reply[i++]);
    UDP.endPacket();
    
    lcd.setCursor(0, 0);
    // Muestra el mensaje Estatico
    scrollText(0, packet, 500, 16);
    // Decodificamos el mensaje
    demostrarDecodificacionMorse(packet);
    // Send return packet
    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    

  }
  // colocar el cursor en la primera columna, primera fila

}

void demostrarDecodificacionMorse(char mensaje[]) {
  cadena="";
  mensaje[strcspn(mensaje, "\r\n")] = 0; // Remover salto de línea
  char delimitador[] = " ";
  // Separamos la cadena por espacios. Más información sobre strtok en https://parzibyte.me/blog/2018/11/13/separar-cadena-delimitadores-c-strtok/
  char *token = strtok(mensaje, delimitador);
  if (token != NULL) {
    while (token != NULL) {
      // Obtener cuál índice tiene este código
      int indice = buscarIndiceDeMorse(token);
      // Aquí puedes hacer lo que gustes con el ascii, yo simplemente lo imprimo
      char *ascii = simbolosAscii[indice];
      cadena += ("%s", ascii);

      token = strtok(NULL, delimitador);
    }
  }
  Serial.println(cadena);
  Serial.println("");
  scrollText(1, cadena, 250, 16);
}
