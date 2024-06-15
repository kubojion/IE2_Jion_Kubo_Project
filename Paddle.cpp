#include "Paddle.h"

Paddle::Paddle()
    : m_shape(sf::Vector2f(100.0f, 20.0f)), m_speed(330.0f)
{
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition(350.0f, 550.0f);
}
void Paddle::input()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_shape.move(-m_speed * m_dt, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_shape.move(m_speed * m_dt, 0);
    }
}

void Paddle::update(sf::Time dt)
{
    m_dt = dt.asSeconds();
    if (m_shape.getPosition().x < 0)
    {
        m_shape.setPosition(0, m_shape.getPosition().y);
    }
    else if (m_shape.getPosition().x + m_shape.getSize().x > 800)
    {
        m_shape.setPosition(800 - m_shape.getSize().x, m_shape.getPosition().y);
    }
}

sf::FloatRect Paddle::get_bounds()const
{
    return m_shape.getGlobalBounds();
}
void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states);
}
