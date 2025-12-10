/*Este é o arquivo main do mini robô sumô CLOUD feito para participar do campeonato interno 
  do GRUPO DE ESTUDOS EM ROBÓTICA da UEA - GEAR*/
#include <Bluepad32.h>
#include<Arduino.h>
#include<uni.h>
#include"funcoes.h"
#include"buzzer.h"

ControllerPtr myControllers[BP32_MAX_GAMEPADS];

// This callback gets called any time a new gamepad is connected.
// Up to 4 gamepads can be connected at the same time.
void onConnectedController(ControllerPtr ctl);

void onDisconnectedController(ControllerPtr ctl);

// ========= SEE CONTROLLER VALUES IN SERIAL MONITOR ========= //

void dumpGamepad(ControllerPtr ctl);

// ========= GAME CONTROLLER ACTIONS SECTION ========= //

void processGamepad(ControllerPtr ctl);

void processControllers();
static const char * controller_addr_string = "14:CB:65:F9:B6:0A";

void setup() {

  Serial.begin(115200);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);

  
    bd_addr_t controller_addr;

    // Parse human-readable Bluetooth address.
    sscanf_bd_addr(controller_addr_string, controller_addr);

    // Notice that this address will be added in the Non-volatile-storage (NVS).
    // If the device reboots, the address will still be stored.
    // Adding a duplicate value will do nothing.
    // You can add up to four entries in the allowlist.
    uni_bt_allowlist_add_addr(controller_addr);

    // Finally, enable the allowlist.
    // Similar to the "add_addr", its value gets stored in the NVS.
    uni_bt_allowlist_set_enabled(true);

  // Enable the motor driver by setting STBY HIGH
  digitalWrite(STBY, HIGH);
    
  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t* addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);

  // Setup the Bluepad32 callbacks
  BP32.setup(&onConnectedController, &onDisconnectedController);

  // "forgetBluetoothKeys()" should be called when the user performs
  // a "device factory reset", or similar.
  // Calling "forgetBluetoothKeys" in setup() just as an example.
  // Forgetting Bluetooth keys prevents "paired" gamepads to reconnect.
  // But it might also fix some connection / re-connection issues.
  BP32.forgetBluetoothKeys();

  // Enables mouse / touchpad support for gamepads that support them.
  // When enabled, controllers like DualSense and DualShock4 generate two connected devices:
  // - First one: the gamepad
  // - Second one, which is a "virtual device", is a mouse.
  // By default, it is disabled.
  BP32.enableVirtualDevice(false);
}

void loop() {
  
  // This call fetches all the controllers' data.
  // Call this function in your main loop.
  bool dataUpdated = BP32.update();
  if (dataUpdated)
    processControllers();

    // The main loop must have some kind of "yield to lower priority task" event.
    // Otherwise, the watchdog will get triggered.
    // If your main loop doesn't have one, just add a simple `vTaskDelay(1)`.
    // Detailed info here:
    // https://stackoverflow.com/questions/66278271/task-watchdog-got-triggered-the-tasks-did-not-reset-the-watchdog-in-time

    // vTaskDelay(1);
  delay(150);
}

void onConnectedController(ControllerPtr ctl) {
  bool foundEmptySlot = false;
  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == nullptr) {
      Serial.printf("CALLBACK: Controller is connected, index=%d\n", i);
      // Additionally, you can get certain gamepad properties like:
      // Model, VID, PID, BTAddr, flags, etc.
      conectado();
      ControllerProperties properties = ctl->getProperties();
      Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id, properties.product_id);
      myControllers[i] = ctl;
      foundEmptySlot = true;
      digitalWrite(2,HIGH);
      break;
      }
    }

    if (!foundEmptySlot) {
      Serial.println("CALLBACK: Controller connected, but could not found empty slot");
    }
}

