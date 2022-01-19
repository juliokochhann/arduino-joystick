#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"

//#define DEBUG

// Define where debug output will be printed.
#define DEBUG_PRINTER Serial

#ifdef DEBUG
    #define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
    #define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
    #define DEBUG_PRINT(...) {}
    #define DEBUG_PRINTLN(...) {}
#endif

#define BUTTON_ACTIVE_SIGNAL    LOW
#define ADC_RESOLUTION          1024
#define JOYSTICK_CENTER         ADC_RESOLUTION / 2 - 1
#define DEFAULT_THRESHOLD       ADC_RESOLUTION / 16
#define NO_THRESHOLD            0
#define NO_INVERT_X             0
#define NO_INVERT_Y             0
#define INVERT_X                1
#define INVERT_Y                1

//Enumerate joystick positions
enum joystickPositions {
    LEFT,
    RIGHT,
    UP,
    DOWN,
    CENTER,
    LEFT_UP,
    RIGHT_UP,
    LEFT_DOWN,
    RIGHT_DOWN
};

class Joystick {
  public:
    Joystick(const int _xAxisPin, const int yAxisPin, int *buttons, int numberOfButtons);

    void begin(void);

    void configureAxes(uint8_t xAxisInvert = NO_INVERT_X, uint8_t yAxisInvert = INVERT_Y);

    int analogReadX(void);

    int analogReadY(void);

    int analogPositionX(int threshold = DEFAULT_THRESHOLD);

    int analogPositionY(int threshold = DEFAULT_THRESHOLD);

    bool isLeft(void);

    bool isRight(void);

    bool isUp(void);

    bool isDown(void);

    bool isCenter(void);

    bool isLeftUp(void);

    bool isRightUp(void);

    bool isLeftDown(void);

    bool isRightDown(void);

    joystickPositions joystickPosition(void);

    bool isPressed(int button);

  private:
    int xAxisPin, yAxisPin, xAxisInvert, yAxisInvert, *buttons, numberOfButtons;
};

#endif
