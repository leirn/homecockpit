// Controls an LED via an attached button.

#include <Adafruit_MCP23X17.h>
#define MCP1_LED_PIN 8     // MCP23XXX pin LED is attached to
#define MCP1_BUTTON_PIN 5  // MCP23XXX pin button is attached to

#define MCP2_LED_PIN 7     // MCP23XXX pin LED is attached to
#define MCP2_BUTTON_PIN 10  // MCP23XXX pin button is attached to

// only used for SPI
#define CS1_PIN 53
#define CS2_PIN 53

Adafruit_MCP23X17 mcp1;
Adafruit_MCP23X17 mcp2;
// MCP23S17 MCP_2(CS2_PIN, 0b001);

int led1_state = 1;
int led2_state = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("MCP23xxx Combo Test!");

  if (!mcp1.begin_SPI(CS1_PIN, &SPI, 0b000)) {
    Serial.println("Error.");
    while (1);
  }
  if (!mcp2.begin_SPI(CS2_PIN, &SPI, 0b001)) {
    Serial.println("Error.");
    while (1);
  }

  // configure LED pin for output
  mcp1.pinMode(MCP1_LED_PIN, OUTPUT);

  // configure button pin for input with pull up
  mcp1.pinMode(MCP1_BUTTON_PIN, INPUT_PULLUP);

  // configure LED pin for output
  mcp2.pinMode(MCP2_LED_PIN, OUTPUT);

  // configure button pin for input with pull up
  mcp2.pinMode(MCP2_BUTTON_PIN, INPUT_PULLUP);

  mcp1.digitalWrite(MCP1_LED_PIN, led1_state);
  mcp2.digitalWrite(MCP2_LED_PIN, led2_state);
  delay(5000);
  Serial.println("Looping...");
}

void loop() {
  Serial.println("Loop");
  int state = mcp2.digitalRead(MCP2_BUTTON_PIN);
  Serial.print("Button 2 status : ");
  Serial.println(state);
  // LOW = pressed, HIGH = not pressed
  if (state == LOW) {
    Serial.println("MCP2 button pressed");
    led1_state = !led1_state;
    mcp1.digitalWrite(MCP1_LED_PIN, led1_state);
    delay(1000);
  }
  int state2 = mcp1.digitalRead(MCP1_BUTTON_PIN);
  Serial.print("Button 1 status : ");
  Serial.println(state2);
  if (state2 == LOW) {
    Serial.println("MCP1 button pressed");
    led2_state = !led2_state;
    mcp2.digitalWrite(MCP2_LED_PIN, led2_state);
    delay(1000);
  }
  delay(10);
  // mcp1.digitalWrite(MCP1_LED_PIN, !mcp2.digitalRead(BUTTON_PIN));
  
  // led1_state = 1 - led1_state;
  // mcp1.digitalWrite(MCP1_LED_PIN, HIGH);
  // delay(5000);
  
  // led2_state = 1 - led2_state;
  // mcp2.digitalWrite(MCP2_LED_PIN, HIGH);
  // delay(5000);

  // led1_state = 1 - led1_state;
  // mcp1.digitalWrite(MCP1_LED_PIN, LOW);
  // delay(5000);
  
  // led2_state = 1 - led2_state;
  // mcp2.digitalWrite(MCP2_LED_PIN, LOW);
  // delay(5000);
}
