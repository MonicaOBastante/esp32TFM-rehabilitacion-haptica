// Include required libraries
#include <BluetoothSerial.h>


// Preprocessor Directives
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Bluetooth Serial object
BluetoothSerial SerialBT;

//motores
int motor1 =13;//arriba muñeca
int motor2 =12;// central arriba
int motor3 =14;//arriba codo
int motor4 =27;//derecha
int motor5 =26;//izquierda
int motor6 =25;//abajo muñeca
int motor7 =15;//central abajo
int motor8 =4;//abajo codo

//variables de control
int mensaje = 10;//mensaje recibimos
int tiempo = 750;//tiempo entre activacion o apagado. De momento valor arbitrario


//vibrar los motores en secuencia del 1 al 8
void todos(int intervalo){

  Serial.println("Inicio");
  digitalWrite(motor1, HIGH);
  delay(intervalo);
  digitalWrite(motor1, LOW);
  delay(intervalo);

  digitalWrite(motor2, HIGH);
  delay(intervalo);
  digitalWrite(motor2, LOW);
  delay(intervalo);

  digitalWrite(motor3, HIGH);
  delay(intervalo);
  digitalWrite(motor3, LOW);
  delay(intervalo);

  digitalWrite(motor4, HIGH);
  delay(intervalo);
  digitalWrite(motor4, LOW);
  delay(intervalo);

  digitalWrite(motor5, HIGH);
  delay(intervalo);
  digitalWrite(motor5, LOW);
  delay(intervalo);

  digitalWrite(motor6, HIGH);
  delay(intervalo);
  digitalWrite(motor6, LOW);
  delay(intervalo);

  digitalWrite(motor7, HIGH);
  delay(intervalo);
  digitalWrite(motor7, LOW);
  delay(intervalo);

  digitalWrite(motor8, HIGH);
  delay(intervalo);
  digitalWrite(motor8, LOW);
  delay(intervalo);
}

//abajo, los dos centrales, solo arriba. Vuelta a empezar 
void abajo(int tiempo){
  
  Serial.println("Arriba");
  digitalWrite(motor6, HIGH);
  digitalWrite(motor7, HIGH);
  digitalWrite(motor8, HIGH);
  delay(tiempo);
  digitalWrite(motor6, LOW);
  digitalWrite(motor7, LOW);
  digitalWrite(motor8, LOW);
 


}

//arriba, los dos centrales, solo abajo. Vuelta a empezar 
void arriba(int tiempo){
  Serial.println("Abajo");
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  delay(tiempo);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  
}

//vibra motor de la izquierda, empuja el brazo
void izquierda(int tiempo){
  
  Serial.println("Derecha");
  digitalWrite(motor5, HIGH);
  delay(tiempo);
  digitalWrite(motor5, LOW);
  
}

//vibra motor de la derecha, empuja el brazo
void derecha(int tiempo){
  Serial.println("Izquierda");
  digitalWrite(motor4, HIGH);
  delay(tiempo);
  digitalWrite(motor4, LOW);
  
}

//empezando por el derecho, va recorriendo anillo central
void rotarIzq(int tiempo){
  Serial.println("Rotar a la Izquierda");
  digitalWrite(motor4, HIGH);//derecha
  delay(tiempo);
  digitalWrite(motor2, HIGH);//arriba
  digitalWrite(motor4, LOW);
  delay(tiempo);
  digitalWrite(motor5, HIGH);//izquierda
  digitalWrite(motor2, LOW);
  delay(tiempo);
  digitalWrite(motor7, HIGH);//abajo
  digitalWrite(motor5, LOW);
  delay(tiempo);
  digitalWrite(motor7, LOW);

}

//empezando por el izquierdo, va recorriendo anillo central
void rotarDer(int tiempo){
  Serial.println("Rotar a la Derecha");
  digitalWrite(motor5, HIGH);//izquierda
  delay(tiempo);
  digitalWrite(motor2, HIGH);//arriba
  digitalWrite(motor5, LOW);
  delay(tiempo);
  digitalWrite(motor4, HIGH);//derecha
  digitalWrite(motor2, LOW);
  delay(tiempo);
  digitalWrite(motor7, HIGH);//abajo
  digitalWrite(motor4, LOW);
  delay(tiempo);
  digitalWrite(motor7, LOW);//abajo
}


//dobla el brazo hacia el codo.
void doblar(int tiempo){
  Serial.println("Abajo");
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor8, HIGH);
  delay(tiempo);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor8, LOW);  
}

//desdobla el brazo hacia el codo.
void desdoblar(int tiempo){
  Serial.println("Abajo");
  digitalWrite(motor6, HIGH);
  digitalWrite(motor7, HIGH);
  digitalWrite(motor3, HIGH);
  delay(tiempo);
  digitalWrite(motor6, LOW);
  digitalWrite(motor7, LOW);
  digitalWrite(motor3, LOW);  
}




//INICIO
void setup(){
   
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(motor5, OUTPUT);
  pinMode(motor6, OUTPUT);
  pinMode(motor7, OUTPUT);
  pinMode(motor8, OUTPUT);
  Serial.begin(115200);
    
     // Initiate Bluetooth
  if(SerialBT.begin("ESP32")) {
    Serial.println("The device started, now you can pair it with bluetooth!");
  }
  else {
    Serial.println("An error occurred initializing Bluetooth");
  }
}

void loop(){
    
    Serial.println("Inicio Bucle");
    if(SerialBT.available()){
      mensaje = SerialBT.read();

      //tiempo entre paso y paso del patron
      if(mensaje!=10){
        Serial.println(mensaje);
        switch(mensaje){
          case 49://1
            tiempo = 100;
            break;
          case 50://2
            tiempo = 200;
            break;
          case 51://3
            tiempo = 300;
            break;
          case 52://4
            tiempo = 400;
            break;
          case 53://5
            tiempo = 500;
            break;
          case 54://6
            tiempo = 600;
            break;
          case 55://7
            tiempo = 700;
            break;
          case 56://8
            tiempo = 800;
            break;
          case 57://9
            tiempo = 900;
            break;
          default:
            Serial.println("Movimiento no reconocido");
          
        }
      }

      //patron
      mensaje = SerialBT.read();
      if(mensaje!=10){
        Serial.println(mensaje);
        switch(mensaje){
          case 49://1
            arriba(tiempo);
            break;
          case 50://2
            abajo(tiempo);
            break;
          case 51://3
            derecha(tiempo);
            break;
          case 52://4
            izquierda(tiempo);
            break;
          case 53://5
            rotarDer(tiempo);
            break;
          case 54://6
            rotarIzq(tiempo);
            break;
          case 55://7
            doblar(tiempo);
            break;
          case 56://8
            desdoblar(tiempo);
            break;
          default:
            Serial.println("Movimiento no reconocido");
          
        }
      }
    }
}
