#include "Arduino.h"
#include "Joystick.h"

Joystick::Joystick(const int _xAxisPin, const int yAxisPin, int *buttons, int numberOfButtons) {
    this->xAxisPin = xAxisPin;
    this->yAxisPin = yAxisPin;
    this->buttons = buttons;
    this->numberOfButtons = numberOfButtons;
}

void Joystick::begin(void) {
    DEBUG_PRINT("X Axis Analog Pin: ")  DEBUG_PRINTLN(xAxisPin)
    DEBUG_PRINT("Y Axis Analog Pin: ")  DEBUG_PRINTLN(yAxisPin)
    DEBUG_PRINT("Number of Joystick Buttons: ")
    DEBUG_PRINTLN(numberOfButtons)

    for (int btn=0; btn < numberOfButtons; btn++) {
        pinMode(buttons[btn], INPUT); 
    }
}

void Joystick::configureAxes(uint8_t xAxisInvert, uint8_t yAxisInvert) {
    this->xAxisInvert = xAxisInvert;
    this->yAxisInvert = yAxisInvert;

    DEBUG_PRINT("Invert X Axis? ")  DEBUG_PRINTLN(xAxisInvert)
    DEBUG_PRINT("Invert Y Axis? ")  DEBUG_PRINTLN(yAxisInvert)
}

int Joystick::analogReadX(void) {  
    int analogX = analogRead(this->xAxisPin);

    // If X axis is inverted then invert reading
    if (xAxisInvert == INVERT_X)
        analogX = map(analogX, 0, ADC_RESOLUTION-1, ADC_RESOLUTION-1, 0);

    return analogX;
}

int Joystick::analogReadY(void) {
    int analogY = analogRead(this->yAxisPin);

    // If Y axis is inverted then invert reading
    if (yAxisInvert == INVERT_Y)
        analogY = map(analogY, 0, ADC_RESOLUTION-1, ADC_RESOLUTION-1, 0);

    return analogY;
}

int Joystick::analogPositionX(int threshold) {
    int positionX = analogReadX() - JOYSTICK_CENTER;

    // Set position to 0 if it's less than the threshold
    positionX = abs(positionX) >= threshold ? positionX : 0;

    return positionX;
}

int Joystick::analogPositionY(int threshold) {
    int positionY = analogReadY() - JOYSTICK_CENTER;

    positionY = abs(positionY) >= threshold ? positionY : 0;

    return positionY;
}

bool Joystick::isLeft(void) {
    return joystickPosition() == LEFT;
}

bool Joystick::isRight(void) {
    return joystickPosition() == RIGHT; 
}

bool Joystick::isUp(void) {
    return joystickPosition() == UP;  
}

bool Joystick::isDown(void) {
    return joystickPosition() == DOWN;  
}

bool Joystick::isCenter(void) {
    return joystickPosition() == CENTER;  
}

bool Joystick::isLeftUp(void) {
    return joystickPosition() == LEFT_UP;  
}

bool Joystick::isRightUp(void) {
    return joystickPosition() == RIGHT_UP; 
}

bool Joystick::isLeftDown(void) {
    return joystickPosition() == LEFT_DOWN;
}

bool Joystick::isRightDown(void) {
    return joystickPosition() == RIGHT_DOWN; 
}

joystickPositions Joystick::joystickPosition(void) {
    int positionX = analogPositionX(ADC_RESOLUTION / 4);

    int positionY = analogPositionY(ADC_RESOLUTION / 4);

    if (positionX < 0) {        // Joystick is at left
        return positionY > 0 ? LEFT_DOWN : positionY < 0 ? LEFT_UP : LEFT;
    }else if (positionX > 0) {  // Joystick is at right
        return positionY > 0 ? RIGHT_DOWN : positionY < 0 ? RIGHT_UP : RIGHT; 
    }else {                     // Joystick is at the center
        return positionY > 0 ? DOWN : positionY < 0 ? UP : CENTER;  
    }
}

bool Joystick::isPressed(int button) {
    return digitalRead(button) == BUTTON_ACTIVE_SIGNAL;
}

