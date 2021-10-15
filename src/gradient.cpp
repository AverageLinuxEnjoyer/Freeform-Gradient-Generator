#include "gradient.hpp"
#include <fstream>
#include "gradient_shader.hpp"

Gradient::Gradient(unsigned int width, unsigned int height)
    : body(sf::Vector2f(width, height))
{
    body.setFillColor(sf::Color::Blue);

    if (!this->texture.create(width, height))
        throw std::runtime_error("Gradient texture couldn't be created.");

    if (!this->shader.loadFromMemory(gradient_shader::source, sf::Shader::Fragment))
        throw std::runtime_error("Gradient shader couldn't be loaded.");

}       

Gradient::~Gradient()
{
}

void Gradient::pollEvents(sf::Event evnt)
{

}

void Gradient::update()
{

}

void Gradient::draw(sf::RenderWindow& window)
{
    this->texture.clear();
    this->texture.draw(body, &shader);
    this->texture.display();

    sf::Sprite sprite(this->texture.getTexture());
    window.draw(sprite);
}

