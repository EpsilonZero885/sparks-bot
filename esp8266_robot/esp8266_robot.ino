// Import required libraries
#include "ESP8266WiFi.h"
#include <aREST.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
 
// And connect 2 DC motors to port M3 & M4 !
Adafruit_DCMotor *L_MOTOR = AFMS.getMotor(3);
Adafruit_DCMotor *R_MOTOR = AFMS.getMotor(4);



// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "sparks-net";
const char* password = "sciencerules!";

// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Function
int stop(String message);
int forward(String message);
int right(String message);
int left(String message);
int backward(String message);

void setup(void)
{  
  // Start Serial
  Serial.begin(115200);

  // Init motor shield
  AFMS.begin();  

  // Functions          
  rest.function("stop", stop);
  rest.function("forward", forward);
  rest.function("left", left);
  rest.function("right", right);
  rest.function("backward", backward);
      
  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("robot");
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
  
  // Print the IP address
  Serial.println(WiFi.localIP());
  
}

void loop() {

  Serial.println("Main loop is good");
  
  // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
  }
  rest.handle(client);
 
}

int stop(String command) {
  int i = 0;
  while (i < 5){
    L_MOTOR->run( RELEASE );
    R_MOTOR->run( RELEASE );
    delay(1);
    i += 1;
  }
}

int backward(String command) {
  L_MOTOR->setSpeed(200);
  R_MOTOR->setSpeed(200);
  int i;
  i = 0 ;
  while (i < 5){
    L_MOTOR->run( FORWARD );
    R_MOTOR->run( FORWARD );
    delay(1);
    i = i + 1;
  
  }
}

int left(String command) {
  
  L_MOTOR->setSpeed(100);
  R_MOTOR->setSpeed(100);
  
  int i = 0;
  while (i < 3){
    L_MOTOR->run( FORWARD );
    R_MOTOR->run( BACKWARD );
    delay(1);
    i += 1;
  }
  
}

int right(String command) {
  
  L_MOTOR->setSpeed(100);
  R_MOTOR->setSpeed(100);

  int i = 0;
  while (i < 3){
    L_MOTOR->run( BACKWARD );
    R_MOTOR->run( FORWARD );
    delay(1);
    i += 1;
  }
  
}
int forward(String command) {
  
  // Stop
  L_MOTOR->setSpeed(150);
  R_MOTOR->setSpeed(150);


  int i = 0;
  while (i < 3){
    L_MOTOR->run( BACKWARD );
    R_MOTOR->run( BACKWARD );
    delay(1);
    i += 1;
  }
}
int dance(String command) {
  
  // Stop
  L_MOTOR->setSpeed(150);
  R_MOTOR->setSpeed(150);


  int i = 0;
  while (i < 3){
    L_MOTOR->run( BACKWARD );
    R_MOTOR->run( BACKWARD );
    
    delay(1);
    i += 1;

    
  }

  while (i < 3){
    L_MOTOR->run( BACKWARD );
    R_MOTOR->run( FORWARD );
    
    delay(1);
    i += 1;
  
  }
}
  
