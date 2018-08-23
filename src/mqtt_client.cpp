/**
 * Copyright (C) 2018 Linagora
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "mqtt_client.h"

MQTT_Client::MQTT_Client(string ip,int16_t port,int QOS,string topics[], int elements) {
  this->ip = ip;
  this->port = port;
  string addr = "tcp://" + ip + ":" + to_string(port);
  cout << addr.c_str() << endl;
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
  if (MQTTClient_create(&mqtt_client, addr.c_str(), "ASR" ,MQTTCLIENT_PERSISTENCE_NONE, NULL) != MQTTCLIENT_SUCCESS) {
    cout << "MQTT_Client creation failed" << endl;
  }
  conn_opts.keepAliveInterval = 20;
  conn_opts.cleansession = 1;
  if (MQTTClient_setCallbacks(mqtt_client, NULL, connlost, msgarrvd, delivered) != MQTTCLIENT_SUCCESS) {
    cout << "MQTT_Client creation failed" << endl;
  }
  if (MQTTClient_connect(mqtt_client, &conn_opts) != MQTTCLIENT_SUCCESS) {
    cout << "MQTT connection failed" << endl;
  }
  for (int i = 0; i < elements; i++) {
    if (MQTTClient_subscribe(mqtt_client,(topics[i]).c_str(), QOS)!= MQTTCLIENT_SUCCESS) {
      cout << "Sub to " << (topics[i]).c_str() << " failed" << endl;
    }
  }
  
}


MQTT_Client::~MQTT_Client() {
  MQTTClient_disconnect(mqtt_client, 100);
  MQTTClient_destroy(&mqtt_client);
}

void delivered(void *context, MQTTClient_deliveryToken dt) {
  cout << "Message with token value" << dt <<"delivery confirmed" << endl;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
  char* value=(char*)malloc(sizeof(message->payloadlen+1));
  memcpy(value,(message->payload),message->payloadlen);
  cout << message->payloadlen << endl;

  cout << "Topic : " << topicName << " Message : " << value << endl; 
  MQTTClient_freeMessage(&message);
  MQTTClient_free(topicName);
  return 1;
}

void connlost(void *context, char *cause) {
  cout << "Connection lost" << endl;
  cout << "Context: " << context <<  " cause: " << cause << endl;
}