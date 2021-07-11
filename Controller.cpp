#include "Controller.h"

Controller::Controller(int num)
  : _controllerNum(num)
{
  ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
  XInputGetState(_controllerNum, &_controllerState);
}

bool Controller::isConnected()
{
  ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
  DWORD Result = XInputGetState(_controllerNum, &_controllerState);
  return Result == ERROR_SUCCESS;
}

bool Controller::is_key_pressed(int key)
{
  auto state = getState();
  switch (key)
  {
  case GP_THRUST:
    return state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP ||
      state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
  case GP_TURN_LEFT:
    return state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT ||
      state.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
  case GP_TURN_RIGHT:
    return state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT ||
      state.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
  case GP_SHOOT:
    return state.Gamepad.wButtons & XINPUT_GAMEPAD_A;
  case GP_PAUSE:
    return state.Gamepad.wButtons & XINPUT_GAMEPAD_START;
  case GP_RESTART:
    return state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
  case GP_EXIT:
    return state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
  default:
    return false;
    break;
  }
}

XINPUT_STATE Controller::getState()
{
  ZeroMemory(&_controllerState, sizeof(XINPUT_STATE));
  XInputGetState(_controllerNum, &_controllerState);
  return _controllerState;
}
