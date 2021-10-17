#include "point.hpp"
#include "helper_functions.hpp"
#include <iostream>

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

void Point::pollEvents(sf::Event evnt, sf::Vector2f mouseWorldPos)
{
    if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::LControl)
        this->drag.ctrlPressed = true;
    else if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::LControl)
        this->drag.ctrlPressed = false;
    else if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left && this->drag.ctrlPressed)
    {
        this->drag.mouseClicked = true;

        if (this->body.getGlobalBounds().contains(mouseWorldPos))
        {
            this->drag.dragging = true;
            this->drag.mouseRectOffset.x = evnt.mouseButton.x - this->body.getGlobalBounds().left - this->body.getOrigin().x;
            this->drag.mouseRectOffset.y = evnt.mouseButton.y - this->body.getGlobalBounds().top - this->body.getOrigin().y;
        }
    }
    else if (evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left)
    {
        this->drag.mouseClicked = false;
        this->drag.dragging = false;
        this->drag.moved = false;
    }
    else if (evnt.type == sf::Event::MouseMoved)
    {
        this->drag.mouseX = evnt.mouseMove.x;
        this->drag.mouseY = evnt.mouseMove.y;

        this->drag.moved = true;
    }
}

void Point::update()
{
    if (this->drag.dragging && this->drag.moved)
    {
        this->position = sf::Vector2f(this->drag.mouseX - this->drag.mouseRectOffset.x, this->drag.mouseY - this->drag.mouseRectOffset.y);
        this->body.setPosition(this->position);

        this->changed = true;
    }
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

const bool Point::getChanged() const
{
    return this->changed;
}

void Point::setChanged(bool change)
{
    this->changed = change;
}

void Point::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(this->body);
}