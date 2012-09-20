// MultiChannels
//
// rcarduino.blogspot.com
//
// A simple approach for reading three RC Channels using pin change interrupts
//
// See related posts - 
// http://rcarduino.blogspot.co.uk/2012/01/how-to-read-rc-receiver-with.html
// http://rcarduino.blogspot.co.uk/2012/03/need-more-interrupts-to-read-more.html
// http://rcarduino.blogspot.co.uk/2012/01/can-i-control-more-than-x-servos-with.html

#include <PinChangeInt.h>
#include <Servo.h>

#define USE_SERVO 1

#define LEFT_MOTOR_DIR_PIN  4
#define LEFT_MOTOR_PIN      5 // PWM - TIMER0
#define RIGHT_MOTOR_PIN     6 // PWM - TIMER0
#define RIGHT_MOTOR_DIR_PIN 7

#define CHANNEL1 A0 // R LR
#define CHANNEL2 A1 // R UD
#define CHANNEL3 A2 // L UD
#define CHANNEL4 A3 // L LR
#define CHANNEL5 A4 // Knob1
#define CHANNEL6 A5 // Knob2

#define THROTTLE_IN_PIN CHANNEL3
#define STEERING_IN_PIN CHANNEL1
#define AUX_IN_PIN CHANNEL6

// These bit flags are set in bUpdateFlagsShared to indicate which channels have new signals
#define THROTTLE_FLAG 1
#define STEERING_FLAG 2
#define AUX_FLAG 4

int leftServoPin = 9;
int rightServoPin = 10;

// holds the update flags defined above
volatile uint8_t bUpdateFlagsShared;

// shared variables are updated by the ISR and read by loop.
// In loop we immediatley take local copies so that the ISR can keep ownership of the 
// shared ones. To access these in loop we first turn interrupts off with noInterrupts
// we take a copy to use in loop and the turn interrupts back on
// as quickly as possible, this ensures that we are always able to receive new signals
volatile uint16_t unThrottleInShared;
volatile uint16_t unSteeringInShared;
volatile uint16_t unAuxInShared;

// These are used to record the rising edge of a pulse in the calcInput functions
// They do not need to be volatile as they are only used in the ISR. If we wanted
// to refer to these in loop and the ISR then they would need to be declared volatile
uint32_t ulThrottleStart;
uint32_t ulSteeringStart;
uint32_t ulAuxStart;

// create local variables to hold a local copies of the channel inputs
// these are declared static so that thier values will be retained 
// between calls to loop.
uint16_t unThrottleIn;
uint16_t unSteeringIn;
uint16_t unAuxIn;

// local copy of update flags
uint8_t bUpdateFlags;



