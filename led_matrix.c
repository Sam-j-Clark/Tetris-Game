/**
    @file   led_matrix.c
    @author Vince Alain W. Verwilligen (vav18), Sam Clark (scl113)
    @date   21 October 2021
    @brief  Controls the display of the led matrix using tinygl.
*/

#include <string.h>
#include "system.h"
#include "../fonts/font5x5_1.h"
#include "tinygl.h"
#include "led_matrix.h"
#include "uint8toa.h"

#define MESSAGE_RATE 20
#define GAME_START_MESSAGE "Push button to start :)\0"
#define GAME_OVER_MESSAGE "Game Over - Lines:"


/** Initializes tinygl to display text and draw pixels. */
void led_matrix_init(uint16_t rate)
{
    tinygl_init(rate);
    tinygl_font_set(&font5x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
}


/** Checks for updates for the display task and lets tinygl know. */
void led_matrix_update(void)
{
    tinygl_update();
}


/** Let tinygl show the message before starting the game. */
void led_matrix_display_start(void)
{
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_text(GAME_START_MESSAGE);
}


/** Let tinygl show the game over message and the amount of lines scored. */
void led_matrix_display_game_over_and_lines(char* message, uint8_t lines)
{
    char *string = message;

    strcpy (string, GAME_OVER_MESSAGE);
    while (*string)
        string++;
    uint8toa(lines, string, 0);

    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
    tinygl_clear ();
    tinygl_text(message);
}


/** Lets tinygl draw all pixels used by tetrominos. */
void led_matrix_draw(uint8_t* display)
{
    uint8_t index = 0;
    uint8_t i;
    uint8_t j;

    for (j = 0; j < TINYGL_HEIGHT; j++) {
        for (i = 0; i < TINYGL_WIDTH; i++) {
            tinygl_point_t point = { i, j };

            tinygl_draw_point(point, display[index++]);
        }
    }
}


/** Lets tinygl clear the display. */
void led_matrix_clear(void)
{
    tinygl_clear();
}