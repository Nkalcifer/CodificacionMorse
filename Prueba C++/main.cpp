#include <stdio.h> // Para printf
#include <string.h> // Para strcmp y strlen
#include <ctype.h> // Para toupper

#define LONGITUD_MENSAJE 500
/**
 * Traductor de código Morse en C
 *
 * Basado en https://gist.github.com/parzibyte/2b9986ee3e820f61e4cadc64722da052
 *
**/
// Código y signo iguales deben estar en el mismo índice
char *codigosMorse[] = {
        ".-", "-...", "-.-.", "-..",
        ".", "..-.", "--.", "....", "..",
        ".---", "-.-", ".-..", "--", "-.",
        "---", ".--.", "--.-", ".-.", "...",
        "-", "..-", "...-", ".--", "-..-",
        "-.--", "--..", "-----", ".----", "..---",
        "...--", "....-", ".....", "-....", "--...",
        "---..", "----.", ".-.-.-", "--..--", "---...",
        "..--..", ".----.", "-....-", "-..-.", ".--.-.",
        "-...-", ".-..-.", "-.-.--", "--.--",};

char *simbolosAscii[] = {"A", "B", "C", "D",
                         "E", "F", "G", "H", "I",
                         "J", "K", "L", "M", "N",
                         "O", "P", "Q", "R", "S",
                         "T", "U", "V", "W", "X",
                         "Y", "Z", "0", "1", "2",
                         "3", "4", "5", "6", "7",
                         "8", "9", ".", ",", ":",
                         "?", "'", "-", "/", "@",
                         "=", "\"", "!", " ",};

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

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
void demostrarCodificacionMorse() {
//    char mensaje[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.,:?'-/@=\"!";
    char mensaje[LONGITUD_MENSAJE];
    printf("Mensaje a transformar en Morse: \n");
    fgets(mensaje, LONGITUD_MENSAJE, stdin);
    mensaje[strcspn(mensaje, "\r\n")] = 0; // Remover salto de línea
    // Recorremos la cadena y transformamos cada letra
    int i = 0;
    while (mensaje[i]) {
        // Convertir a mayúscula porque tenemos equivalencias solo para mayúsculas
        // y Morse no especifica minúscula
        char letraEnMayuscula = (char) toupper(mensaje[i]);
        int indice = buscarIndiceDeAscii(letraEnMayuscula);
        char *codigoMorse = codigosMorse[indice];
        // Aquí puedes hacer lo que gustes con el morse, yo simplemente lo imprimo
        printf("%s ", codigoMorse);
        i++;
    }
}

void demostrarDecodificacionMorse() {
   char mensaje[] = ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --.. ----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----. .-.-.- --..-- ---... ..--.. .----. -....- -..-. .--.-. -...- .-..-. -.-.--";
    // Aquí define tu mensaje separado por espacios
    //char mensaje[LONGITUD_MENSAJE];
    printf("Mensaje Morse a decodificar:\n");
    //fgets(mensaje, LONGITUD_MENSAJE, stdin);
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
            printf("%s", ascii);
            token = strtok(NULL, delimitador);
        }
    }
}

int main(int argc, char** argv) {
	demostrarCodificacionMorse();
    printf("\n");
    
    //char mensaje[] = ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --.. ----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----. .-.-.- --..-- ---... ..--.. .----. -....- -..-. .--.-. -...- .-..-. -.-.--";
    // Aquí define tu mensaje separado por espacios
    char mensaje[LONGITUD_MENSAJE];
    printf("Mensaje Morse a decodificar:\n");
    fgets(mensaje, LONGITUD_MENSAJE, stdin);
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
            printf("%s", ascii);
            token = strtok(NULL, delimitador);
        }
    }
    return 0;		
                         
}
