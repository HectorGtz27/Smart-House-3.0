//Hector Gutierrez
//Moises Ruiz
//Angel Castillo

#include <Servo.h> // libreria
int myNumber;
String msg1 = "(1)Abrir la puerta, (2) Cerrar la puerta";
int pos = 0;
Servo servo_10;

int F_pin = 4;
int R_pin = 5;
int An_in = 0;
int An_in2 = 1;

int analogPin = 3;
int val = 0;
int value = 0;
int val_luz = 0;

int boton;
int led;



void setup()
{

    //puerta
    Serial.begin(9600);
    servo_10.attach(10);
    Serial.println(msg1);            //leer el mensaje
    delay(10000);

    pinMode(F_pin, OUTPUT);
    pinMode(R_pin, OUTPUT);
    Serial.begin(9600);

    pinMode(11, INPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);


}

void loop()
{
    myNumber = Serial.parseInt(); //va analizar el texto como un numero entero
    servo_10.attach(10);

    if (myNumber == 1)
    {
        Serial.println("Entrando a la casa :)");
        for (pos = 0; pos <= 180; pos += 1) {
            servo_10.write(pos);
            delay(5);
        }
        for (pos = 180; pos >= 0; pos -= 1) {
            servo_10.write(pos);
            delay(5);
        }

        Serial.println("Abriendo puerta");
        Serial.println("Cerrando puerta");
        servo_10.detach();
    }

    else {

        Serial.println("Puerta cerrada");
        servo_10.detach();

    }


    val_luz = analogRead(An_in2);
    value = analogRead(An_in);
    Serial.print(val_luz);
    Serial.println(" luz");
    float millivolts = (value / 1023.0) * 5000;
    float celsius = millivolts / 10;


    if (val_luz <= 200) {
        digitalWrite(6, HIGH);
        digitalWrite(7, HIGH);
    }
    else {
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
    }


    if (celsius >= 20) {
        int vel = 75 * 255 / 100;
        analogWrite(analogPin, vel);
        digitalWrite(F_pin, HIGH);
        digitalWrite(R_pin, LOW);
        delay(100);
        Serial.println("celsius>20C");

    }
    else {
        analogWrite(analogPin, 0);
        Serial.println("celsius<20C");
    }


    led = digitalRead(7);
    boton = digitalRead(11);

    if (boton == HIGH) {
        digitalWrite(8, HIGH);
        digitalWrite(9, HIGH);
        delay(3000);

    }
    else {
        digitalWrite(8, LOW);
        digitalWrite(9, LOW);
    }


    Serial.print(celsius);
    delay(1000);
    Serial.println(" C");

}

