//
//  game.hpp
//  sfml_rigidBody
//
//  Created by 이재현 on 2020/10/04.
//

#ifndef game_hpp
#define game_hpp

#include <box2d/box2d.h>
#include "b2GLDraw.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Game{
    
    
public:
    
    Game();
//    ~game();
    
    
    b2World* world;
    b2Body* m_ball;
    b2Body* ground = NULL;
    b2Vec2 Gravity;
    b2RevoluteJoint* m_leftJoint;
    b2RevoluteJoint* m_rightJoint;
    sf::Texture GroundTexture;
    sf::Texture BoxTexture;
    
    b2GLDraw fooDrawInstance;
    
    float timeStep=1.f/60;
    int velocityIter=8;
    int positionIter=3;
    
    const float MAP_WIDTH=800.f;
    const float MAP_HEIGHT=700.f;
    const int WINDOW_WIDTH=3000;
    const int WINDOW_HEIGHT=1500;
    float SCALE=30.f;
    int BodyCount=0;
    bool m_button = false;
    
    void createMap();
    void createBox(float,float);
    void render(sf::RenderWindow& Window);
    void step();
    void doFlip(int);



};

#endif /* game_hpp */
