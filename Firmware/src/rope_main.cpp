#ifdef ROPE_MAIN

#define BYTES 1
#define KB 1024
#define MB 1048576
#define RESERVE(length, scale) (length * scale)

#define MILLIS 1
#define SECONDS 1000
#define EVERY(interval, scale) (interval * scale)

#include <driver/gpio.h>

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

//#include <WiFiParams.h>
//#include <MQTTParams.h>

#include "Rope/RopeToy.hpp"

#include "soc/soc.h"  // Para manipular registros de sistema
#include "soc/rtc_cntl_reg.h"

//#include <LittleFS.h>
//#include "FS.h"

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

BLEServer *pServer = NULL;
BLECharacteristic *pCharacteristic = NULL;
BLECharacteristic *pCharacteristicPassword = NULL;
BLECharacteristic *pCharacteristicSsid = NULL;
BLEDescriptor *pDescr;
BLE2902 *pBLE2902;
bool deviceConnected = false;

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC_SSID_UUID "6820d2bc-3510-47ce-a233-f9def48b718e"
#define CHARACTERISTIC_PASSWORD_UUID "44c5b623-f69f-42d7-a14e-ae644ebe8e4d"

// Initialize the RoPE robot
Rope::RopeToy* rope;

// H4_USE_PLUGINS(SERIAL_SPEED, H4_Q_CAPACITY * 3, false)

// Notifies all registered loggers about the queue status
// H4P_EmitQ emitQueue(EVERY(30, SECONDS));

// Notifies all registered loggers about the heap status
// H4P_EmitHeap emitHeap(EVERY(60, SECONDS));

// Registers a logger for printing events in the serial
// H4P_SerialLogger serialLogger(H4PE_ALMOST_ALL & ~H4PE_GPIO);

// Registers a logger for saving events in the filesystem
// H4P_LocalLogger local(RESERVE(10, KB), H4PE_ALMOST_ALL);

// Registers a logger for sending the heap status to the MQTT topic "heap"
// H4P_MQTTLogger mqttHeapLogger("heap", H4PE_HEAP);

// Registers a logger for sending the heap status to the MQTT topic "queue"
// H4P_MQTTLogger mqttQueueLogger("queue", H4PE_Q);

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string rxValue = pCharacteristic->getValue();
      Serial.println(rxValue[0]);

      std::string ssid = pCharacteristicSsid->getValue();
      String ssid_normalizado = ssid.c_str();

      std::string senha = pCharacteristicPassword->getValue();
      String senha_normalizado = senha.c_str();

      if (ssid.length() > 0) {
        Serial.println("*********");
        Serial.print("SSID Value: ");
        Serial.print(ssid_normalizado);
        Serial.println();
        Serial.println("*********");
      }

      if (senha.length() > 0) {
        Serial.println("*********");
        Serial.print("Password Value: ");
        Serial.print(senha_normalizado);
        Serial.println();
        Serial.println("*********");
      }

      if (rxValue.length() > 0) {
        Serial.println("*********");
        Serial.print("Received Value: ");

        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }
        Serial.println();
        Serial.println("*********");
      }

      // Processa o caracter recebido do aplicativo. Se for A acende o LED. B apaga o LED
      Rope::MoveParameters moveParameters = rope->getDefaultMoveParameters();
      Rope::RotationParameters rotationParameters = rope->getDefaultRotationParameters();
      if (rxValue.find("A") != -1) { 
        Serial.println("Turning ON!");
        //digitalWrite(2, HIGH);
      }
      else if (rxValue.find("B") != -1) {
        Serial.println("Turning OFF!");
        //digitalWrite(2, LOW);
      }
      else if (rxValue.find("F") != -1) {
        Serial.println("Going Forward!");
        rope->moveForward("BLE", moveParameters);
        //digitalWrite(2, LOW);
      }
      else if (rxValue.find("G") != -1) {
        Serial.println("Going Backward!");
        rope->moveBackward("BLE", moveParameters);
        //digitalWrite(2, LOW);
      }
      else if (rxValue.find("R") != -1) {
        Serial.println("Going Right!");
        rope->rotateClockwise("BLE", rotationParameters);
        //digitalWrite(2, LOW);
      }
      else if (rxValue.find("L") != -1) {
        Serial.println("Going Left!");
        rope->rotateCounterClockwise("BLE", rotationParameters);
        //digitalWrite(2, LOW);
      }
    }
};

void setup()
{
    Serial.begin(115200);
    Serial.println("Inicializando RoPE.");
    // if(!LittleFS.begin(true)) {  // O parâmetro 'true' força a formatação
    //     Serial.println("Falha ao montar o sistema de arquivos. Formatando...");
    // } else {
    //     Serial.println("Sistema de arquivos montado com sucesso.");
    // }
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

    gpio_pad_select_gpio(GPIO_NUM_14);
    gpio_set_direction(GPIO_NUM_14, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(GPIO_NUM_12);
    gpio_set_direction(GPIO_NUM_12, GPIO_MODE_OUTPUT);

    // gpio_pad_select_gpio(GPIO_NUM_33);
    // gpio_set_direction(GPIO_NUM_33, GPIO_MODE_INPUT);

    BLEDevice::init("RoPE");

    // Configura o dispositivo como Servidor BLE
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    // Cria o servico UART
    BLEService *pService = pServer->createService(SERVICE_UUID);

    // cria uma característica BLE para recebimento dos dados
    pCharacteristicPassword = pService->createCharacteristic(
                        CHARACTERISTIC_PASSWORD_UUID,
                        BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ
                        );
    
    pCharacteristicPassword->addDescriptor(new BLE2902());

    pCharacteristicSsid = pService->createCharacteristic(
                        CHARACTERISTIC_SSID_UUID,
                        BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ
                        );
                        
    pCharacteristicSsid->addDescriptor(new BLE2902());

    // cria uma característica BLE para recebimento dos dados
    pCharacteristic = pService->createCharacteristic(
                        CHARACTERISTIC_UUID,
                        BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ
                        );

    pCharacteristic->addDescriptor(new BLE2902());

    pCharacteristic->setCallbacks(new MyCallbacks());

    // Inicia o serviço
    pService->start();

    // Inicia a descoberta do ESP32
    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    Serial.println("Esperando um cliente se conectar...");

    //touch_pad_intr_disable();
    rope = new Rope::RopeToy();
    rope->initialize();
}
void loop() {
    
}

//uint32_t controlTopicCallback(std::vector<std::string> vs)
//{
//    return rope.IoT.executeCommands(vs);
//}


#endif // ROPE_MAIN