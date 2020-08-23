#ifndef UNIT_TEST

#include <Arduino.h>
#include <BluetoothSerial.h>

#include "Debug/Trace.h"
#include "FreematicsPlus.h"

#ifdef DEBUG
BluetoothSerial SerialBT;
#endif

COBD obd;
FreematicsESP32 sys;

bool connected = false;
char vin[18] = {0};

void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

#ifdef DEBUG
  digitalWrite(PIN_LED, HIGH);

  Serial.begin(115200);
  SerialBT.begin("55b ONE+ debug");
  // Wait for serial port UART to connect.
  // Without this delay initial writes to the serial port are not captured.
  delay(2000);

  digitalWrite(PIN_LED, LOW);
#endif

  DEBUG_TRACE("[INFO] setup() start\n")

  DEBUG_TRACE("[INFO] Initialising OBD\n")
  while (!sys.begin())
    ;
  obd.begin(sys.link);

  digitalWrite(PIN_LED, LOW);

  DEBUG_TRACE("[INFO] setup() end\n")
}

void loop() {
  DEBUG_TRACE("[INFO] loop() start\n")

  digitalWrite(PIN_LED, HIGH);

  if (!connected) {
    digitalWrite(PIN_LED, HIGH);
    DEBUG_TRACE("[INFO]Connecting to OBD...")
    if (obd.init(PROTO_CAN_11B_500K)) {
      DEBUG_TRACE(" success\n")
      connected = true;
    } else {
      DEBUG_TRACE(" failed\n")
    }
    digitalWrite(PIN_LED, LOW);
    return;
  } else {
    DEBUG_TRACE("[INFO] Connected to OBD\n")
  }

  DEBUG_TRACE("[INFO] Device voltage: ");
  DEBUG_TRACE(obd.getVoltage());
  DEBUG_TRACE(" V\n");

  char buf[128];
  if (obd.getVIN(buf, sizeof(buf))) {
    strncpy(vin, buf, sizeof(vin) - 1);
    DEBUG_TRACE("VIN: ");
    DEBUG_TRACE(vin);
    DEBUG_TRACE("\n");
  } else {
    DEBUG_TRACE("[ERROR] Failed to read VIN\n");
  }

  if (obd.errors > 2) {
    DEBUG_TRACE("[WARN] OBD errors. Resetting.\n");
    connected = false;
    obd.reset();
  }

  digitalWrite(PIN_LED, LOW);

  DEBUG_TRACE("[INFO] loop() end\n")

  delay(2000);
}

#endif
