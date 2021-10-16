#ifndef POINT_HPP
#define POINT_HPP
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#endif

class Point : public sf::Drawable
{
public:
    Point(sf::Vector2f pos = sf::Vector2f(), sf::Color col = sf::Color());

    void pollEvents(sf::Event evnt);
    void update();

    const sf::Vector2f getPosition() const;
    const sf::Color getSfColor() const;
    const ImVec4 getImColor() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Vector2f position;
    sf::Color sfColor;
    ImVec4 imColor;

    sf::RectangleShape body;
};