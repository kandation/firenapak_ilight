#include <Adafruit_NeoPixel.h>
/*
 * Bring Attrack CPE (Prototype)
 * Concept by AJ.Kran, Created by Pyruvate688, Kanoon2017
 */

 // OTA LIBRARY
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#define NUM_RING_ONE_PIX 24
#define NUM_RING_ALL_PIX 384
#define LED_PIN D1

#define CLAP_THRESHOLE 600

#define COLOR_NONE 0,0,0
#define COLOR_RED 255,0,0
#define COLOR_GREEN 0,255,0
#define COLOR_BLUE 0,0,255
#define COLOR_ORANGE 255,170,0
#define COLOR_YELLOW 200,200,0
#define COLOR_WHITE 255,255,255

#ifdef __AVR__
#include <avr/power.h>
#endif
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_RING_ALL_PIX, LED_PIN, NEO_GRB + NEO_KHZ800);
int speedScore = 0;

void openSingle(int num, byte r, byte g, byte b){
  for(int i= num * NUM_RING_ONE_PIX; i < ((num + 1) * NUM_RING_ONE_PIX); i++){
    pixels.setPixelColor(i, r, g, b);
  }
}

void otaConnect(){
  const char* ssid = "itim";
  const char* password = "ilovecpe";
  const char* host = "iLight_host";
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);  
  ArduinoOTA.setHostname(host);
  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });

  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });

  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });

  ArduinoOTA.onError([](ota_error_t error) {
  //ESP.restart();
  Serial.printf("Error[%u]: ", error);
  if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
  else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
  else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
  else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
  else if (error == OTA_END_ERROR) Serial.println("End Failed");

  });

/* setup the OTA server */
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loadWelcomeScreen(){
  openSingle(0, COLOR_WHITE);
  openSingle(1, COLOR_BLUE);
  openSingle(2, COLOR_GREEN);
  openSingle(3, COLOR_GREEN);
  openSingle(4, COLOR_GREEN);
  openSingle(5, COLOR_GREEN);
  openSingle(6, COLOR_BLUE);
  openSingle(7, COLOR_GREEN);
  openSingle(8, COLOR_BLUE);
  openSingle(9, COLOR_BLUE);
  openSingle(10, COLOR_BLUE);
  openSingle(11, COLOR_GREEN);
  openSingle(12, COLOR_GREEN);
  openSingle(13, COLOR_GREEN);
  openSingle(14, COLOR_GREEN);
  openSingle(15, COLOR_GREEN);
  pixels.show();
  delay(2000);
  for(int i=0;i<16;i++){
    openSingle(i, COLOR_NONE);
  }
  pixels.show();
}

int randomPoint(){
  return random(4,16);
}

void showPoint(int pos){
  openSingle(pos, COLOR_RED);
  pixels.show();
  delay(800);
  for(int i = 0; i < 5; i++){
    openSingle(pos, COLOR_RED);
    pixels.show();
    delay(300);
    openSingle(pos, COLOR_NONE);
    pixels.show();
    delay(300);
  }
  openSingle(pos, COLOR_RED);
  pixels.show();
  delay(500);  
}

void showStep(int gameSpeed){
  openSingle(0 , COLOR_RED);
  pixels.show();
  delay(200);
  openSingle(0 , COLOR_ORANGE);
  pixels.show();
  delay(200);
  openSingle(0 , COLOR_YELLOW);
  pixels.show();
  delay(200);
  for(int i = 0; i < 5; i++){
    openSingle(0 , COLOR_GREEN);
    pixels.show();    
    delay(gameSpeed);
    openSingle(0 , COLOR_NONE);
    pixels.show();    
    delay(100);    
  }
}

void fristLineCouting(int gameSpeed){
  for(int i = 0; i <= 3; i++){
    openSingle(i , COLOR_GREEN);
    pixels.show();    
    delay(gameSpeed);
  }
  
}

bool isGameOver(int gameStatus){
  if(gameStatus >= 0 ){
    return false;
  }
  return true;
}

int checkEnemy(int player_pos, int enemy_pos){
  if(player_pos == enemy_pos){
    return 1;
  }else{
    return -1;
  }
  
}

bool delayMilli(int prev, int _delay){
  return (millis() - prev <= _delay)? true : false;
}

void showBlink(){
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 16; j++){
      openSingle(j, COLOR_RED);
    }pixels.show();
    delay(100);
    
    for(int j = 0; j < 16; j++){
      openSingle(j, COLOR_NONE);
    }pixels.show();
    delay(100);
  }
}

