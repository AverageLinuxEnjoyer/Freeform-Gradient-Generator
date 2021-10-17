#include "gui.hpp"
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

/**
 * @brief Construct a new Gui object
 * 
 * @param window where the gui will be displayed
 */
Gui::Gui(sf::RenderWindow &window)
{
    this->window_ptr = std::unique_ptr<sf::RenderWindow>(&window);
    ImGui::SFML::Init(*window_ptr);
}

/**
 * @brief Destroy the Gui object and shuts down ImGui
 * 
 */
Gui::~Gui()
{
    ImGui::SFML::Shutdown();
}

/**
 * @brief Handles any input related to the gui.
 * 
 * @param evnt object containing info about the most recent event
 */
void Gui::pollEvents(sf::Event evnt)
{
    ImGui::SFML::ProcessEvent(evnt);
}

/**
 * @brief Updates the state of the gui each frame.
 * 
 * @param deltaTime needed to make gui features independent to the fps
 */
void Gui::update(sf::Time deltaTime)
{
    ImGui::SFML::Update(*window_ptr, deltaTime);

    this->loadMainInterface();
    ImGui::ShowDemoWindow();
}

/**
 * @brief Draws the gui
 * 
 * @param target where to draw
 * @param states states applied to the draw (unused)
 */
void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    ImGui::SFML::Render(*window_ptr);
}

/**
 * @brief Loads the main interface located on the left of the screen.
 * 
 */
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