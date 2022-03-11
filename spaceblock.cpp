#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace sf;
bool collided(Sprite sprite1, Sprite sprite2){return sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds());}
bool paddle_collide(Sprite s1, Sprite s2){return s1.getGlobalBounds().intersects(s2.getGlobalBounds());}
bool started = false;
int main(){
    Font font;
    font.loadFromFile("images/RadgivareNo1Demo_FREE_FOR_PERSONAL_USE_ONLY.otf"); // use your own fonts

    sf::Text text;
    text.setFont(font);
    text.setString("Press arrow keys left and right to \n move the paddle \n press up key to start the game");
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(50, 300);

    srand(time(NULL));
    int randnum;
    sf::RenderWindow app(sf::VideoMode(520, 450), "Retard game");
    app.setFramerateLimit(60);

    Texture t1,t2,t3,t4,t5,t6,t7; // paths leading to the images
    t1.loadFromFile("images/block01.png"); //use your own paths
    t2.loadFromFile("images/background.jpg");
    t3.loadFromFile("images/ball.png");
    t4.loadFromFile("images/paddle.png");
    t5.loadFromFile("images/block02.png");
    t6.loadFromFile("images/block03.png");
    t7.loadFromFile("images/block05.png");

    Sprite sbackground(t2), spaddle(t4), ball(t3);

    Sprite block[1000];

    sf::Vector2f ballpos(300, 300);
    sf::Vector2f spaddlepos(300, 440);
    spaddle.setPosition(spaddlepos);
    ball.setPosition(ballpos); // init pos of ball
    srand(time(NULL));
    int n = 0;
    for (int x = 1; x <= 10; x ++){ //10 by 10 layout, y axis
        for (int y = 1; y<= 10; y++){ // x axis
            randnum = rand() % 4;
            std::cout << randnum;
            switch (randnum){
            case 0: block[n].setTexture(t1); break; //set the game environment with blocks of different colours :D makes it less dull
            case 1: block[n].setTexture(t5); break;
            case 2: block[n].setTexture(t6); break;
            case 3: block[n].setTexture(t7); break;
            }
            block[n].setPosition(x*43,y*20); // set the position of the block
            n++; //move on to the next block
        }
    }

    float xVelocity = 3;
    float yVelocity = -3;
    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) app.close();
            if(Keyboard::isKeyPressed(Keyboard::Up)){started = true;}
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) app.close();

        }
        //paddle movement
        if(Keyboard::isKeyPressed(Keyboard::Right)){
            if(spaddle.getPosition().x < 450-17){
            spaddle.move(7,0);
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::Left)){
            if(spaddle.getPosition().x > 0){
            spaddle.move(-7,0);
            }
        }
        //if(Keyboard::isKeyPressed(Keyboard::Left)  (spaddle.getPosition().y <450 -10)){spaddle.move(-7,0);}
        //ball physics collide
        for(int i = 0; i < n; i++){
            if(collided(ball, block[i])){
            std::cout << "COLLIDED";
            block[i].setPosition(-1000, 1000);
            xVelocity = xVelocity;
            yVelocity = -yVelocity;
            }
        }
        if(paddle_collide(ball, spaddle)){
            xVelocity *= 1;
            yVelocity *= -1;
            std::cout<<"paddle collided";
        }
        //ball physics

        ballpos = ball.getPosition();
        if (ballpos.x < 0 || ballpos.x > 520 -10) xVelocity *= -1;
        if (ballpos.y < 0) xVelocity *= -1;
        if (ballpos.y > 450){
            text.setString("You lost!");
            text.setFillColor(sf::Color::Red);
            started = false;
            std::cout << "you lost";

        }
        if(started){
        ball.move(xVelocity, 0);
        ball.move(0, yVelocity);
      //  ball.setPosition(ballpos);
        }
        //render
        app.clear();
        //app.draw(sbackground);
        app.draw(ball);
        app.draw(spaddle);
        if (!started){app.draw(text);}
        for(int i=0;i<n;i++){app.draw(block[i]);} //draw all 100 blocks
        app.display();}

    return 0;
}
