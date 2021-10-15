#include "application.hpp"

Application::Application(unsigned int width, unsigned int height, std::string name)
    : window(sf::VideoMode(width, height), name),
      initialWidth(width),
      initialHeight(height),
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
        this->gui.pollEvents(evnt);

        if (evnt.type == sf::Event::Closed)
            this->close();

        handleDragAndZoom(evnt);
    }
}

void Application::update(sf::Time deltaTime)
{
    gui.update(deltaTime);


    // float width_ratio = this->initialWidth / this->window.getSize().x;
    // float height_ratio = this->initialHeight / this->window.getSize().y;

    // sf::View new_view = this->window.getView();
    // new_view.setViewport(sf::FloatRect(0, 0, 1 / width_ratio, 1 / height_ratio));
    // this->window.setView(new_view);

    // Some ugly errors 
}

void Application::draw()
{
    this->window.clear();
    this->gradient.draw(this->window);
    this->window.draw(gui);
    this->window.display();
}

void Application::close()
{
    this->window.close();
}

void Application::handleDragAndZoom(sf::Event evnt)
{   
    if (evnt.type == sf::Event::MouseButtonPressed && sf::Mouse::getPosition(this->window).x > 400)
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