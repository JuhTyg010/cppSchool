//
// Created by juhtyg on 19.2.24.
//

#include "../headers/spriteRenderer.h"


spriteRenderer::spriteRenderer(sf::Texture texture, sf::Vector2f position, sf::Vector2f size,
                               sf::IntRect&& rectSourceSprite, sf::Vector2f matrix) :
position(position), size(size), matrix(matrix), rectSourceSprite(rectSourceSprite){
   // texture.loadFromFile(path);
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setScale(size);
    currentFrame = sf::Vector2f(rectSourceSprite.left, rectSourceSprite.top);
}


void spriteRenderer::nextFrame() {
    if(matrix.x > currentFrame.x) {
        currentFrame.x++;
    } else {
        currentFrame.x = 0;
    }
    rectSourceSprite.left = currentFrame.x * rectSourceSprite.width;
}

void spriteRenderer::prevFrame() {
    if(currentFrame.x > 0) {
        currentFrame.x--;
    } else {
        currentFrame.x = matrix.x;
    }
    rectSourceSprite.left = currentFrame.x * rectSourceSprite.width;
}

void spriteRenderer::nextAnimation() {
    if(matrix.y > currentFrame.y) {
        currentFrame.y++;
    } else {
        currentFrame.y = 0;
    }
    rectSourceSprite.top = currentFrame.y * rectSourceSprite.height;
}

void spriteRenderer::prevAnimation() {
    if(currentFrame.y > 0) {
        currentFrame.y--;
    } else {
        currentFrame.y = matrix.y;
    }
    rectSourceSprite.top = currentFrame.y * rectSourceSprite.height;
}

sf::Vector2f spriteRenderer::getCurrentFrame() {
    return currentFrame;
}

void spriteRenderer::Render(sf::RenderWindow &window) {
    sprite.setTextureRect(rectSourceSprite);
    std::cout << rectSourceSprite.left << " " << rectSourceSprite.top << std::endl;
    window.draw(sprite);
}

void spriteRenderer::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void spriteRenderer::setScale(sf::Vector2f scale) {
    sprite.setScale(scale);
}