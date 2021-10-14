#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "gradient.hpp"
#include "gui/gui.hpp"
#endif

class Application {

public:
    Application(unsigned int width, unsigned int height, std::string name);
    ~Application();

    void run();

private:
    void pollEvents();
    void handleDragAndZoom(sf::Event evnt);

    void update(sf::Time deltaTime);
    void draw();

    void close();

private:
    sf::RenderWindow window;
    Gradient gradient;
    Gui gui;

    sf::Vector2f oldPos;
    bool moving = false;
    float zoom = 1;
    sf::View view;
};