#pragma once
#include <windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib")

#define GP_THRUST 0
#define GP_TURN_LEFT 1
#define GP_TURN_RIGHT 2
#define GP_SHOOT 3
#define GP_PAUSE 4
#define GP_RESTART 5
#define GP_EXIT 6

class Controller
{
public:
  Controller(int num);
  bool isConnected();
  bool is_key_pressed(int key);
private:
  XINPUT_STATE _controllerState;
  int _controllerNum;

  XINPUT_STATE getState();
};