void clearDisplay(){
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 16; j++){
      openSingle(j, COLOR_BLUE);
    }pixels.show();
    delay(100);
    
    for(int j = 0; j < 16; j++){
      openSingle(j, COLOR_NONE);
    }pixels.show();
    delay(100);
  }
}

void openArrayLight(int* num, int n, byte r, byte g, byte b){
  
}

void render_frame_color(byte pics[][48], int frame_num){
  for(int i=0; i < frame_num; i++){
    for(int j=0; j < 48; j+=3){
      openSingle(j/3, pics[i][j+0], pics[i][j+1], pics[i][j+2]);
      yield();
    }pixels.show();
    delay(500);
  }
}

void showNextLevel(){
  byte color_frame[6][48] = {
    {
      COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE,
      COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_RED,
      COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_RED,
      COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_NONE  
    },
    {
      COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_RED,
      COLOR_NONE, COLOR_NONE, COLOR_RED, COLOR_ORANGE,
      COLOR_NONE, COLOR_NONE, COLOR_RED, COLOR_ORANGE,
      COLOR_NONE, COLOR_NONE, COLOR_NONE, COLOR_RED  
    },
    {
      COLOR_NONE, COLOR_NONE, COLOR_RED, COLOR_ORANGE,
      COLOR_NONE, COLOR_RED, COLOR_ORANGE, COLOR_ORANGE,
      COLOR_NONE, COLOR_RED, COLOR_ORANGE, COLOR_ORANGE,
      COLOR_NONE, COLOR_NONE, COLOR_RED, COLOR_ORANGE 
    },
    {
      COLOR_NONE, COLOR_RED, COLOR_ORANGE, COLOR_ORANGE,
      COLOR_RED, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE,
      COLOR_RED, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE,
      COLOR_NONE, COLOR_RED, COLOR_ORANGE, COLOR_ORANGE    
    },
    {
      COLOR_RED, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE,
      COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE,
      COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE,
      COLOR_RED, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE
    },
    {
      COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE,
      COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE,
      COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE,
      COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE, COLOR_ORANGE
    }
    
  };
  render_frame_color(color_frame, 6);
}


bool isWin(){
  return (speedScore > 4);
}

bool isClap(){
  if(analogRead(A0) > CLAP_THRESHOLE){
    return true;
  }return false;
}

void checkAttack(int gameSpeed, int enermyPoint){
  long prev_milli = millis();
  int i = 4;
  int gameStatus = 0;
  
  while(true){
    if(isGameOver(gameStatus)){
      break;
    }

    if(isWin()){
      //break;
    }
    Serial.println("Dead");
    if(millis() - prev_milli <= gameSpeed){
      openSingle(i, COLOR_GREEN);
      pixels.show();
      if(isClap()){
        gameStatus = 0;
        gameStatus = checkEnemy(i, enermyPoint);
        if(gameStatus > 0){
          speedScore += 1;
          showNextLevel();
        }
      }
    }else{
      prev_milli = millis();      
      i++;
    }
     Serial.println("After Dead");
     yield();
    
  }
  Serial.println("Am Alive");
}

int gameSpeedCase(int _speedScore){
  switch( _speedScore ){
    case 0: return 1200;
    case 1: return 1100;
    case 2: return 1000;
    case 3: return 900;
    default: return 500;
  }return 500;
}

void gameStart(int enermyPoint){
  int gameSpeed = 0;
  gameSpeed = (int)gameSpeedCase(speedScore);
  showStep(gameSpeed);
  fristLineCouting(gameSpeed);
  checkAttack(gameSpeed, enermyPoint);
}
int level_sound = 0;
void equlizerCheck(){
  level_sound = map(analogRead(A0),0,720,0,15);
 
  for(int i=0;i<= 16; i++){
     openSingle(i,COLOR_NONE);    
  }
  for(int i=0;i<= level_sound; i++){
  openSingle(i,COLOR_GREEN);    
  }pixels.show(); 
}


void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  Serial.begin(115200);
  pixels.begin();
  pinMode(D7,OUTPUT);
  pinMode(A0, INPUT);
  otaConnect();
  loadWelcomeScreen();

}



void loop() {
  ArduinoOTA.handle();  
  int enemyPoint;
  enemyPoint = randomPoint();
  showPoint(enemyPoint);
  showNextLevel();
  gameStart(enemyPoint);
  showBlink();
  clearDisplay();
}
