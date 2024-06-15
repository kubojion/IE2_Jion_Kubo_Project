#include "Game.h"
#include <iostream> //for cerr and

Game::Game()
    : m_window(sf::VideoMode(800, 600), "Break the Wall"),
    m_paddle(),
    m_ball(),
    m_score(0),
    m_level(1),
    m_is_gameover(0),
    m_transition(0),
    m_ball_speed_increase(50.0f)
{
    if (!m_wall_texture.loadFromFile("C://Users//kuboj//Documents//GitHub//Information_Engineering_2//IE2_Jion_Kubo_Project_Bouncing_Ball//wall.png"))
    {
        std::cerr << "texture failed to load" << std::endl;
        // throw std::runtime_error("failed to load texture");
    }
    if(!m_gameover_texture.loadFromFile("C://Users//kuboj//Documents//GitHub//Information_Engineering_2//IE2_Jion_Kubo_Project_Bouncing_Ball//gameover.png"))
    {
        std::cerr << "texture failed to load" << std::endl;
    }
    m_gameover_sprite.setTexture(m_gameover_texture);

    // sf::Font m_font;
    //better to change font
    if (!m_font.loadFromFile("C://Users//kuboj//Documents//GitHub//Information_Engineering_2//IE2_Jion_Kubo_Project_Bouncing_Ball//GILSANUB.ttf"))
    {
        std::cerr << "texture failed to load" << std::endl;
    }

    m_level_text.setFont(m_font);
    m_level_text.setCharacterSize(24);
    m_level_text.setFillColor(sf::Color::White);
    m_level_text.setPosition(350, 300);

    m_score_text.setFont(m_font);
    m_score_text.setCharacterSize(24);
    m_score_text.setFillColor(sf::Color::White);
    m_score_text.setPosition(10, 10);

    m_current_level_text.setFont(m_font);
    m_current_level_text.setCharacterSize(24);
    m_current_level_text.setFillColor(sf::Color::White);
    m_current_level_text.setPosition(670, 10);

    start_level();
}
void Game::run()
{
    sf::Clock clock;
    while(m_window.isOpen())
    {
        sf::Time dt = clock.restart();
        manage_events();
        if (!m_is_gameover && !m_transition)
        {
            update(dt);
        }
        render();
        if (m_transition && m_transition_clock.getElapsedTime().asSeconds() > 2)
        {
            m_transition = false;
            m_level_text.setString("");
        }
    }
}

void Game::manage_events()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }

        if (m_is_gameover && event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::R)
            {
                reset();
            }
            else if (event.key.code == sf::Keyboard::F)
            {
                m_window.close();
            }
        }
    }
    if (!m_is_gameover && !m_transition)
    {
        m_paddle.input();
    }


}

void Game::update(sf::Time dt)
{
    m_paddle.update(dt);
    m_ball.update(dt);
    collision();

    if(m_walls.empty() && !m_transition)
    {
        m_score += 50; //50 for compleatng a level
        next_level();
    }
    m_score_text.setString("Score: " + std::to_string(m_score));
    m_current_level_text.setString("Level: " + std::to_string(m_level));
}

void Game::render()
{
    m_window.clear();
    if (m_is_gameover)
    {
        m_window.draw(m_gameover_sprite);
        sf::Text final_score_text("Score: " + std::to_string(m_score), m_font, 24);
        final_score_text.setFillColor(sf::Color::White);
        final_score_text.setPosition(345, 420); // not centered if there are 3 digits
        m_window.draw(final_score_text);
    }
    else
    {
        if(m_transition)
        {
            m_window.draw(m_level_text);
        }
        else
        {
            m_window.draw(m_paddle);
            m_window.draw(m_ball);
            for (const auto& wall : m_walls)
            {
                m_window.draw(wall);
            }
            m_window.draw(m_score_text);
            m_window.draw(m_current_level_text);
        }
    }
    m_window.display();
}

void Game::collision()
{
    if (m_ball.get_bounds().intersects(m_paddle.get_bounds()))
    {
        m_ball.bounce_paddle(m_paddle.get_bounds());
    }

    bool ball_bounced = false;
    for (auto it = m_walls.begin(); it != m_walls.end(); )
    {
        if(m_ball.get_bounds().intersects(it->get_bounds()))
        {
            m_ball.bounce_wall();
            it = m_walls.erase(it);
            m_score += 10; //10p for breaking a wall
            ball_bounced = true;
            break;
        }
        else { it++; }
    }
    if (!ball_bounced && m_ball.get_bounds().top < 0)
    { m_is_gameover = true;
    }
    else if (m_ball.is_out_of_bounds() || m_ball.get_bounds().top + m_ball.get_bounds().height > 600)
    {
        m_is_gameover = true;
    }


}
void Game::reset()
{
    m_is_gameover = false;
    m_score = 0;
    m_level = 1; //goes back to lvl 1
    m_ball = Ball();
    m_paddle = Paddle();
    m_ball_speed_increase = 50.0f;
    m_walls.clear();
    start_level();
}

void Game::next_level()
{
    m_transition = true;
    m_transition_clock.restart();
    m_level++; //increase the level
    m_level_text.setString("Level " + std::to_string(m_level));
    m_level_text.setFillColor(sf::Color::White);
    m_ball.set_velocity(m_ball.get_velocity().x, 200.0f + (m_level - 1) * m_ball_speed_increase); //increase the speed with lvl up
    m_walls.clear();
    float block_width = 160.0f; // Set the width to 2x the original size
    float block_height = 30.0f; //height of a wall
    for (int i = 0; i < 5; i++) // for width of 160 use 5 for width of 80 use 10
    {
        Wall wall(sf::Vector2f(i * block_width, 50.0f), sf::Vector2f(block_width, block_height));
        wall.set_texture(m_wall_texture);
        m_walls.push_back(wall);
    }
}

void Game::start_level()
{
    m_transition = true;
    m_transition_clock.restart();
    m_level_text.setString("Level " + std::to_string(m_level));
    m_level_text.setFillColor(sf::Color::White);
    m_walls.clear();
    float block_width = 160.0f;
    float block_height = 30.0f;
    for(int i = 0; i < 5; i++)
    {
        Wall wall(sf::Vector2f(i * block_width, 50.0f), sf::Vector2f(block_width, block_height));
        wall.set_texture(m_wall_texture);
        m_walls.push_back(wall);
    }
}
