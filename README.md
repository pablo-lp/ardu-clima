![alt text](http://dezatec.es/wp-content/uploads/2019/01/ardu-clima.png)

Controlador de clima low-cost, basado en Arduino

English: https://github.com/pablo-lp/ardu-clima/blob/master/README-ENGLISH.md

# Componentes necesarios

Ver en: http://dezatec.es/ardu-clima

# Instalación

1 - Añadimos las librerías que están dentro de la carpeta "Libraries" a nuestro software Arduino, para evitar errores se aconseja usar las versiones incluídas que ya están testeadas. Después podemos eliminar esta carpeta.

2 - Abrimos el sketch con nuestro software Arduino

3 - Compilamos y lo subimos a nuestra placa (Probado solo con Arduino Uno)

# ¿Como funciona?

El controlador de clima mantiene una temperatura y humedad constante (dentro de unos rangos configurables) mediante la activación de 4 salidas, 2 para la temperatura y 2 para la humedad. Por lo tanto puede controlar deshumificación/humificación y calefactor/ventilación (o AC). Se puede configurar mediante el teclado de la pantalla o con un mando a distancia.

# ¿Como usarlo?

Para poder poner en marcha el controlador de clima todos los componentes indicados deben estar correctamente conectados. El control remoto IR es opcional.

Conectar la corriente al módulo y configurarlo mediante los menús.

Según el fabricante del LCD o control remoto que compremos puede que los botones no funcionen correctamente.

Si los botones del LCD no responden deberemos ajustar los valores de cada uno en el fichero core.h dentro del método read_inputs() en la línea 100. Podemos ver los valores de los botones en el monitor serie descomentando las líneas 114 y 115 (Tenemos que activar la salida serial descomentando también la línea 37 del fichero Ardu_Clima.ino).

Para ajustar las teclas del control remoto descomentamos las líneas 106 y 107 del fichero core.h y configuramos los valores que nos salgan en el monitor serie en el fichero config.h

# Licencia

Este trabajo está bajo la licencia Attribution-NonCommercial 4.0 International de Creative Commons. Para ver una copia de esta licencia visite http://creativecommons.org/licenses/by-nc/4.0/ o envíe una carta a Creative Commons, PO Box 1866, Mountain View, CA 94042, USA.

# Exención de responsabilidad

El software se proporciona "tal cual", sin garantías explícitas ni implícitas de ningún tipo, incluyendo, entre otras, garantías de comerciabilidad, idoneidad para un determinado fin, título y ausencia de infracción. Ni los propietarios de copyright ni los que distribuyan el software serán responsables en ningún caso de ningún daño ni de cualquier otra responsabilidad, ya sea por contrato, por litigio, como de cualquier otro tipo, que pudieran surgir de, o en conexión con el software o el uso u otros tratos del software.
