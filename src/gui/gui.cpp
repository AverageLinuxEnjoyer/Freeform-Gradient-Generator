#include "gui.hpp"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

Gui::Gui(sf::RenderWindow &window)
{
    this->window_ptr = std::unique_ptr<sf::RenderWindow>(&window);
    ImGui::SFML::Init(*window_ptr);
}

Gui::~Gui()
{
    ImGui::SFML::Shutdown();
}

void Gui::pollEvents(sf::Event evnt)
{
    ImGui::SFML::ProcessEvent(evnt);
}

void Gui::update(sf::Time deltaTime)
{
    ImGui::SFML::Update(*window_ptr, deltaTime);

    ImGui::ShowDemoWindow();
}

void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    ImGui::SFML::Render(*window_ptr);
}