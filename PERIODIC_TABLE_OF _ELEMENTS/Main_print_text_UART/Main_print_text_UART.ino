
#include <SPI.h>
#include <TFT_eSPI.h> 
#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"
#include "Free_Fonts.h"
#include "Text.h"
#include "Sound_off.h"
#include "Sound_on.h"
#include "Logo.h"


#define TFT_GREY 0x5AEB 
#define RX_PIN 21
#define TX_PIN 22

TFT_eSPI tft = TFT_eSPI();
SoftwareSerial mySerial(RX_PIN, TX_PIN);

#define FPSerial softSerial

static const uint8_t PIN_MP3_TX = 26; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 27; // Connects to module's TX 

SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
DFRobotDFPlayerMini player;
int key = 0;
int previousKey = 0;

byte name = 0;
byte properties = 0;
bool active = false;
void connectDFpalyer(){
  softwareSerial.begin(9600);
  if (player.begin(softwareSerial)) {
    Serial.println("OK");
    player.volume(25);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }

}
void setup(void) {
  Serial.begin(115200);
  tft.init();
  tft.setRotation(3);
  mySerial.begin(115200);
  connectDFpalyer();
  tft.fillScreen(0x0000);
  tft.pushImage(0, 0, logoWidth, logoHeight, logo);
  
}
void clearScreen() {
  tft.fillScreen(0x0000);
}
void info(int value){
  if(value == 129){
    active = true;
    if(++name >= 3){
      name = 1;
    }
    if(name != 0){
      properties = 0;
    }
    clearScreen();
    if(name == 1){
      tft.setTextColor(TFT_ORANGE,TFT_BLACK);
      tft.setFreeFont(FF27);
      tft.drawString("Mode 1: Element name", 0, 40, GFXFF);
      tft.fontHeight(GFXFF);
      tft.pushImage(200, 150, textWidth, textHeight, text);
      tft.setFreeFont(FF18);
      tft.drawString("Display text", 180, 260, GFXFF);
      tft.fontHeight(GFXFF);
    }
    if(name == 2){
      tft.setTextColor(TFT_ORANGE,TFT_BLACK);
      tft.setFreeFont(FF27);
      tft.drawString("Mode 1: Element name", 0, 40, GFXFF);
      tft.fontHeight(GFXFF);
      tft.pushImage(120, 150, textWidth, textHeight, text);
      tft.setFreeFont(FF24);
      tft.drawString("+", 225, 165, GFXFF);
      tft.fontHeight(GFXFF);
      tft.pushImage(280, 150, sound_onWidth, sound_onHeight, sound_on);
      tft.setFreeFont(FF18);
      tft.drawString("Display text + Sound playback", 80, 260, GFXFF);
      tft.fontHeight(GFXFF);
    }
  }
  if( value == 130){
    active = true;
    if(++properties >= 3){
      properties = 1;
    }
    if(properties != 0){
      name = 0;
    }
     clearScreen();
    if(properties == 1){
      tft.setTextColor(0x09f203,TFT_BLACK);
      tft.setFreeFont(FF27);
      tft.drawString("Mode 2: Element properties", 0, 40, GFXFF);
      tft.fontHeight(GFXFF);
      tft.pushImage(200, 150, textWidth, textHeight, text);
      tft.setFreeFont(FF18);
      tft.drawString("Display text", 180, 260, GFXFF);
      tft.fontHeight(GFXFF);
    }
    if (properties >= 2) {
      tft.setTextColor(0x09f203,TFT_BLACK);
      tft.setFreeFont(FF27);
      tft.drawString("Mode 2: Element properties", 0, 40, GFXFF);
      tft.fontHeight(GFXFF);
      tft.pushImage(120, 150, textWidth, textHeight, text);
      tft.setFreeFont(FF24);
      tft.drawString("+", 225, 165, GFXFF);
      tft.fontHeight(GFXFF);
      tft.pushImage(280, 150, sound_onWidth, sound_onHeight, sound_on);
      tft.setFreeFont(FF18);
      tft.drawString("Display text + Sound playback", 80, 260, GFXFF);
      tft.fontHeight(GFXFF);
    }
  }
  if (active){
    if (value>=1 &&  value <= 118){
      clearScreen();
      switch(value){
        case 1:
            if(name >= 1){
            if(name == 2){
              player.playMp3Folder(119);
              Serial.println("OK");
            }
            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Hydrogen", 240, 10, GFXFF);
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: H", 10, 120, GFXFF);
            tft.drawString("Chemical name: Hidrogen", 10, 180, GFXFF);
            tft.drawString("Chemical group: Nonmetal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(1);
              Serial.println("OK");   
            }

            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("1   1.0078");

            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setCursor(35, 35);
            tft.setTextSize(3); 
            tft.println("H");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Hydro");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 1.0078 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 13.99 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 20.28 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1766");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- The Hydrogen atom is the simplest atom in the periodic table, consisting of only one proton and one electron, with an atomic number of 1.");
            tft.setCursor(4, 172);
            tft.println("- Under standard conditions, it exists as a diatomic gas, H2.");
            tft.setCursor(4, 188);
            tft.println("- Hydrogen is colorless, odorless, tasteless, and highly flammable.");
            tft.setCursor(4, 204);
            tft.println("- Its main chemical property is the ability to form hydrogen bonds, which  are essential components of water and organic compounds.");
            tft.setCursor(4, 236);
            tft.println("- Hydrogen also has a high heat of vaporization, making it useful as a rawmaterial in the production of many chemical products as well as in the      energy industry.");
          }
          break;
        case 2:
            if(name >= 1){
            if(name == 2){
                player.playMp3Folder(120);
              Serial.println("OK");
            }
            tft.setTextColor(0xC0E9EF,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Helium", 240, 10, GFXFF); // Thay đổi từ "Hydrogen" thành "Helium"
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: He", 10, 120, GFXFF); // Thay đổi từ "H" thành "He"
            tft.drawString("Chemical name: Helium", 10, 180, GFXFF); // Thay đổi từ "Hidrogen" thành "Helium"
            tft.drawString("Chemical group: Noble Gas", 10, 240, GFXFF); // Thay đổi từ "Nonmetal" thành "Noble gas"
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(2);
              Serial.println("OK");   
            }
            player.playMp3Folder(2);
            //tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("2   4.0026");

            tft.setTextColor(0xC0E9EF,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("He");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Heli");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 4.0026 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: ..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 4.22 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1868");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Helium is a colorless, odorless, and tasteless noble gas. It is the second  lightest and second most abundant element in the universe after hydrogen. Helium remains liquid at extremely low temperatures and only solidifies       under pressure.");
            tft.setCursor(4, 204);
            tft.println("- Helium is chemically inert, meaning it does not readily form compounds   with other elements. It has a complete valence shell, consisting of two      electrons, making it stable and unreactive.");
            tft.setCursor(4,252);
            tft.println("- Helium is widely used in cryogenics, as it remains liquid at very low      temperatures, making it essential for cooling superconducting magnets in MRI machines and particle accelerators. It is also used in gas chromatography,helium-neon lasers, and as a lifting gas in balloons and airships.");
          }
          break;
        case 3:
            if (name >= 1) {
            if (name == 2) { // Nếu chất là Lithium
              player.playMp3Folder(121);
              Serial.println("OK");
            }
            tft.setTextColor(0x050e, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Lithium", 240, 10, GFXFF); // Hiển thị tên Lithium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Li", 10, 120, GFXFF); // Hiển thị ký hiệu hóa học của Lithium
            tft.drawString("Chemical name: Lithium", 10, 180, GFXFF); // Hiển thị tên Lithium
            tft.drawString("Chemical group: Alkali Metal", 10, 240, GFXFF); // Hiển thị nhóm chất của Lithium
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(3);
              Serial.println("OK");   
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("3   6.9410");

            tft.setTextColor(0x050e,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Li");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Lithi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 6.9410 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:453.69 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:1615.15K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1817");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Lithium is a soft, silver-white alkali metal. It's the lightest solid element  and highly reactive. It tarnishes quickly in air, forming a black coating of  lithium oxide. Lithium readily forms compounds, crucially in rechargeable    batteries and medication.");
            tft.setCursor(4, 204);
            tft.println("- Lithium reacts vigorously with water, producing hydrogen gas and lithium hydroxide. It's used in mood stabilizers for mental health conditions like    bipolar disorder. Its applications extend to greases, ceramics, and air       treatment systems.");
            tft.setCursor(4,268);
            tft.println("- Lithium's unique properties contribute to its widespread use in energy    storage, pharmaceuticals, and industrial processes, highlighting its           significance in modern technology and healthcare.");
          }
          break;
        case 4:
            if (name >= 1) {
            if (name == 2) { // Nếu chất là Beryllium
              player.playMp3Folder(122);
              Serial.println("OK");
            }
            tft.setTextColor(0xf980, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Beryllium", 240, 10, GFXFF); // Hiển thị tên Beryllium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Be", 10, 120, GFXFF); // Hiển thị ký hiệu hóa học của Beryllium
            tft.drawString("Chemical name: Beryllium", 10, 180, GFXFF); // Hiển thị tên Beryllium
            tft.drawString("Chemical group: Alkaline Earth Metal", 10, 240, GFXFF); // Hiển thị nhóm chất của Beryllium
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(4);
              Serial.println("OK");   
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("4  9.0122");

            tft.setTextColor(0xf980,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Be");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Beryli");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 9.0122 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1560 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2742.1K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1797");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Beryllium is a lightweight, steel-gray alkaline earth metal. It is highly     toxic when inhaled and has a low melting point. Beryllium has a high        stiffness-to-weight ratio, making it ideal for structural applications in      aerospace and automotive industries.");
            tft.setCursor(4, 204);
            tft.println("- Beryllium readily forms compounds with nonmetals, but it does not react  with water or steam at normal temperatures. It exhibits amphoteric behavior, acting as both an acid and a base. Beryllium compounds are used in       ceramics, electronics, and nuclear reactors.");
            tft.setCursor(4,268);
            tft.println("- Beryllium's lightweight and high strength make it valuable in aerospace   components, such as satellite structures and missile parts. Its unique        properties also find use in X-ray windows.");
          }
          break;
        case 5:
            if (name >= 1) {
          if (name == 2) { // Nếu chất là Boron
              player.playMp3Folder(123);
              Serial.println("OK");
          }
          tft.setTextColor(0xa340, TFT_BLACK);
          tft.setFreeFont(FF32);
          tft.setTextDatum(TC_DATUM);
          tft.drawString("Boron", 240, 10, GFXFF); // Hiển thị tên Boron
          tft.setTextDatum(L_BASELINE);
          tft.setTextColor(0xFFFF, TFT_BLACK);
          tft.setFreeFont(FF18);
          tft.drawString("Chemical symbol: B", 10, 120, GFXFF); // Hiển thị ký hiệu hóa học của Boron
          tft.drawString("Chemical name: Boron", 10, 180, GFXFF); // Hiển thị tên Boron
          tft.drawString("Chemical group: Metalloid", 10, 240, GFXFF); // Hiển thị nhóm chất của Boron
          tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(5);
              Serial.println("OK");   
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("5  10.811");

            tft.setTextColor(0xa340,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("B");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Bor");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 10.811 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:2349.1K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:4273.15K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1808");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Boron is a metalloid with properties intermediate between those of       metalsand nonmetals. It exists in various allotropes including amorphous andcrystalline forms. Boron is lightweight and has a high melting point, making it useful in structural materials.");
            tft.setCursor(4, 204);
            tft.println("- Boron forms compounds with various elements, exhibiting a wide range   ofoxidation states. It acts as a Lewis acid in many reactions and can form  complex compounds with organic molecules. Boron compounds find         applications in agriculture, materials science, and medicine.");
            tft.setCursor(4,268);
            tft.println("- Boron fibers are used in aerospace applications for their high strength  to-weight ratio. Boron compounds are also utilized in glass manufacturing  for enhancing thermal and mechanical properties.");
          }
          break;
        case 6:
            if (name >= 1) {
            if (name == 2) { // Nếu chất là Carbon
              player.playMp3Folder(124);
              Serial.println("OK");
            }
            tft.setTextColor(0x081a, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Carbon", 240, 10, GFXFF); // Hiển thị tên Carbon
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: C", 10, 120, GFXFF); // Hiển thị ký hiệu hóa học của Carbon
            tft.drawString("Chemical name: Carbon", 10, 180, GFXFF); // Hiển thị tên Carbon
            tft.drawString("Chemical group: Nonmetal", 10, 240, GFXFF); // Hiển thị nhóm chất của Carbon
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(6);
              Serial.println("OK");   
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("6  10.811");

            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("C");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Cacbon");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 10.811 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:2349.1K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:4273.15K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1808");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Carbon is a nonmetal with diverse allotropes, including graphite, diamond,and fullerenes. It forms strong covalent bonds, resulting in materials with  varying properties from soft and lubricating to hard and abrasive.");
            tft.setCursor(4, 188);
            tft.println("- Carbon readily forms compounds with numerous elements, exhibiting both organic and inorganic chemistry. It forms the basis of all known life forms and is essential for organic chemistry. Carbon compounds are involved in  various industrial processes, from fuel production to pharmaceutical        synthesis.");
            tft.setCursor(4,268);
            tft.println("- Carbon's versatility spans various industries, utilized in structural        materials like carbon fiber composites, energy storage systems such as      batteries and supercapacitors, and as a catalyst in chemical reactions.");
          }
          break;
        case 7:
            if(name >= 1){
            if(name == 2){
              player.playMp3Folder(125);
              Serial.println("OK");
            }
            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Nitrogen", 240, 10, GFXFF); // Thay đổi từ "Hydrogen" thành "Nitrogen"
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: N", 10, 120, GFXFF); // Thay đổi thông tin về ký hiệu hóa học
            tft.drawString("Chemical name: Nitrogen", 10, 180, GFXFF); // Thay đổi thông tin về tên hóa học
            tft.drawString("Chemical group: Nonmetal", 10, 240, GFXFF); // Thay đổi thông tin về nhóm hóa học
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(7);
              Serial.println("OK");   
            }

            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("7  14.007");

            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("N");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Nito");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 17.007 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 63.14 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 77.36 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1772");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Nitrogen is a colorless, odorless gas that makes up about 78% of Earth'satmosphere. It exists as diatomic molecules N2 and is relatively inert       undernormal conditions. Nitrogen is essential for life and is a crucial     component of proteins and nucleic acids.");
            tft.setCursor(4, 204);
            tft.println("- Nitrogen forms diverse compounds like ammonia, nitric acid, and organic nitrates, exhibiting multiple oxidation states. It plays a pivotal role in the  nitrogen cycle, crucial for ecosystem balance. Bacteria perform nitrogen   fixation, converting atmospheric nitrogen into plant-usable forms.");
            tft.setCursor(4,268);
            tft.println("- Nitrogen is crucial for preventing oxidation in food packaging, boosting crop yields in fertilizer production, and preserving biological samples in   cryogenics.");
          }
          break;
        case 8:
            if(name >= 1){
            if(name == 2){
              player.playMp3Folder(126);
              Serial.println("OK");
            }
            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Oxygen", 240, 10, GFXFF); // Thay đổi từ "Nitrogen" thành "Oxygen" cho chất thứ 8
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: O", 10, 120, GFXFF); // Thay đổi thông tin về ký hiệu hóa học
            tft.drawString("Chemical name: Oxygen", 10, 180, GFXFF); // Thay đổi thông tin về tên hóa học
            tft.drawString("Chemical group: Nonmetal", 10, 240, GFXFF); // Thay đổi thông tin về nhóm hóa học
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(8);
              Serial.println("OK");   
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("8  15.999");

            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("O");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Oxy");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 15.999 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 54.36 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 90.19 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1774");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Oxygen is a colorless, odorless gas that is essential for life. It exists asdiatomic molecules (O2) and is a highly reactive element. Oxygen supports combustion and is vital for respiration in living organisms.");
            tft.setCursor(4, 188);
            tft.println("- Oxygen readily forms compounds with most elements, including oxides, peroxides, and oxyacids. It plays a crucial role in oxidation-reduction reactions and is a key component of various organic and inorganic compounds. Oxygen is also involved in the formation of ozone in the Earth's atmosphere.");
            tft.setCursor(4,252);
            tft.println("- Oxygen is used extensively in various industries, including steelmaking,   healthcare, and aerospace. In steel production, oxygen is used to enhance  combustion in furnaces, improving efficiency and reducing emissions. In     healthcare, oxygen therapy is vital for patients with respiratory conditions.");
          }
          break;
        case 9:
            if(name >= 1){
            if(name == 2){
              player.playMp3Folder(127);
              Serial.println("OK");
            }
            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Fluorine", 240, 10, GFXFF); // Chất thứ 9: Fluorine
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: F", 10, 120, GFXFF);
            tft.drawString("Chemical name: Fluorine", 10, 180, GFXFF);
            tft.drawString("Chemical group: Nonmetal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(9);
              Serial.println("OK");   
            }

            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("9  18.998");

            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("F");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Fluor");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 18.998 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 53.53 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 85.94 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1886");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Fluorine is a pale yellow-green gas at room temperature. It is highly     reactive, forming compounds with almost all other elements. Fluorine is the most electronegative element, making its compounds often highly reactive   and used in various industrial processes.");
            tft.setCursor(4, 204);
            tft.println("- Fluorine is extremely reactive, readily forming compounds with metals,    nonmetals, and even noble gases. It is used in the production of numerous  chemicals, including fluorocarbons, which are used as refrigerants and      propellants, and in the synthesis of pharmaceuticals and agrochemicals.");
            tft.setCursor(4,268);
            tft.println("- Fluorine's applications span pharmaceuticals, agriculture, and electronics. It's essential in dental care for cavity prevention, as well as in high       temperature plastics and semiconductor manufacturing.");
          }
          break;
        case 10:
            if(name >= 1){
            if(name == 2){
              player.playMp3Folder(128);
              Serial.println("OK");
            }
            tft.setTextColor(0xC0E9EF,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Neon", 240, 10, GFXFF); // Chất thứ 10: Neon
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ne", 10, 120, GFXFF);
            tft.drawString("Chemical name: Neon", 10, 180, GFXFF);
            tft.drawString("Chemical group: Noble Gas", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(10);
              Serial.println("OK");   
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("10  20.180");

            tft.setTextColor(0xC0E9EF,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Ne");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Neon");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 20.180 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 24.56 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 27.1 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1898");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Neon is a colorless, odorless noble gas. It is inert, meaning it does not  readily form chemical compounds. Neon emits a bright red-orange light whenelectricity passes through it, making it valuable in lighting applications and advertising signs.");
            tft.setCursor(4, 204);
            tft.println("- Neon is highly stable and doesn't react with other elements under normal conditions. It has a complete valence shell, making it unreactive. This      inertness makes neon suitable for use in vacuum tubes, indicator lights, andhigh-voltage surge arresters.");
            tft.setCursor(4,268);
            tft.println("- Neon is popular for its bright glow in lighting applications like neon     signs, plasma displays, and lamps. It's also used in cryogenics for low       temperatures and in calibrating instruments such as vacuum gauges.");
          }
          break;
        case 11:
            if(name >= 1){
            if(name == 2){
              player.playMp3Folder(129);
              Serial.println("OK");
            }
            tft.setTextColor(0x050e,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Sodium", 240, 10, GFXFF); // Chất thứ 11: Sodium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Na", 10, 120, GFXFF);
            tft.drawString("Chemical name: Sodium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Alkali Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(11);
              Serial.println("OK");   
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("11  22.990");

            tft.setTextColor(0x050e,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Na");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Natri");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 22.990 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:370.94 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:1156 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1807");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Sodium is a soft, silvery-white alkali metal. It's  highly reactive, often stored in oil to prevent oxidation. Sodium is abundant in nature, primarily found in compounds like halite and soda ash.");
            tft.setCursor(4, 188);
            tft.println("- Sodium readily forms compounds, particularly with halogens, exhibiting    diverse oxidation states. It's crucial in various chemical processes and     biological functions, such as nerve signal transmission and maintaining fluidbalance.");
            tft.setCursor(4, 252);
            tft.println("- Sodium has numerous applications, notably in the production of chemicals, detergents, and pharmaceuticals. It's also essential in metallurgy for       refining metals and in food preservation as sodium chloride (table salt).");
          }
          break;
        case 12:
            if(name >= 1){
            if(name == 2){
              player.playMp3Folder(130); // Phát âm thanh cho chất thứ 12
              Serial.println("OK");
            }
            tft.setTextColor(0xf980,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Magnesium", 240, 10, GFXFF); // Chất thứ 12: Magnesium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Mg", 10, 120, GFXFF);
            tft.drawString("Chemical name: Magnesium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Alkaline Earth Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(12);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("12  24.305");

            tft.setTextColor(0xf980,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Mg");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 110);
            tft.setTextSize(1); 
            tft.println("Magnesi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 24.305 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:923.15K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:1364.15K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1755");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Magnesium is a lightweight, silvery-white metal. It has an excellent        strength-to-weight ratio and is abundant in the Earth's crust. Its propertiesmake it suitable for structural alloys, particularly in aerospace and         automotive applications.");
            tft.setCursor(4, 204);
            tft.println("- Magnesium is highly flammable in its pure form, burning with a brilliant   white flame. It readily reacts with oxygen to form magnesium oxide and withwater to form magnesium hydroxide. Additionally, it reacts with acids to    produce magnesium salts.");
            tft.setCursor(4, 268);
            tft.println("- Magnesium is widely used in various fields for its lightweight and strong properties in structural materials, flammability in pyrotechnics and flares,   and essential compounds in medicine, agriculture, and manufacturing.");
          }
          
          break;
        case 13:
          if(name >= 1){
            if(name == 2){
              player.playMp3Folder(131); // Phát âm thanh cho chất thứ 12
              Serial.println("OK");
            }
            tft.setTextColor(0x8A2BE2,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Aluminum", 240, 10, GFXFF); // Chất thứ 13: Aluminum
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Al", 10, 120, GFXFF);
            tft.drawString("Chemical name: Aluminum", 10, 180, GFXFF);
            tft.drawString("Chemical group: Post-Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(13);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("13  26.982");

            tft.setTextColor(0x8A2BE2,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Al");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(10, 100);
            tft.setTextSize(1); 
            tft.println("Aluminum");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 26.982 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 933.47 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2743.1 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1825");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Aluminum is a lightweight silver-white metal. It's one of the most abundant elements in the Earth's crust. Aluminum exhibits corrosion resistance and  ductility, and it has good electrical and thermal conductivity.");
            tft.setCursor(4,188);
            tft.println("- Aluminum does not react with air at room temperature due to its surface being protected by a stable oxide layer. However, it can react with strong acids and bases to form aluminum salts.");
            tft.setCursor(4, 236);
            tft.println("- Aluminum finds widespread applications, from food packaging to           aerospace and space industries. It's used in the manufacturing of householdappliances, automobiles, and building structures due to its lightness and     strength.");
          }
            break;
        case 14:
          if(name >= 1){
            if(name == 2){
              player.playMp3Folder(132); // Phát âm thanh cho chất thứ 13
              Serial.println("OK");
            }
            tft.setTextColor(0xa340,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Silicon", 240, 10, GFXFF); // Chất thứ 14: Silicon
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Si", 10, 120, GFXFF);
            tft.drawString("Chemical name: Silicon", 10, 180, GFXFF);
            tft.drawString("Chemical group: Metalloid", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(14);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("14   28.086");

            tft.setTextColor(0xa340,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Si");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Silic");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 28.0855 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1687 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3538 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1823");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Silicon is a crystalline, grayish-brown metalloid. It's abundant in the     Earth's crust and possesses a shiny, metallic luster. Silicon is a             semiconductor with a high melting point and is brittle in its crystalline form");
            tft.setCursor(4, 188);
            tft.println("- Silicon is relatively unreactive at room temperature, forming a           protective oxide layer on its surface. However, it can react with halogens and strong alkalis. Silicon compounds are vital in various industries, such  as electronics, construction, and solar energy.");
            tft.setCursor(4, 252);
            tft.println("- Silicon's primary application lies in the semiconductor industry, where it serves as the backbone of electronic deviceslike microchips and solar cells. It is also used in building materials, such as silicones and glass, due to itsheat resistance and durability.");
          }
          break;
        case 15:
          if(name >= 1){
            if(name == 2){
              player.playMp3Folder(133); // Phát âm thanh cho chất thứ 15
              Serial.println("OK");
            }
            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Phosphorus", 240, 10, GFXFF); // Chất thứ 15: Phosphorus
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: P", 10, 120, GFXFF);
            tft.drawString("Chemical name: Phosphorus", 10, 180, GFXFF);
            tft.drawString("Chemical group: Nonmetal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }

          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(15);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("15  30.974");

            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setCursor(40, 35);
            tft.setTextSize(3); 
            tft.println("P");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(15, 100);
            tft.setTextSize(1); 
            tft.println("Phosphor");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 30.974 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 317.25 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 553.65 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1669");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Phosphorus, exists in several allotropic forms, including white, red, and  black phosphorus. It is a highly reactive non-metal with a pale-yellow coloranda waxy texture. Phosphorus is essential for life and is commonly found in nature in the form of phosphates.");
            tft.setCursor(4,204);
            tft.println("- Phosphorus readily combines with other elements to form various        compounds, including phosphides, phosphates, and phosphorus oxyacids. It   undergoes combustion in air, producing phosphorus oxides. Phosphorus      compounds have applications in agriculture, industry, and medicine.");
            tft.setCursor(4,268);
            tft.println("- Phosphorus compounds are widely used as fertilizers in agriculture to enhance plant growth. They are also employed in detergents, flame retardantsand in the production of matches and fireworks.");
          }
            break;
        case 16:
          if(name >= 1){
            if(name == 2){
              player.playMp3Folder(134); // Phát âm thanh cho chất thứ 16
              Serial.println("OK");
            }
            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Sulfur", 240, 10, GFXFF); // Chất thứ 16: Sulfur
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: S", 10, 120, GFXFF);
            tft.drawString("Chemical name: Sulfur", 10, 180, GFXFF);
            tft.drawString("Chemical group: Nonmetal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(16);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("16  32.065");

            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setCursor(40, 35);
            tft.setTextSize(3); 
            tft.println("S");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Sulfur");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 32.065 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 385.95 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 717.75 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: ...");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Sulfur, is a yellow, brittle solid at room temperature. It exhibits various allotropes, including rhombic and monoclinic sulfur. Sulfur is insoluble in   water but soluble in organic solvents. It has a distinct odor and is often   associated with volcanic activity.");
            tft.setCursor(4,204);
            tft.println("- Sulfur is a highly reactive non-metal, readily combining with many        elements. It forms sulfides, sulfates, and sulfuric acid. Sulfur compounds   are vital in various industrial processes, including the production of       fertilizers, detergents, and rubber. ");
            tft.setCursor(4,268);
            tft.println("- Sulfur is widely used in agriculture as a fertilizer to improve soil fertility and in the production of sulfuric acid, essential for various industrial   applications like battery manufacturing, explosives, and chemical production.");
          }
            break;
        case 17:
          if(name >= 1){
            if(name == 2){
              player.playMp3Folder(135); // Phát âm thanh cho chất thứ 17
              Serial.println("OK");
            }
            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Chlorine", 240, 10, GFXFF); // Chất thứ 17: Chlorine
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Cl", 10, 120, GFXFF);
            tft.drawString("Chemical name: Chlorine", 10, 180, GFXFF);
            tft.drawString("Chemical group: Nonmetal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(17);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("17  35.453");

            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Cl");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Chlorine");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 35.453 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 171.65 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 239.11 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1774");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Chlorine, is a greenish-yellow gas at room temperature. It is highly        reactive and toxic, with a pungent odor. Chlorine is denser than air and is soluble in water, forming hydrochloric acid when dissolved.");
            tft.setCursor(4,188);
            tft.println("- Chlorine readily reacts with metals to form chlorides and with hydrogen  to form hydrogen chloride. It is a powerful oxidizing agent and can react  explosively with certain organic compounds. Chlorine compounds are used inwater treatment, disinfectants, and the production of plastics.");
            tft.setCursor(4,252);
            tft.println("- Chlorine is widely used in the purification of drinking water and swimming pools due to its disinfectant properties. It is also employed in the         manufacturing of PVC (polyvinyl chloride), solvents, and pesticides.");
          }
            break;
        case 18:
          if(name >= 1){
            if(name == 2){
              player.playMp3Folder(136); // Phát âm thanh cho chất thứ 18
              Serial.println("OK");
            }
            tft.setTextColor(0xC0E9EF,TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Argon", 240, 10, GFXFF); // Chất thứ 18: Argon
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF,TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ar", 10, 120, GFXFF);
            tft.drawString("Chemical name: Argon", 10, 180, GFXFF);
            tft.drawString("Chemical group: Noble Gas", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(18);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("18  39.948");

            tft.setTextColor(0xC0E9EF,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Ar");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Argon");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 39.948 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 83.8 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 87.3 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1774");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Argon is a colorless, odorless, and inert gas at room temperature. It is  the third-most abundant gas in the Earth's atmosphere. Argon is denser thanair and is non-reactive under normal conditions.");
            tft.setCursor(4,188);
            tft.println("- Argon is classified as a noble gas and does not readily form compounds with other elements due to its stable electronic configuration. It is chemically inert and does not undergo chemical reactions under typical conditions.");
            tft.setCursor(4,236);
            tft.println("- Argon is widely used in various applications, including welding, lighting,  and the production of semiconductor devices. It is utilized as a shielding  gas in welding to protect the weld area from atmospheric contamination.    Argon is also employed in gas-discharge lamps for its ability to produce a stable glow.");
          }
            break;
        case 19:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(137); // Phát âm thanh cho chất thứ 19
              Serial.println("OK");
            }
            tft.setTextColor(0x050e, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Potassium", 240, 10, GFXFF); // Chất thứ 19: Potassium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: K", 10, 120, GFXFF);
            tft.drawString("Chemical name: Potassium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Alkali Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(19);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("19   39.098");

            tft.setTextColor(0x050e,TFT_BLACK);
            tft.setCursor(40, 35);
            tft.setTextSize(3); 
            tft.println("K");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(45, 100);
            tft.setTextSize(1); 
            tft.println("Kali");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 39.0983 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 336.7 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1032 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1807");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Potassium is a soft, silvery-white metal at room temperature. It is highly reactive, easily oxidizing in air. Potassium is less dense than water and     floats on its surface. It has a low melting point and is a good conductor   of electricity.");
            tft.setCursor(4, 204);
            tft.println("- Potassium is a highly reactive alkali metal, readily forming compounds    with other elements. It reacts vigorously with water, producing hydrogen   gas and forming potassium hydroxide. Potassium compounds are essential in various industrial processes and in agriculture as fertilizers.");
            tft.setCursor(4, 268);
            tft.println("- Potassium compounds are used in agriculture as fertilizers to promote   plant growth. Potassium metal is used in specialized applications, including    certain types of batteries and chemical production.");
          }
          break;
        case 20:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(138); // Phát âm thanh cho chất thứ 20
              Serial.println("OK");
            }
            tft.setTextColor(0xf980, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Calcium", 240, 10, GFXFF); // Chất thứ 20: Calcium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ca", 10, 120, GFXFF);
            tft.drawString("Chemical name: Calcium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Alkaline Earth Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(20);            
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("20   40.078");

            tft.setTextColor(0xf980,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Ca");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Calci");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 40.078 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1115 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1757 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Calcium is a soft, gray alkaline earth metal. It is the fifth-most abundant element in the Earth's crust. Calcium has a silvery-white appearance when  freshly cut, but it quickly oxidizes in air to form a dull gray surface layer.");
            tft.setCursor(4, 188);
            tft.println("- Calcium is highly reactive, especially with water, producing hydrogen gas and forming calcium hydroxide. It readily forms compounds with other       elements, such as calcium carbonate (found in limestone) and calcium       phosphate (a component of bones and teeth).");
            tft.setCursor(4, 252);
            tft.println("- Calcium is vital for biological processes like bone formation, muscle     contraction, and nerve signaling. It's also widely used in construction      (limestone and cement), metallurgy, and agriculture (soil conditioner and   fertilizer).");
          }
          break;
        case 21:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(139); // Phát âm thanh cho chất thứ 21
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Scandium", 240, 10, GFXFF); // Chất thứ 21: Scandium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Sc", 10, 120, GFXFF);
            tft.drawString("Chemical name: Scandium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(21);            
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("21   44.956");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Sc");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Scandi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 44.956 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1814 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3109 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1879");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Scandium is a silvery-white metallic element. It is relatively soft and hasa density similar to aluminum. Scandium is often found in rare earth        minerals and is relatively rare in nature.");
            tft.setCursor(4, 188);
            tft.println("- Scandium is a reactive metal, but it is less reactive than the other       elements in the same group. It forms various compounds, including oxides,  halides, and scandium alloys. Scandium alloys are known for their strength  and lightweight properties.");
            tft.setCursor(4, 252);
            tft.println("- Scandium has applications in aerospace, particularly in the manufacturingof lightweight alloys for aircraft components. It is also used in high       intensity lamps and in the production of certain types of sports equipment due to its strength-to-weight ratio.");
          }
          break;
        case 22:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(140); // Phát âm thanh cho chất thứ 22
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Titanium", 240, 10, GFXFF); // Chất thứ 22: Titanium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ti", 10, 120, GFXFF);
            tft.drawString("Chemical name: Titanium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }

          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(22);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("22   47.867");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(35, 35);
            tft.setTextSize(3); 
            tft.println("Ti");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Titani");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 47.867 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1941 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3560 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1791");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Titanium is a lustrous transition metal with a silver color. It's lightweight, strong, and corrosion-resistant, making it ideal for various industrial      applications. Titanium has a relatively low density and high strength to     weight ratio.");
            tft.setCursor(4, 204);
            tft.println("- Titanium is highly resistant to corrosion by sea water, aqua regia, and   chlorine. It forms a protective oxide layer when exposed to air, giving it   excellent corrosion resistance. Titanium can also form various compounds, including oxides, halides, and alloys.");
            tft.setCursor(4, 268);
            tft.println("- Titanium's strength and corrosion resistance make it a go-to material in  aerospace, automotive, and medical fields, used in aircraft parts, implants,  and sports gear.");
          }
          break;
        case 23:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(141); // Phát âm thanh cho chất thứ 23
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Vanadium", 240, 10, GFXFF); // Chất thứ 23: Vanadium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: V", 10, 120, GFXFF);
            tft.drawString("Chemical name: Vanadium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(23);           
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("23   50.942");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(45, 35);
            tft.setTextSize(3); 
            tft.println("V");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Vanadi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 50.942 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 2183 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3680 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1801");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Vanadium is a shiny, silvery-grey transition metal. It is relatively hard,   ductile, and has good resistance to corrosion. Vanadium exhibits several   oxidation states, with vanadium(II) and vanadium(V) being the most common.");
            tft.setCursor(4, 188);
            tft.println("- Vanadium reacts with oxygen, nitrogen, sulfur, and carbon at elevated    temperatures. It forms various oxides, such as vanadium dioxide and        vanadium pentoxide, which have applications in ceramics and catalysts.      Vanadium compounds are also used in the production of steel alloys.");
            tft.setCursor(4,252);
            tft.println("- Vanadium is key in steel production, enhancing strength and corrosion   resistance. Its alloys are found in tools, springs, and surgical instruments.  Vanadium compounds serve diverse roles in ceramics, catalysts, and the     chemical industry.");
          }
          break;
        case 24:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(142); // Phát âm thanh cho chất thứ 24
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Chromium", 240, 10, GFXFF); // Chất thứ 24: Chromium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Cr", 10, 120, GFXFF);
            tft.drawString("Chemical name: Chromium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }

          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(24);            
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("24   51.996");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Cr");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Crom");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 51.996 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 2180 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2944 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Chromium, with atomic number 24, is a hard, lustrous, steel-gray metal. It has a high melting point and is corrosion-resistant. Chromium is often used as a decorative coating due to its shiny appearance. It is also known for  its hardness and durability.");
            tft.setCursor(4, 204);
            tft.println("- Chromium exhibits multiple oxidation states, with chromium(III) and        chromium(VI) being the most stable. Chromium is used in various compounds,including chromates and dichromates, which are important in the productionof pigments, metal finishing, and corrosion protection.");
            tft.setCursor(4, 268);
            tft.println("- Chromium is crucial in metallurgy for stainless steel, providing corrosionresistance. It's also used in automotive plating and for wood preservation and leather tanning through its compounds.");
          }
          break;
        case 25:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(143); // Phát âm thanh cho chất thứ 25
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Manganese", 240, 10, GFXFF); // Chất thứ 25: Manganese
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Mn", 10, 120, GFXFF);
            tft.drawString("Chemical name: Manganese", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(25);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("25   54.938");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Mn");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Mangan");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 54.938 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1519 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2334 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1774");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Manganese is a silvery-gray metal that resembles iron. It is hard and    brittle and has a relatively high melting point. Manganese is essential in    steelmaking as a deoxidizing agent and as an alloying element to improve   strength and hardness.");
            tft.setCursor(4, 204);
            tft.println("- Manganese exhibits multiple oxidation states, with manganese(II) and      manganese(IV) being the most common. It forms various compounds,         including oxides, sulfides, and halides. Manganese compounds are used in   batteries, pigments, and fertilizers.");
            tft.setCursor(4, 268);
            tft.println("- Manganese enhances the mechanical properties of steel and cast iron,    and it's used in non-ferrous alloys like aluminum alloys. Manganese dioxide  powers dry-cell batteries, and manganese sulfate enriches fertilizers.");
          }
          break;
        case 26:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(144); // Phát âm thanh cho chất thứ 26
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Iron", 240, 10, GFXFF); // Chất thứ 26: Iron
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Fe", 10, 120, GFXFF);
            tft.drawString("Chemical name: Iron", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(26);            
            }
             tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("26   55.845");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Fe");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(45, 100);
            tft.setTextSize(1); 
            tft.println("Iron");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 55.845 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1811 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3134 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Iron, with atomic number 26, is a lustrous, silvery-gray metal. It's ductileand malleable, with a relatively high melting point. Iron is one of the most abundant elements in the Earth's crust and is essential in the construction  of buildings, bridges, and infrastructure.");
            tft.setCursor(4, 204);
            tft.println("- Iron readily forms compounds, particularly oxides, such as iron(II) oxide (ferrous oxide) and iron(III) oxide (ferric oxide). It reacts with oxygen toform rust, a red-brown iron oxide, which weakens the metal. Iron also formsvarious alloys, including steel and cast iron.");
            tft.setCursor(4, 268);
            tft.println("- Iron is essential in construction, manufacturing and transportation, mainly as the key component of steel used in buildings, machinery, and vehicles. Iron alloys are also used in aerospace, automotive, and industrial equipment.");
          }
          break;
        case 27:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(145); // Phát âm thanh cho chất thứ 27
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Cobalt", 240, 10, GFXFF); // Chất thứ 27: Cobalt
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Co", 10, 120, GFXFF);
            tft.drawString("Chemical name: Cobalt", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(27);            
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("27   58.933");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Co");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Coban");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 58.9332 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1768 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3200 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Cobaltis a hard, lustrous, silver-gray metal. It has a high melting point   and retains its magnetic properties at high temperatures. Cobalt is commonlyfound in ores alongside nickel and is often used as a blue pigment in       ceramics and glass.");
            tft.setCursor(4, 204);
            tft.println("- Cobalt exhibits multiple oxidation states, with cobalt(II) and cobalt(III)   being the most prevalent. It forms various compounds, including cobalt oxide and cobalt salts. Cobalt compounds are used in rechargeable batteries,   catalysts, and magnetic materials.");
            tft.setCursor(4, 268);
            tft.println("- Cobalt is crucial in aerospace and medical industries for making alloys   used in jet engines, prosthetic implants, and dental materials. Its compoundsare used in pigments, ceramics, and as catalysts in chemical reactions.");
          }
          break;
        case 28:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(146); // Phát âm thanh cho chất thứ 28
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Nickel", 240, 10, GFXFF); // Chất thứ 28: Nickel
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ni", 10, 120, GFXFF);
            tft.drawString("Chemical name: Nickel", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(28);           
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("28   58.693");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Ni");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Nicken");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 58.693 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1728 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3186 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Nickel is a hard, silvery-white metal. It has a high melting point and is   ductile and malleable. Nickel is magnetic and exhibits good corrosion        resistance. It is commonly used in alloying with other metals to create materials with specific properties.");
            tft.setCursor(4, 204);
            tft.println("- Nickel has multiple oxidation states, with nickel(II) being the most commonIt forms various compounds, including oxides, sulfides, and salts. Nickel     compounds are used in electroplating, catalysts, and pigments.");
            tft.setCursor(4,252);
            tft.println("- Nickel is extensively used in the production of stainless steel and other alloys due to its ability to enhance the strength, corrosion resistance, and temperature resistance of metals. It's used in coins, jewelry, and electronics, as well as in aerospace and chemical industries.");
          }
          break;
        case 29:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(147); // Phát âm thanh cho chất thứ 29
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Copper", 240, 10, GFXFF); // Chất thứ 29: Copper
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Cu", 10, 120, GFXFF);
            tft.drawString("Chemical name: Copper", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(29);            
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("29   63.546");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Cu");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Copper");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 63.546 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1357.7 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2835 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Copper is a reddish-brown metal that is highly ductile and malleable. It   has excellent electrical conductivity and thermal conductivity, making it     valuable in electrical wiring and heat transfer applications. Copper is also corrosion-resistant and has a relatively high melting point.");
            tft.setCursor(4, 204);
            tft.println("- Copper has a single oxidation state, primarily forming copper(I) and     copper(II) compounds. It readily forms a patina when exposed to air, which protects it from further corrosion. Copper compounds are used in          agriculture, fungicides, and pigments.");
            tft.setCursor(4, 268);
            tft.println("- Copper is essential in electrical wiring, plumbing, and electronics for its conductivity. It's also used in architecture, roofing, and decor. Copper     alloys like bronze and brass are used in sculpture, musical instruments.");
          }
          break;
        case 30:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(148); // Phát âm thanh cho chất thứ 30
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Zinc", 240, 10, GFXFF); // Chất thứ 30: Zinc
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Zn", 10, 120, GFXFF);
            tft.drawString("Chemical name: Zinc", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(30);            
            }
             tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("30   65.38");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Zn");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Zinc");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 65.38 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 692.68 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1180 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Zinc is a bluish-white metal that is ductile and malleable at ordinary     temperatures. It has a relatively low melting point and is brittle at room    temperature. Zinc is corrosion-resistant and does not react with air under normal conditions.");
            tft.setCursor(4, 204);
            tft.println("- Zinc primarily forms compounds in the +2 oxidation state. It reacts slowlywith oxygen and water vapor in the atmosphere to form a protective zinc  carbonate layer. Zinc compounds are used in various applications, includinggalvanizing, batteries, and pharmaceuticals.");
            tft.setCursor(4, 268);
            tft.println("- Zinc is mainly used to coat iron and steel for corrosion protection via  galvanization. It's also used in brass and bronze alloys, die-casting, and    making zinc oxide for rubber production and pharmaceuticals.");
          }
          break;
        case 31:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(149); // Phát âm thanh cho chất thứ 31
              Serial.println("OK");
            }
            tft.setTextColor(0x8A2BE2, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Gallium", 240, 10, GFXFF); // Chất thứ 31: Gallium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ga", 10, 120, GFXFF);
            tft.drawString("Chemical name: Gallium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Post-Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(31);           
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("31   69.723");

            tft.setTextColor(0x8A2BE2,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Ga");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Gali");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 69.723 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 302.91 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2673 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1875");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Gallium is a soft, silvery metal with a melting point just above room      temperature. It has a low melting point of 29.76°C (85.57°F), making it      unique among metals. Gallium has a high boiling point and expands slightly  when it freezes, unlike most substances.");
            tft.setCursor(4, 204);
            tft.println("- Gallium reacts slowly with oxygen and water to form gallium oxide and    gallium hydroxide. It exhibits both +1 and +3 oxidation states. Gallium is    notable for its ability to alloy with other metals, which can enhance their  properties.");
            tft.setCursor(4, 268);
            tft.println("- Gallium used in various electronic applications, including semiconductors, LEDs, and solar panels. It's also utilized in medical imaging as gallium scansand in the production of certain types of alloys and compounds.");
          }
          break;
        case 32:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(150); // Phát âm thanh cho chất thứ 32
              Serial.println("OK");
            }
            tft.setTextColor(0xa340, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Germanium", 240, 10, GFXFF); // Chất thứ 32: Germanium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ge", 10, 120, GFXFF);
            tft.drawString("Chemical name: Germanium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Metalloid", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(32);          
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("32   72.630");

            tft.setTextColor(0xa340,TFT_BLACK);
            tft.setCursor(18, 35);
            tft.setTextSize(3); 
            tft.println("Ge");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Germani");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 72.630 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1211 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3093 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1886");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Germanium is a lustrous, hard, grayish-white metalloid. It has a crystallinestructure and is brittle at low temperatures. Germanium is a semiconductor  with electrical properties between those of metals and nonmetals.");
            tft.setCursor(4, 188);
            tft.println("- Germanium doesn't react with oxygen at room temperature but does react with halogens. It forms various compounds, including germanium dioxide and germanium tetrachloride. Germanium can exhibit both +2 and +4 oxidation   states.");
            tft.setCursor(4,252);
            tft.println("- Germanium is primarily used in the production of semiconductors for     electronic devices such as transistors and diodes. It is also used in        infrared optics, fiber optics, and as a catalyst in organic synthesis.");
          }
          break;
        case 33:
              if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(151); // Phát âm thanh cho chất thứ 33
              Serial.println("OK");
            }
            tft.setTextColor(0xa340, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Arsenic", 240, 10, GFXFF); // Chất thứ 33: Arsenic
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: As", 10, 120, GFXFF);
            tft.drawString("Chemical name: Arsenic", 10, 180, GFXFF);
            tft.drawString("Chemical group: Metalloid", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(33);        
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("33   74.922");

            tft.setTextColor(0xa340,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("As");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Arsenic");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 74.922 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1090 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 887 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Arsenicis a brittle, gray metallicloid. It can exist in several allotropes,   with gray arsenic being the most stable form. Arsenic sublimes at           temperatures above 615°C (1139°F).");
            tft.setCursor(4, 188);
            tft.println("- Arsenic is known for its toxicity and can form both inorganic and        organic compounds. It readily combines with metals to form arsenides and  with nonmetals to form oxides and halides. Arsenic compounds have been   historically used in pesticides, herbicides, and medicines.");
            tft.setCursor(4,252);
            tft.println("- Despite its toxicity, arsenic has several industrial applications. It is usedin the production of semiconductors, lead-acid batteries, and wood         preservatives. Arsenic compounds are also used in the production of       certain types of glass and pigments.");
          }
          break;
        case 34:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(152); // Phát âm thanh cho chất thứ 34
              Serial.println("OK");
            }
            tft.setTextColor(0x081a, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Selenium", 240, 10, GFXFF); // Chất thứ 34: Selenium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Se", 10, 120, GFXFF);
            tft.drawString("Chemical name: Selenium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Nonmetal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(34);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("34  78.960");

            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Se");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(15, 100);
            tft.setTextSize(1); 
            tft.println("Selenium");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 78.960 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 493.15 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 958 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1817");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Selenium is a nonmetal with a gray appearance in its natural form. It is  typically found in two forms: amorphous and crystalline. Selenium is a semiconductor with electrical conductivity that increases with exposure to light.");
            tft.setCursor(4,188);
            tft.println("- Selenium exhibits both nonmetallic and metallic properties. It reacts with acids and alkalis but is relatively unreactive with air. Selenium can form   compounds with various elements, including oxygen, sulfur, and halogens. It can exist in several oxidation states, including -2, +4, and +6.");
            tft.setCursor(4,252);
            tft.println("- Selenium is primarily used in electronic devices such as photocopiers,    printers, and solar cells due to its photoconductivity properties. It is also used in glassmaking, metallurgy, and as a nutritional supplement in small     doses.");
          }
            break;
        case 35:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(153); // Phát âm thanh cho chất thứ 35
              Serial.println("OK");
            }
            tft.setTextColor(0x081a, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Bromine", 240, 10, GFXFF); // Chất thứ 35: Bromine
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Br", 10, 120, GFXFF);
            tft.drawString("Chemical name: Bromine", 10, 180, GFXFF);
            tft.drawString("Chemical group: Nonmetal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(35);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("35  79.904");

            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Br");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Bromine");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 79.904 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 265.95 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 331.95 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1826");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Bromine is a reddish-brown liquid at room temperature, making it the only nonmetallic element that is liquid under standard conditions. It has a pungent odor and is highly reactive. Bromine evaporates easily, forming a       reddish-brown vapor. ");
            tft.setCursor(4,204);
            tft.println("- Bromine is a halogen and it readily forms compounds with other elementsparticularly metals, to form bromides. It reacts vigorously with many        substances, especially organic compounds, and is often used as a reagent inchemical synthesis.");
            tft.setCursor(4,268);
            tft.println("- Bromine compounds are used as flame retardants in plastics, textiles, and furniture. Bromine is also used in the production of pharmaceuticals,       pesticides, and dyes. ");
          }
            break;
        case 36:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(154); // Phát âm thanh cho chất thứ 36
              Serial.println("OK");
            }
            tft.setTextColor(0xC0E9EF, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Krypton", 240, 10, GFXFF); // Chất thứ 36: Krypton
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Kr", 10, 120, GFXFF);
            tft.drawString("Chemical name: Krypton", 10, 180, GFXFF);
            tft.drawString("Chemical group: Noble Gas", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties == 2) {
              player.playMp3Folder(36);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("36  83.798");

            tft.setTextColor(0xC0E9EF,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Kr");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Krypton");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 83.798 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 115.79 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 119.74 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1898");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Krypton is a colorless, odorless, and tasteless noble gas. It is relativelyrare in Earth's atmosphere and is often extracted through air fractionation. Krypton is denser than air and is used in certain types of lighting, such as fluorescent lamps and flash lamps, due to its ability to emit a bright white  light when electrically stimulated.");
            tft.setCursor(4,220);
            tft.println("- Krypton is inert and does not readily form compounds with other elements. It has a complete outer electron shell, making it stable and unreactive   under normal conditions. Krypton is primarily used in lighting and laser     technologies due to its unique spectral lines.");
            tft.setCursor(4,284);
            tft.println("- Krypton is mainly used in lighting for bright white light and in lasers forscientific research and medical procedures.");
          }
            break;
        case 37:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(155); // Phát âm thanh cho chất thứ 37
              Serial.println("OK");
            }
            tft.setTextColor(0x050e, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Rubidium", 240, 10, GFXFF); // Chất thứ 37: Rubidium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Rb", 10, 120, GFXFF);
            tft.drawString("Chemical name: Rubidium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Alkali Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(37);           
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("37   85.468");

            tft.setTextColor(0x050e,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Rb");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Rubidi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 85.468 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 312.46 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 961 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1861");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Rubidium is a soft, silvery-white metallic element. It is highly reactive,   tarnishing rapidly upon exposure to air due to its strong affinity for oxy. It is one of the most electropositive elements.");
            tft.setCursor(4, 188);
            tft.println("- Rubidium is an alkali metal and exhibits typical properties of this group. It reacts vigorously with water, releasing hydrogen gas and forming rubidiumhydroxide. It also reacts with other nonmetals, halogens, and acids to form various compounds. Rubidium is commonly used in research laboratories andin the production of special glasses and fireworks.");
            tft.setCursor(4, 268);
            tft.println("- Rubidium, due to its reactivity and rarity, is mainly used in research,     especially in atomic clocks for precise timekeeping. It's also used in        manufacturing photocells and certain medical treatments.");
          }
          break;
        case 38:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(156); // Phát âm thanh cho chất thứ 38
              Serial.println("OK");
            }
            tft.setTextColor(0xf980, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Strontium", 240, 10, GFXFF); // Chất thứ 38: Strontium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Sr", 10, 120, GFXFF);
            tft.drawString("Chemical name: Strontium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Alkaline Earth Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(38);            
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("38   87.62");

            tft.setTextColor(0xf980,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Sr");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Stronti");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 87.62 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1050 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1655 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1790");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Strontium is a soft, silvery-white alkaline earth metal. It's highly reactivewith air and water, tarnishing quickly in air to form a protective oxide     layer. Strontium compounds emit a bright red color when burned, used in   fireworks and flares.");
            tft.setCursor(4, 204);
            tft.println("- Strontium readily forms compounds with elements such as oxygen and     sulfur. Strontium compounds are utilized in the production of cathode ray tubes, ferrite magnets, and pyrotechnics. Strontium salts are used in        medicine for treating osteoporosis.");
            tft.setCursor(4, 268);
            tft.println("- Strontium's most notable applications include its use in the manufacture  of cathode ray tubes for televisions, in ferrite magnets for electronic     devices, and in pyrotechnics for producing red flame effects in fireworks.");
          }
          break;
        case 39:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(157); // Phát âm thanh cho chất thứ 39
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Yttrium", 240, 10, GFXFF); // Chất thứ 39: Yttrium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Y", 10, 120, GFXFF);
            tft.drawString("Chemical name: Yttrium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(39);           
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("39   88.906");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(40, 35);
            tft.setTextSize(3); 
            tft.println("Y");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(45, 100);
            tft.setTextSize(1); 
            tft.println("Ytri");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 88.906 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1799 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3609 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1794");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Yttrium is a silvery-metallic transition metal. It isrelatively stable in air but will slowly oxidize to form a protective oxide layer. It is often found  in combination with other rare earth elements in minerals such as xenotime and monazite.");
            tft.setCursor(4, 204);
            tft.println("- Yttrium is chemically similar to the lanthanides and exhibits many of theircharacteristic properties. It forms compounds with oxygen, sulfur, and      nitrogen, and it can act as both a trivalent and tetravalent cation in       chemical reactions.");
            tft.setCursor(4, 268);
            tft.println("- Yttrium has numerous applications due to its unique chemical and physicaproperties. It is used in the production of phosphors for various display   technologies, including cathode ray tubes and LED displays.");
          }
          break;
        case 40:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(158); // Phát âm thanh cho chất thứ 40
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Zirconium", 240, 10, GFXFF); // Chất thứ 40: Zirconium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Zr", 10, 120, GFXFF);
            tft.drawString("Chemical name: Zirconium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(40);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("40   91.224");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Zr");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Zirconi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 91.224 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 2128 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 4682 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1789");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Zirconium is a lustrous, grayish-white, strong transition metal. Zirconium is often found in minerals such as zircon and baddeleyite.");
            tft.setCursor(4, 172);
            tft.println("- Zirconium forms a passive oxide layer that makes it highly resistant to   corrosion. It reacts with oxygen, nitrogen, hydrogen, and halogens to form various compounds. Zirconium compounds are used in numerous industrial   applications, including nuclear reactors, aerospace components and chemicalprocessing equipment.");
            tft.setCursor(4, 252);
            tft.println("- Zirconium has diverse applications due to its unique combination of      properties. It is widely used in the nuclear industry for cladding fuel rods in nuclear reactors due to its excellent corrosion resistance and low       neutron absorption cross-section.");
          }
          break;
        case 41:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(159); // Phát âm thanh cho chất thứ 41
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Niobium", 240, 10, GFXFF); // Chất thứ 41: Niobium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Nb", 10, 120, GFXFF);
            tft.drawString("Chemical name: Niobium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(41);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("41   92.906");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Nb");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Niobi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 92.906 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 2750 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 5017 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1801");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Niobium is a shiny, silver-gray, ductile transition metal. It exhibits high   melting and boiling points, with  melting at 2477°C and boiling at 4744°C.    Niobium is often alloyed with other metals for various applications.");
            tft.setCursor(4, 188);
            tft.println("- Niobium forms a protective oxide layer, rendering it highly resistant to  corrosion. It reacts with acids, oxygen and halogens to form various       compounds. Niobium compounds are used in superalloys, superconductors    and electronic components.");
            tft.setCursor(4, 252);
            tft.println("- Niobium finds applications in superconducting magnets, jet engines, and   nuclear reactors due to its high melting point and resistance to corrosion. It is also used in jewelry and in the aerospace industry for its lightweight  and strength.");
          }
          break;
        case 42:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(160); // Phát âm thanh cho chất thứ 42
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Molybdenum", 240, 10, GFXFF); // Chất thứ 42: Molybdenum
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Mo", 10, 120, GFXFF);
            tft.drawString("Chemical name: Molybdenum", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(42);            
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("42    95.95");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(10, 35);
            tft.setTextSize(3); 
            tft.println("Mo");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(10, 100);
            tft.setTextSize(1); 
            tft.println("Molybden");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 95.95 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 2896 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 4912 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Molybdenum is a silvery-white, hard, transition metal. It has a high       melting point of 2623°C and a boiling point of 4639°C, making it suitable forhigh-temperature applications.");
            tft.setCursor(4, 188);
            tft.println("- Molybdenum forms various compounds, including oxides, sulfides, and     halides. It is highly resistant to corrosion and reacts with acids only at    high temperatures. Molybdenum compounds find use in lubricants, catalysts, and pigments.");
            tft.setCursor(4, 252);
            tft.println("- Molybdenum is vital in metallurgy, being used in alloys to enhance        strength and corrosion resistance. It's crucial in the production of         stainlesssteel, tool steel, and high-speed steel. Additionally, it is utilized in electronics and as a catalyst in chemical processes.");
          }
          break;
        case 43:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(161); // Phát âm thanh cho chất thứ 43
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Technetium", 240, 10, GFXFF); // Chất thứ 43: Technetium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Tc", 10, 120, GFXFF);
            tft.drawString("Chemical name: Technetium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(43);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("43          98");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Tc");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(15, 100);
            tft.setTextSize(1); 
            tft.println("Techneti");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 98 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 2477 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 4538 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1937");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Technetium is a silvery-gray metal. It is radioactive and has no stable   isotopes. Technetium has a relatively low melting point of 2157°C and a     boiling point of 4265°C.");
            tft.setCursor(4, 188);
            tft.println("- Technetium readily forms compounds with various elements, including     oxides, halides, and complexes. It exhibits multiple oxidation states, commonlyranging from -1 to +7. Technetium compounds are used in nuclear medicine for diagnostic imaging.");
            tft.setCursor(4, 252);
            tft.println("- Technetium-99m, a radioactive isotope, is widely used in medical imaging procedures such as single-photon emission computed tomography (SPECT)  and positron emission tomography (PET). It allows for non-invasive        visualization of internal organs and tissues.");
          }
          break;
        case 44:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(162); // Phát âm thanh cho chất thứ 44
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Ruthenium", 240, 10, GFXFF); // Chất thứ 44: Ruthenium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ru", 10, 120, GFXFF);
            tft.drawString("Chemical name: Ruthenium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(44);           
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("44   101.07");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Ru");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(18, 100);
            tft.setTextSize(1); 
            tft.println("Rutheni");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 101.07 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 2607 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 4423 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1844");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Ruthenium is a hard, brittle, silvery-white metal. It is one of the densest elements and has a high melting point of 2334°C. Ruthenium is often used asa catalyst in various chemical reactions.");
            tft.setCursor(4, 188);
            tft.println("- Ruthenium is relatively inert but can form a variety of oxidation states  in compounds. It forms complexes with ligands and exhibits catalytic activityin hydrogenation and oxidation reactions. Ruthenium compounds are         employed in electronics and jewelry.");
            tft.setCursor(4, 252);
            tft.println("- Ruthenium finds use in electronics for its electrical contacts' durability  and resistance to corrosion. It is also utilized in the production of wear   resistant electrical contacts, jewelry, and as a catalyst in ammonia          production.");
          }
          break;
        case 45:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(163); // Phát âm thanh cho chất thứ 45
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Rhodium", 240, 10, GFXFF); // Chất thứ 45: Rhodium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Rh", 10, 120, GFXFF);
            tft.drawString("Chemical name: Rhodium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(45);           
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("45   102.91");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Rh");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Rhodi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 102.91 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:2237.1 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:3968 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1803");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Rhodium is a rare, silvery-white metal. It is highly reflective and has a  high melting point of 1964°C. Rhodium is one of the most corrosion         resistant metals.");
            tft.setCursor(4, 188);
            tft.println("- Rhodium is inert in most conditions and resists tarnishing. It forms       various compounds, including oxides and halides, but is mostly known for itsuse as a catalyst in automotive catalytic converters and in jewelry plating.");
            tft.setCursor(4, 236);
            tft.println("- Rhodium is extensively used in catalytic converters to reduce harmful    emissions in automobiles. It is also utilized in jewelry for plating white goldand silver to enhance their appearance and durability.");
          }
          break;
        case 46:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(164); // Phát âm thanh cho chất thứ 46
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Palladium", 240, 10, GFXFF); // Chất thứ 46: Palladium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Pd", 10, 120, GFXFF);
            tft.drawString("Chemical name: Palladium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(46);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("46   106.42");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Pd");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Paladi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 106.42 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1828.1 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:3236 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1803");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Palladium is a shiny, silvery-white metal. It has excellent corrosion       resistance and is one of the least dense platinum group metals.");
            tft.setCursor(4, 188);
            tft.println("- Palladium has a remarkable ability to absorb hydrogen, forming palladium hydride. It also forms various compounds with other elements, exhibiting    catalytic properties extensively used in the automotive industry.");
            tft.setCursor(4, 252);
            tft.println("- Palladium is widely used in catalytic converters to reduce harmful        emissions from vehicles. It's also utilized in electronics, dentistry, and      jewelry due to its durability, conductivity, and attractive appearance.");
          }
          break;
        case 47:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(165); // Phát âm thanh cho chất thứ 47
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Silver", 240, 10, GFXFF); // Chất thứ 47: Silver
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ag", 10, 120, GFXFF);
            tft.drawString("Chemical name: Silver", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(47);
            
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("47   107.87");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Ag");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(33, 110);
            tft.setTextSize(1); 
            tft.println("Silver");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 107.87 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1234.9K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:2435K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Silver is a shiny, white metal with excellent thermal and electrical        conductivity. It is malleable and ductile, making it ideal for jewelry and currency.");
            tft.setCursor(4, 188);
            tft.println("- Silver doesn't react with oxygen or water, but it tarnishes when exposed to sulfur compounds in the air. It forms compounds with sulfur, halogens,   and other elements, and its ions exhibit antimicrobial properties.");
            tft.setCursor(4, 236);
            tft.println("- Silver is widely used in jewelry, silverware and coins due to its aestheticappeal and corrosion resistance. It's also utilized in electronics, mirrors,   and photography, as well as in medical applications for wound dressings    and antimicrobial coatings.");
          }
          break;
        case 48:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(166); // Phát âm thanh cho chất thứ 48
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Cadmium", 240, 10, GFXFF); // Chất thứ 48: Cadmium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Cd", 10, 120, GFXFF);
            tft.drawString("Chemical name: Cadmium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(48);
            
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("48   112.41");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Cd");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(28, 100);
            tft.setTextSize(1); 
            tft.println("Cadmi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 112.41 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 594.22 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1040 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1817");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Cadmium, with atomic number 48, is a soft, bluish-white metal. It's ductile and malleable at room temperature but becomes brittle at low temperatures. Cadmium is often used as a protective coating for other metals.");
            tft.setCursor(4, 204);
            tft.println("- Cadmium is resistant to corrosion but can tarnish in moist air. It forms  compounds with various elements like sulfur, chlorine, and oxygen. Some    cadmium compounds are toxic and pose environmental hazards.");
            tft.setCursor(4, 268);
            tft.println("- Cadmium is primarily used in rechargeable batteries pigments and coatings.It's also found in solder, electroplating, and as a component in nuclear    reactors, albeit in declining usage due to environmental concerns.");
          }
          break;
        case 49:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(167); // Phát âm thanh cho chất thứ 49
              Serial.println("OK");
            }
            tft.setTextColor(0x8A2BE2, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Indium", 240, 10, GFXFF); // Chất thứ 49: Indium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: In", 10, 120, GFXFF);
            tft.drawString("Chemical name: Indium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Post-Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(49);           
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("49   114.82");

            tft.setTextColor(0x8A2BE2,TFT_BLACK);
            tft.setCursor(35, 35);
            tft.setTextSize(3); 
            tft.println("In");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(45, 100);
            tft.setTextSize(1); 
            tft.println("Indi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 114.82 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 429.75 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2345 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1863");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Indiumis a soft, silvery-white metal. It is ductile, malleable, and has a low melting point, making it useful in alloys and solders.");
            tft.setCursor(4, 188);
            tft.println("- Indium is relatively inert in air but reacts with nonmetals such as        halogens, sulfur, and phosphorus. It forms a protective oxide layer on its  surface, making it corrosion-resistant.");
            tft.setCursor(4, 252);
            tft.println("- Indium is used extensively in electronic devices including as a componentin semiconductors, touchscreen displays, and solar panels. It's also used in low-melting alloys for fire sprinkler systems and solders for joining metals.");
          }
          break;
        case 50:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(168); // Phát âm thanh cho chất thứ 50
              Serial.println("OK");
            }
            tft.setTextColor(0x8A2BE2, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Tin", 240, 10, GFXFF); // Chất thứ 50: Tin
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Sn", 10, 120, GFXFF);
            tft.drawString("Chemical name: Tin", 10, 180, GFXFF);
            tft.drawString("Chemical group: Post-Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(50);            
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("50   118.71");

            tft.setTextColor(0x8A2BE2,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Sn");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(43, 100);
            tft.setTextSize(1); 
            tft.println("Tin");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 118.71 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 505.08 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2875 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Tin is a silvery-white, soft metal with a low melting point. It is malleable and ductile, making it easy to shape into various forms.");
            tft.setCursor(4, 188);
            tft.println("- Tin is relatively unreactive in air and water at room temperature. It     reacts slowly with acids but dissolves more rapidly in concentrated acids   and alkalis. Tin forms various compounds, including tin oxide and tin        chloride.");
            tft.setCursor(4, 252);
            tft.println("- Tin has a wide range of applications. It is commonly used as a coating   for steel to prevent corrosion, known as tinplate. Tin alloys, such as bronze and solder, are used in the manufacturing of electrical equipment,        plumbing fixtures, and metal containers.");
          }
          break;
        case 51:
              if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(169); // Phát âm thanh cho chất thứ 52
              Serial.println("OK");
            }
            tft.setTextColor(0xa340, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Antimony", 240, 10, GFXFF); // Chất thứ 52: Xenon
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Sb", 10, 120, GFXFF);
            tft.drawString("Chemical name: Antimony", 10, 180, GFXFF);
            tft.drawString("Chemical group: Metalloid", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(51);            
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("51   121.76");

            tft.setTextColor(0xa340,TFT_BLACK);
            tft.setCursor(23, 35);
            tft.setTextSize(3); 
            tft.println("Sb");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(22, 100);
            tft.setTextSize(1); 
            tft.println("Antimon");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 121.76 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 903.78 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1860 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Antimony, with atomic number 51, is a silvery, lustrous, brittle metalloid. It possesses poor thermal and electrical conductivity and expands when     cooled. Antimony is commonly found in minerals such as stibnite and        antimony glance.");
            tft.setCursor(4, 204);
            tft.println("- Antimony exhibits both metallic and non-metallic properties. It reacts withacids and oxygen, forming oxides and antimonides. Antimony compounds findapplications in flame retardants, pigments, and semiconductor materials.");
            tft.setCursor(4, 252);
            tft.println("- Antimony compounds are utilized extensively, particularly in flame        retardant formulations for plastics, textiles, and coatings. Additionally, theyare employed in lead-acid batteries as grid alloys, and in the production  of semiconductors, glass, and ceramics.");
          }
          break;
        case 52:
              if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(170); // Phát âm thanh cho chất thứ 55
              Serial.println("OK");
            }
            tft.setTextColor(0xa340, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Tellurium", 240, 10, GFXFF); // Chất thứ 55: Lanthanum
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Te", 10, 120, GFXFF);
            tft.drawString("Chemical name: Tellurium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Metalloid", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(52);           
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("52     127.6");

            tft.setTextColor(0xa340,TFT_BLACK);
            tft.setCursor(27, 35);
            tft.setTextSize(3); 
            tft.println("Te");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(38, 100);
            tft.setTextSize(1); 
            tft.println("Teluri");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 127.6 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 722.66 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1261 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1782");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Tellurium is a brittle, silvery-white semimetal. It exhibits semiconductor   properties and has a pungent odor when freshly crushed. Tellurium is primarily obtained from the processing of copper ores.");
            tft.setCursor(4, 188);
            tft.println("- Tellurium reacts with oxygen, sulfur, and halogens to form compounds. It is primarily used in the production of alloys, such as steel and copper, andin the manufacturing of semiconductors and solar cells.");
            tft.setCursor(4, 236);
            tft.println("- Tellurium finds applications in diverse fields. It is crucial in the         production of cadmium telluride (CdTe) solar panels due to its ability to   absorb sunlight efficiently. Additionally, it is used in the production of     thermoelectric materials for waste heat recovery and in the pharmaceutical industry for certain medicinal purposes.");
          }
          break;
        case 53:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(171); // Phát âm thanh cho chất thứ 51
              Serial.println("OK");
            }
            tft.setTextColor(0x081a, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Iodine", 240, 10, GFXFF); // Chất thứ 51: Iodine
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: I", 10, 120, GFXFF);
            tft.drawString("Chemical name: Iodine", 10, 180, GFXFF);
            tft.drawString("Chemical group: Nonmetal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
        
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(53);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("53   126.9");

            tft.setTextColor(0x081a,TFT_BLACK);
            tft.setCursor(53, 35);
            tft.setTextSize(3); 
            tft.println("I");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(45, 100);
            tft.setTextSize(1); 
            tft.println("Iod");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 126.9 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 386.85 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 457.4 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1811");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Iodine is a shiny, blackish-purple solid at room temperature. It sublimes  easily into a violet gas, exhibiting a characteristic odor. Iodine is sparinglysoluble in water but dissolves readily in organic solvents.");
            tft.setCursor(4, 188);
            tft.println("- Iodine is a halogen, exhibiting typical halogen properties. It reacts with  metals to form iodides and with non-metals to form iodides or oxides.      Iodine compounds find applications in medicine, photography, and analytical chemistry.");
            tft.setCursor(4, 252);
            tft.println("- Iodine and its compounds are extensively    used in medicine as antiseptics, disinfectants, and in thyroid treatments. In photography, silver iodide is used in photographic emulsions. Additionally, iodine is utilized in the       production of dyes, pigments, and as a catalyst in organic synthesis.");
          }
          break;
        case 54:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(172); // Phát âm thanh cho chất thứ 52
              Serial.println("OK");
            }
            tft.setTextColor(0xC0E9EF, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Xenon", 240, 10, GFXFF); // Chất thứ 52: Xenon
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Xe", 10, 120, GFXFF);
            tft.drawString("Chemical name: Xenon", 10, 180, GFXFF);
            tft.drawString("Chemical group: Noble Gas", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(54);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("54  131.29");

            tft.setTextColor(0xC0E9EF,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Xe");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Xenon");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 131.29 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 161.4 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 165.03 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1898");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Xenon is a colorless, odorless noble gas. It is the heaviest stable noblegas and has a density greater than air. Xenon has a very low boiling point, allowing it to exist as a gas at room temperature.");
            tft.setCursor(4,188);
            tft.println("- Xenon is chemically inert under normal conditions, though it can form a  few compounds under extreme conditions. It has a complete valence shell,  making it stable and unreactive in most situations.");
            tft.setCursor(4,236);
            tft.println("- Xenon is used in various applications such as in lighting, where it        produces a bright white light in xenon arc lamps. It is also utilized in      medical imaging, as xenon gas can be hyperpolarized and used as a contrastagent in MRI scans. Additionally, xenon is used in certain types of ion      propulsion systems for spacecraft.");
          }
          break;
        case 55:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(173); // Phát âm thanh cho chất thứ 53
              Serial.println("OK");
            }
            tft.setTextColor(0x050e, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Cesium", 240, 10, GFXFF); // Chất thứ 53: Cesium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Cs", 10, 120, GFXFF);
            tft.drawString("Chemical name: Cesium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Alkali Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
        
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(55);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("55   132.9");

            tft.setTextColor(0x050e,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Cs");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Caesi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 132.9 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 301.7 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 944 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1860");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Cesium is a soft, silvery-gold alkali metal. It is the most reactive metal,  rapidly oxidizing in air. Cesium has the lowest melting point of all metals   and is liquid near room temperature.");
            tft.setCursor(4, 204);
            tft.println("- Cesium reacts violently with water, producing hydrogen gas. It forms     various compounds, including cesium hydroxide and cesium chloride, which   are used in the chemical industry and in research laboratories.");
            tft.setCursor(4, 268);
            tft.println("- Cesium-based atomic clocks are vital in navigation systems and           telecommunications. Cesium compounds are used in photoelectric cells,      vacuum tubes, and in the drilling of oil wells.");
          }
          break;
        case 56:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(174); // Phát âm thanh cho chất thứ 54
              Serial.println("OK");
            }
            tft.setTextColor(0xf980, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Barium", 240, 10, GFXFF); // Chất thứ 54: Barium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ba", 5, 120, GFXFF);
            tft.drawString("Chemical name: Barium", 5, 180, GFXFF);
            tft.drawString("Chemical group: Alkaline Earth Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(56);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("56   137.32");

            tft.setTextColor(0xf980,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Ba");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(44, 100);
            tft.setTextSize(1); 
            tft.println("Bari");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 137.32 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1000 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2170 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1808");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Barium, with atomic number 56, is a soft, silvery alkaline earth metal. It  is highly reactive, oxidizing rapidly in air to form a protective oxide layer Barium is commonly used in alloys and as a getter in vacuum tubes.");
            tft.setCursor(4, 204);
            tft.println("- Barium reacts vigorously with water to form barium hydroxide and        hydrogen gas. It forms various compounds, such as barium sulfate and      barium chloride, which are utilized in industries like oil drilling and         manufacturing of ceramics.");
            tft.setCursor(4, 268);
            tft.println("- Barium compounds are used in various applications, including the         production of glass, ceramics, and fireworks. Barium sulfate is used as a   contrast agent in medical imaging procedures like X-rays and CT scans.");
          }
          break;
        case 57:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(175); // Phát âm thanh cho chất thứ 55
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Lanthanum", 240, 10, GFXFF); // Chất thứ 55: Lanthanum
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: La", 10, 120, GFXFF);
            tft.drawString("Chemical name: Lanthanum", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(57);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("57     138.9");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("La");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Lanthan");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 138.9 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1193 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3737 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1839");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Lanthanum is a silvery-white rare-earth metal. It is malleable and ductile,and it has a relatively high melting point. Lanthanum exhibits paramagnetismand has a hexagonal crystal structure.");
            tft.setCursor(4, 204);
            tft.println("- Lanthanum is highly reactive and quickly tarnishes in air. It reacts with  water to form lanthanum hydroxide and hydrogen gas. Lanthanum compoundsare used in catalysts, glass production, and in rechargeable batteries.");
            tft.setCursor(4, 268);
            tft.println("- Lanthanum is used in various applications, including the production of   carbon arc lamps, camera lenses, and as a component in hybrid car         batteries.");
          }
          break;
        case 58:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(176); // Phát âm thanh cho chất thứ 56
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Cerium", 240, 10, GFXFF); // Chất thứ 56: Cerium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ce", 10, 120, GFXFF);
            tft.drawString("Chemical name: Cerium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(58);

            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("58   140.11");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Ce");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Cerium");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 140.11 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1068 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3716 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1803");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Cerium is a soft, ductile, and silvery-white metal that oxidizes in air.");
            tft.setCursor(4, 156);
            tft.println("- Cerium is used in certain types of alloys, in catalysts, and in certain     types of glass and ceramics.");
            tft.setCursor(4,188);
            tft.println("- Cerium compounds have applications in automotive catalytic converters  and in self-cleaning ovens.");
          }
          break;
        case 59:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(177); // Phát âm thanh cho chất thứ 57
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Praseodymium", 240, 10, GFXFF); // Chất thứ 57: Praseodymium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Pr", 10, 120, GFXFF);
            tft.drawString("Chemical name: Praseodymium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(59);

            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("59      140.9");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Pr");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(5, 100);
            tft.setTextSize(1); 
            tft.println("Praseodymi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 140.9 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1208 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3793 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1885");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Praseodymium is a soft, silvery, malleable rare-earth metal. It tarnishes  rapidly in air and reacts slowly with water. Praseodymium is paramagnetic   at room temperature.");
            tft.setCursor(4, 204);
            tft.println("- Praseodymium readily forms a green oxide layer when exposed to air,    which gives it its distinctive color. It reacts slowly with oxygen, water, andacids, but rapidly dissolves in concentrated sulfuric acid.");
            tft.setCursor(4, 268);
            tft.println("- Praseodymium is used in various applications such as in rare-earth       magnets for wind turbines and electric vehicles, in colorants for glass and ceramics, and as an alloying agent in metallic alloys.");
          }
          break;
        case 60:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(178); // Phát âm thanh cho chất thứ 58
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Neodymium", 240, 10, GFXFF); // Chất thứ 58: Neodymium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Nd", 10, 120, GFXFF);
            tft.drawString("Chemical name: Neodymium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(60);
            }
             tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("60   144.24");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Nd");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Neodymi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 144.24 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1297 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3347 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1885");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Neodymium is a soft, silvery metal belonging to the lanthanide series. It  is one of the rare-earth elements and is ductile and malleable.");
            tft.setCursor(4, 188);
            tft.println("- Neodymium readily forms compounds with oxygen, sulfur, and halogens. It tarnishes slowly in air and reacts with water to form neodymium hydroxide.");
            tft.setCursor(4, 236);
            tft.println("- Neodymium is primarily used in powerful permanent magnets, particularly  in neodymium-iron-boron (NdFeB) magnets used in computer hard drives,   wind turbines, and electric vehicles.");
          }
          break;
        case 61:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(179); // Phát âm thanh cho chất thứ 59
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Promethium", 240, 10, GFXFF); // Chất thứ 59: Promethium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Pm", 10, 120, GFXFF);
            tft.drawString("Chemical name: Promethium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(61);

            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("61     145");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Pm");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Promethi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 145 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: ..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: ..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1945");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Promethium is a rare, radioactive, silvery metallic element. It's the only  lanthanide with no stable isotopes. It's paramagnetic at room temperature.");
            tft.setCursor(4, 188);
            tft.println("- Promethium reacts with oxygen, water, and acids. It forms various        compounds like oxide, hydroxide, and halides.");
            tft.setCursor(4, 236);
            tft.println("- Promethium isotopes are used in nuclear batteries, thickness gauges, and luminous paint for watches. Its compounds find applications in research andspecialized industries.");
          }
          break;
        case 62:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(180); // Phát âm thanh cho chất thứ 60
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Samarium", 240, 10, GFXFF); // Chất thứ 60: Samarium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Sm", 10, 120, GFXFF);
            tft.drawString("Chemical name: Samarium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(62);

            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("62   150.36");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Sm");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Samari");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 150.36 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1345 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2173 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1853");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Samarium is a silvery-white, lustrous, rare-earth metal. It's relatively     hard and brittle and has a hexagonal crystalline structure.");
            tft.setCursor(4, 188);
            tft.println("- Samarium is reactive and forms various compounds, including oxides,     halides, and salts. It's used in samarium-cobalt magnets and as a neutron    absorber.");
            tft.setCursor(4, 252);
            tft.println("- Samarium is crucial in making powerful magnets used in headphones, smallmotors, and sensors. It's also used in nuclear reactors as control rods and in cancer treatment.");
          }
          break;
        case 63:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(181); // Phát âm thanh cho chất thứ 61
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Europium", 240, 10, GFXFF); // Chất thứ 61: Europium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Eu", 10, 120, GFXFF);
            tft.drawString("Chemical name: Europium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(63);

            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("63   151.96");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Eu");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Europi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 151.96 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1099 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1802 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1890");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Europium is a silvery-white, soft, and ductile rare-earth metal. It's       paramagnetic at room temperature but becomes ferromagnetic below 20 K.");
            tft.setCursor(4, 188);
            tft.println("- Europium is highly reactive, tarnishing quickly in air. It reacts slowly    with water and oxidizes in water. It forms compounds with various oxidationstates.");
            tft.setCursor(4, 252);
            tft.println("- Europium is essential in phosphors for fluorescent lamps, CRT displays,  and LEDs. It's also used in nuclear reactors as a neutron absorber.");
          }
          break;
        case 64:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(182); // Phát âm thanh cho chất thứ 62
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Gadolinium", 240, 10, GFXFF); // Chất thứ 62: Gadolinium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Gd", 10, 120, GFXFF);
            tft.drawString("Chemical name: Gadolinium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(64);

            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("64   157.25");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Gd");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Gadolini");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 157.25 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1585 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3546 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1880");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Gadolinium is a silvery-white, malleable, and ductile rare-earth metal.");
            tft.setCursor(4, 172);
            tft.println("- Gadolinium is used in certain types of magnets, in MRI contrast agents,   and in nuclear reactor control rods.");
            tft.setCursor(4,220);
            tft.println("- Gadolinium compounds have applications in electronics, ceramics, and as  phosphors in fluorescent lamps.");
          }
          break;
        case 65:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(183); // Phát âm thanh cho chất thứ 63
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Terbium", 240, 10, GFXFF); // Chất thứ 63: Terbium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Tb", 10, 120, GFXFF);
            tft.drawString("Chemical name: Terbium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(65);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("65   158.92");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Tb");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Terbi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 158.92 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1629 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3503 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1843");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Terbium is a silvery-white rare earth metal. It possesses a high melting  point of 1356°C and a boiling point of 3230°C. Terbium is primarily used in phosphors, magneto-optical devices, and lasers.");
            tft.setCursor(4, 188);
            tft.println("- Terbium is relatively stable in air, but it tarnishes slowly in moist air. It reacts slowly with water and acids and forms various compounds. Terbium  compounds are utilized in catalysis, electronic devices, and glass           manufacturing.");
            tft.setCursor(4, 252);
            tft.println("- Terbium finds applications in a variety of fields. It is crucial in the     production of green phosphors for color television tubes and              energy-efficient fluorescent lamps.");
          }
          break;
        case 66:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(184); // Phát âm thanh cho chất thứ 64
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Dysprosium", 240, 10, GFXFF); // Chất thứ 64: Dysprosium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Dy", 10, 120, GFXFF);
            tft.drawString("Chemical name: Dysprosium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(66);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("66   162.50");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Dy");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Dysprosi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 162.50 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1680 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2840 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1886");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Dysprosium silvery metal. It has a relativelyhigh melting point of 1412°C and a boiling point of 2567°C. Dysprosium exhibits magnetic properties and is used in various magnetic applications.");
            tft.setCursor(4, 188);
            tft.println("- Dysprosium is highly reactive and tarnishes rapidly in air. It reacts with water to form dysprosium hydroxide and hydrogen gas. Dysprosium          compounds are utilized in catalysts, phosphors, and nuclear reactors.");
            tft.setCursor(4, 236);
            tft.println("- Dysprosium finds applications in magnets for electric motors, hard disk   drives, and MRI machines due to its magnetic properties. It is also crucial  in lighting applications such as compact fluorescent lamps and LEDs for    color rendering improvement.");
          }
          break;
        case 67:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(185); // Phát âm thanh cho chất thứ 65
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Holmium", 240, 10, GFXFF); // Chất thứ 65: Holmium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ho", 10, 120, GFXFF);
            tft.drawString("Chemical name: Holmium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(67);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("67   164.93");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Ho");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Holmi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 164.93 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1734 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2993 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1878");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Holmium, atomic number 67, is a soft, silvery metal. It has a melting point of 1474°C and a boiling pointof 2700°C. Holmium is paramagnetic at room  temperature.");
            tft.setCursor(4, 204);
            tft.println("- Holmium is relatively stable in dry air but tarnishes in moist air.It reactsslowly with water and dissolves in acids. Holmium forms various compounds with oxygen, sulfur, and halogens.");
            tft.setCursor(4, 268);
            tft.println("- Holmium is used in nuclear control rods due to its high neutron          absorbing ability. It is also utilized in solid-state lasers, magnetic resonance imaging (MRI) machines, and as a dopant in optical glasses.");
          }
          break;
        case 68:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(186); // Phát âm thanh cho chất thứ 66
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Erbium", 240, 10, GFXFF); // Chất thứ 66: Erbium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Er", 10, 120, GFXFF);
            tft.drawString("Chemical name: Erbium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(68);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("68    167.26");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Er");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Erbi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 167.26 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1802 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3141 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1842");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Erbium, with atomic number 68, is a soft, malleable, silvery metal. It has amelting point of 1529°C and a boiling point of 2868°C. Erbium is used in    fiber optics and optical amplifiers.");
            tft.setCursor(4, 188);
            tft.println("- Erbium is relatively stable in air but slowly oxidizes. It reacts slowly withwater and acids. Erbium forms various compounds with oxygen, sulfur, and  halogens.");
            tft.setCursor(4, 252);
            tft.println("- Erbium is utilized in telecommunications for amplifying optical signals in fiber optic cables. It is also used in nuclear reactors for controlling       nuclear chain reactions and as a dopant in lasers for medical and dental   procedures.");
          }
          break;
        case 69:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(187); // Phát âm thanh cho chất thứ 67
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Thulium", 240, 10, GFXFF); // Chất thứ 67: Thulium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Tm", 10, 120, GFXFF);
            tft.drawString("Chemical name: Thulium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(69);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("69   168.93");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Tm");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Thulium");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 168.93 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1818 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2223 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1879");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Thulium is a soft, silvery-gray, rare earth metal. It has a melting point   of 1545°C and a boiling point of 1950°C. Thulium is paramagnetic at room  temperature.");
            tft.setCursor(4, 188);
            tft.println("- Thulium is relatively stable in air but tarnishes slowly. It reacts slowly   with water and acids. Thulium forms various compounds with oxygen, sulfur, and halogens.");
            tft.setCursor(4, 252);
            tft.println("- Thulium is used in various applications including medical imaging, laser   technology, and nuclear research. It is utilized in portable X-ray devices,  high-power solid-state lasers, and as a radiation source in portable X-ray fluorescence spectrometry.");
          }
          break;
        case 70:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(188); // Phát âm thanh cho chất thứ 68
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Ytterbium", 240, 10, GFXFF); // Chất thứ 68: Ytterbium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Yb", 10, 120, GFXFF);
            tft.drawString("Chemical name: Ytterbium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(70);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("70   173.04");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Yb");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Yterbi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 173.04 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1097 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1469 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1878");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Ytterbium is a soft, malleable, silvery metal. It has a relatively low       melting point of 824°C and a boiling point of 1196°C. Ytterbium is a rare   earth element belonging to the lanthanide series.");
            tft.setCursor(4, 188);
            tft.println("- Ytterbium is stable in dry air but tarnishes in moist air. It reacts slowly with water and acids but rapidly with strong acids. Ytterbium forms various compounds, including oxides, halides, and sulfides.");
            tft.setCursor(4, 252);
            tft.println("- Ytterbium finds applications in various fields such as laser technology,  medical imaging, and nuclear reactors. It is used in the production of high power solid-state lasers, as a dopant in optical fibers, and as a radiation  source in portable X-ray devices.");
          }
          break;
        case 71:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(189); // Phát âm thanh cho chất thứ 69
              Serial.println("OK");
            }
            tft.setTextColor(0x0393, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Lutetium", 240, 10, GFXFF); // Chất thứ 69: Lutetium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Lu", 10, 120, GFXFF);
            tft.drawString("Chemical name: Lutetium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Lanthanide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(71);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("71   174.97");

            tft.setTextColor(0x0393,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Lu");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Luteti");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 174.97 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1925 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3675 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1907");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Lutetium is a silvery-white, rare earth metal. It is relatively stable in airand has a high melting point of 1663°C and a boiling point of 3402°C.      Lutetium is one of the densest and hardest rare earth elements.");
            tft.setCursor(4, 204);
            tft.println("- Lutetium is relatively resistant to oxidation and reacts slowly with water and acids. It forms various compounds including oxides halides and sulfides.Lutetium compounds are used in research and medical applications.");
            tft.setCursor(4, 268);
            tft.println("- Lutetium has limited industrial applications but finds use in research,     particularly in the field of nuclear medicine. It is used as a catalyst in     certain organic reactions and as a phosphor in some LED technologies.");
          }
          break;
        case 72:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(190); // Phát âm thanh cho chất thứ 70
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Hafnium", 240, 10, GFXFF); // Chất thứ 70: Hafnium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Hf", 10, 120, GFXFF);
            tft.drawString("Chemical name: Hafnium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(72);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("72   178.49");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Hf");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Hafni");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 178.49 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 2506 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 4876 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1923");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Hafnium is a lustrous, silvery-gray metal. It has a high melting point of  2233°C and a boiling point of 4603°C. Hafnium is corrosion-resistant and   has good ductility and malleability.");
            tft.setCursor(4, 188);
            tft.println("- Hafnium forms a protective oxide layer that makes it highly resistant to  corrosion. It reacts with oxygen, nitrogen, hydrogen, and halogens to form various compounds. Hafnium compounds are used in the aerospace industry and in nuclear reactors.");
            tft.setCursor(4, 252);
            tft.println("- Hafnium is primarily used in nuclear reactors as control rods due to its high neutron absorption capability. It is also used in aerospace components, such as turbine blades and rocket engines, where its high melting point andstrength are advantageous.");
          }
          break;
        case 73:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(191); // Phát âm thanh cho chất thứ 71
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Tantalum", 240, 10, GFXFF); // Chất thứ 71: Tantalum
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ta", 10, 120, GFXFF);
            tft.drawString("Chemical name: Tantalum", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(73);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("73   180.95");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Ta");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(33, 100);
            tft.setTextSize(1); 
            tft.println("Tantal");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 180.95 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 3290 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 5731 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1802");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Tantalum is a dense, blue-gray metal. It has a high melting point of      3017°C and a boiling point of 5458°C. Tantalum is highly corrosion-resistantand has excellent conductivity.");
            tft.setCursor(4, 188);
            tft.println("- Tantalum forms a protective oxide layer that makes it highly resistant to corrosion. It reacts with acids, but it is stable against most other chemicalsTantalum compounds are used in electronics, chemical processing, and       medical implants.");
            tft.setCursor(4, 252);
            tft.println("- Tantalum is widely used in electronics, particularly in capacitors and highpower resistors, due to its high capacitance and stability. It is also used inchemical processing equipment, surgical implants, and superalloys for jet engines.");
          }
          break;
        case 74:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(192); // Phát âm thanh cho chất thứ 72
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Tungsten", 240, 10, GFXFF); // Chất thứ 72: Tungsten
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: W", 10, 120, GFXFF);
            tft.drawString("Chemical name: Tungsten", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(74);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("74   183.84");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(40, 35);
            tft.setTextSize(3); 
            tft.println("W");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Wolfram");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 183.84 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 3695 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 5828 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Tungsten is a dense, steel-gray metal with the highest melting point of   all elements. It is exceptionally hard and has a high density, making it       suitable for various industrial applications.");
            tft.setCursor(4, 188);
            tft.println("- Tungsten is highly resistant to corrosion and does not react with most   acids. It forms oxides when heated but is generally inert to oxygen at roomtemperature. Tungsten compounds are used in catalysts, pigments, and high  temperature lubricants.");
            tft.setCursor(4, 252);
            tft.println("- Tungsten has widespread use in the manufacturing industry, particularly inthe production of filaments in incandescent light bulbs, electrical contacts, and heating elements due to its high melting point and electrical            conductivity.");
          }
          break;
        case 75:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(193); // Phát âm thanh cho chất thứ 73
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Rhenium", 240, 10, GFXFF); // Chất thứ 73: Rhenium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Re", 10, 120, GFXFF);
            tft.drawString("Chemical name: Rhenium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(75);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("75   186.20");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Re");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Rheni");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 186.20 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 3459 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 5869 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1925");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Rhenium is a silvery-white, dense metal with one of the highest melting   points of all elements. It is exceptionally resistant to heat and wear, makingit valuable in high-temperature applications.");
            tft.setCursor(4, 188);
            tft.println("- Rhenium is resistant to acids and does not react with oxygen at room    temperature. It forms oxides when heated. Rhenium compounds are used as  catalysts in the chemical industry.");
            tft.setCursor(4, 252);
            tft.println("- Rhenium is primarily used in superalloys for jet engines, where its high   melting point and resistance to thermal creep are crucial. It is also used inelectrical contacts, filaments for mass spectrometers, and as a catalyst in  the petroleum industry.");
          }
          break;
        case 76:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(194); // Phát âm thanh cho chất thứ 74
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Osmium", 240, 10, GFXFF); // Chất thứ 74: Osmium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Os", 10, 120, GFXFF);
            tft.drawString("Chemical name: Osmium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(76);

            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("76   190.23");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Os");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Osmi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 190.23 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 3306 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 5285 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1803");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Osmium is a dense, lustrous, bluish-gray metal, known for its hardness andhigh melting point. It is one of the densest naturally occurring elements.");
            tft.setCursor(4, 172);
            tft.println("- Osmium is highly resistant to corrosion and oxidation.It forms compoundswith various elements, including oxygen, sulfur, and halogens. Osmium        tetroxide, a compound of osmium, is highly toxic and is used in staining     biological specimens and in organic synthesis.");
            tft.setCursor(4, 236);
            tft.println("- Osmium has limited commercial applications due to its rarity and toxicity. It is used in alloys, particularly with platinum, to make fountain pen nibs,   electrical contacts, and other items requiring extreme hardness and         durability.");
          }
          break;
        case 77:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(195); // Phát âm thanh cho chất thứ 75
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Iridium", 240, 10, GFXFF); // Chất thứ 75: Iridium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ir", 10, 120, GFXFF);
            tft.drawString("Chemical name: Iridium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(77);

            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("77   192.22");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(40, 35);
            tft.setTextSize(3); 
            tft.println("Ir");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Iridi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 192.22 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 2719.1K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 4701.1K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1803");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Iridium is a dense, silvery-white, transition metal known for its extreme   hardness and resistance to corrosion even at high temperatures. It is one  of the densest and most corrosion-resistant elements.");
            tft.setCursor(4, 188);
            tft.println("- Iridium is highly resistant to corrosion and oxidation. It forms compoundswith various elements, including oxygen, sulfur, and chlorine. Iridium        compounds are used in catalysts, electronics, and organic synthesis.");
            tft.setCursor(4, 236);
            tft.println("- Iridium's hardness and resistance to corrosion make it valuable in        various industrial applications. It is used in spark plugs, electrical contactsand crucibles for high-temperature applications. Additionally, its            radioactive isotopes are used in cancer treatment and in industrial         radiography.");
          }
          break;
        case 78:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(196); // Phát âm thanh cho chất thứ 76
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Platinum", 240, 10, GFXFF); // Chất thứ 76: Platinum
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Pt", 10, 120, GFXFF);
            tft.drawString("Chemical name: Platinum", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(78);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("78    195.1");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Pt");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(28, 100);
            tft.setTextSize(1); 
            tft.println("Platin");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 195.1 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 2041.5K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 4098.1K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1735");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Platinum is a dense, malleable, ductile, and precious transition metal. It   has a silver-white color and is resistant to corrosion, making it highly      valuable in various industrial applications.");
            tft.setCursor(4, 188);
            tft.println("- Platinum is inert and does not oxidize under normal conditions. It forms stable compounds with elements like oxygen, sulfur, and chlorine. Platinum  catalysts are extensively used in chemical reactions and pollution control  devices.");
            tft.setCursor(4, 252);
            tft.println("- Platinum has diverse applications. Its inertness, high melting point and   resistance to corrosion make it ideal for jewelry, electrical contacts, and  laboratory equipment. It is also used in catalytic converters, fuel cells,    and chemotherapy drugs.");
          }
          break;
        case 79:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(197); // Phát âm thanh cho chất thứ 77
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Gold", 240, 10, GFXFF); // Chất thứ 77: Gold
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Au", 10, 120, GFXFF);
            tft.drawString("Chemical name: Gold", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(79);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("79   196.97");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Au");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Gold");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 196.97 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1337.3K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3109.2"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Gold is a dense, soft, shiny, and yellow transition metal. It is highly      malleable and ductile, and an excellent conductor of electricity. Gold is    often found in nuggets or veins in rocks and alluvial deposits.");
            tft.setCursor(4, 188);
            tft.println("- Gold is chemically inert and does not tarnish or corrode. It forms stablecompounds with elements like cyanide and chlorine. Gold is resistant to     acids and bases, making it suitable for various industrial and medical       applications.");
            tft.setCursor(4, 252);
            tft.println("- Gold has been used for millennia for jewelry, currency, and decorative  purposes. It is also widely used in electronics, dentistry, and aerospace    technology. Additionally, gold nanoparticles have applications in cancer    treatment and drug delivery systems.");
          }
          break;
        case 80:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(198); // Phát âm thanh cho chất thứ 78
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Mercury", 240, 10, GFXFF); // Chất thứ 78: Mercury
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Hg", 10, 120, GFXFF);
            tft.drawString("Chemical name: Mercury", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(80);

            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("80   200.59");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Hg");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 110);
            tft.setTextSize(1); 
            tft.println("Mercury");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 200.59 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 234.3 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 629.9 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Mercur is a dense, silvery-white transition metal. It is the only metal     that is liquid at room temperature. Mercury has a high surface tension and forms small droplets.");
            tft.setCursor(4, 188);
            tft.println("- Mercury is relatively inert and does not react with most acids, but it    does react with strong oxidizing agents. It forms amalgams with other metals, allowing it to be used in dentistry and gold mining.");
            tft.setCursor(4, 252);
            tft.println("- Mercury has various applications, including in thermometers, barometers, and fluorescent lights. It is also used in dental amalgams, batteries, and    some industrial processes.");
          }
          break;
        case 81:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(199); // Phát âm thanh cho chất thứ 79
              Serial.println("OK");
            }
            tft.setTextColor(0x8A2BE2, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Thallium", 240, 10, GFXFF); // Chất thứ 79: Thallium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Tl", 10, 120, GFXFF);
            tft.drawString("Chemical name: Thallium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Post-Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(81);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("81   204.38");

            tft.setTextColor(0x8A2BE2,TFT_BLACK);
            tft.setCursor(35, 35);
            tft.setTextSize(3); 
            tft.println("Tl");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Thali");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 204.38 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 577 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1746 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1861");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Thallium is a soft, bluish-white metal. It is highly malleable and can be   easily cut with a knife. Thallium is a poor conductor  of electricity and    heat.");
            tft.setCursor(4, 204);
            tft.println("- Thallium reacts slowly with oxygen and water but dissolves readily in     acids. It forms various compounds, including thallium sulfate and thallium   chloride, which are toxic to humans and other organisms.");
            tft.setCursor(4, 268);
            tft.println("- Thallium has limited commercial applications. Historically, it was used in  rat poisons and insecticides. Its radioactive isotope, thallium-201, is used  in medical imaging for diagnosing heart diseases.");
          }
          break;
        case 82:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(200); // Phát âm thanh cho chất thứ 80
              Serial.println("OK");
            }
            tft.setTextColor(0x8A2BE2, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Lead", 240, 10, GFXFF); // Chất thứ 80: Lead
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Pb", 10, 120, GFXFF);
            tft.drawString("Chemical name: Lead", 10, 180, GFXFF);
            tft.drawString("Chemical group: Post-Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(82);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("82      207.2");

            tft.setTextColor(0x8A2BE2,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Pb");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Lead");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 207.2 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 600.7 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2022.2 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Lead is a dense, soft, and malleable metal. It has a bluish-white color    when freshly cut but tarnishes to dull gray when exposed to air.");
            tft.setCursor(4, 188);
            tft.println("- Lead is relatively unreactive. It forms stable compounds such as lead    oxide and lead sulfate. Lead poisoning is a significant concern due to its  toxicity to humans and the environment.");
            tft.setCursor(4, 252);
            tft.println("- Lead has been used historically in various applications, including         plumbing, batteries, and radiation shielding. However, due to its toxicity, itsuse has decreased, with alternatives being sought.");
          }
          break;
        case 83:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(201); // Phát âm thanh cho chất thứ 81
              Serial.println("OK");
            }
            tft.setTextColor(0x8A2BE2, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Bismuth", 240, 10, GFXFF); // Chất thứ 81: Bismuth
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Bi", 10, 120, GFXFF);
            tft.drawString("Chemical name: Bismuth", 10, 180, GFXFF);
            tft.drawString("Chemical group: Post-Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(83);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("83   208.98");

            tft.setTextColor(0x8A2BE2,TFT_BLACK);
            tft.setCursor(35, 35);
            tft.setTextSize(3); 
            tft.println("Bi");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Bismuth");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 208.98 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 544.6 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1837.2 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: Ancient");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Bismuth is a brittle, lustrous, silvery-white metal with a pink tinge. It     expands when it solidifies, making it useful in certain applications like      casting.");
            tft.setCursor(4, 204);
            tft.println("- Bismuth is relatively stable and does not react with air or water at      ordinary temperatures. However, it forms oxides, sulfides, and halides when heated. It's used in cosmetics, pharmaceuticals, and some alloys.");
            tft.setCursor(4, 268);
            tft.println("- Bismuth finds applications in various fields. Its low toxicity makes it     suitable for pharmaceutical and cosmetic uses. It's also used in alloys for  safety devices such as fire sprinklers and electrical fuses.");
          }
          break;
        case 84:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(202); // Phát âm thanh cho chất thứ 82
              Serial.println("OK");
            }
            tft.setTextColor(0x8A2BE2, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Polonium", 240, 10, GFXFF); // Chất thứ 82: Polonium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Po", 10, 120, GFXFF);
            tft.drawString("Chemical name: Polonium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Post-Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(84);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("84        209");

            tft.setTextColor(0x8A2BE2,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Po");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Poloni");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 209 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 527.2 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 1235.2 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1898");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Polonium is a rare, highly radioactive metal. It has a silver appearance  that quickly tarnishes to a dull gray. Po-210 is the most well-known        isotope and emits alpha particles.");
            tft.setCursor(4, 204);
            tft.println("- Polonium is chemically similar to tellurium and selenium. It forms oxides  and halides but is primarily known for its radioactive decay. It's extremely toxic and presents a significant radiation hazard.");
            tft.setCursor(4, 268);
            tft.println("- Polonium has limited practical applications due to it extreme radioactivityand toxicity. It has historically been used in nuclear physics research and  in devices like antistatic brushes and sources of neutrons.");
          }
          break;
        case 85:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(203); // Phát âm thanh cho chất thứ 83
              Serial.println("OK");
            }
            tft.setTextColor(0x8A2BE2, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Astatine", 240, 10, GFXFF); // Chất thứ 83: Astatine
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: At", 10, 120, GFXFF);
            tft.drawString("Chemical name: Astatine", 10, 180, GFXFF);
            tft.drawString("Chemical group: Post-Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(85);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("85      210");

            tft.setTextColor(0x8A2BE2,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("At");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Astatin");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 210 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 575 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 610 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1940");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Polonium is a rare, highly radioactive metal. It has a silver appearance  that quickly tarnishes to a dull gray. Po-210 is the most well-known        isotope and emits alpha particles.");
            tft.setCursor(4, 188);
            tft.println("- Polonium is chemically similar to tellurium  and selenium. It forms oxides and halides but is primarily known for its radioactive decay. It's            extremelytoxic and presents a significant radiation hazard.");
            tft.setCursor(4, 236);
            tft.println("- Polonium has limited practical applications due to it extreme radioactivityand toxicity. It has historically been used in nuclear physics research and  in devices like antistatic brushes and sources of neutrons.");
          }
          break;
        case 86:
           if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(204); // Phát âm thanh cho chất thứ 84
              Serial.println("OK");
            }
            tft.setTextColor(0xC0E9EF, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Radon", 240, 10, GFXFF); // Chất thứ 84: Radon
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Rn", 10, 120, GFXFF);
            tft.drawString("Chemical name: Radon", 10, 180, GFXFF);
            tft.drawString("Chemical group: Noble Gas", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(86);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("86       222");

            tft.setTextColor(0xC0E9EF,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Ra");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Radon");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 222 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 202 K");
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 211.5 K");
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1900");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Radon is a colorless, odorless, and tasteless noble gas. It is radioactive,emitting alpha, beta, and gamma rays. Radon is denser than air and is often found in soil and rock formations.");
            tft.setCursor(4,188);
            tft.println("- Radon is a noble gas and is generally inert under normal conditions.     However, it can form compounds under extreme conditions. Radon           compoundsare typically unstable and reactive.");
            tft.setCursor(4,236);
            tft.println("- Radon's most notable application is in radiation therapy for cancer      treatment. It is also used in radiography to detect leaks in pipelines and in the study of atmospheric dispersion. Radon is also employed in some       medical research studies.");
          }
          break;
        case 87:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(205); // Phát âm thanh cho chất thứ 85
              Serial.println("OK");
            }
            tft.setTextColor(0x050e, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Francium", 240, 10, GFXFF); // Chất thứ 85: Francium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Fr", 10, 120, GFXFF);
            tft.drawString("Chemical name: Francium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Alkali Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(87);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("87      223");

            tft.setTextColor(0x050e,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Fr");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Franci");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 223 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 300.1 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 950.1 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1939");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Francium is a highly radioactive alkali metal. It is the second rarest     naturally occurring element. Due to its extreme rarity and radioactivity,    only tiny amounts of francium have been produced and studied.");
            tft.setCursor(4, 188);
            tft.println("- Francium is highly reactive, readily reacting with water to produce       hydrogen gas and aqueous francium hydroxide. It's the most electropositive of all known elements, making it extremely reactive with other elements.");
            tft.setCursor(4, 236);
            tft.println("- Due to its extreme rarity and high radioactivity, francium has no         significant commercial applications. However, it has been used in scientific research to study the behavior of alkali metals and nuclear reactions.");
          }
          break;
        case 88:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(206); // Phát âm thanh cho chất thứ 86
              Serial.println("OK");
            }
            tft.setTextColor(0xf980, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Radium", 240, 10, GFXFF); // Chất thứ 86: Radium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ra", 10, 120, GFXFF);
            tft.drawString("Chemical name: Radium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Alkaline Earth Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(88);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("88        226");

            tft.setTextColor(0xf980,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Ra");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Radi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 226 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 969.1 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 2010.1 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1898");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Radium is a highly radioactive alkaline earth metal. It appears as silvery-white metallic radium when freshly prepared, but it readily oxidizes on      exposure to air, turning black over time due to the formation of radium    oxide.");
            tft.setCursor(4, 204);
            tft.println("- Radium is highly reactive and forms compounds with various elements,    such as radium chloride and radium bromide. These compounds exhibit       luminescence, emitting a faint blue glow in the dark.");
            tft.setCursor(4, 252);
            tft.println("- Historically, radium was used in self-luminous paints for watch dials,      aircraft switches, and instrument dials due to its luminescent properties.    However, its use declined due to its highly radioactive nature and          associated health risks.");
          }
          break;
        case 89:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(207); // Phát âm thanh cho chất thứ 87
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Actinium", 240, 10, GFXFF); // Chất thứ 87: Actinium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ac", 10, 120, GFXFF);
            tft.drawString("Chemical name: Actinium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(89);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("89        227");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Ac");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Actini");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 227 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1323.1 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3470 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1899");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Actinium is a silvery-white, radioactive metal. It glows in the dark due toits intense radioactivity. Actinium readily reacts with oxygen and moisture  in the air, forming a white oxide coating.");
            tft.setCursor(4, 188);
            tft.println("- Actinium is highly radioactive and exhibits similar chemical properties to other actinides. It reacts with acids to form salts, and it can form various compounds with halogens and other elements.");
            tft.setCursor(4, 236);
            tft.println("- Actinium has limited commercial applications due to its high radioactivity.It has been used in scientific research and as a neutron source. Actinium  225 isotope has potential applications in targeted alpha-particle therapy   for cancer treatment.");
          }
          break;
        case 90:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(208); // Phát âm thanh cho chất thứ 88
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Thorium ", 240, 10, GFXFF); // Chất thứ 88: Rutherfordium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Th", 10, 120, GFXFF);
            tft.drawString("Chemical name: Thorium ", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
        
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(90);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("90   232.03");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Th");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Thori");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 232.03 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 2028 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 5060 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1828");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Thorium is a silvery, radioactive metal. It is relatively soft and can be  cut with a knife. Thorium is paramagnetic and exhibits superconductivity    below 1.4K.");
            tft.setCursor(4, 188);
            tft.println("- Thorium reacts slowly with oxygen, water, and acids to form thorium      dioxide and other compounds. It is primarily found in the +4 oxidation stateand forms stable complexes with ligands.");
            tft.setCursor(4, 236);
            tft.println("- Thorium has been explored as a potential fuel for nuclear reactors due  to its ability to undergo nuclear fission. It is also used in specialized      applications such as gas mantles, high-temperature ceramics, and aerospace alloys.");
          }
          break;
        case 91:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(209); // Phát âm thanh cho chất thứ 89
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Protactinium", 240, 10, GFXFF); // Chất thứ 89: Dubnium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Pa", 10, 120, GFXFF);
            tft.drawString("Chemical name: Protactinium ", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(91);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("91   231.04");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Pa");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(15, 100);
            tft.setTextSize(1); 
            tft.println("Protactini");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 231.04 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 1814.1K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 4273.1K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1913");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Protactinium is a dense, silvery-gray metal. It is highly radioactive and  undergoes decay into other elements. Protactinium has no stable isotopes.");
            tft.setCursor(4, 188);
            tft.println("- Protactinium reacts slowly with oxygen, water, and acids to form various compounds, primarily in the +5 oxidation state. It exhibits similarities to    other actinides in its chemical behavior.");
            tft.setCursor(4, 252);
            tft.println("- Due to its scarcity and radioactivity, protactinium has limited practical   applications. It has been used in research related to nuclear energy and   isotope production. Its scarcity and radioactive properties make it         unsuitable for widespread industrial use.");
          }
          break;
        case 92:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(210); // Phát âm thanh cho chất thứ 92
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Uranium", 240, 10, GFXFF); // Chất thứ 92: Uranium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: U", 10, 120, GFXFF);
            tft.drawString("Chemical name: Uranium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(92);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("92   238.03");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(40, 35);
            tft.setTextSize(3); 
            tft.println("U");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(35, 100);
            tft.setTextSize(1); 
            tft.println("Urani");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 238.03 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1405.3K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:4404.1K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1789");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Uranium is a dense, silvery-white, metallic element. It's weakly radioactiveand has the highest atomic weight of the naturally occurring elements.      Uranium is primarily found in ores like uraninite and carnotite.");
            tft.setCursor(4, 188);
            tft.println("- Uranium is reactive, forming various compounds including oxides, halides, and sulfides. It is known for its ability to undergo nuclear fission,          releasingvast amounts of energy. Uranium compounds are utilized in nuclearreactors, military applications, and medical treatments.");
            tft.setCursor(4, 252);
            tft.println("- Uranium is primarily used as fuel in nuclear reactors for energy         production through fission. It's also utilized in military weapons, notably   nuclear warheads, and in uranium compounds for radiation therapy in       cancer treatment.");
          }
          break;
        case 93:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(211); // Phát âm thanh cho chất thứ 93
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Neptunium", 240, 10, GFXFF); // Chất thứ 93: Neptunium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Np", 10, 120, GFXFF);
            tft.drawString("Chemical name: Neptunium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(93);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("93        237");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Np");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Neptuni");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 237 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 912 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 4175 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1940");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Neptunium is a silvery, radioactive metal. It is the first transuranic      element and belongs to the actinide series. Neptunium is typically found in trace amounts in uranium ores.");
            tft.setCursor(4, 204);
            tft.println("- Neptunium exhibits both +3 and +4 oxidation states, forming various      compounds such as oxides, halides, and coordination complexes. It is highly reactive and undergoes corrosion in air.");
            tft.setCursor(4, 268);
            tft.println("- Neptunium has limited practical applications due to its scarcity and       radioactivity. It has been used in research for the synthesis of heavy      isotopes and in nuclear fuels for experimental breeder reactors.");
          }
          break;
        case 94:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(212); // Phát âm thanh cho chất thứ 94
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Plutonium", 240, 10, GFXFF); // Chất thứ 94: Plutonium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Pu", 10, 120, GFXFF);
            tft.drawString("Chemical name: Plutonium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(94);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("94       244");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Pu");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Plutoni");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 244 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature: 912.5 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature: 3505 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1940");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Plutonium is a silvery-white, radioactive metal. It is highly malleable and ductile, with six allotropes. Plutonium is primarily produced in nuclear      reactors by irradiating uranium-238.");
            tft.setCursor(4, 188);
            tft.println("- Plutonium is highly reactive, forming various compounds with elements    like oxygen, hydrogen, and halogens. It exhibits multiple oxidation states,    including +3, +4, +5, and +6.");
            tft.setCursor(4, 236);
            tft.println("- Plutonium is primarily used in nuclear weapons and reactors, where it    serves as fuel for both fission and fusion reactions. It is also employed inradioisotope thermoelectric generators for space missions and as a power  source in pacemakers.");
          }
          break;
        case 95:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(213); // Phát âm thanh cho chất thứ 95
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Americium", 240, 10, GFXFF); // Chất thứ 95: Americium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Am", 10, 120, GFXFF);
            tft.drawString("Chemical name: Americium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(95);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("95       243");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(10, 35);
            tft.setTextSize(3); 
            tft.println("Am");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Americi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 243 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1449.1K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:2880K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1944");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Americium is a silvery-white, radioactive metal. It is denser than lead and has a higher melting point than uranium. Americium is primarily produced in nuclear reactors and is used in smoke detectors.");
            tft.setCursor(4, 188);
            tft.println("- Americium is highly reactive, forming various compounds with elements   like oxygen, nitrogen, and halogens. It exhibits multiple oxidation states,   including +3, +4, +5, and +6.");
            tft.setCursor(4, 236);
            tft.println("- Americium is mainly used in smoke detectors due to its ability to ionize  air particles, facilitating the detection of smoke. It is also used in some    industrial gauges and in research for its radioactivity.");
          }
          break;
        case 96:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(214); // Phát âm thanh cho chất thứ 96
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Curium", 240, 10, GFXFF); // Chất thứ 96: Curium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Cm", 10, 120, GFXFF);
            tft.drawString("Chemical name: Curium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(96);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("96       247");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(10, 35);
            tft.setTextSize(3); 
            tft.println("Cm");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Curium");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 247 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1620"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:3383"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1944");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Curium is a silvery, radioactive metal. It has a relatively high melting point and is ductile. Curium is artificially produced in nuclear reactors and is one of the transuranic elements.");
            tft.setCursor(4, 188);
            tft.println("- Curium is highly reactive, forming various compounds with elements like  oxygen, nitrogen and halogens. It exhibits multiple oxidation states including +3 and +4.");
            tft.setCursor(4, 236);
            tft.println("- Curium is primarily used in research and has limited practical applicationsdue to its radioactivity. It is used as a neutron source in portable neutronradiography devices and as a target material for the production of heavier transuranic elements.");
          }
          break; 
        case 97:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(215); // Phát âm thanh cho chất thứ 97
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Berkelium", 240, 10, GFXFF); // Chất thứ 97: Berkelium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Bk", 10, 120, GFXFF);
            tft.drawString("Chemical name: Berkelium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(97);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("97       249");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Bk");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(20, 100);
            tft.setTextSize(1); 
            tft.println("Berkeli");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 249 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1258 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:2900.1K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1949");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Berkelium is a silvery-white, radioactive metal. It is artificially produced in nuclear reactors and is one of the transuranic elements. Berkelium is    denser than lead and exhibits paramagnetic properties.");
            tft.setCursor(4, 204);
            tft.println("- Berkelium is highly reactive, forming various compounds with elements    like oxygen, nitrogen, and halogens. It primarily exists in the +3 oxidation  state in compounds.");
            tft.setCursor(4, 268);
            tft.println("- Berkelium is primarily used in research and has limited practical          applications due to its radioactivity. It is used in the synthesis of heavier transuranic elements and in the study of nuclear properties.");
          }
          break;
        case 98:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(216); // Phát âm thanh cho chất thứ 98
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Californium", 240, 10, GFXFF); // Chất thứ 98: Californium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Cf", 10, 120, GFXFF);
            tft.drawString("Chemical name: Californium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(98);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("98       251");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Cf");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(15, 100);
            tft.setTextSize(1); 
            tft.println("Californi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 251 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1172 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:1745.1 K"); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1950");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Californium is a radioactive metallic element. It is silvery-white in color and is the heaviest element that can be formed through neutron bombardmenof curium. Californium is highly radioactive and undergoes spontaneous    fission.");
            tft.setCursor(4, 204);
            tft.println("- Californium exhibits diverse chemical behavior due to its high atomic     number and electronic configuration. It forms various compounds, primarily in the +3 oxidation state, and is mainly used in research and the productionof heavier elements.");
            tft.setCursor(4, 268);
            tft.println("- Californium is primarily used as a neutron source in nuclear reactors andfor various applications in neutron activation analysis. It is also used in   portable metal detectors and in nuclear medicine for cancer treatment.");
          }
          break;
        case 99:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(217); // Phát âm thanh cho chất thứ 99
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Einsteinium", 240, 10, GFXFF); // Chất thứ 99: Einsteinium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Es", 10, 120, GFXFF);
            tft.drawString("Chemical name: Einsteinium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(99);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(15, 10);
            tft.setTextFont(4);
            tft.println("99       252");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Es");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Einsteini");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 252 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1133.1K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1952");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Einsteinium is a synthetic element and a member of the actinide series. It is radioactive and typically exists in trace amounts. Due to its short half-life, its physical properties are not well-characterized, including its melting and boiling points.");
            tft.setCursor(4, 204);
            tft.println("- Einsteinium is highly reactive and forms compounds primarily in the +3   oxidation state. It exhibits similarities to other actinides in its chemical     behavior, but its reactivity decreases with increasing atomic number.");
            tft.setCursor(4, 252);
            tft.println("- Einsteinium is primarily used for scientific research purposes, particularlyin studies related to nuclear physics and the synthesis of heavier elements.");
          }
          break;
        case 100:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(218); // Phát âm thanh cho chất thứ 100
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Fermium", 240, 10, GFXFF); // Chất thứ 100: Fermium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Fm", 10, 120, GFXFF);
            tft.drawString("Chemical name: Fermium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(100);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("100       257");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Fm");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Fermi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 257 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1800 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1953");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Fermium is a synthetic element and a member of the actinide series. It is highly radioactive and typically exists in trace amounts. Due to its short   half-life, its physical properties such as melting and boiling points remain  unknown.");
            tft.setCursor(4, 204);
            tft.println("- Fermium exhibits primarily the +3 oxidation state and is highly reactive.  It forms compounds with oxygen, halogens, and other elements. Fermium     compounds are primarily of research interest due to its radioactivity and     limited availability.");
            tft.setCursor(4, 268);
            tft.println("- Fermium is primarily used for scientific research purposes, particularly instudies related to nuclear physics, the synthesis of heavy elements, and    understanding the behavior of radioactive materials.");
          }
          break; 
        case 101:
           if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(219); // Phát âm thanh cho chất thứ 101
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Mendelevium", 240, 10, GFXFF); // Chất thứ 101: Mendelevium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Md", 10, 120, GFXFF);
            tft.drawString("Chemical name: Mendelevium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(101);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("101       258");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Md");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(15, 100);
            tft.setTextSize(1); 
            tft.println("Mendelevi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 258 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1100 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1955");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Mendelevium is a radioactive synthetic element belonging to the actinide series. Its physical properties such as melting and boiling points are not   well-established due to its short half-life and limited availability.");
            tft.setCursor(4, 188);
            tft.println("- Mendelevium primarily exhibits the +2 and +3 oxidation states. It reacts  with oxygen, halogens, and other elements to form various compounds.     Mendelevium compounds are primarily of research interest due to its          radioactivity and limited availability.");
            tft.setCursor(4, 252);
            tft.println("- Mendelevium is primarily used for scientific research purposes,           particularly in studies related to nuclear physics, the synthesis of heavy   elements, and understanding the behavior of radioactive materials.");
          }
          break;
        case 102:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(220); // Phát âm thanh cho chất thứ 102
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Nobelium", 240, 10, GFXFF); // Chất thứ 102: Nobelium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: No", 10, 120, GFXFF);
            tft.drawString("Chemical name: Nobelium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(102);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("102      259");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("No");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Nobeli");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 259 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1100 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1958");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Nobelium is a synthetic radioactive element. Due to its short half-life, itsphysical properties such as melting and boiling points are not precisely    known. It is predicted to have metallic properties similar to other actinides.");
            tft.setCursor(4, 188);
            tft.println("- Nobelium's chemistry is primarily studied in trace amounts due to its       limited availability. It likely exhibits properties consistent with other       actinides, such as forming complexes with ligands and displaying multiple    oxidation states.");
            tft.setCursor(4, 252);
            tft.println("- Nobelium is exclusively used for scientific research purposes, particularly in studies related to the synthesis of heavy elements, nuclear physics, and understanding the behavior of radioactive materials.");
          }
          break;
        case 103:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(221); // Phát âm thanh cho chất thứ 103
              Serial.println("OK");
            }
            tft.setTextColor(0xe4e0, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Lawrencium", 240, 10, GFXFF); // Chất thứ 103: Lawrencium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Lr", 10, 120, GFXFF);
            tft.drawString("Chemical name: Lawrencium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Actinide", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(103);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("103      262");

            tft.setTextColor(0xe4e0,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Lr");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Lawrenci");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 262 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:1900 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1961");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Lawrencium is a synthetic radioactive element. Its physical properties    such as melting and boiling points are not precisely known due to its short half-life and limited availability. It is predicted to be a silvery-white,       metallic element.");
            tft.setCursor(4, 204);
            tft.println("- Lawrencium's chemistry is primarily studied in trace amounts due to its   short half-life. It likely exhibits properties consistent with other actinides, such as forming complexes with ligands and displaying multiple oxidation     states.");
            tft.setCursor(4, 268);
            tft.println("- Lawrencium is exclusively used for scientific research purposes,          particularly in studies related to the synthesis of heavy elements, nuclear  physics, and understanding the behavior of radioactive materials.");
          }
          break;
        case 104:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(222); // Phát âm thanh cho chất thứ 104
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Rutherfordium", 240, 10, GFXFF); // Chất thứ 104: Rutherfordium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Rf", 10, 120, GFXFF);
            tft.drawString("Chemical name: Rutherfordium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(104);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("104      261");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Rf");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(10, 100);
            tft.setTextSize(1); 
            tft.println("Rutherfordi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 261 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:2373.1 K"); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1969");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Rutherfordium is a synthetic radioactive element. Its physical properties  such as melting and boiling points are not well-defined due to its short    half-life and limited availability for study. It is predicted to be a metallic  element with properties similar to hafnium.");
            tft.setCursor(4, 204);
            tft.println("- Being a transactinide element, Rutherfordium's chemical properties are    primarily theoretical and extrapolated from its position in the periodic     table. It is expected to display properties consistent with other group 4     elements, such as forming stable compounds with oxygen and halogens.");
            tft.setCursor(4, 268);
            tft.println("- Due to its synthetic and radioactive nature, Rutherfordium has no        practical applications and is solely used for fundamental research          purposes, particularly in the study of heavy elements and nuclear physics.");
          }
          break;
        case 105:
            if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(223); // Phát âm thanh cho chất thứ 105
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Dubnium", 240, 10, GFXFF); // Chất thứ 105: Dubnium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Db", 10, 120, GFXFF);
            tft.drawString("Chemical name: Dubnium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(105);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("105      268");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Db");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Dubni");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 262 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1967");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Dubnium is a synthetic radioactive element. Due to its short half-life and limited availability for study, its physical properties such as melting and   boiling points are not well-defined. It is predicted to be a metallic element.");
            tft.setCursor(4, 188);
            tft.println("- Being a transactinide element, Dubnium's chemical properties are primarily theoretical. It is expected to react with oxygen, halogens, and possibly    other nonmetals to form various compounds, though specific compounds    have not been characterized due to its scarcity.");
            tft.setCursor(4, 252);
            tft.println("- Dubnium's practical applications are limited due to its synthetic and      radioactive nature. It is primarily used for fundamental research purposes, particularly in the study of heavy elements and nuclear physics.");
          }
          break;
        case 106:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(224); // Phát âm thanh cho chất thứ 106
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Seaborgium", 240, 10, GFXFF); // Chất thứ 106: Seaborgium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Sg", 10, 120, GFXFF);
            tft.drawString("Chemical name: Seaborgium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(106);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("106      271");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Sg");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Seaborgi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 266 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1974");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Seaborgium is a synthetic element and is highly radioactive. It has a     very short half-life, making it difficult to study.");
            tft.setCursor(4, 172);
            tft.println("- Seaborgium is expected to exhibit properties of transition metals due to its position in the periodic table.");
            tft.setCursor(4,204);
            tft.println("- Due to its extreme rarity and short-lived nature, seaborgium currently   has no practical applications and is primarily of scientific interest in       understanding the properties of superheavy elements.");
          }
          break;
        case 107:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(225); // Phát âm thanh cho chất thứ 107
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Bohrium", 240, 10, GFXFF); // Chất thứ 107: Bohrium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Bh", 10, 120, GFXFF);
            tft.drawString("Chemical name: Bohrium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(107);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("107      270");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Bh");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(40, 100);
            tft.setTextSize(1); 
            tft.println("Bohri");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 270 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1981");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Bohrium is a synthetic element and a member of the transactinide series. Due to its synthetic nature and short half-life, its physical properties such as melting and boiling points have not been accurately determined. It is    expected to be a solid metal at room temperature.");
            tft.setCursor(4, 204);
            tft.println("- Being a transactinide element, Bohrium's chemical properties are primarilytheoretical. It is predicted to be highly reactive and capable of forming   compounds with various elements, though specific compounds have not beencharacterized due to its limited availability.");
            tft.setCursor(4, 268);
            tft.println("- Bohrium is predominantly used in scientific research, particularly in the  exploration of heavy elements and nuclear physics. Its short half-life and  limited availability restrict its applications solely to fundamental research.");
          }
          break;
        case 108:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(226); // Phát âm thanh cho chất thứ 108
              Serial.println("OK");
            }
            tft.setTextColor(0x7811, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Hassium", 240, 10, GFXFF); // Chất thứ 108: Hassium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Hs", 10, 120, GFXFF);
            tft.drawString("Chemical name: Hassium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Transition Metal", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(108);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("108      277");

            tft.setTextColor(0x7811,TFT_BLACK);
            tft.setCursor(22, 35);
            tft.setTextSize(3); 
            tft.println("Hs");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(33, 100);
            tft.setTextSize(1); 
            tft.println("Hassi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 277 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1984");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Hassium is a synthetic element and belongs to the transition metal group.It is predicted to be a solid metal with a silvery appearance.");
            tft.setCursor(4, 188);
            tft.println("- Due to its high atomic number and placement in the periodic table,       hassium is expected to exhibit properties similar to other transactinide      elements. It may demonstrate high reactivity and form compounds with otherelements.");
            tft.setCursor(4, 268);
            tft.println("- Hassium's applications are limited to scientific research and              experimentation due to its extremely short half-life and the challenges      associated with its production and handling.");
          }
          break;
        case 109:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(227); // Phát âm thanh cho chất thứ 109
              Serial.println("OK");
            }
            tft.setTextColor(TFT_GREY, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Meitnerium", 240, 10, GFXFF); // Chất thứ 109: Meitnerium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Mt", 10, 120, GFXFF);
            tft.drawString("Chemical name: Meitnerium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Undefined Characteristic", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(109);

            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("109      278");

            tft.setTextColor(TFT_GREY,TFT_BLACK);
            tft.setCursor(25, 35);
            tft.setTextSize(3); 
            tft.println("Mt");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Meitneri");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 278 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1982");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Meitnerium is a synthetic element and belongs to the transition metal     group. It is expected to be a solid metal with a silvery-white appearance,   although specific physical properties are difficult to determine due to its  limited production and short half-life.");
            tft.setCursor(4, 204);
            tft.println("- Meitnerium's chemical properties are predicted to resemble those of its  homologues in Group 9 of the periodic table, such as cobalt, rhodium, and  iridium. It is likely to exhibit a range of oxidation states and reactivity    with other elements.");
            tft.setCursor(4, 268);
            tft.println("- Meitnerium has no practical applications beyond scientific research due  to its extremely limited production and unstable nature.");
          }
          break;
        case 110:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(228); // Phát âm thanh cho chất thứ 110
              Serial.println("OK");
            }
            tft.setTextColor(TFT_GREY, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Darmstadtium", 240, 10, GFXFF); // Chất thứ 110: Darmstadtium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ds", 10, 120, GFXFF);
            tft.drawString("Chemical name: Darmstadtium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Undefined Characteristic", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(110);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("110      281");

            tft.setTextColor(TFT_GREY,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Ds");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(10, 100);
            tft.setTextSize(1); 
            tft.println("Darmstadti");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 281 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1994");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Darmstadtium is a synthetic element and a member of the transition metal group. It is predicted to be a solid metal, but specific physical properties  are challenging to determine due to it limited production and short half-life");
            tft.setCursor(4, 204);
            tft.println("- Darmstadtium is expected to exhibit properties similar to other Group 10 elements like nickel, palladium, and platinum. It would likely have a high     reactivity with other elements, particularly halogens.");
            tft.setCursor(4, 268);
            tft.println("- Due to its extreme rarity and short half-life, Darmstadtium currently has no practical applications beyond fundamental scientific research.");
          }
          break;
        case 111:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(229); // Phát âm thanh cho chất thứ 111
              Serial.println("OK");
            }
            tft.setTextColor(TFT_GREY, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Roentgenium", 240, 10, GFXFF); // Chất thứ 111: Roentgenium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Rg", 10, 120, GFXFF);
            tft.drawString("Chemical name: Roentgenium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Undefined Characteristic", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(111);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("111      282");

            tft.setTextColor(TFT_GREY,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Rg");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(10, 110);
            tft.setTextSize(1); 
            tft.println("Roentgeni");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 282 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1994");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Roentgenium is a synthetic element and belongs to the group of          transition metals. It is expected to be a solid metal with a silvery-white    appearance.");
            tft.setCursor(4, 188);
            tft.println("- Due to its high atomic number, Roentgenium is predicted to be highly     unstable and radioactive, decaying quickly by emitting alpha particles. It    likely exhibits properties similar to other Group 11 elements like gold and  copper.");
            tft.setCursor(4, 268);
            tft.println("- Roentgenium's practical applications are limited due to its instability and short half-life. It serves mainly as a subject of scientific research to      better understand the behavior of superheavy elements.");
          }
          break;
        case 112:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(230); // Phát âm thanh cho chất thứ 112
              Serial.println("OK");
            }
            tft.setTextColor(TFT_GREY, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Copernicium", 240, 10, GFXFF); // Chất thứ 112: Copernicium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Cn", 10, 120, GFXFF);
            tft.drawString("Chemical name: Copernicium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Undefined Characteristic", 10, 240, GFXFF);
          }
          if (properties >= 1) {
            if (properties == 2) {
              player.playMp3Folder(112);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("112      285");

            tft.setTextColor(TFT_GREY,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Cn");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(13, 100);
            tft.setTextSize(1); 
            tft.println("Copernici");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 285 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1996");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Copernicium is a synthetic element and one of the heaviest elements     known. It is predicted to be a solid at room temperature, likely a silvery   metal. Due to its synthetic nature and short half-life it physical properties are still under investigation.");
            tft.setCursor(4, 204);
            tft.println("- Copernicium is expected to exhibit properties similar to other elements inthe same group, such as mercury. It may be a noble gas or exhibit noble    gas-like behavior.");
            tft.setCursor(4, 252);
            tft.println("- Copernicium currently has no practical applications due to its short-livednature and high radioactivity. Its primary use is in scientific research to   understand the behavior of superheavy elements.");
          }
          break;
        case 113:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(231); // Phát âm thanh cho chất thứ 113
              Serial.println("OK");
            }
            tft.setTextColor(TFT_GREY, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Nihonium", 240, 10, GFXFF); // Chất thứ 113: Nihonium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Nh", 10, 120, GFXFF);
            tft.drawString("Chemical name: Nihonium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Undefined Characteristic", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(113);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("113      286");

            tft.setTextColor(TFT_GREY,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Nh");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Nihoni");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 286 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 2003");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Nihonium is a synthetic element and one of the heaviest elements known. It is predicted to be a solid at room temperature, likely a silvery metal. Dueto its synthetic nature and short half-life, its physical properties are still  under investigation.");
            tft.setCursor(4, 204);
            tft.println("- Nihonium is expected to exhibit properties similar to other elements in   the same group, such as thallium and bismuth. It may be reactive, forming   compounds with other elements.");
            tft.setCursor(4, 252);
            tft.println("- Nihonium currently has no practical applications due to its short-lived   nature and high radioactivity. Its primary use is in scientific research to   understand the behavior of superheavy elements.");
          }
          break;
        case 114:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(232); // Phát âm thanh cho chất thứ 114
              Serial.println("OK");
            }
            tft.setTextColor(TFT_GREY, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Flerovium", 240, 10, GFXFF); // Chất thứ 114: Flerovium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Fl", 10, 120, GFXFF);
            tft.drawString("Chemical name: Flerovium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Undefined Characteristic", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(114);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("114      289");

            tft.setTextColor(TFT_GREY,TFT_BLACK);
            tft.setCursor(35, 35);
            tft.setTextSize(3); 
            tft.println("Fl");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(30, 100);
            tft.setTextSize(1); 
            tft.println("Flerovi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 289 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 1998");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Flerovium is a synthetic element and one of the heaviest elements knownIt is predicted to be a solid at room temperature, likely a silvery metal.    Due to its synthetic nature and short half-life, its physical properties are  still under investigation.");
            tft.setCursor(4, 204);
            tft.println("- Flerovium is expected to exhibit properties similar to other elements in  the same group, such as lead and tin. It may be reactive, forming           compounds with other elements.");
            tft.setCursor(4, 252);
            tft.println("- Flerovium currently has no practical applications due to its short-lived  nature and high radioactivity. Its primary use is in scientific research to   understand the behavior of superheavy elements.");
          }
          break;
        case 115:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(233); // Phát âm thanh cho chất thứ 115
              Serial.println("OK");
            }
            tft.setTextColor(TFT_GREY, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Moscovium", 240, 10, GFXFF); // Chất thứ 115: Moscovium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Mc", 10, 120, GFXFF);
            tft.drawString("Chemical name: Moscovium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Undefined Characteristic", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(115);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("115      288");

            tft.setTextColor(TFT_GREY,TFT_BLACK);
            tft.setCursor(20, 35);
            tft.setTextSize(3); 
            tft.println("Mc");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(25, 100);
            tft.setTextSize(1); 
            tft.println("Moscovi");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 288 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 2003");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Moscovium is a synthetic element and one of the heaviest elements knownIt is predicted to be a solid at room temperature, likely a silvery metal. Dueto its synthetic nature and short half-life, its physical properties are still  under investigation.");
            tft.setCursor(4, 204);
            tft.println("- Moscovium is expected to exhibit properties similar to other elements in the boron group. It may be reactive, forming compounds with other         elements.");
            tft.setCursor(4, 252);
            tft.println("- Moscovium currently has no practical applications due to its short-lived nature and high radioactivity. Its primary use is in scientific research to   understand the behavior of superheavy elements.");
          }
          break;
        case 116:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(234); // Phát âm thanh cho chất thứ 116
              Serial.println("OK");
            }
            tft.setTextColor(TFT_GREY, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Livermorium", 240, 10, GFXFF); // Chất thứ 116: Livermorium
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Lv", 10, 120, GFXFF);
            tft.drawString("Chemical name: Livermorium", 10, 180, GFXFF);
            tft.drawString("Chemical group: Undefined Characteristic", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(116);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("116      293");

            tft.setTextColor(TFT_GREY,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Lv");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(15, 100);
            tft.setTextSize(1); 
            tft.println("Livermori");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 293 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 2000");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Livermorium is a synthetic element and one of the heaviest elements     known. It is predicted to be a solid at room temperature, likely a silvery   metal. Due to its synthetic nature and short half-life, its physical          properties are still under investigation.");
            tft.setCursor(4, 204);
            tft.println("- Livermorium is expected to exhibit properties similar to other members ofthe chalcogen group, such as oxygen and sulfur. It is likely to be highly    reactive, forming compounds with metals and nonmetals.");
            tft.setCursor(4, 252);
            tft.println("- Livermorium currently has no practical applications due to its short-livednature and high radioactivity. Its primary use is in scientific research to   understand the behavior of superheavy elements.");
          }
          break;
        case 117:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(235); // Phát âm thanh cho chất thứ 117
              Serial.println("OK");
            }
            tft.setTextColor(TFT_GREY, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Tennessine", 240, 10, GFXFF); // Chất thứ 117: Tennessine
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Ts", 10, 120, GFXFF);
            tft.drawString("Chemical name: Tennessine", 10, 180, GFXFF);
            tft.drawString("Chemical group: Undefined Characteristic", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(117);
            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("117      294");

            tft.setTextColor(TFT_GREY,TFT_BLACK);
            tft.setCursor(30, 35);
            tft.setTextSize(3); 
            tft.println("Te");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(5, 100);
            tft.setTextSize(1); 
            tft.println("Tennessine");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 294 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 2010");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("-Tennessine is a synthetic element and one of the heaviest elements knownIt is predicted to be a solid at room temperature, likely a silvery-white     metal, but its exact physical properties are still being researched due to its instability and short half-life.");
            tft.setCursor(4, 204);
            tft.println("- Tennessine is expected to exhibit properties similar to other halogens    due to its position in the periodic table. It is likely to be highly reactive  and can form compounds with metals.");
            tft.setCursor(4,252);
            tft.println("-Tennessine is expected to exhibit properties similar to other halogens dueto its position in the periodic table. It is likely to be highly reactive and  can form compounds with metals.");
          }
          break;
        case 118:
          if (name >= 1) {
            if (name == 2) {
              player.playMp3Folder(236); // Phát âm thanh cho chất thứ 118
              Serial.println("OK");
            }
            tft.setTextColor(TFT_GREY, TFT_BLACK);
            tft.setFreeFont(FF32);
            tft.setTextDatum(TC_DATUM);
            tft.drawString("Oganesson", 240, 10, GFXFF); // Chất thứ 118: Oganesson
            tft.setTextDatum(L_BASELINE);
            tft.setTextColor(0xFFFF, TFT_BLACK);
            tft.setFreeFont(FF18);
            tft.drawString("Chemical symbol: Og", 10, 120, GFXFF);
            tft.drawString("Chemical name: Oganesson", 10, 180, GFXFF);
            tft.drawString("Chemical group: Undefined Characteristic", 10, 240, GFXFF);
            tft.fontHeight(GFXFF);
          }
          if (properties >= 1) {
            if (properties >= 2) {
              player.playMp3Folder(118);

            }
            tft.setTextSize(1);
            tft.setTextColor(0xF9F400,TFT_BLACK);
            tft.setCursor(10, 10);
            tft.setTextFont(4);
            tft.println("118      294");

            tft.setTextColor(TFT_GREY,TFT_BLACK);
            tft.setCursor(15, 35);
            tft.setTextSize(3); 
            tft.println("Og");

            tft.setTextColor(TFT_WHITE,TFT_BLACK);
            tft.setCursor(5, 110);
            tft.setTextSize(1); 
            tft.println("Oganesson");

            tft.setTextColor(0xFCDAD5,TFT_BLACK);
            tft.setCursor(140, 10);
            tft.setTextFont(4); 
            tft.println("Atomic mass: 294 u");
            tft.setCursor(140, 43);
            tft.setTextFont(4); 
            tft.println("Melting temperature:..."); // nong chay
            tft.setCursor(140,76);
            tft.setTextFont(4); 
            tft.println("Boiling temperature:..."); // soi
            tft.setCursor(140, 109);
            tft.setTextFont(4); 
            tft.println("Date of discovery: 2002");

            tft.setTextColor(0xFFFF33,TFT_BLACK);
            tft.setTextFont(2); 
            tft.setCursor(4, 140);
            tft.println("- Oganesson is a synthetic element and is the heaviest element in the      periodic table. It is predicted to be a gas at room temperature and is      highly radioactive, making its physical properties difficult to study.");
            tft.setCursor(4, 204);
            tft.println("- Oganesson likely exhibits noble gas-like properties due to its position in the periodic table. It is expected to be inert and unreactive under normal  conditions.");
            tft.setCursor(4,268);
            tft.println("- Due to its extreme rarity and short-lived nature, oganesson currently hasno practical applications and is primarily of scientific interest in           understanding the properties of superheavy elements.");
          }
          break;
      }
    }
  }
}

/*
   line 1: 140
   line 2: 156
   line 3: 172
   line 4: 188
   line 5: 204
   line 6: 220
   line 7: 236
   line 8: 252
   line 9: 268
   line 10: 284
   line 11: 300

  */

void loop() {
  if (mySerial.available()>0) {
    int receivedValue = mySerial.parseInt();
    if (receivedValue != 0) { 
      key = receivedValue;
      if (key != previousKey && key != 129 && key != 130) { 
        info(key);
        previousKey = key;
      }
      if(key == 129 || key == 130){
        info(key);
        previousKey = key;
      }
      Serial.print(key);
    }
  }
}



