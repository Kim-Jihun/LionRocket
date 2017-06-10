//#include <MsTimer2.h>

#include <Event.h>
#include <Timer.h>

#include <Process.h>
#include <Bridge.h>


#define IRRX0 A0
#define IRRX1 A1
#define LED 13

Timer t;

Process date;                 // process used to get the date
int hours, minutes, seconds;  // for the results
int lastSecond = -1;          // need an impossible value for comparison

int thresh;
static double count = 0;
static double in = 0;
static double out = 0;
double congestion_level = 10;

void setup()
{
  Bridge.begin();
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  Serial.println("Time Check");

  t.every(60000, Report);
      
  // run an initial date process. Should return:
  // hh:mm:ss :
      
  if (!date.running())
   {
     date.begin("date");
     date.addParameter("+%D+%T");
     date.runAsynchronously();
   }

}

void loop()
{ 
  
  int r0 = analogRead(IRRX0);
  int r1 = analogRead(IRRX1);

  thresh = 500;
  t.update();
  if(r0<thresh && r1>thresh)
  {
    count = count+1;
    in = in+1;
    delay(1300);
  }
  else{
    count = count;
    in  = in;
  }

  if(r1<thresh && r0>thresh)
  {
    count = count-1;
    out = out+1;
    delay(1300);
  }
  else{
    count = count;
    out = out;
  }

    congestion_level = count/100;
  
    Serial.print("IR0 sensor value: ");
    Serial.println(r0);

    Serial.print("IR1 sensor value: ");
    Serial.println(r1);

    Serial.print("!!COUNT value: ");
    Serial.println(count);

    Serial.print("!!CONGESTION_LEVEL value: ");
    Serial.println(congestion_level);

    Serial.println();
    delay(100);
}

   void Report(){
          if (!date.running()) {
              date.begin("date");
              date.addParameter("+%D-%T");
              date.runAsynchronously();
           }


          String date_string = date.readString();
          Serial.print(date_string);
          Serial.println();Serial.println();Serial.println();
                  
          String jsonString = "{\"Time_Key\" : \"";
          String key2 = date_string.substring(1,date_string.length()-2);
          jsonString += key2;
          jsonString +="\"}";
          Serial.print("************json***********************\n");
          Serial.print(jsonString);
          Serial.print("***********************************\n"); 
          
          Process p;
            p.runShellCommand("curl -k -X POST https://arduino2-c0fe0.firebaseio.com/Lion_Data.json -d '{ \"sensor_value\" : " + String(count) +", \"congestion_ratio\" : "
           + String(congestion_level) +", \"post_time\" : " + jsonString + ", \"people_in\" : " + String(in) + ", \"people out\" : " + String(out) + "}'"); 

            p.runShellCommand("curl -k -X POST https://donwork-233dd.firebaseio.com/Lion_Data.json -d '{ \"sensor_value\" : " + String(count) +", \"congestion_ratio\" : "
            + String(congestion_level) +", \"post_time\" : " + jsonString + ", \"people_in\" : " + String(in) + ", \"people out\" : " + String(out) + "}'"); 


            
          //  p.runShellCommand("curl -k -X POST https://donwork-233dd.firebaseio.com/Lion_Data.json -d '{ \"congestion_ratio\" : " + String(congestion_level) +" }'");
           //p.runShellCommand("curl -k -X POST https://donwork-233dd.firebaseio.com/Lion_Data.json -d '{ \"post_time\" : " + jsonString +" }'");
            while(p.running());
            
           digitalWrite(LED, HIGH);
           delay(100);
           digitalWrite(LED, LOW);
         
    } 


