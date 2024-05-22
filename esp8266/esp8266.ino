#include <ESP8266WiFi.h>
#include <string>
#include "DHT.h"
#include <ESP8266WebServer.h>
using namespace std;

#define DHTTYPE DHT11

const char* ssid = "****";
const char* password = "****";

WiFiServer server(80);

// led
int led = 2;
bool led_web = 0;

// DHT Sensor
uint8_t DHTPin = 0; 
// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);                
 
float temperature;
float humidity;


void setup()
{


  Serial.begin(115200);
  delay(100);

  pinMode(led,OUTPUT);
  digitalWrite(led,0);

  pinMode(DHTPin, INPUT);
  dht.begin();    

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected.");

  server.begin();
  Serial.println("Server Started");

  Serial.println(WiFi.localIP());
 
}

void loop() 
{
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  Serial.println("new client");

  while (!client.available())
  {
    delay(1);
  }

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  //-----------------------------------------
  if (req.indexOf("/on") != -1)
  {
    digitalWrite(led,1);
    led_web = 1;
  }
  else if (req.indexOf("/off") != -1)
  {
    digitalWrite(led,0);
    led_web =  0;
  }
  //-----------------------------------------
  client.flush();
  //----------------read temp&hum
  temperature = dht.readTemperature(); // Gets the values of the temperature
  humidity = dht.readHumidity(); // Gets the values of the humidity 
  //-----------------
  char temp[200];
  char hum[200];
  sprintf(temp,"%f",temperature);
  sprintf(hum,"%f",humidity);

String result = "<!DOCTYPE html> \n";
    result += "     <html>";
    result += "<head>";
    result += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">";
    result += "<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>";
    result += "<meta http-equiv=\"refresh\" content=\"60\">";
    result += "<style>";
    result += "";
result += ".switch {";
result += "  position: relative;";
result += "  display: inline-block;";
result += "  width: 10vw;";
result += "  height: 5.66vw;";
result += "    margin-bottom: 25px;";
result += "}";
result += "";
result += "";
result += ".switch input {";
result += "  opacity: 0;";
result += "  width: 0;";
result += "  height: 0;";
result += "}";
result += "";
result += ".slider {";
result += "  position: absolute;";
result += "  cursor: pointer;";
result += "  top: 0;";
result += "  left: 0;";
result += "  right: 0;";
result += "  bottom: 0;";
result += "  background-color: #ccc;";
result += "  -webkit-transition: .4s;";
result += "  transition: .4s;";
result += "}";
result += "";
result += ".slider:before {";
result += "  position: absolute;";
result += "  content: \"\";";
result += "  height: 4.2vw;";
result += "  width:  4.2vw;";
result += "  left: 0.66vw;";
result += "  bottom: 0.66vw;";
result += "  background-color: #353632;";
result += "  -webkit-transition: .4s;";
result += "  transition: .4s;";
result += "}";
result += "";
result += "input:checked + .slider {";
result += "  background-color: #bfe004;";
result += "}";
result += "";
result += "input:focus + .slider {";
result += "  box-shadow: 0 0 1px #2196F3;";
result += "}";
result += "";
result += "input:checked + .slider:before {";
result += "  -webkit-transform: translateX(4.2vw);";
result += "  -ms-transform: translateX(4.2vw);";
result += "  transform: translateX(4.2vw);";
result += "}";
result += "";
result += ".slider.round {";
result += "  border-radius: 4.2vw;";
result += "}";
result += "";
result += ".slider.round:before {";
result += "  border-radius: 50%;";
result += "}";
result += ".container{";
result += "  text-align: center;";
result += "  border: 3px solid black;";
result += "  border-radius: 2%;";
result += "  width: 60%;";
result += "  max-width: 700px;";
result += "  margin: 0 auto;";
result += "  background:rgb(20, 18, 21);";
result += "}";
result += "body {";
result += "  background: #D2D5D9;";
result += "}";
result += "";
result += "";
result += ".gauge {";
result += "  width: 100%;";
result += "  font-family: \"Roboto\", sans-serif;";
result += "  font-size: 3vw;";
result += "  color: #4b85e3;";
result += "  margin:auto;";
result += "";
result += "}";
result += "";
result += ".gauge__body {";
result += "  width: 100%;";
result += "  height: 0;";
result += "  padding-bottom: 50%;";
result += "  background: #b4c0be;";
result += "  position: relative;";
result += "  border-top-left-radius: 100% 200%;";
result += "  border-top-right-radius: 100% 200%;";
result += "  overflow: hidden;";
result += "}";
result += "";
result += ".gauge__fill {";
result += "  position: absolute;";
result += "  top: 100%;";
result += "  left: 0;";
result += "  width: inherit;";
result += "  height: 100%;";
result += "  background: #4b85e3;";
result += "  transform-origin: center top;";
result += "  transform: rotate(0.25turn);";
result += "  transition: transform 0.2s ease-out;";
result += "}";
result += "";
result += ".gauge__cover {";
result += "  width: 75%;";
result += "  height: 150%;";
result += "  background:rgb(20, 18, 21);";
result += "  border-radius: 50%;";
result += "  position: absolute;";
result += "  top: 25%;";
result += "  left: 50%;";
result += "  transform: translateX(-50%);";
result += "";
result += "  display: flex;";
result += "  align-items: center;";
result += "  justify-content: center;";
result += "  padding-bottom: 25%;";
result += "  box-sizing: border-box;";
result += "";
result += "}";
result += "";
result += "";
result += "";
result += "";
result += ".gauge2 {";
result += "  width: 100%;";
result += "  font-family: \"Roboto\", sans-serif;";
result += "  font-size: 3vw;";
result += "  color: #eb5910;";
result += "  margin:auto;";
result += "}";
result += "";
result += ".gauge__body2 {";
result += "  width: 100%;";
result += "  height: 0;";
result += "  padding-bottom: 50%;";
result += "  background: #b4c0be;";
result += "  position: relative;";
result += "  border-top-left-radius: 100% 200%;";
result += "  border-top-right-radius: 100% 200%;";
result += "  overflow: hidden;";
result += "}";
result += "";
result += ".gauge__fill2 {";
result += "  position: absolute;";
result += "  top: 100%;";
result += "  left: 0;";
result += "  width: inherit;";
result += "  height: 100%;";
result += "  background: #eb5910;";
result += "  transform-origin: center top;";
result += "  transform: rotate(0.25turn);";
result += "  transition: transform 0.2s ease-out;";
result += "}";
result += "";
result += ".gauge__cover2 {";
result += "  width: 75%;";
result += "  height: 150%;";
result += "  background:rgb(20, 18, 21);";
result += "  border-radius: 50%;";
result += "  position: absolute;";
result += "  top: 25%;";
result += "  left: 50%;";
result += "  transform: translateX(-50%);";
result += "";
result += "  display: flex;";
result += "  align-items: center;";
result += "  justify-content: center;";
result += "  padding-bottom: 25%;";
result += "  box-sizing: border-box;";
result += "}";
result += "";
result += "";
result += "";
result += "</style>";
    result += "</head>";
    result += "<body>";
    
result += "<div class=\"container\">";
result += "    <h2 style=\"font-size: 4vw; color: #b4c0be;\">esp8266 project</h2>";
result += "    <h2 style=\"font-size: 1.7vw; color: #b4c0be;\">Erfan Nateghi</h2>";
result += "    <h2 style=\"font-size: 1.7vw; color: #b4c0be;\">Mehdi sabokkhiz</h2>";
result += "</div>";
    result += "<div class=\"container\">";
    result += "<h2 style=\"font-size: 2.75vw; color: #b4c0be\";>LED</h2>";
    result += "<label class=\"switch\">";
    
    if (led_web == 0)
        result += "  <input type=\"checkbox\" id=\"agree\" onclick=\"checkClickfunc()\">";
   else if (led_web == 1)
        result += "<input type = \"checkbox\" id=\"agree\" checked onclick=\"checkClickfunc()\"> ";
        
    
    result += "  <span class=\"slider round\"></span>";
    result += "</label>";
    result += "</div>";

result += "<div class=\"container\">";
result += "    <h1 style=\"font-size: 3.5vw;color: #b4c0be;\">Weather Station</h1>";
result += "    <div>";
result += "        <div class=\"gauge-section\">";
result += "            <h3 style=\"font-size: 2.75vw; color: #b4c0be;\">Humidity</h3>";
result += "            <div class=\"container\"style=\"border-color: rgb(20, 18, 21)\">";
result += "                    <div class=\"gauge\">";
result += "                  <div class=\"gauge__body\">";
result += "                    <div class=\"gauge__fill\"></div>";
result += "                    <div class=\"gauge__cover\"></div>";
result += "                  </div>";
result += "                        <p  style=\" margin: auto; text-align: start;position: absolute;";
result += "                    font-size: 3vw; \">0</p><p style=\"  margin: auto; text-align: end;";
result += "                    font-size: 3vw;\">100</p>";
result += "                </div>";
result += "                </div>";
result += "            </div>";
result += "            <div class=\"gauge-section\">";
result += "                <h3 style=\"font-size: 2.75vw;color: #b4c0be;\">Temperature</h3>";
result += "                <div id=\"temp\" class=\"\">";
result += "                <div class=\"container\" style=\"border-color: rgb(20, 18, 21);\">";
result += "                        <div class=\"gauge2\">";
result += "                      <div class=\"gauge__body2\">";
result += "                        <div class=\"gauge__fill2\"></div>";
result += "                        <div class=\"gauge__cover2\"></div>";
result += "                      </div>";
result += "                            <p  style=\" margin: auto; text-align: start;position: absolute;";
result += "                    font-size: 3vw;\">-20</p><p style=\"  margin: auto; text-align: end;";
result += "                    font-size: 3vw;\">60</p>";
result += "                    </div>";
result += "                </div>";
result += "                </div>";
result += "            </div>";
result += "        </div>";
result += "    </div>";
    result += "     ";
    result += "     ";
    result += "     <script>";
    result += "    const gaugeElement = document.querySelector(\".gauge\");";
    result += "    function setGaugeValue(gauge, value) {";
    result += "      if (value < 0 || value > 100) {";
    result += "        return;";
    result += "      }";
    result += "      gauge.querySelector(\".gauge__fill\").style.transform = `rotate(${value / 200 }turn)`;";
    result += "      gauge.querySelector(\".gauge__cover\").textContent = `${Math.round(value)}%`;";
    result += "    }";
    result += "";
    result += "    setGaugeValue(gaugeElement, ";
    result += hum;
    result += ");";
    result += "    ";
    result += "</script>";
    result += "<script>";
    result += "    const gaugeElement2 = document.querySelector(\".gauge2\");";
    result += "    function setGaugeValue2(gauge2, value) {";
    result += "      if (value < -20 || value > 60) {";
    result += "        return;";
    result += "      }";
    result += "      gauge2.querySelector(\".gauge__fill2\").style.transform = `rotate(${(value+20) / 160 }turn)`;";
    result += "      gauge2.querySelector(\".gauge__cover2\").textContent = `${Math.round(value)}°`;";
    result += "    }";
    result += "    setGaugeValue2(gaugeElement2, ";
    result += temp;
    result += ");";
    result += "</script>";
    result += "<script>function checkClickfunc() {var checkbox = document.getElementById('agree'); if(checkbox.checked == true){on();}else{off();}}</script>";
    result += "<script>function on() {$.get(\"/on\");}</script>";
    result += "<script>function off() {$.get(\"/off\");}</script>";
    result += "</body>";
    result += "</html> ";

  client.print(result);
  delay(1);
  
  Serial.println("disconnected");

  
  
}
