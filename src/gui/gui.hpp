#ifndef GUI_HPP
#define GUI_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#endif

class Gui : public sf::Drawable
{
public:
    Gui(sf::RenderWindow &window);
    ~Gui();

    void pollEvents(sf::Event evnt);
    void update(sf::Time deltaTime);

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    std::unique_ptr<sf::RenderWindow> window_ptr;
};
