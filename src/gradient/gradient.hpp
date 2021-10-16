#ifndef GRADIENT_HPP
#define GRADIENT_HPP
#include <SFML/Graphics.hpp>
#include <vector>
#include "point.hpp"
#endif

class Gradient
{
public:
    Gradient(unsigned int width, unsigned int height);
    ~Gradient();

    void pollEvents(sf::Event evnt, sf::Vector2f mouseWorldPos);
    void update();
    //void exportPNG();

    void draw(sf::RenderWindow &window);

private:


private:
    sf::RectangleShape body;
    const sf::Vector2u size;

    sf::Shader shader;

    sf::RenderTexture texture;

    std::vector<Point> points;
};