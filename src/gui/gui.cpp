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

    this->loadMainInterface();
    ImGui::ShowDemoWindow();
}

void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    ImGui::SFML::Render(*window_ptr);
}

void Gui::loadMainInterface()
{   
    ImGui::SetNextWindowSize(ImVec2(400,720));
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::Begin("Main window", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    if(ImGui::BeginTabBar("TabBar", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem("Configuration"))
        {
            ImGui::Text("This is the configuration tab.");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Points"))
        {
            ImGui::Text("This is the points tab.");
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Export"))
        {
            ImGui::Text("This is the export tab.");
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::End();
}