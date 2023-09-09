#include <Arduino.h>
#include <AMMSutils.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

void AMMSutils::begin(String token) {
  client->setCACert(root_ca);
	this->token = token;
}

DynamicJsonDocument data(1024);
JsonObject sensorsData = data.createNestedObject("sensors");
JsonObject stationData = data.createNestedObject("station");

void AMMSutils::setSensorField(String fieldName, float value) {
	sensorsData[fieldName] = value;
}

void AMMSutils::setSensorField(String fieldName, int value) {
	sensorsData[fieldName] = value;
}

void AMMSutils::setSensorField(String fieldName, String value) {
	sensorsData[fieldName] = value;
}

void AMMSutils::setStationField(String fieldName, float value) {
	stationData[fieldName] = value;
}

void AMMSutils::setStationField(String fieldName, int value) {
	stationData[fieldName] = value;
}

void AMMSutils::setStationField(String fieldName, String value) {
	stationData[fieldName] = value;
}

String AMMSutils::sendData() {
	String jsonData;
  serializeJson(data, jsonData);
	sensorsData.clear();
	stationData.clear();

	return post("https://weather.iacca.ml/api/data/point", jsonData);
}

String AMMSutils::post(String url, String data) {
  https.begin(*client, url);
  https.addHeader("Authorization", "Bearer " + token);
  https.addHeader("Content-type", "application/json");
  int httpResponseCode = https.POST(data);
  String payload = https.getString();
  https.end();
  return payload;
}

String AMMSutils::get(String url) {
  https.begin(*client, url);
  https.addHeader("Authorization", "Bearer " + token);
  https.addHeader("Content-type", "application/json");
  int httpResponseCode = https.GET();
  String payload = https.getString();
  https.end();
  return payload;
}
