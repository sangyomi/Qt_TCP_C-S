#include "joy.h"
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#include <iostream>
#define JOY_DEV "/dev/input/js0"

JoyStick::JoyStick() :
        joy_fd(-1),
        num_of_axis(0),
        num_of_buttons(0)
{
    if((joy_fd=open(JOY_DEV,O_RDONLY)) < 0)
    {
        std::cerr<<"Failed to open "<<JOY_DEV<<std::endl;
        return;
    }

    ioctl(joy_fd, JSIOCGAXES, &num_of_axis);
    ioctl(joy_fd, JSIOCGBUTTONS, &num_of_buttons);
    ioctl(joy_fd, JSIOCGNAME(80), &name_of_joystick);

    joy_button.resize(num_of_buttons,0);
    joy_axis.resize(num_of_axis,0);

    std::cout<<"Joystick: "<<name_of_joystick<<std::endl
             <<"  axis: "<<num_of_axis<<std::endl
             <<"  buttons: "<<num_of_buttons<<std::endl;

    fcntl(joy_fd, F_SETFL, O_NONBLOCK);   // using non-blocking mode
}

JoyStick::~JoyStick()
{
    close(joy_fd);
}

void JoyStick::read()
{
    js_event js;

    while (read(joy_fd, &js, sizeof(js_event)) > 0)
    {
        switch (js.type & ~JS_EVENT_INIT)
        {
            case JS_EVENT_AXIS:
                if((int)js.number>=joy_axis.size())
                {
                    std::cerr<<"err:"<<(int)js.number<<std::endl;
                    continue;
                }
                joy_axis[(int)js.number]= js.value;
                break;
            case JS_EVENT_BUTTON:
                if((int)js.number>=joy_button.size())
                {
                    std::cerr<<"err:"<<(int)js.number<<std::endl;
                    continue;
                }
                joy_button[(int)js.number]= js.value;
                break;
        }
    }

    usleep(100);
}

std::vector<int> JoyStick::getAxis() const
{
    return joy_axis;
}

std::vector<char> JoyStick::getButton() const
{
    return joy_button;
