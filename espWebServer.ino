/*
*
* WORKING TEST AJAX WITH JSON NODEMCU sketch
* Author: John Glatts
* Date: 4/17/19
*
*   REFACTOR ME! Currently getting a stack overflow
*
*    ToDo:
 *    - Add a defense mechanism to 'private' lins, like checking the bool's, so unauthorized users can't access it
 *    - Clean up the new feature to have multiple cards
 *    - Include a new and improved .h file
 *      - A header file with .cpp function
 *      - Make a LIBRARY! - Did dat
*/
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <MFRC522.h>
// JS-HTML file
#include "htmlpage.h"


// neo-pixel pins
#define pix_pin 5
#define NUM_PIX 12
// MFRC522 pins
#define SS_PIN  2
#define RST_PIN  0
// HC-SR04 pins
#define TRIG 4
#define ECHO 16


// MFRC522 Card
#define RFID_CARD_UID_JG "76 CC CA F7"
#define RFID_CARD_UID_GG "93 63 6E 24"
#define USER_NAME_JG "John Glatts"
#define USER_NAME_GG "George Glatts"
#define USER_UNKNOWN "User Unknown"


// network credentials
const char* ssid = "";
const char* password = "";


// set up instances
ESP8266WebServer server(80);
MFRC522 mfrc522(SS_PIN, RST_PIN);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIX, pix_pin, NEO_GRB + NEO_KHZ800);


// globals for HTML pages
String rfid_page = rfid_page_html;
String index_page = page;

// globals for MFRC522, Pixel, etc...
unsigned long data;
bool rfid_connection_status_john = false; // flag for RFID tag
bool rfid_connection_status_george = false; // flag for RFID tag
int number_of_checkins = 0;


/* Set it up homie */
void setup(void){
    delay(1000);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, OUTPUT);
    randomSeed(analogRead(0));  // seed for random(), used for random PIXEL colors
    pixels.begin();
    pixels.show();
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.begin(115200);
    WiFi.begin(ssid, password); // begin WiFi connection
    Serial.println("");
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    serverOnEveryThing();
    server.begin();
    Serial.println("Web server started!");
}


/* Run the server and handle incoming clients */
void loop(void){
    server.handleClient();
}


/* Map the href's, and improve readability */
void serverOnEveryThing() {
    server.onNotFound(handleNotFound);
    server.on("/data.txt", updateSysTime);
    server.on("/distance.txt", updatePingSensor);
    server.on("/GetDistance", sendPingDistance);
    server.on("/time.txt", pixelCalc);
    server.on("/Time", displayElapsedTime);
    server.on("/MotorOn", turnMotorOn);
    server.on("/stats.json", updateStatsXML);
    server.on("/Stats", displayStats);
    server.on("/PixelControl.txt", updatePixelColor);
    server.on("/about.json", updateAboutXML);
    server.on("/About", displayAbout);
    server.on("/RFID", rfidAccess);
    server.on("/RFID.txt", rfidUpdate);
    server.on("/RFIDMotor.txt", rfidCycleMotor);
    server.on("/resetUID.json", rfidReset);
    server.on("/Reboot", espReboot);
    server.on("/", landingPage);
}



/* Record the time, in millis, to be used later on
 * Uses JSON
 * */
void updateSysTime() {
    StaticJsonDocument<500> sys_uptime_json;
    String sys_uptime, time_data;

    // test and see if getting rid of String time_data will work
    // if it does, ykwtfgo
    data = millis();

    sys_uptime_json["total_system_time"] = time_data;
    // clean this up, maybe add an extra flag
    if (rfid_connection_status_john) {
        sys_uptime_json["current_user"] = USER_NAME_JG;
        sys_uptime_json["current_id"] = RFID_CARD_UID_JG;
    }
    else if (rfid_connection_status_george) {
        sys_uptime_json["current_user"] = USER_NAME_GG;
        sys_uptime_json["current_id"] = RFID_CARD_UID_GG;
    }
    else {
        sys_uptime_json["current_user"] = USER_UNKNOWN;
        sys_uptime_json["current_id"] = "No Current User";
    }
    sys_uptime_json["number_check_ins"] = String(number_of_checkins);
    serializeJson(sys_uptime_json, sys_uptime);
    server.send(200, "application/json", sys_uptime);
}


