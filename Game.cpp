#include "Engine.h"
#include "Draw.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Score.h"
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
static Score score;
static vector<Bullet> bullets;
static vector<Asteroid> asteroids;
static bool pause = false;
static float pause_timer = -1.0f;

float rand(float min, float max) 
{
    float answer = static_cast<float>(rand()) / RAND_MAX;
    return min + answer * (max - min);
}

void reset()
{
    player->reset();
    score.reset();
    asteroids.clear();
    bullets.clear();
}

// initialize game data in this function
void initialize()
{
  srand(time(0));
  player = new Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
  asteroids.push_back(Asteroid({ 100, 100 }, 2, 50, 3));
  asteroids.push_back(Asteroid({ 1004, 100 }, 4, 50, 3));
  asteroids.push_back(Asteroid({ 1004, 700 }, 5, 50, 3));
  asteroids.push_back(Asteroid({ 504, 100 }, 4, 50, 3));
  asteroids.push_back(Asteroid({ 204, 700 }, 5, 50, 3));
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
  if (is_key_pressed('P') && pause_timer < 0)
  {
    pause = !pause;
    pause_timer = 0.5f;
  }
  if (pause_timer > 0)
    pause_timer -= dt;
  if (pause)
    return;

  if (player->is_thrust())
    player->set_thrust(false);

  if (is_key_pressed(VK_RETURN))
    reset();
  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game();
  if (is_key_pressed(VK_LEFT) || is_key_pressed('A'))
    player->turn_left(dt);
  if (is_key_pressed(VK_RIGHT) || is_key_pressed('D'))
    player->turn_right(dt);
  if (is_key_pressed(VK_UP) || is_key_pressed('W'))
    player->thrust(dt);
  if (is_key_pressed(VK_SPACE) && player->is_reloaded())
  {
    player->reload();
    bullets.push_back(Bullet(player->get_shoot_pos(), player->get_angle(), 300.0f));
  }

  player->update(dt);
  for (auto &bullet : bullets)
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
        float angle = asteroids[j].get_angle();
        int size = asteroids[j].get_size();
        if (size > 1)
        {
          asteroids.push_back(Asteroid({ asteroids[j].get_position(), rand(angle + pi() * 0.25, angle + pi() * 0.75), 50, size - 1 }));
          asteroids.push_back(Asteroid({ asteroids[j].get_position(), rand(angle - pi() * 0.25, angle - pi() * 0.75), 50, size - 1 }));
        }
        score.add_score(100 * size);
        asteroids.erase(asteroids.begin() + j);
        bullets.erase(bullets.begin() + i--);
        break;
      }
    }
  }
  for (int i = 0; i < asteroids.size() && !player->is_invulnerability(); ++i)
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
  score.draw();
  player->draw_lifes();
}

// free game data in this function
void finalize()
{
  delete player;
}