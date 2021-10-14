#include "gradient.hpp"

Gradient::Gradient(unsigned int width, unsigned int height)
    : body(sf::Vector2f(width, height))
{
    body.setFillColor(sf::Color::Blue);
}

Gradient::~Gradient()
{
}

void Gradient::pollEvents(sf::Event evnt)
{

}

void Gradient::update()
{

}

void Gradient::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(body);
}