/* Get the elapsed time and display it on the html page and the neopixel */
void pixelCalc() {
    unsigned long elapsed_time, mod, motor_mins, motor_secs;
    StaticJsonDocument<500> elapsed_time_json;
    String elapsed_time_xml;

    // crunch these lines down --> 1 to 2 lines
    elapsed_time = millis() - data;
    motor_mins = int(elapsed_time / 60000);
    mod = elapsed_time % 60000;
    motor_secs = int(mod / 1000);

    elapsed_time_json["mins"] = motor_mins;
    elapsed_time_json["secs"] = motor_secs;
    serializeJson(elapsed_time_json, elapsed_time_xml);

    // light up the pixel
    motor_mins >= 1 ? lightUpPixel(motor_mins) : turnOffPixel();

    server.send(200, "text/html", elapsed_time_xml);
}

/* Use the HC-SR04 sensor to record an object's distance */
void updatePingSensor() {
    int distance, duration = 0;
    String distance_xml;
    StaticJsonDocument<500> distance_json;

    // get distance
    digitalWrite(TRIG, LOW); // clear the trig_pin
    delayMicroseconds(5);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(5);
    digitalWrite(ECHO, LOW);

    // update distance
    duration = pulseIn(ECHO, HIGH);
    distance= duration * 0.034/2;

    Serial.println(distance);
    distance_json["distance"] = String(distance);
    serializeJson(distance_json, distance_xml);

    server.send(200, "text/html", distance_xml);
}


/* Send the Distance Landing Page to the server */
void sendPingDistance() {
    String distance_str = distance_page;
    server.send(200, "text/html", distance_str);
}


/* URL not found, Display whatever the arguments were */
void handleNotFound() {
    String message = "File Not Found\n\n";
    message += "URI: ";
    message += server.uri();
    message += "\nMethod: ";
    message += (server.method() == HTTP_GET) ? "GET" : "POST";
    message += "\nArguments: ";
    message += server.args();
    message += "\n";
    // display the URL that's not found
    for (uint8_t i = 0; i < server.args(); i++) {
        message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }

    server.send(404, "text/plain", message);
}


/* HTML landing page */
void landingPage(){
    turnOffPixel();     // turn pixel off
    server.send(200, "text/html", index_page);
}


/* Receive color commands from the server to display on the neopixel */
/*
void controlPixel() {
    String pix_ctrl_page = pixel_control_page;
    Server.send(200, "text/html", pix_ctrl_page);
};
*/


/* Collect the color code from the HTML-page and display */
void updatePixelColor() {
    int color_1 , color_2, color_3;

    // flash the pixel in a dank way
    // only gets executed when the right RFID card is activated
    for (int j = 0; j < 15; ++j) {
        color_1 = random(0, 256);
        color_2 = random(0, 256);
        color_3 = random(0, 256);
        for (int i = 0; i < NUM_PIX; ++i) {
            pixels.setPixelColor(i, pixels.Color(color_1, color_2, color_3));
            pixels.show();
        }
        delay(75);
    }
}


/* Display the elapsed time */
void displayElapsedTime() {
    String calc_time_page = time_page;
    server.send(200, "text/html", calc_time_page);
}


/* Put the board stats (JSON) on an XML page, to be parsed by a JS script */
void updateStatsXML() {
    StaticJsonDocument<500> stats;
    String stats_xml;

    // ESP board info
    stats["chipID"] = String(ESP.getChipId());
    stats["sketch_hash"] = ESP.getSketchMD5();
    stats["mac_address"] = String(WiFi.macAddress());
    stats["wifi_mode"] = String(WiFi.getMode());
    stats["local_ip"] = WiFi.localIP();

    serializeJson(stats, stats_xml);
    server.send(200, "application/json", stats_xml);
}


