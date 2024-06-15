#include "Ball.h"

Ball::Ball()
    : m_shape(10.0f), m_velocity(0.0f, 200.0f) //it should start going down
{
    m_shape.setFillColor(sf::Color::Red);
    m_shape.setPosition(400.0f, 300.0f);
}
void Ball::update(sf::Time dt)
{
    m_shape.move(m_velocity*dt.asSeconds());

    if(m_shape.getPosition().x<0 || m_shape.getPosition().x+m_shape.getRadius()*2>800)
    {
        m_velocity.x = -m_velocity.x;
    }
    // if (m_shape.getPosition().y < 0)
    // {
    //     m_velocity.y = -m_velocity.y;
    // }
}

sf::FloatRect Ball::get_bounds() const{
    return m_shape.getGlobalBounds();
}

void Ball::bounce_paddle(const sf::FloatRect& paddle_bounds)
{
    m_velocity.y = -m_velocity.y;
    // adjust velocity based on where it contact the paddle
    float paddle_center = (paddle_bounds.left + paddle_bounds.width/2);
    float ball_center = m_shape.getPosition().x + m_shape.getRadius();
    m_velocity.x=200.0f*(ball_center-paddle_center)/(paddle_bounds.width/2);
}
void Ball::bounce_wall()
{
    m_velocity.y = -m_velocity.y;
}

bool Ball::is_out_of_bounds() const
{
    return m_shape.getPosition().y> 600;
}

void Ball::set_velocity(float vx, float vy)
{
    m_velocity.x = vx;
    m_velocity.y = vy;
}
sf::Vector2f Ball::get_velocity() const
{
    return m_velocity;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const //override
{
    target.draw(m_shape, states);
}
