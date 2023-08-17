#include <AccelStepper.h>

/**
 * @brief This code is used to control the fully electric drink can opener at the Castor Space club
 * @details The code is written for the Arduino Nano board using Arduino IDE.
 */

/**************************************************************/
/*                        CONSTANTS                           */
/**************************************************************/

// Pin numbers
constexpr unsigned int PIN_BUTTON_DC_1 = 2;         // DC motor button 1
constexpr unsigned int PIN_BUTTON_DC_2 = 3;         // DC motor button 2
constexpr unsigned int PIN_BUTTON_STEPPER_1 = 4;    // Stepper motor button 1
constexpr unsigned int PIN_BUTTON_STEPPER_2 = 5;    // Stepper motor button 2

constexpr unsigned int PIN_STEPPER_DIRECTION = 6;   // Stepper motor direction pin
constexpr unsigned int PIN_STEPPER_STEP = 7;        // Stepper motor step pin
constexpr unsigned int PIN_STEPPER_ENABLE = 8;      // Stepper motor enable pin

// When INA or INB is 1 and other 0, the motor rotates.
// The rotation direction is determined by INA and INB.
// The motor speed is determined by the PWM pin value.
constexpr unsigned int PIN_DC_MOTOR_INB = 9;
constexpr unsigned int PIN_DC_MOTOR_PWM = 10;
constexpr unsigned int PIN_DC_MOTOR_INA = 11;

constexpr unsigned int PIN_ARDUINO_LED = 13;        // Arduino Nano integrated LED

constexpr unsigned int PIN_NOT_USED = 0;            // Not used pin
constexpr unsigned int PIN_NOT_USED_2 = 1;          // Not used pin
constexpr unsigned int PIN_NOT_USED_3 = 12;         // Not used pin

// Motor speed and acceleration constants
constexpr int STEPPER_MAX_SPEED = 500;     // Magic number from testing the motor in the project
constexpr int DC_MOTOR_MAX_SPEED = 255;    // 8-bit value written to motor PWM pin

/**************************************************************/
/*                      GLOBAL VARIABLES                      */
/**************************************************************/

// Initialize the stepper motor driver
AccelStepper stepper(AccelStepper::DRIVER, PIN_STEPPER_STEP, PIN_STEPPER_DIRECTION);

int stepper_motor_speed = 0;
int dc_motor_speed = 0;

unsigned int stepper_motor_acceleration = 10;       // Acceleration every millisecond
unsigned int dc_motor_acceleration = 5;             // Acceleration every millisecond

unsigned long last_motor_speed_calculation_time = 0;

/**************************************************************/
/*                        MAIN PROGRAM                        */
/**************************************************************/

bool buttonPressed(unsigned int pin) {
    return !digitalRead(pin);
}


void setup() {
    pinMode(PIN_BUTTON_DC_1, INPUT_PULLUP);
    pinMode(PIN_BUTTON_DC_2, INPUT_PULLUP);
    pinMode(PIN_BUTTON_STEPPER_1, INPUT_PULLUP);
    pinMode(PIN_BUTTON_STEPPER_2, INPUT_PULLUP);
    pinMode(PIN_STEPPER_DIRECTION, OUTPUT);
    pinMode(PIN_STEPPER_STEP, OUTPUT);
    pinMode(PIN_STEPPER_ENABLE, OUTPUT);
    pinMode(PIN_DC_MOTOR_INB, OUTPUT);
    pinMode(PIN_DC_MOTOR_PWM, OUTPUT);
    pinMode(PIN_DC_MOTOR_INA, OUTPUT);
    pinMode(PIN_ARDUINO_LED, OUTPUT);

    stepper.setMaxSpeed(500);
    stepper.setSpeed(0);
}

void loop() {

    bool stepper_motor_button_1_pressed = buttonPressed(PIN_BUTTON_STEPPER_1);
    bool stepper_motor_button_2_pressed = buttonPressed(PIN_BUTTON_STEPPER_2);
    bool dc_motor_button_1_pressed = buttonPressed(PIN_BUTTON_DC_1);
    bool dc_motor_button_2_pressed = buttonPressed(PIN_BUTTON_DC_2);

    // Calculate motor speeds every millisecond
    if (millis() > last_motor_speed_calculation_time) {
        last_motor_speed_calculation_time = millis();

        // CALCULATE STEPPER MOTOR SPEED
        if (stepper_motor_button_1_pressed && stepper_motor_button_2_pressed) {
            // If both buttons are pressed, do nothing
        } else if (stepper_motor_button_1_pressed) {
            // If button 1 is pressed, increase speed
            stepper_motor_speed += stepper_motor_acceleration;
        } else if (stepper_motor_button_2_pressed) {
            // If button 2 is pressed, decrease speed
            stepper_motor_speed -= stepper_motor_acceleration;
        } else { // If buttons are not pressed, stop the motor
            if (stepper_motor_speed > 0) {
                stepper_motor_speed -= stepper_motor_acceleration;
            } else if (stepper_motor_speed < 0) {
                stepper_motor_speed += stepper_motor_acceleration;
            }
        }

        // Constrain the stepper motor speed to the max speed
        stepper_motor_speed = constrain(stepper_motor_speed, -STEPPER_MAX_SPEED, STEPPER_MAX_SPEED);

        // Set the stepper motor speed
        stepper.setSpeed(stepper_motor_speed);

        // CALCULATE DC MOTOR SPEED
        if (dc_motor_button_1_pressed && dc_motor_button_2_pressed) {
            // If both buttons are pressed, do nothing
        } else if (dc_motor_button_1_pressed) {
            // If button 1 is pressed, increase speed
            dc_motor_speed += dc_motor_acceleration;
        } else if (dc_motor_button_2_pressed) {
            // If button 2 is pressed, decrease speed
            dc_motor_speed -= dc_motor_acceleration;
        } else { // If buttons are not pressed, stop the motor
            if (dc_motor_speed > 0) {
                dc_motor_speed -= dc_motor_acceleration;
            } else if (dc_motor_speed < 0) {
                dc_motor_speed += dc_motor_acceleration;
            }
        }

        // Constrain the DC motor speed to the max speed
        dc_motor_speed = constrain(dc_motor_speed, -DC_MOTOR_MAX_SPEED, DC_MOTOR_MAX_SPEED);

        // Set the DC motor speed
        analogWrite(PIN_DC_MOTOR_PWM, abs(dc_motor_speed));

        // Set INA and INB pins based on the DC motor speed
        if (dc_motor_speed > 0) {
            digitalWrite(PIN_DC_MOTOR_INB, HIGH);
            digitalWrite(PIN_DC_MOTOR_INA, LOW);
        } else if (dc_motor_speed < 0) {
            digitalWrite(PIN_DC_MOTOR_INB, LOW);
            digitalWrite(PIN_DC_MOTOR_INA, HIGH);
        } else {
            digitalWrite(PIN_DC_MOTOR_INB, LOW);
            digitalWrite(PIN_DC_MOTOR_INA, LOW);
        }
    }

    stepper.runSpeed();
}
