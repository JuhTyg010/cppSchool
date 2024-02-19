//
// Created by juhtyg on 19.2.24.
//

#ifndef INC_3D_GAME_SPRITERENDERER_H
#define INC_3D_GAME_SPRITERENDERER_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class spriteRenderer {
private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::IntRect rectSourceSprite;
    sf::Vector2f matrix;
    sf::Vector2f currentFrame;
public:
    sf::Sprite sprite;
    //sf::Texture texture;
    spriteRenderer(sf::Texture texture, sf::Vector2f position, sf::Vector2f size, sf::IntRect&& rectSourceSprite, sf::Vector2f matrix);
    void nextFrame();
    void prevFrame();

    void nextAnimation();
    void prevAnimation();
    void Render(sf::RenderWindow &window);
    void setPosition(sf::Vector2f position);
    void setScale(sf::Vector2f size);
    sf::Vector2f getCurrentFrame();

};


#endif //INC_3D_GAME_SPRITERENDERER_H
