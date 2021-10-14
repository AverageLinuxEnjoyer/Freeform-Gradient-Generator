#ifndef GRADIENT_HPP
#define GRADIENT_HPP
#include <SFML/Graphics.hpp>
#endif

class Gradient : public sf::Drawable
{
public:
    Gradient(unsigned int width, unsigned int height);
    ~Gradient();

    void pollEvents(sf::Event evnt);
    void update();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::RectangleShape body;

};