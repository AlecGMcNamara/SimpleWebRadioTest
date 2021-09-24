#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"
#include <EEPROM.h>

#define I2S_DOUT     27
#define I2S_BCLK     26
#define I2S_LRC      25
#define VOL_BUT      0   // Boot button on board
#define VOL_MAX      12
#define VOL_MIN      0
#define VOL_STEP     2
#define EEPROM_LENGTH           2
#define EEPROM_CHECK_ADDRESS    0
#define EEPROM_CHECK_NUMBER     69
#define EEPROM_VOLUME_ADDRESS   1

Audio audio;

String ssid =    "SKYPEMHG";
String password = "8NHetSWQAJ75";
uint8_t volume = 6;

void setVolume(){
static bool LastStateVolButon = true;
static bool VolumeUP = true;
bool CurrentStateVolButton = digitalRead(VOL_BUT);
 
    if(LastStateVolButon != CurrentStateVolButton && !CurrentStateVolButton){
        if(VolumeUP){
            volume +=VOL_STEP;
            if(volume >= VOL_MAX){
                volume = VOL_MAX;
                VolumeUP=false;
            } 
        }
        else{
            volume -=VOL_STEP;
            if(volume <= VOL_MIN){
                volume = VOL_MIN;
                VolumeUP = true;
            }
        }
        audio.setVolume(volume);
        EEPROM.write(EEPROM_CHECK_ADDRESS,EEPROM_CHECK_NUMBER);
        EEPROM.write(EEPROM_VOLUME_ADDRESS,volume);
        EEPROM.commit();
    }

    LastStateVolButon = CurrentStateVolButton;
}

void setup() {
  Serial.begin(115200);
  pinMode(VOL_BUT,PULLUP);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  Serial.println("Starting WiFi");
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED)
  delay(1500);
  Serial.println("WiFi Connected!");
  
  EEPROM.begin(EEPROM_LENGTH);
  if(EEPROM.read(EEPROM_CHECK_ADDRESS) == EEPROM_CHECK_NUMBER){ 
      volume = EEPROM.read(EEPROM_VOLUME_ADDRESS); 
  } 

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(volume);

// Greatest hits radio Stafford and cheshire
audio.connecttohost("www.radiofeeds.co.uk/bauerflash.pls?station=net2stoke.mp3.m3u");
}

void loop()
{
    audio.loop();
    setVolume();
}

// optional
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);   
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}