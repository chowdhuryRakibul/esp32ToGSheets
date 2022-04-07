#include <WiFi.h>
#include <HTTPClient.h>
//----------------------------
//ENTER_GOOGLE_DEPLOYMENT_ID
const char* ssid = "Shadhinota";
const char* password = "Bangladesh1971";
String GOOGLE_SCRIPT_ID = "AKfycbyx_MEEBqTCVW4JlXEQuTln3c0-lZf0xNVSKAdi1YpBFzCwjkPBYmZF1tVqIg3yhAHr";
//---------------------------------------------------------------------

const int sendInterval = 2000;

/************************************************************************************
 *  setup function starts
 **********************************************************************************/
 void setup() {
  Serial.begin(115200);
  
  connectWiFi(ssid,password);
}

/************************************************************************************
 *  loop function starts
 **********************************************************************************/
void loop() {
  // in future we will receive this string over uart
  String param = print_data();
  
  write_to_google_sheet(param);

  delay(sendInterval);
}

void connectWiFi(const char* ssid, const char* password)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
}
/************************************************************************************
 *  loop function starts
 **********************************************************************************/
String print_data()
{
  int dist = 10;
  float tmp = 23.1;
  //String gps_speed = String(gps.speed.kmph());
  Serial.println(dist);
  Serial.println(tmp);

  String param;
  param  = "dist="+String(dist);
  param += "&tmp="+String(tmp, 6);

  Serial.println(param);

  return param;
}

/************************************************************************************
 *  loop function starts
 **********************************************************************************/
void write_to_google_sheet(String params) {
  HTTPClient http;
  String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
  Serial.print(url);
  Serial.println("Posting GPS data to Google Sheet");
  //---------------------------------------------------------------------
  //starts posting data to google sheet
  http.begin(url.c_str());
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  int httpCode = http.GET();  
  Serial.print("HTTP Status Code: ");
  Serial.println(httpCode);
  //---------------------------------------------------------------------
  //getting response from google sheet
  String payload;
  if (httpCode > 0) {
      payload = http.getString();
      Serial.println("Payload: "+payload);     
  }else{
    Serial.println("Wrong http Code");
  }
  //---------------------------------------------------------------------
  http.end();
}
