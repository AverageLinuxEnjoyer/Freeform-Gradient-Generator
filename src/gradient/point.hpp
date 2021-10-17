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

    void pollEvents(sf::Event evnt, sf::Vector2f mouseWorldPos);
    void update();

    const sf::Vector2f getPosition() const;
    const sf::Color getSfColor() const;
    const ImVec4 getImColor() const;

    const bool getChanged() const;
    void setChanged(bool change);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Vector2f position;
    sf::Color sfColor;
    ImVec4 imColor;

    sf::RectangleShape body;

    struct {
        bool mouseClicked = false;
        bool mouseInsideRect = false;
        bool dragging = false;
        bool ctrlPressed = false;
        bool moved = false;

        int mouseX = 0;
        int mouseY = 0;
        
        sf::Vector2f mouseRectOffset;
    } drag;

    bool changed = false;
};