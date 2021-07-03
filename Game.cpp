#include "Engine.h"
#include "Draw.h"
#include "Player.h"
#include "Bullet.h"
#include <stdlib.h>
#include <memory.h>

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
Player* player;
vector<Bullet> bullets;
// initialize game data in this function
void initialize()
{
  player = new Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
}
int a = 0, b = 0;
// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
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
  draw_thick_line(300, 300, 350, 400, 0xffff00, 2);
  draw_thick_line(300, 300, 250, 400, 0xffff00, 2);
  draw_thick_line(350, 400, 300, 380, 0xffff00, 2);
  draw_thick_line(300, 380, 250, 400, 0xffff00, 2);
  draw_dot(a, b, 0xffff00, 10);
  player->draw();
  //draw_thick_line(300, 500, 320, 320, 0xffff00, 10);
  for (auto& bullet : bullets)
  {
    bullet.draw();
  }
  //draw_dot(50, 50, 0xffff00, 10);
  //draw_line(300, 300, 500, 300, 0xff0000);
  //draw_line(200, 200, 100, 200);
  //buffer[500][1000] = 0xff0000;
}

// free game data in this function
void finalize()
{
  delete player;
}

