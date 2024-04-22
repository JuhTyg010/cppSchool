//
// Created by juhtyg on 18.2.24.
//

#ifndef INC_3D_GAME_UTILS_H
#define INC_3D_GAME_UTILS_H
#include  <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm> 
#include <iostream> 
#include <filesystem> 


/**
 * @brief Get the Distance between two vectors
 * 
 * @param vec1 
 * @param vec2 
 * @return double 
 */
double getDistance(sf::Vector2f vec1, sf::Vector2f vec2);

/**
 * @brief divide two vectors or a vector and a number
 * 
 * @tparam T 
 * @param a 
 * @param b 
 * @return T 
 */
template <typename T>
concept vec2dim = requires(T t) {
    { t.x };
    { t.y };
};

template <typename T> requires vec2dim<T>
T divide(T a, T b){
    return {a.x / b.x, a.y / b.y};
}
template <typename T, typename C> requires vec2dim<T>
T divide(T a, C b){
    return {a.x / b, a.y / b};
}


class MyMath {
public:
    static double DegToRad(double deg);
    static double RadToDeg(double rad);
};

/**
 * @brief Struct to store a 2d vector of type double (because of sfml not having one)
 * 
 */
struct Vector2d{
public:
    double x;
    double y;
    Vector2d() = default;
    Vector2d(double x, double y): x(x), y(y) {}
    Vector2d operator+(Vector2d vec) const{
        return {x + vec.x, y + vec.y};
    }
    Vector2d operator-(Vector2d vec) const{
        return {x - vec.x, y - vec.y};
    }
    Vector2d operator*(double scalar) const{
        return {x * scalar, y * scalar};
    }
    Vector2d operator/(double scalar) const{
        return {x / scalar, y / scalar};
    }
};

/**
 * @brief Struct to store a texture information
 * 
 */
struct Texture{
private:
    std::string name;
    std::unique_ptr<sf::Texture> texture;
    sf::Vector2f size;
    sf::Vector2f matrix;
public:
    /**
     * @brief Construct a new Texture object
     * 
     * @param name 
     * @param path 
     * @param size 
     * @param matrix 
     */
    Texture(std::string name,const std::string& path, sf::Vector2f size, sf::Vector2f matrix);

    /**
     * @brief Copy construct a new Texture object
     * 
     * @param other 
     */
    Texture(const Texture& other);

    /**
     * @brief Get the Texture object
     * 
     * @return const sf::Texture& 
     */
    const sf::Texture & getTexture();

    /**
     * @brief Get the Size object
     * 
     * @return const sf::Vector2f& 
     */
    const sf::Vector2f& getSize();

    /**
     * @brief Get the Matrix object
     * 
     * @return const sf::Vector2f& 
     */
    const sf::Vector2f& getMatrix();

    /**
     * @brief Get the Name object
     * 
     * @return const std::string& 
     */
    const std::string& getName();
};


/**
 * @brief Get the Texture By Name by iterating through the textures
 *  
 * @param name 
 * @param textures 
 * @return const Texture& 
 */
const Texture& getTextureByName(const std::string& name, std::vector<Texture>& textures);

#endif //INC_3D_GAME_UTILS_H
