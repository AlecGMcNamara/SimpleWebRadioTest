#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"

#include "SPIFFS.h"

#define I2S_DOUT     27
#define I2S_BCLK     26
#define I2S_LRC      25
Audio audio;

String ssid =    "SKYPEMHG";
String password = "8NHetSWQAJ75";
void setup() {
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  Serial.println("Starting WiFi");
  WiFi.begin(ssid.c_str(), password.c_str());
  while (WiFi.status() != WL_CONNECTED)
  delay(1500);
  Serial.println("WiFi Connected!");

// Launch SPIFFS file system  
//  if(!SPIFFS.begin()){ 
//    Serial.println("An Error has occurred while mounting SPIFFS");  
//  }
  //File file = SPIFFS.open("/test.mp3"); 
  //if(!file){ 
  //  Serial.println("Failed to open file for reading"); 
  //return; 
  //} 
  //Serial.print("File size: "); 
  //Serial.println(file.size()); 
  //file.close();

  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(5);
  
  //audio.connecttoFS(SPIFFS,"/test.mp3" );

//  audio.connecttohost("smb://192.168.0.9/Portable/test.mp3");

  audio.connecttohost("vis.media-ice.musicradio.com/CapitalMP3");

//  audio.connecttohost("http://0n-80s.radionetz.de:8000/0n-70s.mp3");
//  audio.connecttohost("http://mediaserv30.live-streams.nl:8000/stream");
//  audio.connecttohost("http://www.surfmusic.de/m3u/100-5-das-hitradio,4529.m3u");
//  audio.connecttohost("http://stream.1a-webradio.de/deutsch/mp3-128/vtuner-1a");
//  audio.connecttohost("http://mp3.ffh.de/radioffh/hqlivestream.aac");


}
void loop()
{
  audio.loop();
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
    //delay(1000);
    //audio.connecttoFS(SPIFFS,"/test.mp3" );
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