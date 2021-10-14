#include "application.hpp"

Application::Application(unsigned int width, unsigned int height, std::string name)
    : window(sf::VideoMode(width, height), name),
      gradient(500, 500),
      view(window.getView()),
      gui(window)
{

}

Application::~Application()
{

}

void Application::run()
{
    sf::Clock deltaClock;

    while (true)
    {
        sf::Time deltaTime = deltaClock.restart();

        this->pollEvents();

        this->update(deltaTime);

        this->draw();
    }
}

void Application::pollEvents()
{
    sf::Event evnt;
    while (this->window.pollEvent(evnt))
    {
        gui.pollEvents(evnt);

        if (evnt.type == sf::Event::Closed)
            this->close();

        handleDragAndZoom(evnt);
    }
}

void Application::update(sf::Time deltaTime)
{
    gui.update(deltaTime);
}

void Application::draw()
{
    this->window.clear();
    this->window.draw(gradient);
    this->window.draw(gui);
    this->window.display();
}

void Application::close()
{
    this->window.close();
}

void Application::handleDragAndZoom(sf::Event evnt)
{
    if (evnt.type == sf::Event::MouseButtonPressed)
    {
        if (evnt.mouseButton.button == sf::Mouse::Button::Left)
        {
            moving = true;
            oldPos = window.mapPixelToCoords(sf::Vector2i(evnt.mouseButton.x, evnt.mouseButton.y));
        }
    }
    else if (evnt.type == sf::Event::MouseButtonReleased)
    {
        if (evnt.mouseButton.button == sf::Mouse::Button::Left)
            moving = false;
    }
    else if (evnt.type == sf::Event::MouseMoved && moving)
    {
        const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(evnt.mouseMove.x, evnt.mouseMove.y));

        const sf::Vector2f deltaPos = oldPos - newPos;

        view.setCenter(view.getCenter() + deltaPos);
        window.setView(view);

        oldPos = window.mapPixelToCoords(sf::Vector2i(evnt.mouseMove.x, evnt.mouseMove.y));
    }
    else if (evnt.type == sf::Event::MouseMoved && moving)
    {
        const sf::Vector2f newPos = window.mapPixelToCoords(sf::Vector2i(evnt.mouseMove.x, evnt.mouseMove.y));
        const sf::Vector2f deltaPos = oldPos - newPos;
        view.setCenter(view.getCenter() + deltaPos);
        window.setView(view);

        oldPos = window.mapPixelToCoords(sf::Vector2i(evnt.mouseMove.x, evnt.mouseMove.y));
    }
    else if (evnt.type == sf::Event::MouseWheelScrolled && !moving)
    {
        if (evnt.mouseWheelScroll.delta <= -1)
            zoom = std::min(2.f, zoom + .1f);
        else if (evnt.mouseWheelScroll.delta >= 1)
            zoom = std::max(.5f, zoom - .1f);

        view.setSize(window.getDefaultView().getSize());
        view.zoom(zoom);
        window.setView(view);
    }
}