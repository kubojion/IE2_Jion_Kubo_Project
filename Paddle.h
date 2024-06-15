#pragma once
#include <SFML/Graphics.hpp>

class Paddle : public sf::Drawable
{
public:
    Paddle();
    void input();
    void update(sf::Time dt);
    sf::FloatRect get_bounds() const;

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::RectangleShape m_shape;
    float m_speed;
    float m_dt;
};
