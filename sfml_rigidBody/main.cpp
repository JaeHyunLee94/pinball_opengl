//
//  main.cpp
//  RigidBody_sim
//
//  Created by 이재현 on 2020/10/01.
//
#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <stdio.h>

#include <GL/glew.h>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>
#include "b2GLDraw.h"

#include "game.hpp"
#include "signal.h"
#include "controller.hpp"
#include <imgui.h>
#include <imgui-SFML.h>


/** We need this to easily convert between pixel and real-world coordinates*/

const int WINDOW_WIDTH=3000;
const int WINDOW_HEIGHT=1500;
int main()
{
    /** Prepare the window */
    sf::RenderWindow Window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT,32), "Pinball Game");
    Window.setFramerateLimit(60);
    
    Game m_game;
    
    m_game.createMap();
    Controller controller(Window,m_game);
    ImGui::SFML::Init(Window);
    
    
    

    while (Window.isOpen())
    {

        Window.clear(sf::Color::White);

        controller.processInput();
        
        m_game.step();
        m_game.render(Window);
    
        
        Window.display();
    }
    
    return 0;
}
