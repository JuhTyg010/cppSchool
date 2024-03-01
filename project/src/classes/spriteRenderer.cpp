//
// Created by juhtyg on 19.2.24.
//

#include "../headers/spriteRenderer.h"


spriteRenderer::spriteRenderer(sf::Texture& texture, sf::Vector2f position, sf::Vector2f scale,
                               sf::Vector2f size, sf::Vector2f matrix) : matrix(matrix){
    //texture.loadFromFile(path);

    sprite.setTexture(texture);
    sprite.setOrigin(size.x / 2, size.y / 2);
    sprite.setPosition(position);
    sprite.setScale(scale);
    rectSourceSprite = sf::IntRect(0, 0, (int) size.x, (int) size.y);
    currentFrame = sf::Vector2f(0, 0);
}


void spriteRenderer::nextFrame() {
    if(matrix.x > currentFrame.x) {
        currentFrame.x += 1;
    } else {
        currentFrame.x = 0;
    }
    rectSourceSprite.left = (int)( currentFrame.x * (float) rectSourceSprite.width);
}

void spriteRenderer::prevFrame() {
    if(currentFrame.x > 0) {
        currentFrame.x--;
    } else {
        currentFrame.x = matrix.x;
    }
    rectSourceSprite.left = (int)( currentFrame.x * (float) rectSourceSprite.width);
}

void spriteRenderer::nextAnimation() {
    if(matrix.y > currentFrame.y) {
        currentFrame.y++;
    } else {
        currentFrame.y = 0;
    }
    rectSourceSprite.top = (int)( currentFrame.y * (float) rectSourceSprite.height);
}

void spriteRenderer::prevAnimation() {
    if(currentFrame.y > 0) {
        currentFrame.y--;
    } else {
        currentFrame.y = matrix.y;
    }
    rectSourceSprite.top = (int)( currentFrame.y * (float) rectSourceSprite.height);
}

sf::Vector2f spriteRenderer::getCurrentFrame() {
    return currentFrame;
}

void spriteRenderer::setTextureRect(sf::IntRect rect) {
    rectSourceSprite = rect;
}

void spriteRenderer::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}

void spriteRenderer::setScale(sf::Vector2f scale_) {
    sprite.setScale(scale_);
}

void spriteRenderer::Render(sf::RenderWindow &window) {
    sprite.setTextureRect(rectSourceSprite);
    window.draw(sprite);
}