/* Update some 'About' info to a XML page */
void updateAboutXML() {
    StaticJsonDocument<500> about;
    String about_xml;

    about["author"] = "John Glatts";
    about["created"] = "4-21-2019";
    about["brief"] = "Nodemcu sketch with some Ajax to make it fun ;)";
    about["version"] = "1.0";

    serializeJson(about, about_xml);
    serializeJsonPretty(about, Serial);
    server.send(200, "application/json", about_xml);
}


/* Parse the JSON Stats object and display on a html page */
void displayStats() {
    // get the header
    String stats_page;

    stats_page = board_stats_page;
    server.send(200, "text/html", stats_page);
}


/* Display the 'About' Page */
void displayAbout() {
    // get the header
    String about_page;

    about_page = board_about_page;
    server.send(200, "text/html", about_page);
}


/* Turn the small motor on, using a NPN transitor */
void turnMotorOn() {
    String motor_page = time_page;

    server.send(200, "text/html", motor_page);
}


/* RFID Module
 *  - Display current card readings
 * */
void rfidAccess() {
    server.send(200, "text/html", rfid_page);
}


/* RFID Module
 *  - Updates JSon
 *  - Todo:
 *      - Improve readability and add some helper fn()s
 *      - Works as intended right now, stops checking for cards if the register one has already been swipedS
 * */
void rfidUpdate() {
    unsigned long check_in_time;
    String rfid_status_xml, content, active_user, active_card;
    byte letter;

    // Make sure the card/tag has NOT been verified
    // clean this two if's up
    if (rfid_connection_status_john) {
        displayCardInfo("John Is Checked In", RFID_CARD_UID_JG);
    }
    else if (rfid_connection_status_george) {
        displayCardInfo("George Is Checked In", RFID_CARD_UID_GG);
    }
    else {
        // Look for new cards
        if ( !mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
        {
            displayCardInfo("No Card Present", "none");
        }
        else {
            // Get the UID from the card
            for (byte i = 0; i < mfrc522.uid.size; i++) {
                content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
                content.concat(String(mfrc522.uid.uidByte[i], HEX));
            }
            content.toUpperCase();
            if (content.substring(1) == RFID_CARD_UID_JG) {
                rfid_connection_status_john = true;
                ++number_of_checkins;
                check_in_time = millis();   // grab the time whenever a user is present
                lightUpPixel(NUM_PIX);
                delay(1000);
            }
            else if (content.substring(1) == RFID_CARD_UID_GG) {
                rfid_connection_status_george = true;
                ++number_of_checkins;
                check_in_time = millis();
                lightUpPixel(NUM_PIX);
                delay(1000);
            }
            else   {
                displayCardInfo("Access Denied", content.substring(1));
            }
            // Make sure Pixel is off
            turnOffPixel();
        }
    }
}


/* RFID Module
 *  - Change the motor cycle, just a bunch of on/offs
 *  - function is only able to execute if
 * */
void rfidCycleMotor() {
    String mo_page = time_page;

    server.send(200, "text/html", mo_page);
}


/* RFID Module
 *  - Updates JSON to 'Access Denied' when no card is present
 * */
void displayCardInfo(String user_card, String card_id) {
    String user_card_xml;

    StaticJsonDocument<500> new_card;
    new_card["user"] = user_card;
    card_id == "none" ? new_card["tag_card_id"]="N/A" : new_card["tag_card_id"]=card_id;

    serializeJson(new_card, user_card_xml);
    server.send(200, "application/json", user_card_xml);
}


/* RFID Module
 *  - Reset the module, allowing new cards to be presented
 * */
void rfidReset() {
    rfid_connection_status_john = false;
    rfid_connection_status_george = false;
}


/* Turn on the Pixel, displaying the elapsed time (in mins.) or turn on all LEDs */
void lightUpPixel(int count) {
    // light up the pixel
    for (int i = 0; i < count; ++i) {
        pixels.setPixelColor(i, pixels.Color(random(0, 256), random(0, 256), random(0, 256)));
        pixels.show();
    }
}


/* Clear the Pixel */
void turnOffPixel() {
    for (int i = 0; i < NUM_PIX; ++i) {
        pixels.setPixelColor(i, 0);
        pixels.show();
    }
}


/* ESP Restart */
void espReboot() {
    ESP.reset();
}
  
