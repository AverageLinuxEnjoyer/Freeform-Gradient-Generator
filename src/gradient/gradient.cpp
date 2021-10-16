#include "gradient.hpp"
#include "helper_functions.hpp"
#include "gradient_shader.hpp"
#include <iostream>

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

Gradient::~Gradient()
{
    
}

void Gradient::pollEvents(sf::Event evnt, sf::Vector2f mouseWorldPos)
{
    if (evnt.type == sf::Event::MouseButtonPressed && 
        evnt.mouseButton.button == sf::Mouse::Right &&
        sf::FloatRect(sf::Vector2f(0.0f, 0.0f), body.getSize()).contains(mouseWorldPos))
    {
        sf::Color randomColor = getRandomColor();
        points.push_back(Point(mouseWorldPos, randomColor));

        shader.setUniform("used_points", static_cast<int>(points.size()));

        int point_index = points.size() - 1;
        shader.setUniform("points[" + std::to_string(point_index) + "]", mouseWorldPos);
        shader.setUniform("colors[" + std::to_string(point_index) + "]", sf::Glsl::Vec4(points[point_index].getSfColor()));
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
}

void Gradient::update()
{
}

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

