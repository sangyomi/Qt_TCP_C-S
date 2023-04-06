#ifndef JOY_H
#define JOY_H

#include <vector>

class JoyStick {
public:
    JoyStick();
    ~JoyStick();

    void read();
    std::vector<int> getAxis() const;
    std::vector<char> getButton() const;

private:
    int joy_fd;
    int num_of_axis;
    int num_of_buttons;
    char name_of_joystick[80];
    std::vector<char> joy_button;
    std::vector<int> joy_axis;
};

#endif // JOY_H
