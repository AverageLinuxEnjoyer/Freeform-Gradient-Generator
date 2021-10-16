#ifndef APPLICATION_HPP
#define APPLICATION_HPP
#include "gradient/gradient.hpp"
#include "gui/gui.hpp"
#endif


class Application {

public:
    static Application& getInstance(unsigned int width = 0, unsigned int height = 0, std::string name = 0);

    void run();

private:
    Application(unsigned int width, unsigned int height, std::string name);
    ~Application();

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
    } details;

    Gradient gradient;
    Gui gui;

    struct 
    {
        sf::Vector2f oldPos;
        bool moving = false;
        float zoom = 1.0;
        sf::View view;
    } dragAndZoom;
    
};