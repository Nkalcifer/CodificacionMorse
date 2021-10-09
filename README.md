# CodificacionMorse  :letras_latinas_mayúsculas:

<p style='text-align: justify;'> Proyecto que busca aplicar la codificación y decodificación del código Morse, utilizando dos módulos basados en arduino (ESP8266, ESP32), cada uno de ellos con especificaciones Cliente Servidor, para transmitir mensajes codificados en morse, y recibir decodificando el mensaje. </p>



## Un poco de historia del codigo Morse :detective_tono_de_piel_claro_medio:

<p style='text-align: justify;'> El código morse fue desarrollado en 1830, por Samuel F. B. Morse y su asistente, Alfred Vail, es creado luego de la aparición del telégrafo, un medio de comunicación basado en señales eléctricas, o pulsos, generados por una maquina y recibidos en otra. El código morse esta diseñado a base de un lenguaje simple estructurado por puntos y rayas, el cual se adopta especialmente para la transmisión por señales o pulsos eléctricos, como los del telégrafo, el invento de este lenguaje redujo la complejidad que poseía el telégrafo con 5 o hasta 26 cables, a tan solo 1. Morse diseño esta forma de comunicación a razones de que en su vida recibió el mensaje de la muerte de su esposa con varios días de retardo, y a base de oír una conversación sobre la electricidad, decidió inventar el morse. El logra modificar el telégrafo junto al profesor Gale, haciendo que este generara pulsos largos(guiones), y pulsos cortos (puntos), a través de un solo cable, y finalmente junto a la ayuda de Alfred, logran crear lo que conocemos hoy en día como Código Morse. </p>


