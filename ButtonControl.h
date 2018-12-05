#ifndef BUTTONCONTROL_H
#define BUTTONCONTROL_H

enum Command {
    INC = 9, //SW310
    DECR = 10, //SW312
    LEFT = 11, //SW314
    RIGHT = 12, //SW316
    SUBMIT = 13, //SW318
    NONE = 0, //
};
typedef enum Command Command;

Command buttons_getCommand();

#endif