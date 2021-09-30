#define LONGITUD_MENSAJE 500
#include <ctype.h> // Para toupper

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
const int NUMERO_CODIGOS = sizeof(codigosMorse) / sizeof(codigosMorse[0]);
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

String CodificacionMorse(char mensaje[]) {
  String cadena = "";
  //char mensaje[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,:?'-/@=\"!";
  //char mensaje[LONGITUD_MENSAJE];
  mensaje[strcspn(mensaje, "\r\n")] = 0; // Remover salto de línea
  // Recorremos la cadena y transformamos cada letra
  Serial.println(mensaje);
  int i = 0;
  while (mensaje[i]) {
    // Convertir a mayúscula porque tenemos equivalencias solo para mayúsculas
    // y Morse no especifica minúscula
    char letraEnMayuscula = (char) toupper(mensaje[i]);
    int indice = buscarIndiceDeAscii(letraEnMayuscula);
    char *codigoMorse = codigosMorse[indice];
    cadena += ("%s", (codigoMorse));
    cadena += (" ");

    i++;
  }
  return cadena;
}
