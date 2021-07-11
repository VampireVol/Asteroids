#include "Engine.h"
#include "Draw.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Score.h"
#include "Logo.h"
#include <stdlib.h>
#include <memory.h>
#include <time.h>

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

static Player* player;
static Logo *logo;
static Score score;
static vector<Bullet> bullets;
static vector<Asteroid> asteroids;
static bool pause = false;
static bool start = false;
static bool logo_shade = false;
static float pause_timer = -1.0f;
static float next_level_timer = -1.0f;
static float difficult = 1.0f;

float rand(float min, float max)
{
  float answer = static_cast<float>(rand()) / RAND_MAX;
  return min + answer * (max - min);
}

void generate_level()
{
  vector<int> asteroids_colors{ 0xffffff, 0x0000ff, 0x00d9e0,
      0x00ff00, 0x009900, 0x999999, 0x8b00ff, 0x964b00,
      0xac00e0, 0x00ffbf, 0xffb700, 0xc3ff00, 0xc2c2c2 };
  int asteroids_count = static_cast<int>(10 * difficult);
  for (int i = 0; i < asteroids_count; ++i)
  {
    float random = rand(0.0f, 1.0f);
    float x = 0, y = 0;
    if (random >= 0.0f && random < 0.25f)
    {
      x = rand(0, SCREEN_WIDTH);
      y = rand(0, SCREEN_HEIGHT * 0.15f);
    }
    else if (random >= 0.25f && random < 0.5f)
    {
      x = rand(SCREEN_WIDTH * 0.85f, SCREEN_WIDTH);
      y = rand(0, SCREEN_HEIGHT);
    }
    else if (random >= 0.5f && random < 0.75f)
    {
      x = rand(0, SCREEN_WIDTH);
      y = rand(SCREEN_HEIGHT * 0.85f, SCREEN_HEIGHT);
    }
    else if (random >= 0.75f && random <= 1.0f)
    {
      x = rand(0, SCREEN_WIDTH * 0.15f);
      y = rand(0, SCREEN_HEIGHT);
    }
    asteroids.push_back(Asteroid(
      { x, y },
      rand(0, 2 * pi()),
      rand(50, 100) * difficult,
      rand(-1.5f, 1.5f),
      rand() % 3 + 1,
      asteroids_colors[rand() % asteroids_colors.size()]
    ));
  }
}

void generate_next_level()
{
  bullets.clear();
  difficult += 0.2f;
  generate_level();
}

void reset()
{
  player->reset();
  score.reset();
  asteroids.clear();
  bullets.clear();
  difficult = 1.0f;
  generate_level();
}

// initialize game data in this function
void initialize()
{
  srand(time(0));
  player = new Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
  logo = new Logo({ SCREEN_WIDTH / 2 - 480, SCREEN_HEIGHT / 2 - 80 });
  generate_level();
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
  if (!start)
  {
    for (int i = 0; i < 256; ++i)
    {
      if (is_key_pressed(i))
      {
        start = true;
        logo_shade = true;
      }
    }
  }
  else if (logo_shade)
    logo->update(dt);
  if (logo_shade && logo->is_shaded())
  {
    logo_shade = false;
    reset();
  }

  if (is_key_pressed('P') && pause_timer < 0)
  {
    pause = !pause;
    pause_timer = 0.5f;
  }
  if (pause_timer > 0)
    pause_timer -= dt;
  if (pause)
    return;

  if (next_level_timer > 0)
  {
    next_level_timer -= dt;
    if (next_level_timer <= 0)
      generate_next_level();
  }
  if (asteroids.empty() && next_level_timer < 0)
    next_level_timer = 5.0f;

  if (player->is_thrust())
    player->set_thrust(false);

  if (is_key_pressed(VK_RETURN))
    reset();
  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game();
  if (player->is_alive())
  {
    if (is_key_pressed(VK_LEFT) || is_key_pressed('A'))
      player->turn_left(dt);
    if (is_key_pressed(VK_RIGHT) || is_key_pressed('D'))
      player->turn_right(dt);
    if (is_key_pressed(VK_UP) || is_key_pressed('W'))
      player->thrust(dt);
    if (is_key_pressed(VK_SPACE) && player->is_reloaded())
    {
      player->reload();
      bullets.push_back(Bullet(player->get_shoot_pos(), player->get_angle(), 450.0f));
    }
  }

  player->update(dt);
  for (auto& bullet : bullets)
  {
    bullet.update(dt);
  }
  for (auto& asteroid : asteroids)
  {
    asteroid.update(dt);
  }

  for (int i = 0; i < bullets.size(); ++i)
  {
    for (int j = 0; i < bullets.size() && j < asteroids.size(); ++j)
    {
      if (asteroids[j].is_collided({ bullets[i].get_position() }))
      {
        asteroids[j].get_damage();
        if (asteroids[j].is_destroyed())
        {
          float angle = asteroids[j].get_angle();
          int size = asteroids[j].get_size();
          int color = asteroids[j].get_color();
          if (size > 1)
          {
            asteroids.push_back(Asteroid(asteroids[j].get_position(),
              rand(angle + pi() * 0.25f, angle + pi() * 0.75f), 
              rand(50, 100) * difficult,
              rand(-1.5f, 1.5f), size - 1, color));
            asteroids.push_back(Asteroid(asteroids[j].get_position(),
              rand(angle - pi() * 0.25f, angle - pi() * 0.75f), 
              rand(50, 100) * difficult,
              rand(-1.5f, 1.5f), size - 1, color));
          }
          int old = score.get_score() / 10000;
          score.add_score(100 * size);
          int last = score.get_score() / 10000;
          if (old != last) player->add_life();
          asteroids.erase(asteroids.begin() + j);
        }
        bullets.erase(bullets.begin() + i--);
        break;
      }
    }
  }
  for (int i = 0; i < asteroids.size() && !player->is_invulnerability() && player->is_alive(); ++i)
  {
    if (asteroids[i].is_collided(player->get_global_points()))
    {
      player->destroyed();
    }
  }

  for (auto it = bullets.begin(); it != bullets.end();)
  {
    if ((*it).is_lifetime_over())
      it = bullets.erase(it);
    else
      ++it;
  }
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
  // clear backbuffer
  memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
  if ((!start || logo_shade) && logo->is_half_color())
    logo->draw();
  
  //Objects
  if (player->is_alive() && !player->is_flicker())
  {
    player->draw();
  }
  for (auto& bullet : bullets)
  {
    bullet.draw();
  }
  for (auto& asteroid : asteroids)
  {
    asteroid.draw();
  }
  //GUI
  if (start && !logo_shade)
    score.draw();
  if ((!start || logo_shade) && !logo->is_half_color())
    logo->draw();
  player->draw_lifes();
}

// free game data in this function
void finalize()
{
  delete player;
  delete logo;
}