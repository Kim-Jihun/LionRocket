#include <Process.h>
#define IRRX0 A0
#define IRRX1 A1
#define LED 13

int thresh;
static int count = 0;


void setup()
{
  Bridge.begin();
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
 int r0 = analogRead(IRRX0);
 int r1 = analogRead(IRRX1);

  thresh = 500;
  if(r0<thresh && r1>thresh)
  {
    count = count+1;
    delay(600);
  }
  else{
    count = count;
  }

  if(r1<thresh && r0>thresh)
  {
    count = count-1;
    delay(600);
  }
  else{
    count = count;
  }
    
    Serial.print("IR0 sensor value: ");
    Serial.println(r0);

    Serial.print("IR1 sensor value: ");
    Serial.println(r1);
    
    Serial.print("!!COUNT value: ");
    Serial.println(count);
   
    Serial.println();
    
   int sensor0 = r0;
   int sensor1 = r1;
   Process p; 
   p.runShellCommand("curl -k -X POST https://lionrocket-project.firebaseio.com/temperature.json -d '{ \"value0\" : " + String(sensor0) + "}'");   
   p.runShellCommand("curl -k -X POST https://lionrocket-project.firebaseio.com/temperature.json -d '{ \"value1\" : " + String(sensor1) + "}'"); 
   while(p.running());  
   delay(100);     

  
 
}



/*sensA = analogRead(A0);                        // READ SENSOR A AND B
sensB= analogRead(A1);
thresh = 300;                                  // !!!!!!!!!!!!!!!   CHANGE THE VALUE OF THRESHOLD ACCORDING TO THE AMBIENT LIGHT
if(sensA<thresh && sensB>thresh)
{
ctr=ctr+1;                                      //  INCREMENT
delay(900);
}
else{ctr=ctr;
}

if(sensA>thresh && sensB<thresh)
{
ctr=ctr-1;                                       // DECREMENT
delay(900);
}
else
{
  ctr=ctr;
}

Serial.print("sensA is :  ");                          // PRINT ALL THE VALUES AND COUNTER 
Serial.print(sensA   ); 
Serial.print("      sensB is :  ");
Serial.print(sensB    );
Serial.print("     counter :  "); 
Serial.print(ctr); 
Serial.print("  thresh val : ");
Serial.println(thresh);
*/  



