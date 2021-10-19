//MQTT publishing

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

char networkSSID[] = "WIN5357";
char networkPASSWORD[] = "jklu2021";

//char mqttSERVER[] = "test.mosquitto.org";
//char mqttSERVER[] = "mqtt.eclipse.org";
char mqttSERVER[] = "broker.mqttdashboard.com";

char mqttUSERNAME[] = "";
char mqttPASSWORD[] = "";

const char* ssid = networkSSID;
const char* password = networkPASSWORD;
const char* mqttServer = mqttSERVER;
const char* mqttUsername = mqttUSERNAME;
const char* mqttPassword = mqttPASSWORD;

char pubTopic[] = "JKLU/Gustavo2";     //payload[0] will control/set LED

char subTopic[] = "JKLU/Gustavo2/LED"; 


int counter = 0;
char cstr[16];

const int sensor=A0; // Assigning analog pin A0 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int switchState = 0;


void callback(char* topic, byte* payload, unsigned int length) {
  char message_received[2];
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < 2; i++) {
    Serial.print((char)payload[i]);
    message_received[i] = (char)payload[i];
  }
  if ( ( message_received[0] == 'O' ) && ( message_received[1] == 'N' )  )
    digitalWrite(LED_BUILTIN,0);
  else
    digitalWrite(LED_BUILTIN,1);
    
  Serial.println();
  Serial.println("-----------------------");
 
}


void setup_wifi() 
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() 
{
  // Loop until we're reconnected
  while (!client.connected()) 
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), mqttUsername, mqttPassword)) 
    {
      Serial.println("connected");
    } else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);  
  digitalWrite(LED_BUILTIN,1); //Turn LED off
  
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
}

void loop() 
{
   if (!client.connected()) 
  {
    reconnect();
    client.subscribe(subTopic);
  }
  
  client.loop();

  vout=analogRead(sensor);
  tempc = 0.322*vout - 56;
  //tempc = vout;
  tempf=(tempc*1.8)+32; // Converting to Fahrenheit 
  /*Serial.print("in DegreeC=");
  Serial.print("\t");
  Serial.print(tempc);
  Serial.println();
  Serial.print("in Fahrenheit=");
  Serial.print("\t");
  Serial.print(tempf);
  Serial.println();*/

  itoa(100*tempc, cstr, 10);
  client.publish(pubTopic, cstr);
  delay(2000);
}
