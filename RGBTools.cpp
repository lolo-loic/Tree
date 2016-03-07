/*
* RGBTools
* Version 1.0 November, 2012
* Copyright 2012 Johannes Mittendorfer
* 
* Use this code with RGB-LEDs.
*/
// modified a bit by Loic 

#include "RGBTools.h"
// constructor; saves the pins
RGBTools::RGBTools(int r, int g, int b){
  this->r_pin = r;
  this->g_pin = g;
  this->b_pin = b;
}

// Set LED-color to custom color instantely
void RGBTools::setColor(int r, int g, int b){
  // set color of LED
  analogWrite(r_pin, r);
  analogWrite(g_pin, g);
  analogWrite(b_pin, b);

  // save state
  this->curr_r = r;
  this->curr_g = g;
  this->curr_b = b;
}

// Use a 32 bit hex value to set a color. See Colors class in header file
void RGBTools::setColorTo(uint32_t color){
  setColor((color & 0xFF0000) >> 16, (color & 0x00FF00) >> 8, color & 0x0000FF);
}

// Fade to custom color in specific time in specific steps
void RGBTools::fadeTo(int r,int g,int b,int steps,int duration){

  // calculate difference to target
  int diff_r = r-curr_r;
  int diff_g = g-curr_g;
  int diff_b = b-curr_b;

  // calculate the width of each step
  int steps_r = diff_r / steps;
  int steps_g = diff_g / steps;
  int steps_b = diff_b / steps;

  // loop through the steps (i: distance to target)
  for(int i = steps - 1; i >= 0; i--){

    // set color of current step
    this->setColor(
      r - i * steps_r,  // red target minus distance to target steps
      g - i * steps_g,  // green
      b - i * steps_b   // blue
    );

    // delay until next step
    delay(duration/steps);  
  }
}
