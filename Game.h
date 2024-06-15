#pragma once
#include "Paddle.h"
#include "Ball.h"

#include "Wall.h"

#include <SFML/Graphics.hpp>


class Game
{
public:
    Game();
    void run();
private:
    void manage_events();
    void update(sf::Time dt);
    void render();
    void collision();
    void reset();
    void next_level();
    void start_level();

    sf::RenderWindow m_window;
    Paddle m_paddle;
    Ball m_ball;
    std::vector<Wall> m_walls;
    sf::Texture m_wall_texture;
    sf::Texture m_gameover_texture;
    sf::Text m_score_text;
    sf::Text m_current_level_text;
    sf::Sprite m_gameover_sprite;
    sf::Text m_level_text;
    sf::Font m_font;

    bool m_transition;
    int m_score;
    int m_level;
    bool m_is_gameover;
    double m_ball_speed_increase;
    sf::Clock m_transition_clock;
};
