

#include <LiquidCrystal_I2C.h>
// si no conoce su dirección de visualización, ejecute un boceto de escáner I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);  
String messageStatic = "Mensaje Estatico";
String messageToScroll = "Este es un mensaje de desplazamiento con más de 16 caracteres";
// Función para desplazar el texto
// La función acepta los siguientes argumentos:
// fila: número de fila donde se mostrará el texto
// mensaje: mensaje para desplazarse
// delayTime: retraso entre cada cambio de carácter
// lcdColumns: número de columnas de su LCD
void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

void setup(){
  // Inicializa LCD
  lcd.init();
  // encender la luz de fondo de la pantalla LCD                     
  lcd.backlight();
}
void loop(){
  // colocar el cursor en la primera columna, primera fila
  lcd.setCursor(0, 0);
  // Muestra el mensaje Estatico
  lcd.print(messageStatic);
  // Muestra el Mensaje Desplazandose
  scrollText(1, messageToScroll, 250, 16);
}
