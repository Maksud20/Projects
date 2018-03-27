// connect motor controller pins           to Arduino digital pins
// motor one
//int enA = 10;

#include <Servo.h>  //Load the servo Library
int pos = 150;    // variable to store the servo position 
int servoPin= 5; //Servo is hooked to pin 9
int servoDelay=500; // 25 millisecond delay after each servo write
Servo myPointer;
 



int in1 = 7;
int in2 = 8;
// motor two
//int enB = 5;
int in3 = 12;
int in4 = 13;


#include <SimpleDHT.h>
int wait=1;
int pinDHT11 = A2;
SimpleDHT11 dht11;
int soilmoisture=A1;
//int soilmoisture=8;
int percentmoisture;




int LPWM = 9; // H-bridge 1 ->
int RPWM = 6;
int LPWM1 = 11;
int RPWM1 = 10; // H-bridge  2 ->
int persec = 1000;
int persec1 = 1000;
int pwm=250;
//  - Receive with start- and end-markers combined with parsing

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

      // variables to hold the parsed data

int integerFromPC = 0;
int integerFromPC1 = 0;
int integerFromPC2= 0;

boolean newData = false;

//============

void setup() {
    Serial.begin(9600);
 // set all the motor control pins to outputs
  //pinMode(enA, OUTPUT);
  //pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);


    
 pinMode(13, OUTPUT);
   pinMode(LPWM, OUTPUT); 
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM1, OUTPUT); 
  pinMode(RPWM1, OUTPUT);  

  myPointer.attach(servoPin);
  
}

//============

void loop() {
  
    
    
    
    

  
  
  
  
    
     myPointer.write(120);
    
    
   byte temperature = 0;                                  ///SENSORS
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    return;
  }//
  
  
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" %");
  int sensorvalue=analogRead(A1);//SOIL MOSITURE
  
   Serial.print("mosture level: ");
  Serial.println(sensorvalue);
  percentmoisture=map(sensorvalue,245,1023,100,0);
  Serial.println(percentmoisture);
  delay(1000);
        
    
    
    
    persec = 1000; 
  persec1 = 1000;
  
    
    recvWithStartEndMarkers();           //RECIEVING DATA FROM RASPBERRY PI
    if (newData == true) {
      
        strcpy(tempChars, receivedChars);
            // this temporary copy is necessary to protect the original data
            //   because strtok() used in parseData() replaces the commas with \0
        parseData();
           if(integerFromPC==1){        //IF ON ON WEBPAGE
             Serial.println(1);
          digitalWrite(13,HIGH);
           while(persec<=4000){
  analogWrite(RPWM,pwm); //pwm value      RUN X DIR MOTORS
  analogWrite(LPWM,0);
  
  delay(persec);
  analogWrite(RPWM,0);
  delay(500);
  
  while(persec1<=6000){
  
  analogWrite(RPWM1,pwm); //              //////RUN Y DIRECTION MOTORS
  analogWrite(LPWM1,0);
  delay(persec1);
  analogWrite(RPWM1,0);
  persec1=persec1+1500;
  delay(500);


   
     
     digitalWrite(in1, HIGH);                /////RUN ACTUATORS
  digitalWrite(in2, LOW);
    delay(1000);                                                   
      digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

   delay(1000);

    digitalWrite(in3, LOW);
      digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);                                                             
 digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

 
  
  
  
  myPointer.write(60);               ////SEEDING ACTION
    delay(servoDelay);                

myPointer.write(120);
myPointer.write(120);
 
for (pos=120; pos>=55; pos=pos-1) {
  
  myPointer.write(pos);
  delay(servoDelay);
  
}

myPointer.write(120);
     



  
  }
  
  digitalWrite(RPWM1,LOW); //pwm value
  analogWrite(LPWM1,pwm);
  delay(6000);
  analogWrite(LPWM1,0);
    
  persec=persec+1000;
  delay(500);
  }
   
  digitalWrite(RPWM,LOW); //pwm value
  analogWrite(LPWM,pwm);
  
  delay(4000);
  digitalWrite(LPWM,LOW);
   
           }
            if(integerFromPC==2){              ///IF INPUT FORWARD
              digitalWrite(13,HIGH);

                analogWrite(RPWM,pwm); //pwm value
                analogWrite(LPWM,0);
  
                  delay(persec);
                  analogWrite(RPWM,0);
              
              
              
              
              }
              if(integerFromPC==3){           ///IF INPUT BACKWARD
                digitalWrite(13,HIGH);
                 digitalWrite(RPWM,LOW); //pwm value
                 analogWrite(LPWM,pwm);
  
                  delay(persec);
                 digitalWrite(LPWM,LOW);
                
                
                
                }
                 if(integerFromPC==4){                   //IF INPUT right
                  digitalWrite(13,HIGH);
                   analogWrite(RPWM1,pwm); //pwm value
                  analogWrite(LPWM1,0);
                 delay(persec1);
                   analogWrite(RPWM1,0);
                  
                  
                  }
                  if(integerFromPC==5){                         ///IF INPUT left
                    digitalWrite(13,HIGH);
                    digitalWrite(RPWM1,LOW); //pwm value
                   analogWrite(LPWM1,pwm);
                    delay(persec1);
                      analogWrite(LPWM1,0);
                    
                    
                    }

           
          else{
            digitalWrite(13,LOW);                                    ////IF OFF
            Serial.println(0);
            analogWrite(LPWM1,0);
            digitalWrite(RPWM1,LOW);

               digitalWrite(RPWM,LOW); //pwm value
               
  
              digitalWrite(LPWM,LOW);
          }
    
           
   
        newData = false;
    }
    
    
}

//============

void recvWithStartEndMarkers() {                 ////METHOD FOR RECIECING DATA FROM PI
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;

    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {                           
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; 
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}

//============

void parseData() {      //PARSING THE DATA RECIEVED
    char * strtokIndx; 

    strtokIndx = strtok(tempChars,",");      
    integerFromPC = atoi(strtokIndx); 
 
    strtokIndx = strtok(NULL, ","); 
    integerFromPC1 = atoi(strtokIndx);     

    strtokIndx = strtok(NULL, ",");
    integerFromPC2 = atoi(strtokIndx);   

}

//============


