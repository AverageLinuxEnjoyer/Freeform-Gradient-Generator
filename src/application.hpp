#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "gradient/gradient.hpp"
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

    struct {
        const std::string initialName;
        const sf::Vector2u initialSize;
    } info;

    Gradient gradient;
    Gui gui;

    struct 
    {
        sf::Vector2f oldPos;
        bool moving = false;
        float zoom = 1.0;
        sf::View view;
        bool ctrlPressed = false;
    } dragAndZoom;
    
};