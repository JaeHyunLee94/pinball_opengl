//
//  game.cpp
//  sfml_rigidBody
//
//  Created by 이재현 on 2020/10/04.
//

#include "game.hpp"
#include <box2d/box2d.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "signal.h"
//constructor
Game::Game(){
    
    
    Gravity=b2Vec2(0,10);
//    world.SetGravity(Gravity);
    
    
    world=new b2World(Gravity);
    
    
    
    world->SetDebugDraw(&fooDrawInstance);
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
//    flags += b2Draw::e_jointBit;
//    flags += b2Draw::e_aabbBit;
//    flags += b2Draw::e_pairBit;
//    flags += b2Draw::e_centerOfMassBit;
    fooDrawInstance.SetFlags(flags);

    
    GroundTexture.loadFromFile("ground.png");
    BoxTexture.loadFromFile("box.png");
    
    
    
    
}

void Game::createMap(){
    



    b2Body* ground = NULL;
    {
        b2BodyDef bd;
        ground = world->CreateBody(&bd);

        b2Vec2 vs[5];
        vs[0].Set((WINDOW_WIDTH/2-400)/SCALE, 100/SCALE);
        vs[1].Set((WINDOW_WIDTH/2-400)/SCALE, (100+MAP_HEIGHT)/SCALE);
        vs[2].Set((WINDOW_WIDTH/2)/SCALE, (100+MAP_HEIGHT+400)/SCALE);
        vs[3].Set((WINDOW_WIDTH/2+400)/SCALE, (100+MAP_HEIGHT)/SCALE);
        vs[4].Set((WINDOW_WIDTH/2+400)/SCALE,100/SCALE);

        b2ChainShape loop;
        loop.CreateLoop(vs, 5);
        b2FixtureDef fd;
        fd.shape = &loop;
        fd.density = 0.0f;
        ground->CreateFixture(&fd);
    }
    // Flippers
    {
        
        
        b2Vec2 p1(((WINDOW_WIDTH/2)-100)/SCALE, (100+MAP_HEIGHT+400*0.75)/SCALE), p2(((WINDOW_WIDTH/2)+100)/SCALE, (100+MAP_HEIGHT+400*0.75)/SCALE);

        b2BodyDef bd;
        bd.type = b2_dynamicBody;

        bd.position = p1;
        b2Body* leftFlipper = world->CreateBody(&bd);

        bd.position = p2;
        b2Body* rightFlipper = world->CreateBody(&bd);

        b2PolygonShape box;
        box.SetAsBox(90.f/SCALE, 5.f/SCALE);

        b2FixtureDef fd;
        fd.shape = &box;
        fd.density = 0.1f;

        leftFlipper->CreateFixture(&fd);
        rightFlipper->CreateFixture(&fd);

        b2RevoluteJointDef jd;
        jd.bodyA = ground;
        jd.localAnchorB.SetZero();
        jd.enableMotor = true;
        jd.maxMotorTorque = 1000.0f;
        jd.enableLimit = true;

        jd.motorSpeed = 0.0f;
        
        jd.localAnchorA=p1;
        jd.bodyB = leftFlipper;
        jd.lowerAngle = -30.0f * b2_pi / 180.0f;
        jd.upperAngle = 5.0f * b2_pi / 180.0f;
        m_leftJoint = (b2RevoluteJoint*)world->CreateJoint(&jd);

        jd.motorSpeed = 0.0f;
        
        jd.localAnchorA=p2;
        jd.bodyB = rightFlipper;
        jd.lowerAngle = -5.0f * b2_pi / 180.0f;
        jd.upperAngle = 30.0f * b2_pi / 180.0f;
        m_rightJoint = (b2RevoluteJoint*)world->CreateJoint(&jd);
    }
    {
        
       
        b2BodyDef bd;
        bd.position.Set(1250.f/SCALE, 200.f/SCALE);
        bd.type = b2_dynamicBody;
        bd.bullet = true;

        m_ball = world->CreateBody(&bd);

        b2CircleShape shape;
        shape.m_radius = 10.f/SCALE;

        b2FixtureDef fd;
        fd.shape = &shape;
        fd.density = 1.0f;
        m_ball->CreateFixture(&fd);
    }
}
void Game::createBox(float MouseX,float MouseY){
    b2BodyDef BodyDef;
    std::cout <<"create box!!\n";

    
    BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
    BodyDef.type = b2_dynamicBody;
    b2Body* Body = world->CreateBody(&BodyDef);
    
    b2PolygonShape Shape;
    Shape.SetAsBox((32.f / 2) / SCALE, (32.f / 2) / SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}

void Game::render(sf::RenderWindow& Window){
    
    for (b2Body* BodyIterator = world->GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    {
        if (BodyIterator->GetType() == b2_dynamicBody)
        {
            sf::Sprite Sprite;
            Sprite.setTexture(BoxTexture);
            Sprite.setOrigin(16.f, 16.f);
            Sprite.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
            Sprite.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
            Window.draw(Sprite);
            ++BodyCount;
        }
        else
        {
            sf::Sprite GroundSprite;
            GroundSprite.setTexture(GroundTexture);
            GroundSprite.setOrigin(400.f, 8.f);
            GroundSprite.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
            GroundSprite.setRotation(180 / b2_pi * BodyIterator->GetAngle());
            Window.draw(GroundSprite);
        }
    }
    
    world->DebugDraw();
}

void Game::step(){
 
    
    world->Step(timeStep, velocityIter, positionIter);
   
}

void Game::doFlip(int signal){
    
    
    switch (signal) {
            
        case GameSignal::DO_NOT_FLIP:
            m_leftJoint->SetMotorSpeed(20.0f);
            m_rightJoint->SetMotorSpeed(-20.0f);
            break;
            
        case GameSignal::DO_FLIP:
            m_leftJoint->SetMotorSpeed(-10.0f);
            m_rightJoint->SetMotorSpeed(10.0f);
            break;
            
        default:
            break;
    }
    
    
}



