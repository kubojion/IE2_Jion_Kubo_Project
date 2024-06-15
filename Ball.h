#pragma once
#include <SFML/Graphics.hpp>

class Ball : public sf::Drawable
{
public:
    Ball();
    void update(sf::Time dt);
    sf::FloatRect get_bounds() const;
    void bounce_paddle(const sf::FloatRect& paddle_bounds);
    void bounce_wall();
    bool is_out_of_bounds() const;
    void set_velocity(float vx, float vy);
    sf::Vector2f get_velocity() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::CircleShape m_shape;
    // sf::Vector2f
    sf::Vector2f m_velocity;
};
