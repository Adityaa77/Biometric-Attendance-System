#include <Adafruit_Fingerprint.h>
#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(D3, D4);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

const char* ssid = "Redmi 10 Prime";            //replace with your own SSID
const char* password = "dileep123";  //replace with your own password
const char* host = "api.pushingbox.com";
String member = "";

int flag = 0;

int getFingerprintID()
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  return finger.fingerID;
}

void setup() {
  Serial.begin(115200);
  //lcd.begin(16, 2);
  lcd.init();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("WELCOME");
  delay(2000);

  lcd.clear();

  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to WiFi...       ");

  lcd.setCursor(0, 0);
  lcd.print("Connecting to");
  lcd.setCursor(4, 1);
  lcd.print("WIFI");
  delay(2000);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  lcd.setCursor(0, 0);
  lcd.print("Connecting to");
  lcd.setCursor(1, 1);
  lcd.print(ssid);
  delay(2000);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.setCursor(0, 0);
  lcd.print("WiFi connected");
  lcd.setCursor(0, 1);
  lcd.print("IP:");
  lcd.setCursor(4, 1);
  lcd.print(WiFi.localIP());

  delay(1500);

  while (!Serial)
    ;
  delay(100);
  Serial.println("\n\n Waiting for Fingerprint Sensor");
  lcd.setCursor(0, 0);
  lcd.print("    Waiting for           ");
  lcd.setCursor(0, 1);
  lcd.print("      Sensor              ");
  delay(1500);
  finger.begin(57600);

  if (finger.verifyPassword()) {
    Serial.println("Found Successfully");
    lcd.setCursor(0, 0);
    lcd.print("Sensor found!         ");
    lcd.setCursor(0, 1);
    lcd.print("                      ");
    delay(1500);
  } else {
    Serial.println("Fingerprint sensor not found!!!");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Not found!         ");
    lcd.setCursor(0, 1);
    lcd.print("                      ");
    while (1) {
      delay(1);
    }
  }
}

void loop() {
  int fingerprintID = getFingerprintID();
  delay(50);
  if (fingerprintID == -1) {
    lcd.setCursor(0, 0);
    lcd.print("Place finger on ");
    lcd.setCursor(0, 1);
    lcd.print(" sensor        ");
  } else {
    if (fingerprintID == 1) {
      // Handle the case where fingerprint matches person 1
      Serial.println("Welcome Dileep");
      lcd.setCursor(0, 0);
      lcd.print("Welcome Dileep         ");
      lcd.setCursor(0, 1);
      lcd.print("                       ");
      connecthost("Dileep");
      flag = 0;
    } else if (fingerprintID == 2) {
      // Handle the case where fingerprint matches person 2
      Serial.println("Welcome Swaroop");
      lcd.setCursor(0, 0);
      lcd.print("Welcome Swaroop          ");
      lcd.setCursor(0, 1);
      lcd.print("                       ");
      connecthost("Swaroop");
      flag = 0;
    } else if (fingerprintID == 3) {
      // Handle the case where fingerprint matches person 3
      Serial.println("Welcome Aditya");
      lcd.setCursor(0, 0);
      lcd.print("Welcome Aditya           ");
      lcd.setCursor(0, 1);
      lcd.print("                       ");
      connecthost("Aditya");
      flag = 0;
    } else if (fingerprintID == 4) {
      // Handle the case where fingerprint matches person 4
      Serial.println("Welcome HEMANT SIR");
      lcd.setCursor(0, 0);
      lcd.print("Welcome HEMANT SIR           ");
      lcd.setCursor(0, 1);
      lcd.print("                       ");
      connecthost("HEMANT SIR");
      flag = 0;
    } else {
      // Handle the case of an invalid fingerprint
      Serial.println("Invalid fingerprint!");
      lcd.setCursor(0, 0);
      lcd.print("Invalid fingerprint!  ");
      lcd.setCursor(0, 1);
      lcd.print("Try again              ");
    }
  }
}

void connecthost(String data) {
  if (flag == 0) {
    member = data;
    flag = 1;
    Serial.print("connecting to ");
    Serial.println(host);
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
      Serial.println("connection failed");
      return;
    }

    // We now create a URL for the request
    String url = "/pushingbox?";
    url += "devid=";
    url += "v63FD0916B442C76";
    url += "&Name=" + String(member);

    Serial.print("Requesting URL: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }
    while (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
      Serial.println("Data Sent!");
    }

    Serial.println("closing connection");
  }
}

