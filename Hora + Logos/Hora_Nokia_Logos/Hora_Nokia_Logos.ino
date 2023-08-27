// LINK PARA HACER DIBUJOS MONOCROMÁTICO BMP 84X48 https://javl.github.io/image2cpp/
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const char* ssid = "VANEGAS";
const char* password = "1006849389";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

const int CLK = 18;
const int DIN = 23;
const int D_C = 04;
const int CE  = 15;
const int RST = 02;
Adafruit_PCD8544 display = Adafruit_PCD8544(CLK,DIN,D_C,CE,RST);

static const uint8_t logo_completo[1024]  = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xf8, 0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x41, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x7c, 0x20, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x03, 0xe0, 0x7c, 0x20, 0x80, 0x0f, 0x00, 0x38, 0xc0, 0x08, 0x00, 0x07, 0xe0, 0x7c, 0x10, 0x40, 
  0x3f, 0x86, 0x38, 0xe0, 0x08, 0x00, 0x07, 0xc0, 0x7c, 0x10, 0x40, 0x70, 0x87, 0x60, 0x70, 0x1c, 
  0x00, 0x0f, 0xc0, 0x7c, 0x08, 0x60, 0x70, 0x87, 0x60, 0x70, 0x1c, 0x00, 0x1f, 0x80, 0x7c, 0x04, 
  0x60, 0x60, 0x0f, 0x60, 0x70, 0x3e, 0x00, 0x1f, 0x00, 0x7c, 0x04, 0x70, 0xe0, 0x0f, 0xe0, 0x38, 
  0x3e, 0x00, 0x3f, 0x00, 0x7c, 0x02, 0xf0, 0xc0, 0x0f, 0xff, 0x38, 0x3e, 0x00, 0x3e, 0x00, 0x7c, 
  0x02, 0xf0, 0xc0, 0x19, 0xff, 0xf8, 0x77, 0x00, 0x3e, 0x00, 0x7c, 0x01, 0xf0, 0xc0, 0x18, 0xff, 
  0xdc, 0x63, 0x00, 0x3d, 0x00, 0x7c, 0x01, 0xf0, 0xc0, 0x18, 0xc0, 0xcc, 0x63, 0x00, 0x1c, 0x80, 
  0x7c, 0x03, 0xf0, 0x60, 0x30, 0x00, 0xce, 0xc0, 0x00, 0x1c, 0x80, 0x7c, 0x03, 0xe0, 0x60, 0x30, 
  0x00, 0xce, 0xc0, 0x00, 0x08, 0x40, 0x7c, 0x07, 0xe0, 0x7c, 0x30, 0x61, 0xc6, 0xc1, 0x80, 0x08, 
  0x40, 0x7c, 0x07, 0xc0, 0x3e, 0x20, 0x61, 0xc6, 0xc1, 0xc0, 0x04, 0x20, 0x7c, 0x0f, 0xc0, 0x1f, 
  0x60, 0x31, 0x85, 0x80, 0xc0, 0x04, 0x20, 0x7c, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x02, 0x10, 0x7c, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x10, 0x7c, 0x3f, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x08, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0x08, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x7c, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
  0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

byte sol[] = {
  0xfb, 0xe0, 0xbb, 0xa0, 0xdf, 0x60, 0xf1, 0xe0, 0xee, 0xe0, 0x2e, 0x80, 0xee, 0xe0, 0xf1, 0xe0, 
  0xdf, 0x60, 0xbb, 0xa0, 0xfb, 0xe0
};

byte luna[] = {
  0x0f, 0x00, 0x3f, 0x00, 0x3e, 0x00, 0x7c, 0x00, 0x7c, 0x00, 0xfc, 0x00, 0x7c, 0x00, 0x7e, 0x00, 
  0x3f, 0x80, 0x3f, 0xc0, 0x0f, 0x00
};
const unsigned char wifid [] = {
  0xff, 0xe0, 0xc0, 0x60, 0xbf, 0xa0, 0x60, 0xc0, 0xdf, 0x60, 0xb1, 0xa0, 0xee, 0xe0, 0xfb, 0xe0, 
  0xf1, 0xe0, 0xff, 0xe0, 0xff, 0xe0
};
const unsigned char wifin [] = {
  0x00, 0x00, 0x3f, 0x80, 0x40, 0x40, 0x9f, 0x20, 0x20, 0x80, 0x4e, 0x40, 0x11, 0x00, 0x04, 0x00, 
  0x0e, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char btd [] = {
  0xe6, 0xea, 0xec, 0x6a, 0xa6, 0xce, 0xa6, 0x6a, 0xec, 0xea, 0xe6
};
const unsigned char btn [] = {
    0x18, 0x14, 0x12, 0x94, 0x58, 0x30, 0x58, 0x94, 0x12, 0x14, 0x18
};
bool blink = true; // Variable de estado para el parpadeo
unsigned long previousMillis = 0; // Variable para almacenar el tiempo anterior
int hr12 = 0;
char ampm[] = " M";
String formattedDate;
String dayStamp;
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");Serial.println("Conexión WiFi exitosa");
  timeClient.begin();
  timeClient.setTimeOffset(-18003); // Ajusta el desfase horario según tu zona horaria (en segundos)

  

  display.begin();
  display.setContrast(50);
  display.clearDisplay();

  display.drawBitmap(0, 0, logo_completo , 84, 48, 1);
  display.display();
  delay(5000);
  display.clearDisplay();
  display.display();
  delay(200);
  
}

void loop() {
  timeClient.update();
  /*while(!timeClient.update()) {
  timeClient.forceUpdate();
  }*/
  int formattedDate = timeClient.getDay();
  int hr24 = timeClient.getHours();
  int mins = timeClient.getMinutes();

  bool isNight = (hr24 >= 18 || hr24 < 5);
  display.invertDisplay(isNight);// Invertir el color de la pantalla si es de noche
  
  if (hr24 >= 12){
    hr12=hr24-12;
    if (hr12==0) hr12=12;
    ampm[0] = 'P';
  }else if(hr24 == 0){
    hr12=12;
    ampm[0] = 'A';
  }else{
    hr12=hr24;
    ampm[0] = 'A';
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 500) {
    previousMillis = currentMillis;
    blink = !blink; // Cambiar el estado del parpadeo cada segundo
  }
  
  display.clearDisplay();
  
  display.setRotation(0);
  display.setTextColor(BLACK);
  display.setTextSize(1);
  display.setCursor(4,0);
  display.print("ST V3");
  display.drawBitmap(1, 9, (isNight ? luna : sol), 11, 11, BLACK); //Imprimir Sol o Luna si es de dia o noche
  display.drawBitmap(13,9,(isNight ? wifin : wifid), 11, 11, BLACK);
  display.drawBitmap(25,9,(isNight ? btn : btd), 7, 11, BLACK);
  
  display.setTextSize(3);
  if(hr12>=10){
    display.setCursor(0,22);
    display.print("1");
    display.setCursor(14, 22);
    display.print(hr12-10);
  }else {
    display.setCursor(14, 22);
    display.print(hr12);
  }
  // Ajustar posición del cursor
  int hourWidth = display.getCursorX();
  int colonPosition = hourWidth-8;
  display.setCursor(colonPosition, 22);
  display.print(blink ? ":" : " ");
  int colonWidth = display.getCursorX();
  int minPosition = colonWidth-8;
  display.setCursor(minPosition, 22);
  if(mins<10)display.print("0");
  display.print(mins);
  
  display.setRotation(1);
  display.setTextSize(2);
  display.setCursor(5,70);
  display.print(ampm);
  
  display.display();
  delay(1000);
}
