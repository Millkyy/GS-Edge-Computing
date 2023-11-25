#include <WiFi.h>  
#include <PubSubClient.h>
#include <DHTesp.h>

const int DHT_PIN = 12;  
DHTesp dht; 
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "mqtt-dashboard.com";



WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
float temp = 0;
float hum = 0;

void setup_wifi() { 
  delay(10);
  Serial.println();
  Serial.print("Conectando à ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("endereço de IP: ");
  Serial.println(WiFi.localIP());
}
void callback(char* topic, byte* payload, unsigned int length) { 
  Serial.print("Mensagem chegou [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) { 
    Serial.print((char)payload[i]);
  }}
void reconnect() { 
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado");
      client.publish("/ThinkIOT/Publish", "Bem vindo");
      client.subscribe("/ThinkIOT/Subscribe"); 
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tente novamente em 5 segundos");
      delay(5000);
    }}
}
void setup() {
  pinMode(2, OUTPUT);     
  Serial.begin(115200);
  setup_wifi(); 
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); 
  dht.setup(DHT_PIN, DHTesp::DHT22);
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) { 
    lastMsg = now;
    TempAndHumidity  data = dht.getTempAndHumidity();

    String temp = String(data.temperature, 2);
    client.publish("/Thinkitive/BPM", temp.c_str()); 
    String hum = String(data.humidity, 1); 
    client.publish("/Thinkitive/Saturação", hum.c_str());  
    Serial.print("BPM: ");
    Serial.println(temp);
    Serial.print("Saturação: ");
    Serial.println(hum);
  }
}
