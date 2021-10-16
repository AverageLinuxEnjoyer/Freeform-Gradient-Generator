#include "point.hpp"
#include "helper_functions.hpp"

Point::Point(sf::Vector2f pos, sf::Color col)
    : position(pos),
      sfColor(col),
      imColor(getImVecColor(col)),
      body(sf::Vector2f(20,20))
{
    this->body.setFillColor(sf::Color::White);
    this->body.setOutlineColor(sf::Color::Black);
    this->body.setOutlineThickness(-3);
    this->body.setOrigin(this->body.getSize() / 2.0f);
    this->body.setPosition(pos);
}

void pollEvents(sf::Event evnt)
{

}

void update()
{

}

const sf::Vector2f Point::getPosition() const
{
    return this->position;
}

const sf::Color Point::getSfColor() const
{
    return this->sfColor;
}

const ImVec4 Point::getImColor() const
{
    return this->imColor;
}

void Point::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(this->body);
}