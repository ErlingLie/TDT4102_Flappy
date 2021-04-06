#include <cstdlib>
#include <iostream>

#include "constants.h"
#include "track.h"

//Initialiser bakgrunnsbilder:


void Track::draw() {
    //Tegn bakgrunn her
 

    if(!gameOver){
        update();    
    } 
    //Tegn pipes her

    if(gameOver){
        game_over.draw(this->w()/2 - game_over.data_w()/2, this->h()/2);
    }    
}

void Track::update() {
    // Check for collision

    for (auto it = pipes.begin(); it != pipes.end();) {
        // Update pipes
        
        if (it->x() <= birdPosition && it->x() > birdPosition - speed) {
            // Count points
        }

        // Remove pipes no longer visible
        if (it->x() < -it->w()) {
            it = pipes.erase(it);
        }
        else {
            ++it;
        }
    }
    // Add pipes
}


void Track::addPipe() {
    // Adds a pipe every 4*pipeWidth
    static int position = pipeWidth*4;
    position += speed;
    if (position > pipeWidth * 4) {
        int height = rand() % maxPipeHeight;
        pipes.emplace_back(this->w(), ground, height, pipeGap);
        position = 0;
    }
}

bool Track::collision() const {
    // Checks if bird has collided with ground or a pipe
    return false;
}


Track::Track(int w, int h) :
    Fl_Widget(0, 0, w, h),
    //Endre ground til å være avhengig av base
    ground(h),
    gameOver{false}{}
