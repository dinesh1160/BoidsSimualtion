#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "constants.hpp"

struct Boid
{
    sf::Vector2f pos;
    sf::Vector2f vel;

    Boid() {

        pos.x = rand() % WINDOW_WIDTH;
        pos.y = rand() % WINDOW_HEIGHT;

        vel.x =  2;
        vel.y =  -2;

    }

    void update_physics(std::vector<Boid> &boids) {

        float xpos_avg = 0 , ypos_avg = 0;
        float xvel_avg = 0 , yvel_avg = 0;
        float close_dx = 0 , close_dy = 0;
        int neighbour_boids = 0;

        //every other boid in the window
        for ( auto &other_boid : boids) {
            if (&other_boid == this ) continue;

            float dx = other_boid.pos.x - pos.x;
            float dy = other_boid.pos.y - pos.y;

            if (abs(dx) < VISUAL_RANGE && abs(dy) < VISUAL_RANGE)
            {   
                float squared_distance = dx*dx + dy*dy;
    
                if (squared_distance < PROTECTED_RANGE*PROTECTED_RANGE)
                {   //for boids in the protected area
                    close_dx += pos.x - other_boid.pos.x;
                    close_dy += pos.y - other_boid.pos.y;

                }
                else if (squared_distance < VISUAL_RANGE*VISUAL_RANGE)
                {   
                    //accumaulator variables
                    xpos_avg += other_boid.pos.x;
                    ypos_avg += other_boid.pos.y;

                    xvel_avg += other_boid.vel.x;
                    yvel_avg += other_boid.vel.y;

                    neighbour_boids++;
                }
            }
            
        }


        if (neighbour_boids > 0) {

            xpos_avg = xpos_avg/neighbour_boids;
            ypos_avg = ypos_avg/neighbour_boids;

            xvel_avg = xvel_avg/neighbour_boids;
            yvel_avg = yvel_avg/neighbour_boids;


            //Alignment and Cohension
            vel.x = vel.x + (xpos_avg - pos.x)*CENTERING_FACTOR + (xvel_avg - vel.x)*MATCHING_FACTOR;
            vel.y = vel.y + (ypos_avg - pos.y)*CENTERING_FACTOR + (yvel_avg - vel.y)*MATCHING_FACTOR;

        }

        //Seperation
        vel.x = vel.x + close_dx*AVOID_FACTOR;
        vel.y = vel.y + close_dy*AVOID_FACTOR;

        //Border Logic
        if (pos.x < 100) {vel.x += TURN_FACTOR;}
        if (pos.x > WINDOW_WIDTH - 100) {vel.x -= TURN_FACTOR;}
        
        if (pos.y < 100) {vel.y += TURN_FACTOR;}
        if (pos.y > WINDOW_HEIGHT - 100) {vel.y -= TURN_FACTOR;}

        float speed = sqrt(vel.x * vel.x + vel.y * vel.y);

        if (speed < MIN_SPEED) {
            vel.x = (vel.x / speed) * MIN_SPEED;
            vel.y = (vel.y / speed) * MIN_SPEED;
        }
        if (speed > MAX_SPEED) {
            vel.x = (vel.x / speed) * MAX_SPEED;
            vel.y = (vel.y / speed) * MAX_SPEED;
        }

        

        pos += vel;
    }



};


int main() 
{

    sf::RenderWindow window;
    window.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT), "Boids Simulation", sf::Style::None);

    window.setFramerateLimit(60);

    std::vector<Boid> boids(NUM_BOIDS);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || (event.type = sf::Event::Closed))
            {
                window.close();

            }
            
        }
        for (auto& boid : boids)
        {
            boid.update_physics(boids);
        }
        
        window.clear(sf::Color::Black);

        for (auto& boid : boids)
        {
            sf::CircleShape b(4 ,3);
            b.setPosition(boid.pos.x , boid.pos.y);
            b.setFillColor(sf::Color::White);
            window.draw(b);
        }

        window.display();
    }

    return 0;

}
