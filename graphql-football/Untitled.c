/******************************************************************************
  Micro-OLED-Shield-Example.ino
  SparkFun Micro OLED Library Hello World Example
  Jim Lindblom @ SparkFun Electronics
  Original Creation Date: June 22, 2015

  This sketch prints a friendly, recognizable logo on the OLED Shield, then
  goes on to demo the Micro OLED library's functionality drawing pixels,
  lines, shapes, and text.

  Hardware Connections:
	This sketch was written specifically for the Photon Micro OLED Shield,
	which does all the wiring for you. If you have a Micro OLED breakout,
	use the following hardware setup:

    MicroOLED ------------- Photon
      GND ------------------- GND
      VDD ------------------- 3.3V (VCC)
    D1/MOSI ----------------- A5 (don't change)
    D0/SCK ------------------ A3 (don't change)
      D2
      D/C ------------------- D6 (can be any digital pin)
      RST ------------------- D7 (can be any digital pin)
      CS  ------------------- A2 (can be any digital pin)

  Development environment specifics:
  	IDE: Particle Build
  	Hardware Platform: Particle Photon
                       SparkFun Photon Micro OLED Shield

  This code is beerware; if you see me (or any other SparkFun
  employee) at the local, and you've found our code helpful,
  please buy us a round!

  Distributed as-is; no warranty is given.
*******************************************************************************/
#include "SparkFunMicroOLED/SparkFunMicroOLED.h"  // Include MicroOLED library
#include "math.h"

//////////////////////////////////
// MicroOLED Object Declaration //
//////////////////////////////////
// Declare a MicroOLED object. If no parameters are supplied, default pins are
// used, which will work for the Photon Micro OLED Shield (RST=D7, DC=D6, CS=A2)
MicroOLED oled;
//MicroOLED oled(MODE_I2C, D7, 0);    // Example I2C declaration RST=D7, DC=LOW (0)

//SYSTEM_MODE(MANUAL);

void setup()
{
  Serial.begin(9600);
  oled.begin();    // Initialize the OLED
  oled.clear(ALL); // Clear the display's internal memory
  oled.display();  // Display what's in the buffer (splashscreen)
  delay(1000);     // Delay 1000 ms
  randomSeed(analogRead(A0) + analogRead(A1));
  pinMode(D4, INPUT);
  digitalWrite(D4, LOW);
}

void loop()
{
  shapeExample();  // Then the shape example
}

void shapeExample()
{
  printTitle("PONG!!!", 0);
  delay(2000);

  // Silly pong demo. It takes a lot of work to fake pong...
  int paddleW = 3;  // Paddle width
  int paddleH = 15;  // Paddle height
  // Paddle 0 (left) position coordinates
  int paddle0_Y = (oled.getLCDHeight() / 2) - (paddleH / 2);
  int paddle0_X = 2;
  // Paddle 1 (right) position coordinates
  int paddle1_Y = (oled.getLCDHeight() / 2) - (paddleH / 2);
  int paddle1_X = oled.getLCDWidth() - 3 - paddleW;
  int ball_rad = 2;  // Ball radius
  // Ball position coordinates
  int ball_X = paddle0_X + paddleW + ball_rad;
  int ball_Y = random(1 + ball_rad, oled.getLCDHeight() - ball_rad);//paddle0_Y + ball_rad;
  int ballVelocityX = 1;  // Ball left/right velocity
  int ballVelocityY = 1;  // Ball up/down velocity
  int paddle0Velocity = -1;  // Paddle 0 velocity
  int paddle1Velocity = 1;  // Paddle 1 velocity

  //while(ball_X >= paddle0_X + paddleW - 1)
  while ((ball_X - ball_rad > 1) &&
         (ball_X + ball_rad < oled.getLCDWidth() - 2))
  {
    // Increment ball's position
    ball_X+=ballVelocityX;
    ball_Y+=ballVelocityY;
    // Check if the ball is colliding with the left paddle
    if (ball_X - ball_rad < paddle0_X + paddleW)
    {
      // Check if ball is within paddle's height
      if ((ball_Y > paddle0_Y) && (ball_Y < paddle0_Y + paddleH))
      {
        ball_X++;  // Move ball over one to the right
        ballVelocityX = -ballVelocityX; // Change velocity
      }
    }
    // Check if the ball hit the right paddle
    if (ball_X + ball_rad > paddle1_X)
    {
      // Check if ball is within paddle's height
      if ((ball_Y > paddle1_Y) && (ball_Y < paddle1_Y + paddleH))
      {
        ball_X--;  // Move ball over one to the left
        ballVelocityX = -ballVelocityX; // change velocity
      }
    }
    // Check if the ball hit the top or bottom
    if ((ball_Y <= ball_rad) || (ball_Y >= (oled.getLCDHeight() - ball_rad - 1)))
    {
      // Change up/down velocity direction
      ballVelocityY = -ballVelocityY;
    }
    // Move the paddles up and down

    int val = digitalRead(D4);
    debug("Please = %d", val);
    if(val == HIGH) {
        paddle0_Y += paddle0Velocity;
    } else {
        paddle1_Y += paddle1Velocity;
    }
    // Change paddle 0's direction if it hit top/bottom
    if ((paddle0_Y <= 1) || (paddle0_Y > oled.getLCDHeight() - 2 - paddleH))
    {
      paddle0Velocity = -paddle0Velocity;
    }
    // Change paddle 1's direction if it hit top/bottom
    if ((paddle1_Y <= 1) || (paddle1_Y > oled.getLCDHeight() - 2 - paddleH))
    {
      paddle1Velocity = -paddle1Velocity;
    }

    // Draw the Pong Field
    oled.clear(PAGE);  // Clear the page
    // Draw an outline of the screen:
    oled.rect(0, 0, oled.getLCDWidth() - 1, oled.getLCDHeight());
    // Draw the center line
    oled.rectFill(oled.getLCDWidth()/2 - 1, 0, 2, oled.getLCDHeight());
    // Draw the Paddles:
    oled.rectFill(paddle0_X, paddle0_Y, paddleW, paddleH);
    oled.rectFill(paddle1_X, paddle1_Y, paddleW, paddleH);
    // Draw the ball:
    oled.circle(ball_X, ball_Y, ball_rad);
    // Actually draw everything on the screen:
    oled.display();
    delay(50);  // Delay for visibility
  }
  delay(1000);
}

// Center and print a small title
// This function is quick and dirty. Only works for titles one
// line long.
void printTitle(String title, int font)
{
  int middleX = oled.getLCDWidth() / 2;
  int middleY = oled.getLCDHeight() / 2;

  oled.clear(PAGE);
  oled.setFontType(font);
  // Try to set the cursor in the middle of the screen
  oled.setCursor(middleX - (oled.getFontWidth() * (title.length()/2)),
                 middleY - (oled.getFontWidth() / 2));
  // Print the title:
  oled.print(title);
  oled.display();
  delay(1500);
  oled.clear(PAGE);
}

void debug(String message, int value) {
    char msg [50];
    sprintf(msg, message.c_str(), value);
    Spark.publish("DEBUG", msg);
}
