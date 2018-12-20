/******************************************************
* GUI Control header file				      		            *
*                                                     *
* Authors:  Klaas Govaerts                            *
*                                                     *
******************************************************/

#ifndef GUICONTROL_H
#define GUICONTROL_H

struct Settings{
    int32_t period;
    int32_t unixTime;
};

typedef struct Settings Settings;

void gui_getSettings(Settings *settings);
int32_t gui_getValue(const char *query);
#endif
