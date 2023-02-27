#ifndef COLOR_H
#define COLOR_H

#include <Arduino.h>

#define COLOR_S0 4
#define COLOR_S1 5
#define COLOR_S2 6
#define COLOR_S3 7
#define COLOR_OUTPUT 8


extern int red_frequency;
extern int green_frequency;
extern int blue_frequency;

extern int red_probability;
extern int yellow_probability;
extern int blue_probability;

void color_setup();
void color_sequence();

void reset_color_probabilities();

int resultant_color();

#endif
