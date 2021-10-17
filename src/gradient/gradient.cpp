#include "gradient.hpp"
#include "helper_functions.hpp"
#include "gradient_shader.hpp"
#include <iostream>

/**
 * @brief Construct a new Gradient object.
 * 
 * @param width width of the gradient (can be scaled at export)
 * @param height height of the gradient (can be scaled at export)
 */
Gradient::Gradient(unsigned int width, unsigned int height)
    : body(sf::Vector2f(width, height)),
      size(width, height)
{
    if (!this->texture.create(width, height))
        throw std::runtime_error("Gradient texture couldn't be created.");

    if (!this->shader.loadFromMemory(gradient_shader::source, sf::Shader::Fragment))
        throw std::runtime_error("Gradient shader couldn't be loaded.");

    this->shader.setUniform("gradient_height", static_cast<int>(height));
}      

/**
 * @brief Destroy the Gradient object
 * 
 */
Gradient::~Gradient()
{
    
}

/**
 * @brief Handles any input related to the gradient. (ex: addition of new points) 
 * 
 * @param evnt object containing info about the most recent event
 * @param mouseWorldPos position of the mouse in the view
 */
void Gradient::pollEvents(sf::Event evnt, sf::Vector2f mouseWorldPos)
{

    if (evnt.type == sf::Event::MouseButtonPressed && 
        evnt.mouseButton.button == sf::Mouse::Right &&
        sf::FloatRect(sf::Vector2f(0.0f, 0.0f), this->body.getSize()).contains(mouseWorldPos))
    {
        this->points.push_back(Point(mouseWorldPos, getRandomColor()));

        this->shader.setUniform("used_points", static_cast<int>(this->points.size()));

        int point_index = this->points.size() - 1;
        this->shader.setUniform("points[" + std::to_string(point_index) + "]", mouseWorldPos);
        this->shader.setUniform("colors[" + std::to_string(point_index) + "]", sf::Glsl::Vec4(this->points[point_index].getSfColor()));
    }
    else if (evnt.type == sf::Event::KeyPressed && evnt.key.code == sf::Keyboard::P)
    {
        for (int i = 0; i < points.size(); i++)
        {
            std::cout << "points[" << i << "]:\n";
            std::cout << "\t<0>position:\t(" << points[i].getPosition().x << ", " << points[i].getPosition().y << ")\n";

            sf::Color sfcolor = points[i].getSfColor();
            std::cout << "\t<1>sfcolor:\t(" << (int)sfcolor.r << ", " << (int)sfcolor.g << ", " << (int)sfcolor.b << ", " << (int)sfcolor.a << ")\n";

            ImVec4 imcolor = points[i].getImColor();
            std::cout << "\t<2>imcolor:\t(" << imcolor.x << ", " << imcolor.y << ", " << imcolor.z << ", " << imcolor.w << ")\n\n";
        }
    }

    for (int i = 0; i < this->points.size(); i++)
        this->points[i].pollEvents(evnt, mouseWorldPos);
}

void Gradient::update()
{
    for (int i = 0; i < this->points.size(); i++)
    {
        this->points[i].update();

        if (points[i].getChanged())
        {
            this->shader.setUniform("points[" + std::to_string(i) + "]", this->points[i].getPosition());
            this->shader.setUniform("colors[" + std::to_string(i) + "]", sf::Glsl::Vec4(this->points[i].getSfColor()));
        }
    }
}

/**
 * @brief Draws the gradient and the point handles.
 * 
 * @param window where the draw will happen
 */
void Gradient::draw(sf::RenderWindow& window)
{
    this->texture.clear();
    this->texture.draw(this->body, &shader);
    this->texture.display();

    sf::Sprite sprite(this->texture.getTexture());
    window.draw(sprite);

    for(const auto point : this->points)
        window.draw(point);
}