![Codigo Morse](https://github.com/Nkalcifer/CodificacionMorse/blob/main/Imagenes/codigo.png)

## Herramientas usadas en el proyecto :caja_de_herramientas:

### Modulos Arduino 
<p style='text-align: justify;'> Arduino es una plataforma electrónica de código abierto basada en hardware y software fáciles de usar. Está destinado a cualquiera que realice proyectos interactivos.[4] Esta plataforma está apoyada en un sinfín de módulos, a los cuales se les conoces como placas de arquitectura, o embebidos, y otras compañías o proyectos libres que los producen con el objetivo de realizar proyectos o crear nuevas formas de programación. </p>


<p style='text-align: justify;'> Los módulos ESP son placas basadas en arquitecturas como las de arduino, pero con características especificas enfocadas a la aplicación de IoT, a los proyectos generados en estas. En cuestión se usarán dos placas distintas: </p>

* **ESP8266:** <p style='text-align: justify;'> es una placa de NODEMCU, basada en un modulo que permite múltiples conexiones como lo hacen las placas básicas de arduino, pero que integra un chip de Wifi, es un módulo open source, en el ambiente de hardware y software, en sus posibilidades también podemos integrar módulos bluetooth, o múltiples sensores. </p>

![ESP8266](https://github.com/Nkalcifer/CodificacionMorse/blob/main/Imagenes/esp8266.png)

* **ESP32:**  <p style='text-align: justify;'>es una placa desarrollada por Espressif System [6], este chip se considera el sucesor del ESP8266, ya que integra características muy parecidas, en versión mejorada, y además integra tecnología bluetooth, sensores de radiofrecuencia, un diseño mas robusto, y un consumo energético mucho menor, además de puertos específicos para transmisión serial, algo mejor diseñado en comparación con el ESP8266, al cual le debíamos hacer una conversión en código para lograr una efectividad en los puertos digitales.</p>


![ESP32](https://github.com/Nkalcifer/CodificacionMorse/blob/main/Imagenes/esp32.png)

### Modulo LCD 16X2
<p style='text-align: justify;'>Se integrara un Modulo LCD 16X2 acoplado con un conversor I2C, para su adecuado manejo mediante la placa ESP32.  </p>


![LCD](https://github.com/Nkalcifer/CodificacionMorse/blob/main/Imagenes/lcdi2c.jpg)

### Protocolo de comunicación UDP :flechas_en_sentido_antihorario:

<p style='text-align: justify;'> La comunicación UDP esta determinada por el protocolo UDP, permite la transmisión sin conexión de datagramas en redes basadas en IP, esto quiere decir comunicación de paquetes de información por la red. Para obtener los servicios deseados en los hosts de destino, se basa en los puertos que están listados como uno de los campos principales en la cabecera UDP. Como muchos otros protocolos de red, UDP pertenece a la familia de protocolos de Internet, por lo que debe clasificarse en el nivel de transporte y, en consecuencia, se encuentra en una capa intermedia entre la capa de red y la capa de aplicación. El protocolo UDP es una alternativa directa al protocolo más utilizado, el TCP, aunque ambos se diferencian sobre todo en un punto: mientras que la transmisión en el protocolo TCP tiene lugar una vez se ha producido el enlace obligatorio de 3 vías (con acuse de recibo mutuo entre el emisor y el receptor, incluida la sesión de comunicación), el protocolo UDP no utiliza este procedimiento con el fin de mantener el tiempo de transmisión lo más bajo posible. Mediante este protocolo una aplicación puede enviar información muy rápidamente, ya que no es necesario establecer una conexión con el receptor ni esperar una respuesta. Sin embargo, no hay garantía de que los paquetes vayan a llegar completos y respetando el orden en el que fueron enviados. Además, este protocolo no ofrece ninguna protección frente a la alteración o acceso por parte de terceros. Sin embargo, el UDP puede añadir opcionalmente una suma de verificación. </p>


<p style='text-align: justify;'>Para realizar la comunicación UDP en las placas, se hará de forma Cliente Servidor, El ESP8266 proveerá una página web en la que se ingresara el mensaje y lo mostrara codificado, y esta codificación la transmitiremos por medio de Packet Sender una aplicación tipo servidor UDP, y hará que nuestro mensaje codificado llegue al módulo ESP32, el cual nos mostrar el mensaje que recibe y su correspondiente decodificación.  </p>

![packetSender](https://github.com/Nkalcifer/CodificacionMorse/blob/main/Imagenes/packetSender.png)


## Programacación de la codificación y decodificación Morse 	:ordenador_portátil: 

<p style='text-align: justify;'>Para la codificación y decodificación del código se utilizaron 2 softwares distintos, 1 de prueba, y otro de servicio. Para las pruebas se codifico en C++, y en servicio, se usó el entorno de ARDUINO.
El alfabeto usado es el siguiente: </p>


![morse](https://github.com/Nkalcifer/CodificacionMorse/blob/main/Imagenes/abcM.png)

<p style='text-align: justify;'> Tanto el abecedario como la equivalencia en morse irán en un arreglo, aquí cada punto es equivalente en cuanto a la posición en el arreglo en que serán incluidos. </p>


<p style='text-align: justify;'>En el código en C, seguido de los abecedarios, se encontrarán funciones como, la búsqueda de los índices o posiciones en que se encuentra un elemento en los abecedarios, la codificación a morse, y la decodificación.  </p>


:chincheta: <p style='text-align: justify;'>Teniendo Realizada la prueba lo siguiente que se realizó, fue la unificación del cliente con el protocolo UDP, y la decodificación de los mensajes recibidos por los servidores que transmiten. Esto se hace mediante el código en la ruta del GitHub, en: </p> El código de prueba en C++ lo encontraremos en el link del GitHub del proyecto. https://github.com/Nkalcifer/CodificacionMorse.git

:chincheta: <p style='text-align: justify;'> CodificacionMorse/CodificacionMorseESP/ESP_MORSE/ESP_MORSE.ino </p> 


## Front end :ojos:
<p style='text-align: justify;'>Para el desarrollo de la parte del front de la pagin web se uso html y css de forma sencilla, obteniendo como resultado la siguiente vista: </p>


![front](https://github.com/Nkalcifer/CodificacionMorse/blob/main/Imagenes/vista.png)

## Montaje del LCD
<p style='text-align: justify;'>Una vez todo esta en correcto funcionamiento se hizo el montaje de la pantalla LCD donde se visuliza el mensaje codificado y descodificado, obteniendo como resultado lo siguiente:  </p>


![montaje](https://github.com/Nkalcifer/CodificacionMorse/blob/main/Imagenes/Montaje.jpg)


## Conclusiones :cara_de_empollón:

* <p style='text-align: justify;'> El proyecto no es algo complejo, la codificación morse, resulta sencilla ya que se trata de un diccionario pequeño, y simple, pero realizar el manejo con arduino, y embebidos le da un toque más interesante a realizar dicha configuración, es complejo usar dos tipos de protocolos al mismo tiempo, como vimos aquí, no podemos generar un servidor http, y luego UDP, por ello, se genera el intermedio de usar PACKET SENDER como transmisor UDP. </p> 
* <p style='text-align: justify;'>  Los protocolos de comunicación resultan bastante útiles, y depende de nuestras necesidades, el uso de uno u otro, que beneficie y no retrase el proyecto que queremos realizar. Separar por fichero los proyectos en arduino no es complejo, y da orden tanto visual como estructural al proyecto, por esto es recomendable realizarlo de esta forma. </p>
* <p style='text-align: justify;'> La codificación Morse no implica el tema del cifrado de la información, por ello, para hacer que sea segura de transmitir, se debería establecer algún modelo de cifrado de información antes de codificar para así transmitir con agilidad como lo provee el código morse, ya que la seguridad del propio código, ya puede ser bastante sencilla de descifrar si no se aplica algún método de seguridad.
 </p>

## Autores  :profesional_de_la_tecnología_hombre_tono_de_piel_claro: :profesional_de_la_tecnología_mujer_tono_de_piel_claro:

* **Diana Valentina Uscategui Tobo - 20172020063**
* **Neider Puentes Sanchez - 20162021307**
