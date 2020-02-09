#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "DJChrizzemann";
const char* passord = "TardisTardis";

void wifiinfo();


void setup() {
Serial.begin(115200);
  WiFi.begin(ssid,passord);
  while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
wifiinfo();


}

void loop() {

  
  Serial.println("—————");
  StaticJsonBuffer<300> JSONbuffer;  // Velg strl paa melding i byte f.eks 300
  JsonObject& JSONencoder = JSONbuffer.createObject();
 
  JSONencoder["sensorType"] = "Sensor";
  JsonArray& values = JSONencoder.createNestedArray("verdier"); //lag et nested array med valgfrie verdier
 
  values.add(1); //her erstatter vi med verdier vi selv måtte onske
  values.add(1);
  values.add(1);

  int lenghtSimple = JSONencoder.measureLength();  //skriver ut lengden på meldingen, kan kjores som prettyprint om det er å foretrekke
  Serial.print("Less overhead JSON message size: ");
  Serial.println(lenghtSimple);
  
 
  Serial.println("\nPretty JSON message from buffer: "); //skriver ut selve JSON meldingen til serial monitor for forhaandsvisning
  char JSONmessageBuffer[300];
  JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
  Serial.println(JSONmessageBuffer);
  Serial.println();


      HTTPClient http;
      http.begin("https://www.vibecheck.no/");  //Velg adresse for mottaker av melding 
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
      int httpResponseCode = http.POST(JSONmessageBuffer);


      if (httpResponseCode >0){ //funksjon som returner feilkode om noe går galt, snedig i debug stadiet, men unodvendig for selve koden
                String response = http.getString();
                Serial.println(httpResponseCode);
                Serial.println(response);
              }
              else{
                Serial.print("Error on sending post");
                Serial.println(httpResponseCode);
              }

      http.end(); // Avslutter foresporselen til nettsiden

      delay(10000); // delay 



}

void wifiinfo(){
  Serial.println("");
  Serial.println("Wifi connected");
  Serial.println("IP ADRESS");
  Serial.println(WiFi.localIP());
}