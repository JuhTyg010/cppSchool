//
// Created by juhtyg on 19.2.24.
//

#include "../headers/spriteRenderer.h"


spriteRenderer::spriteRenderer(Texture& texture, sf::Vector2f position, Vector2d size)
    : texture(texture), actualSize(size){
    sprite.setTexture(texture.getTexture());
    sf::Vector2u textureSize = texture.getSize();
    sprite.setOrigin((float) textureSize.x / 2, (float)textureSize.y / 2);
    sprite.setPosition(position);
    sf::Vector2f scale(size.x / textureSize.x, size.y / (float) textureSize.y);
    sprite.setScale(scale);
    rectSourceSprite = sf::IntRect(0, 0,(int) textureSize.x, (int) textureSize.y);
    currentFrame = sf::Vector2u(0, 0);
}


void spriteRenderer::nextFrame() {
    if(texture.getMatrix().x > currentFrame.x) {
        currentFrame.x += 1;
    } else {
        currentFrame.x = 0;
    }
    rectSourceSprite.left = (int)(currentFrame.x * rectSourceSprite.width);
}

void spriteRenderer::prevFrame() {
    if(currentFrame.x > 0) {
        currentFrame.x--;
    } else {
        currentFrame.x = texture.getMatrix().x;
    }
    rectSourceSprite.left = (int)(currentFrame.x * rectSourceSprite.width);
}

void spriteRenderer::nextAnimation() {
    if(texture.getMatrix().y > currentFrame.y) {
        currentFrame.y++;
    } else {
        currentFrame.y = 0;
    }
    rectSourceSprite.top = (int)(currentFrame.y * rectSourceSprite.height);
}

void spriteRenderer::prevAnimation() {
    if(currentFrame.y > 0) {
        currentFrame.y--;
    } else {
        currentFrame.y = texture.getMatrix().y;
    }
    rectSourceSprite.top = (int)(currentFrame.y * rectSourceSprite.height);
}

sf::Vector2u spriteRenderer::getCurrentFrame() {
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

void spriteRenderer::Render(sf::RenderWindow &window, sf::Vector2f position) {
    sprite.setPosition(position);
    sprite.setTextureRect(rectSourceSprite);
    window.draw(sprite);
}

void spriteRenderer::Render(sf::RenderWindow &window) {
    sprite.setTextureRect(rectSourceSprite);
    window.draw(sprite);
}