#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT= 1080;

// Boids Properties
const int NUM_BOIDS= 300;
const float VISUAL_RANGE = 50.0f;
const float PROTECTED_RANGE = 20.0f;
const float AVOID_FACTOR = 0.05f;
const float MATCHING_FACTOR = 0.05f;
const float CENTERING_FACTOR = 0.0005f;
const float TURN_FACTOR = 0.2f;
const float MIN_SPEED = 2.0f;
const float MAX_SPEED = 3.0f;

#endif