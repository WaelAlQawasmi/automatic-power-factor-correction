#include <PZEM004Tv30.h>//

/* Use software serial for the PZEM
 * Pin 11 Rx (Connects to the Tx pin on the PZEM)
 * Pin 12 Tx (Connects to the Rx pin on the PZEM)
*/
PZEM004Tv30 pzem(11, 12);

float cap (float pf , float p , float v , float f )// to calculat cap value
{float s=p/pf;// to calculat s value
float x =pow(s, 2);
float y=pow(p, 2);
 float z=x-y;
 float Q1=sqrt(z);
 float s2=p/.943;
 float x2 =pow(s2, 2);
 float y2=pow(p,2);
 float z2=x2-y2; 
 float  Q2=sqrt(z2);
 float Q=Q1-Q2;
 
 float  Xc=pow(v, 2)/Q;
 float u=(2*3.14*f*Xc);
float   c=pow (10,6)/u;
if (c<0)
 c=0;
  Serial.print ("proper C =");
   Serial.print(c);
   Serial.println("uf");
   return c;}
void setup() {
  pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
      pinMode(7,OUTPUT);
  Serial.begin(115200);
}

void loop() {
    float voltage = pzem.voltage(); // to read voltage from pf sensor
    if( !isnan(voltage) ){
        Serial.print("Voltage: "); Serial.print(voltage); Serial.println("V");
    } else {
        Serial.println("Error reading voltage");
    }

    float current = pzem.current();// to read current from pf sensor
    if( !isnan(current) ){
        Serial.print("Current: "); Serial.print(current); Serial.println("A");
    } else {
        Serial.println("Error reading current");
    }

    float power = pzem.power();// to read power from pf sensor
    if( !isnan(power) ){
        Serial.print("Power: "); Serial.print(power); Serial.println("W");
    } else {
        Serial.println("Error reading power");
    }

    float energy = pzem.energy();// to read energy from pf sensor
    if( !isnan(energy) ){
        Serial.print("Energy: "); Serial.print(energy,3); Serial.println("kWh");
    } else {
        Serial.println("Error reading energy");
    }

    float frequency = pzem.frequency();
    if( !isnan(frequency) ){
        Serial.print("Frequency: "); Serial.print(frequency, 1); Serial.println("Hz");
    } else {
        Serial.println("Error reading frequency");
    }

    float pf = pzem.pf();
    if( !isnan(pf) ){
        Serial.print("PF: "); Serial.println(pf);
    } else {
        Serial.println("Error reading power factor");
        
   digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);}

    float c =cap ( pf , power ,voltage , frequency );
   if(power>100){
digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    delay(380);}

    
else
    if (c>.9){
  
     if (power< 70&& power >50)
    { digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    }
       if (power< 30&& power >10)
    { digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(7,LOW);
    }
    
      }
    Serial.println();
    delay(2000);
}
