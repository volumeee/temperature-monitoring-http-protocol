#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"

#define API_ENDPOINT "http://your_domain.com/path/to/api.php"
#define API_KEY "tPmAT5Ab3j7F9"

#define DHT_PIN 4
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  dht.begin();
}

void loop() {
  // Read sensor data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if any reads failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read data from DHT sensor");
    return;
  }

  // Create JSON payload
  String payload = "{\"api_key\":\"" + String(API_KEY) + "\",";
  payload += "\"sensor\":\"DHT11\",";
  payload += "\"location\":\"Living Room\",";
  payload += "\"value1\":\"" + String(temperature) + "\",";
  payload += "\"value2\":\"" + String(humidity) + "\",";
  payload += "\"value3\":\"\"}";

  // Send data to API endpoint
  HTTPClient http;
  http.begin(API_ENDPOINT);
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.POST(payload);
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("Error sending HTTP request: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  delay(5000);  // Delay for 5 seconds before sending the next data
}