void onDisconnectedController(ControllerPtr ctl) {
  bool foundController = false;

  for (int i = 0; i < BP32_MAX_GAMEPADS; i++) {
    if (myControllers[i] == ctl) {
      Serial.printf("CALLBACK: Controller disconnected from index=%d\n", i);
      myControllers[i] = nullptr;
      foundController = true;
      break;
    }
  }

    if (!foundController) {
      Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}

void dumpGamepad(ControllerPtr ctl) {
  Serial.printf(
  "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
  "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
  ctl->index(),        // Controller Index
  ctl->dpad(),         // D-pad
  ctl->buttons(),      // bitmask of pressed buttons
  ctl->axisX(),        // (-511 - 512) left X Axis
  ctl->axisY(),        // (-511 - 512) left Y axis
  ctl->axisRX(),       // (-511 - 512) right X axis
  ctl->axisRY(),       // (-511 - 512) right Y axis
  ctl->brake(),        // (0 - 1023): brake button
  ctl->throttle(),     // (0 - 1023): throttle (AKA gas) button
  ctl->miscButtons(),  // bitmask of pressed "misc" buttons
  ctl->gyroX(),        // Gyro X
  ctl->gyroY(),        // Gyro Y
  ctl->gyroZ(),        // Gyro Z
  ctl->accelX(),       // Accelerometer X
  ctl->accelY(),       // Accelerometer Y
  ctl->accelZ()        // Accelerometer Z
  );
}

void processGamepad(ControllerPtr ctl){
  // There are different ways to query whether a button is pressed.
  // By query each button individually:
  //  a(), b(), x(), y(), l1(), etc...
 
  //== PS4 X button = 0x0001 ==//
  if (ctl->buttons() == 0x0001) {
    // code for when X button is pushed
    wars();
  }
  if (ctl->buttons() != 0x0001) {
    // code for when X button is released

    paraBuzzer();
    
  }

  //== PS4 Square button = 0x0004 ==//
  if (ctl->buttons() == 0x0004) {
    // code for when square button is pushed
  }
  if (ctl->buttons() != 0x0004) {
  // code for when square button is released
  }

  //== PS4 Triangle button = 0x0008 ==//
  if (ctl->buttons() == 0x0008) {
    // code for when triangle button is pushed
  }
  if (ctl->buttons() != 0x0008) {
    // code for when triangle button is released
  }

  //== PS4 Circle button = 0x0002 ==//
  if (ctl->buttons() == 0x0002) {
    // code for when circle button is pushed

    fantasy();

  }
  if (ctl->buttons() != 0x0002) {
    // code for when circle button is released

    paraBuzzer();

  }

  //== PS4 Dpad UP button = 0x01 ==//
  if (ctl->buttons() == 0x01) {
    // code for when dpad up button is pushed
  }
  if (ctl->buttons() != 0x01) {
    // code for when dpad up button is released
  }

  //==PS4 Dpad DOWN button = 0x02==//
  if (ctl->buttons() == 0x02) {
    // code for when dpad down button is pushed
  }
  if (ctl->buttons() != 0x02) {
    // code for when dpad down button is released
  }

  //== PS4 Dpad LEFT button = 0x08 ==//
  if (ctl->buttons() == 0x08) {
    // code for when dpad left button is pushed
  }
  if (ctl->buttons() != 0x08) {
    // code for when dpad left button is released
  }

  //== PS4 Dpad RIGHT button = 0x04 ==//
  if (ctl->buttons() == 0x04) {
    // code for when dpad right button is pushed
  }
  if (ctl->buttons() != 0x04) {
    // code for when dpad right button is released
  }

  //== PS4 R1 trigger button = 0x0020 ==//
  if (ctl->buttons() == 0x0020) {
    // code for when R1 button is pushed
  }
  if (ctl->buttons() != 0x0020) {
    // code for when R1 button is released
  }

  //== PS4 R2 trigger button = 0x0080 ==//
  if (ctl->buttons() == 0x0080) {
    frente();
  }
 
  if (ctl->buttons() != 0x0080) {
    // code for when R2 button is released
     parado();
  }

  //== PS4 L1 trigger button = 0x0010 ==//
  if (ctl->buttons() == 0x0010) {
    // code for when L1 button is pushed
  }
  if (ctl->buttons() != 0x0010) {
    // code for when L1 button is released
  }

  //== PS4 L2 trigger button = 0x0040 ==//
  if (ctl->buttons() == 0x0040) {
    re();
  }
  if (ctl->buttons() != 0x0040) {
    // code for when L2 button is released
    parado();
  }

  //== LEFT JOYSTICK - UP ==//
  if (ctl->axisY() <= -25) {

    frente();
  
  }

  //== LEFT JOYSTICK - DOWN ==//
  if (ctl->axisY() >= 25) {
    // code for when left joystick is pushed down

    re();
  }

  //== LEFT JOYSTICK - LEFT ==//
  if (ctl->axisX() <= -25) {
    // code for when left joystick is pushed left
    esquerda();
  }

  //== LEFT JOYSTICK - RIGHT ==//
  if (ctl->axisX() >= 25) {
    // code for when left joystick is pushed right
    direita();
  }

  //== LEFT JOYSTICK DEADZONE ==//
  if (ctl->axisY() > -25 && ctl->axisY() < 25 && ctl->axisX() > -25 && ctl->axisX() < 25) {
    // code for when left joystick is at idle
  }

  //== RIGHT JOYSTICK - X AXIS ==//
  if (ctl->axisRX()) {
    // code for when right joystick moves along x-axis
  }

  //== RIGHT JOYSTICK - Y AXIS ==//
  if (ctl->axisRY()) {
  // code for when right joystick moves along y-axis
  }
  dumpGamepad(ctl);
}

void processControllers() {
  for (auto myController : myControllers) {
    if (myController && myController->isConnected() && myController->hasData()) {
      if (myController->isGamepad()) {
         processGamepad(myController);
      }
      else {
        Serial.println("Unsupported controller");
      }
    }
  }
}