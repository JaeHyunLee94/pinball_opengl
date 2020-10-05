//
//  controller.hpp
//  sfml_rigidBody
//
//  Created by 이재현 on 2020/10/04.
//

#ifndef controller_hpp
#define controller_hpp
#include "game.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>




class Controller{
    
    
public:
    
    
    
    
    sf::RenderWindow* m_window;
    Game* m_game;
    sf::Clock deltaClock;
    sf::Color bgColor;
    bool my_tool_active=true;
    float my_color[4]={0,0,0,0};
    
    Controller(sf::RenderWindow& m_window,Game& m_game);
    
    void processInput();
    
    
    
};

#endif /* controller_hpp */
