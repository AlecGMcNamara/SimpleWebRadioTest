#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"

//#include "SPIFFS.h"

#define I2S_DOUT     27
#define I2S_BCLK     26
#define I2S_LRC      25
#define VOL_BUT      0
#define VOL_MAX      12

Audio audio;

String ssid =    "SKYPEMHG";
String password = "8NHetSWQAJ75";
uint8_t volume = 6;

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

// Launch SPIFFS file system  
// if(!SPIFFS.begin()){ 
//    Serial.println("An Error has occurred while mounting SPIFFS");  
//  }
  
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(volume);

//audio.connecttoFS(SPIFFS,"/test.mp3" );

// Greatest hits radio Stafford and cheshire
audio.connecttohost("www.radiofeeds.co.uk/bauerflash.pls?station=net2stoke.mp3.m3u");

}
void loop()
{
static bool LastStateVolButon = true;
static bool VolumeUP = true;
bool CurrentStateVolButton = digitalRead(VOL_BUT);
 
    audio.loop();

    if(LastStateVolButon != CurrentStateVolButton && !CurrentStateVolButton){
        if(VolumeUP){
            volume +=3;
            if(volume >= VOL_MAX){
                VolumeUP=false;
            } 
        }
        else{
            volume -=3;
            if(volume <= 0){
                VolumeUP = true;
            }
        }
        audio.setVolume(volume);
        Serial.print("Volume ");
        Serial.println(volume);
    }

    LastStateVolButon = CurrentStateVolButton;
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