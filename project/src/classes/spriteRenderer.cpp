//
// Created by juhtyg on 19.2.24.
//

#include "../headers/spriteRenderer.h"


spriteRenderer::spriteRenderer(Texture& texture, sf::Vector2f position, sf::Vector2f size) : texture(texture){
    sf::Vector2f scale = divide(size, texture.getSize());
    sprite.setTexture(texture.getTexture());
    //TODO: fix the origin cause for stripes it 1/2 == 0.5, also using texture.getSize() is not good
    sprite.setOrigin(divide(texture.getSize(), 2));
    sprite.setPosition(position);
    sprite.setScale(scale);
    rectSourceSprite = sf::IntRect(0, 0, (int) texture.getSize().x, (int) texture.getSize().y);
    currentFrame = sf::Vector2f(0, 0);
}

spriteRenderer::spriteRenderer(const spriteRenderer& other) : texture(other.texture) {
    sprite.setTexture(texture.getTexture());
    sprite.setOrigin(divide(texture.getSize(), 2));
    sprite.setPosition(other.sprite.getPosition());
    sprite.setScale(other.sprite.getScale());
    rectSourceSprite = other.rectSourceSprite;
    currentFrame = other.currentFrame;
}

void spriteRenderer::nextFrame() {
    if(texture.getMatrix().x > currentFrame.x) {
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
        currentFrame.x = texture.getMatrix().x;
    }
    rectSourceSprite.left = (int)( currentFrame.x * (float) rectSourceSprite.width);
}

void spriteRenderer::nextAnimation() {
    if(texture.getMatrix().y > currentFrame.y) {
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
        currentFrame.y = texture.getMatrix().y;
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

void spriteRenderer::setOrigin(sf::Vector2f origin) {
    sprite.setOrigin(origin);
}

sf::Vector2f spriteRenderer::getTextureSize() {
    return texture.getSize();
}

void spriteRenderer::Render(sf::RenderWindow &window) {
    sprite.setTextureRect(rectSourceSprite);
    window.draw(sprite);
}