#include "application.hpp"
#include <iostream>


/**
 * @brief Construct a new Application object that encompasses the entire program.
 * 
 * @param width width of the window
 * @param height height of the window
 * @param name name of the window
 */ 
Application::Application(unsigned int width, unsigned int height, std::string name)
    : window(sf::VideoMode(width, height), name),
      info({std::string(name), sf::Vector2u(width, height)}),
      gradient(1000, 1000),
      gui(window),
      dragAndZoom({sf::Vector2f(), false, 1, window.getView()})
{

}

/**
 * @brief Destroy the Application object. 
 * 
 */
Application::~Application()
{

}

/**
 * @brief Runs the main loop.
 * 
 */
void Application::run()
{
    sf::Clock deltaClock;

    while (this->window.isOpen())
    {
        sf::Time deltaTime = deltaClock.restart();

        this->pollEvents();

        this->update(deltaTime);

        this->draw();
    }
}

/**
 * @brief Handles the events (such as clicks, key presses, window closing). 
 * 
 */
void Application::pollEvents()
{
    sf::Event evnt;
    while (this->window.pollEvent(evnt))
    {
        this->gui.pollEvents(evnt);

        sf::Vector2i mousePixelPos = sf::Mouse::getPosition(this->window);
        sf::Vector2f mouseWorldPos = this->window.mapPixelToCoords(mousePixelPos);

        this->gradient.pollEvents(evnt, mouseWorldPos);

        if (evnt.type == sf::Event::Closed)
            this->close();

        handleDragAndZoom(evnt);
    }
}

/**
 * @brief Updates the state of the program. 
 * 
 * @param deltaTime needed for time based updates, only used by ImGui as of now.
 */
void Application::update(sf::Time deltaTime)
{
    gui.update(deltaTime);
    gradient.update();
}

/**
 * @brief Makes all the draw calls to display everything on the screen.
 * 
 */
void Application::draw()
{
    this->window.clear(sf::Color(25,25,30));
    this->gradient.draw(this->window);
    this->window.draw(gui);
    this->window.display();
}

/**
 * @brief Called when the program should be closed.
 * Currently only closes the window. It's extracted in a function so new features can easily be added before the program closes.
 * 
 */
void Application::close()
{
    this->window.close();
}

/**
 * @brief Handles the pan and zoom with mouse.
 * Has helping variables stored in the Application::dragAndZoom object. 
 * 
 * @param evnt object containing information about the most recent event
 */
void Application::handleDragAndZoom(sf::Event evnt)
{   
    if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::LControl)
        this->dragAndZoom.ctrlPressed = true;
    else if (evnt.type == sf::Event::KeyReleased && evnt.key.code == sf::Keyboard::LControl)
        this->dragAndZoom.ctrlPressed = false;
    else if (evnt.type == sf::Event::MouseButtonPressed && sf::Mouse::getPosition(this->window).x > 400 && !this->dragAndZoom.ctrlPressed)
    {
        if (evnt.mouseButton.button == sf::Mouse::Button::Left)
        {
            dragAndZoom.moving = true;
            dragAndZoom.oldPos = this->window.mapPixelToCoords(sf::Vector2i(evnt.mouseButton.x, evnt.mouseButton.y));
        }
    }
    else if (evnt.type == sf::Event::MouseButtonReleased)
    {
        if (evnt.mouseButton.button == sf::Mouse::Button::Left)
            dragAndZoom.moving = false;
    }
    else if (evnt.type == sf::Event::MouseMoved && dragAndZoom.moving)
    {
        const sf::Vector2f newPos = this->window.mapPixelToCoords(sf::Vector2i(evnt.mouseMove.x, evnt.mouseMove.y));

        const sf::Vector2f deltaPos = dragAndZoom.oldPos - newPos;

        dragAndZoom.view.setCenter(dragAndZoom.view.getCenter() + deltaPos);
        this->window.setView(dragAndZoom.view);

        dragAndZoom.oldPos = this->window.mapPixelToCoords(sf::Vector2i(evnt.mouseMove.x, evnt.mouseMove.y));
    }
    else if (evnt.type == sf::Event::MouseMoved && dragAndZoom.moving)
    {
        const sf::Vector2f newPos = this->window.mapPixelToCoords(sf::Vector2i(evnt.mouseMove.x, evnt.mouseMove.y));
        const sf::Vector2f deltaPos = dragAndZoom.oldPos - newPos;
        dragAndZoom.view.setCenter(dragAndZoom.view.getCenter() + deltaPos);
        window.setView(dragAndZoom.view);

        dragAndZoom.oldPos = this->window.mapPixelToCoords(sf::Vector2i(evnt.mouseMove.x, evnt.mouseMove.y));
    }
    else if (evnt.type == sf::Event::MouseWheelScrolled && !dragAndZoom.moving)
    {
        if (evnt.mouseWheelScroll.delta <= -1)
            dragAndZoom.zoom = std::min(2.f, dragAndZoom.zoom + .1f);
        else if (evnt.mouseWheelScroll.delta >= 1)
            dragAndZoom.zoom = std::max(.5f, dragAndZoom.zoom - .1f);

        dragAndZoom.view.setSize(window.getDefaultView().getSize());
        dragAndZoom.view.zoom(dragAndZoom.zoom);
        this->window.setView(dragAndZoom.view);
    }
}