#pragma once
#include <SFML/Graphics.hpp>

class Wall : public sf::Drawable
{
public:
    Wall(sf::Vector2f position, sf::Vector2f size = sf::Vector2f(160.0f, 30.0f)); // default size 160x30 // ir 20
    void set_texture(const sf::Texture& texture);
    sf::FloatRect get_bounds() const;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::RectangleShape m_shape;

};
