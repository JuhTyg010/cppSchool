//
// Created by juhtyg on 19.2.24.
//

#ifndef INC_3D_GAME_SPRITERENDERER_H
#define INC_3D_GAME_SPRITERENDERER_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Utils.h"

class spriteRenderer {
private:
    Texture& texture;
    sf::IntRect rectSourceSprite;
    sf::Vector2f currentFrame;
public:
    sf::Sprite sprite;

    /**
     * @brief Construct a new sprite Renderer object
     * 
     */
    spriteRenderer() = default;
    /**
     * @brief Construct a new sprite Renderer object
     * 
     * @param texture 
     * @param position 
     * @param scale 
     * @param size 
     * @param matrix 
     */
    spriteRenderer(Texture& texture, sf::Vector2f position, sf::Vector2f  size);
    /**
     * @brief nextFrame calculate position of the frame on the right side of the texture (is circular)
     * 
     */
    void nextFrame();
    /**
     * @brief prevFrame calculate position of the frame on the left side of the texture (is circular)
     * 
     */
    void prevFrame();

    /**
     * @brief nextAnimation animation is specified as line so it goes down for next animation (is circular)
     * 
     */
    void nextAnimation();
    /**
     * @brief prevAnimation animation is specified as line so it goes up for previous animation (is circular)
     * 
     */
    void prevAnimation();
    /**
     * @brief renders the sprite on the window
     * 
     * @param window 
     */
    void Render(sf::RenderWindow &window);
    /**
     * @brief Set the Position of the object
     * 
     * @param position 
     */
    void setPosition(sf::Vector2f position);
    /**
     * @brief Set the Texture Rect object, its safer to use next/prev frame or animation this is for non full texture rendering
     * 
     * @param rect 
     */
    void setTextureRect(sf::IntRect rect);
    /**
     * @brief Set the Scale of the object
     * 
     * @param scale_ 
     */
    void setScale(sf::Vector2f scale_);
    /**
     * @brief Get the Current Frame of the object (position of the frame and animation on the texture)
     * 
     * @return sf::Vector2f 
     */
    sf::Vector2f getCurrentFrame();

};


#endif //INC_3D_GAME_SPRITERENDERER_H
