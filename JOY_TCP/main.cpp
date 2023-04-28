#include "JoystickOnex.h"

int main()
{
    JoystickOnex joystick;
    while(true)
    {
        joystick.Read();
    }
    joystick.Close();

    return 0;
}