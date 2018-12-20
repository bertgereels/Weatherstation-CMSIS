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

/**
 * Request the period and UNIX system time from the user. Blocking function.
 * @param settings A pointer to the struct where the result will be written.
 */
void gui_getSettings(Settings *settings);

/**
 * Display a query on the screen, and return the result. Blocking function.
 * @param query A null terminited character array. The text that will be displayed at first line of LCD. Query should not be longer than 16 characters.
 * @return The numerical value entered by the user.
 */
int32_t gui_getValue(const char *query);
#endif
