#ifndef ROPE_MQTT_PARAMS
#define ROPE_MQTT_PARAMS

#define MQTT_URL "http://smartrope.com.br:1883"
#define MQTT_CLIENT_ID "RoPE {{serial_number}}"

#define MQTT_CONTROL_TOPIC "control"
#define MQTT_EVENTS_TOPIC "rope/{{serial_number}}/events"

#define MQTT_IDENTITY_TOPIC "rope/{{serial_number}}/identity"
#define MQTT_STATUS_TOPIC "rope/{{serial_number}}/status"
#define MQTT_OFFLINE_PAYLOAD "{\"status\":\"OFFLINE\"}"

#endif // ROPE_MQTT_PARAMS