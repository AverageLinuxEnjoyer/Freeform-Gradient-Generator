#ifndef GRADIENT_HPP
#define GRADIENT_HPP
#include <SFML/Graphics.hpp>
#endif

class Gradient
{
public:
    Gradient(unsigned int width, unsigned int height);
    ~Gradient();

    void pollEvents(sf::Event evnt);
    void update();

    void draw(sf::RenderWindow &window);

private:


private:
    sf::RectangleShape body;

    sf::Shader shader;

    sf::RenderTexture texture;
};