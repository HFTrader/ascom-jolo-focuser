// Interrupt serial event
void serialEvent() {
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read(); 
    if (inChar == '\n') {
      serialCommand(inputString); 
      inputString = "";
    } 
    else {
      inputString += inChar;
    }
  }  
}

void serialCommand(String command) {
  String param = command.substring(2); 

  switch(command.charAt(0)) {
  case '#':
    Serial.print(DEVICE_RESPONSE);
    buzz(BUZZ_LONG, 1);
    break;
  case 'T':    // Read temperature
    printTemp();
    break;
  case 'P':    // Return current position
    printCurrentPosition();
    break;
  case 'H':    // Halt focuser
    halt();   
    break;
  case 'I':
    printInMoveStatus();
    break;
  case 'M':    // Move focuser to new position
    moveStepper(stringToNumber(param), false); 
    break;
  case 'S':
    saveStepperSpeed(stringToNumber(param));
    break;
  case 'D':
    saveDutyCycle(stringToNumber(param));
    break;
  case 'R':
    saveCurrentPos(stringToNumber(param));
    break;
  default:
    Serial.print("ERR:");      
    Serial.print(byte(command.charAt(1)), DEC); 
    buzz(BUZZ_SHORT, 5);
  }
  Serial.print('\n');
}

// Serial commands subroutines
void printTemp() {
  if(sensorConnected) {
    Serial.print("T:");
    Serial.print(currentTemp, 1);  
  } else {
    Serial.print("T:false"); 
  }  
}

void printCurrentPosition() {
  Serial.print("P:");
  Serial.print(stepper.currentPosition());
}

void printInMoveStatus() {
  Serial.print("I:");
  if(stepper.distanceToGo() == 0) 
    Serial.print("false");
  else
    Serial.print("true");
}

void moveStepper(word newPos, boolean manualMove) {
  if(newPos != stepper.currentPosition()) {
    tempRequestMilis = tempReadMilis = 0;
    pwmWrite(STEPPER_PWM_PIN, 255);
    stepper.moveTo(newPos);
    positionSaved = false;
  }
  if(!manualMove) Serial.print("M");
}

void halt() {
  stepper.stop();
  Serial.print("H");
}

void saveCurrentPos(word newPos) {
  stepper.setCurrentPosition(newPos);
  positionSaved = true;
  saveFocuserPos(newPos);
  Serial.print("R");
}

void saveStepperSpeed(word stepperSpeed) {
  writeWord(STEPPER_SPEED_ADD, stepperSpeed);
  stepper.setMaxSpeed(readWord(STEPPER_SPEED_ADD));
  Serial.print("S");
}

void saveDutyCycle(byte dutyCycle) {
  if(dutyCycle > 100) dutyCycle = 100;
  EEPROM.write(DUTY_CYCLE_ADDR, dutyCycle);
  Serial.print("D");
}



