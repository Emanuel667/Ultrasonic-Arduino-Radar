#include <Servo.h>.
const int motor=9;    
const int pushbutton=4; 
const int trigPin = 10;
const int echoPin = 11;
long duration;
int distance;
int unu[121], doi[121];
int number=0;
Servo myServo;
int power=1000;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myServo.attach(12);
  pinMode(motor,OUTPUT);    
  pinMode(pushbutton,INPUT); 

}
void loop() {
  for(int i=30;i<=120;i++){
    int sensor1_value=analogRead(A0);  
    myServo.write(i);
    //delay(30);
    distance = calculateDistance();
    //test de spart balonul
    Serial.print("senzor infrarosu=");
    Serial.println(sensor1_value);
    if (sensor1_value>400)
    {
      digitalWrite(motor,HIGH);  
    } 
    else
      digitalWrite(motor,LOW); //turn off alarm 
    //pana aici cod de spart balon
    if(distance>30){distance=0;unu[i]=doi[i]=0;}
    if(number==0) unu[i]=doi[i]=distance;
    else {
      if(number%2==0)
        unu[i]=distance;//reactualizare distanta
      else 
        doi[i]=distance;//reactualizare distanta
      if(abs(unu[i]-doi[i])>2){
            //aici tage
            if(power>0)
            {
               if(abs(unu[i]-doi[i])<15){
                  Serial.print(" FOC ");
                  power=power-10;
                  digitalWrite(LED_BUILTIN, HIGH);
                  delay(3000);
                  digitalWrite(LED_BUILTIN, LOW);
               }
               else Serial.print("error");
            }
            else Serial.print(" Nu mai am curent ");
        }
   }
   Serial.print(i);
   Serial.print(", ");
   Serial.print(unu[i]);Serial.print(" ");Serial.println(doi[i]);  
  }
  for(int i=30;i<=120;i++){  
  myServo.write(i);}
  delay(1000);
  /*
  for(int i=45;i<=135;i++){  
  myServo.write(i);
  delay(300);
  distance = calculateDistance();
   if(distance>25){distance=0;unu[i]=doi[i]=0;}
  //Serial.print(distance);
  //Serial.println(".");
  doi[i]=distance;
  if(abs(unu[i]-doi[i])>7)
      {Serial.print(" FOC ");
      //aici trage
      power=power-10;
      digitalWrite(LED_BUILTIN, HIGH);
        delay(3000);
        digitalWrite(LED_BUILTIN, LOW);
      }
    Serial.print(i);
    Serial.print(", ");
    Serial.print(unu[i]);Serial.print(" ");Serial.println(doi[i]);
  }
  */
  number++;
}
int calculateDistance(){ 
  delay(300);    
  Serial.print("distance: ");
  Serial.println(distance);
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance= duration*0.034/2;
  return distance;
  }

