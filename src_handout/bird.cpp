#include "bird.h"
#include "constants.h"
#include <cmath>
#include <FL/fl_draw.H>

Bird::Bird() : Fl_Widget(birdPosition, birdPosition, 34, 24), stopBird{true} {}

void Bird::draw() {

    if(!stopBird){
        steer();
        update();
    }
   //Lag kode som tegner fuglen her    
}

void Bird::steer() {
    // Handles user input
    if (Fl::event_key(' ')) {
        velocity = -flapVelocity;
    }
}

void Bird::update() {
    // Handles physics
    velocity += birdAcceleration;
    double position = y() + velocity;
    if (position < 0) {
        // Not allowed outside of screen
        position = 0;
        velocity = 0;
    }
    y(position);
}

void Bird::reset() {
    y(birdPosition);
    velocity = 0;
    stopBird = true;
}