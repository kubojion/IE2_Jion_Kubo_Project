#include "Wall.h"

Wall::Wall(sf::Vector2f position, sf::Vector2f size)
{
    m_shape.setSize(size);
    m_shape.setPosition(position);
}
void Wall::set_texture(const sf::Texture& texture)
{
    m_shape.setTexture(&texture);
}

sf::FloatRect Wall::get_bounds() const
{
    return m_shape.getGlobalBounds();
}

void Wall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape,states);
}
