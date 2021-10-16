#ifndef HERLPER_FUNCTIONS_HPP
#define HERLPER_FUNCTIONS_HPP
#include <random>
#include <SFML/Graphics.hpp>
#include <imgui-SFML.h>
#include <imgui.h>
#endif

static sf::Color getRandomColor()
{
    static std::random_device dev;
    static std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> colorRange(0,255);

    return sf::Color(colorRange(rng), colorRange(rng), colorRange(rng));

}

static ImVec4 getImVecColor(sf::Color color)
{
    return ImVec4(color.r / 255.0, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f);
}

static sf::Vector2f getNormalisedPosition(sf::Vector2f pos)
{
    return sf::Vector2f(pos.x/255.0, pos.y/255.0);
}