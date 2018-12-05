#ifndef BUTTONCONTROL_H
#define BUTTONCONTROL_H

enum Command {
    INC = 9,
    DECR = 10,
    LEFT = 11,
    RIGHT = 12,
    SUBMIT = 13,
    NONE = 0,
};

enum Command getCommand();

#endif
