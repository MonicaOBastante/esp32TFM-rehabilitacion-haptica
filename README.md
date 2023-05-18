# esp32TFM-rehabilitacion-haptica
Código usado para crear un prototipo háptico de ayuda en la rehabilitación del brazo en el TFM:
"Prototipo háptico para la ayuda de rehabilitación motriz de los brazos". 
Placa usada:  ESP32 Sparkfun Thing. Compatible con Arduino si se cambia la biblioteca de Bluetooth por la de Arduino 
8 motores vibrotáctiles que vibran con diversos patrones siguiendo ordenes que llegan por mensajes Bluetooth.

Nombre para enlacar "ESP32."

Los mensajes deben tener longitud par, pues recibe dos valores. Primero el tiempo que está cada motor vibrando, después el patrón.
Ambos están codificados de la siguiente forma:

Tiempo: 
  1 - 100 ms
  2 - 200 ms
  3 - 300 ms
  4 - 400 ms
  5 - 500 ms
  6 - 600 ms
  7 - 700 ms
  8 - 800 ms
  9 - 900 ms
Patrones:
  1 - arriba
  2 - abajo
  3 - derecha
  4 - izquierda
  5 - rotar derecha
  6 - rotar izquierda
  7 - doblar
  8 - desdoblar
  
  Los mensajes deben ser de longitud par, cogiendo cada par de valores por separado la placa. Si se mandase 123456, ejecutaría 3 patrones.
  El 2 a 100 ms, el 4 a 300 ms y el 6 a 500 ms. Si solo se envía 1 número, lo rechazará. Si se envían imparees, el último digito lo rechazará.
  
