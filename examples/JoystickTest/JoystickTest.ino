#include "TFT_HX8357.h"
#include "Joystick.h"

// Joystick buttons definition
#define BTN_B 2

TFT_HX8357 tft = TFT_HX8357();  // Invoke custom library

int joyButtons[] = {BTN_B};

int numberOfButtons = 1;

Joystick joystick = Joystick(A0, A1, joyButtons, numberOfButtons);

int x = 240;

int y = 160;

void setup() {
    Serial.begin(9600);

    tft.init();
    tft.setRotation(1);   //Landscape mode

    tft.fillScreen(TFT_BLACK);

    joystick.begin();
    joystick.configureAxes();
}

void loop() {
    drawJoystick();

    if (joystick.isLeft()) {
        Serial.println("Joystick is Left");
    }

    if (joystick.isRight()) {
        Serial.println("Joystick is Right");
    }

    if (joystick.isUp()) {
        Serial.println("Joystick is Up");
    }

    if (joystick.isDown()) {
        Serial.println("Joystick is Down");
    }

    if (joystick.isLeftUp()) {
        Serial.println("Joystick is LeftUp");
    }

    if (joystick.isRightUp()) {
        Serial.println("Joystick is RightUp");
    }

    if (joystick.isLeftDown()) {
        Serial.println("Joystick is LeftDown");
    }

    if (joystick.isRightDown()) {
        Serial.println("Joystick is RightDown");
    }

    delay(100);
}

void drawJoystick() {
    int positionX = 0;

    int positionY = 0;

    positionX = map(joystick.analogPositionX(), -512, 512, -24, 24);

    positionY = map(joystick.analogPositionY(), -512, 512, -24, 24);

    drawCross(x, y, TFT_BLACK);

    x += positionX;

    y += positionY;

    x > 473 ? x = 473 : x < 7 ? x = 7 : x = x;

    y > 313 ? y = 313 : y < 7 ? y = 7 : y = y;

    if (joystick.isPressed(BTN_B)) {
        drawCross(x, y, TFT_RED);
    }else {
        drawCross(x, y, TFT_WHITE);
    }
}

void drawCross(int x, int y, unsigned int color) {
    tft.drawLine(x - 7, y, x + 7, y, color);
    tft.drawLine(x, y - 7, x, y + 7, color);
}
