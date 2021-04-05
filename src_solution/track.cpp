#include <cstdlib>
#include <iostream>

#include "constants.h"
#include "track.h"

Fl_PNG_Image Track::background{"../sprites/flappyBirdBackground.png"};
Fl_PNG_Image Track::base{"../sprites/base.png"};

void Track::draw() {
    
    if(score->getScore()%20 < 10){
        background.draw(0,0, this->w(), this->h());
    }
    else {
        background_night.draw(0,0,this->w(), this->h());
    }
    base.draw(0, h() - base.data_h(), this->w(), this->h());

    if(!initialized){
        initialize_game.draw(w()/2 - initialize_game.data_w()/2, 0);
        if(Fl::event_key(' ')){
            initialized = true;
            bird->initializeGame();
            score->initialize();
        }
        return;
    }    
    if(!gameOver){
        update();    
    } 
    // Pipe::draw() kalles ikke automatisk siden pipes ikke er lagt til i main() (mellom win->begin() og win->end())
    for (auto& pipe : pipes) {
        pipe.draw();
    }
    if(gameOver){
        game_over.draw(this->w()/2 - game_over.data_w()/2, this->h()/2);
        restart_im.draw(this->w()/2 - restart_im.data_w()/2, 2*this->h()/3);
        if (Fl::event_key(FL_Enter)){
            restart();
        }
    }    
}

void Track::restart() {
    gameOver = false;
    initialized = false;
    bird->reset();
    score->reset();
    pipes.clear();
}

void Track::update() {
    if (collision()) {
        gameOver = true;
        bird->setGameOver();
    }

    for (auto it = pipes.begin(); it != pipes.end();) {
        // Update pipes
        it->move(speed);

        // Count points
        if (it->x() <= birdPosition && it->x() > birdPosition - speed) {
            if(!(score->getScore() % 10)){
                speed+=1.0;
            }
            score->increment();
        }

        // Remove pipes no longer visible
        if (it->x() < -it->w()) {
            it = pipes.erase(it);
        }
        else {
            ++it;
        }
    }

    addPipe();
}


void Track::addPipe() {
    // Adds a pipe every 4*pipeWidth
    static int position = pipeWidth*4;
    position+= speed;
    if (position > pipeWidth * 4) {
        int height = rand() % maxPipeHeight;
        pipes.emplace_back(this->w(), ground, height, pipeGap);
        position = 0;
    }
}

bool Track::collision() const {
    // Checks if bird has collided with ground or a pipe
    // Collides with ground
    if (bird->y() + bird->h() >= ground) {
        return true;
    }

    // No pipes to collide with
    if (!pipes.size()) {
        return false;
    }

    // Can only collide with first pipe
    const Pipe& pipe = pipes.front();

    // auto [top, bottom] = pipe.getBounds(); // Structured bindings requires C++17
    // C++14:
    auto bound = pipe.getBounds();
    int top = bound.first;
    int bottom = bound.second;
    return (bird->x() + bird->w() >= pipe.x() + collisionMargin && bird->x() <= pipe.x() + pipe.w() - collisionMargin)
        && ((bird->y() <= top - collisionMargin) || (bird->y() + bird->h() >= bottom + collisionMargin));
}

Track::Track(int w, int h) : Fl_Widget(0, 0, w, h), ground(h-base.h()), gameOver{false}, initialized{false} {
     score = std::make_unique<Score>((w-scoreWidth)/2, 40);
}
