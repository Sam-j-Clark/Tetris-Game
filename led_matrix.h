/**
    @file   led_matrix.h
    @author Vince Alain W. Verwilligen (vav18), Sam Clark (scl113)
    @date   21 October 2021
    @brief  Controls the display of the led matrix using tinygl.
*/

#ifndef H_LED_MATRIX
#define H_LED_MATRIX

/** Initializes tinygl to display text and draw pixels. */
void led_matrix_init(uint16_t rate);

/** Checks for updates for the display task and lets tinygl know. */
void led_matrix_update(void);

/** Let tinygl show the message before starting the game. */
void led_matrix_display_start(void);

/** Let tinygl show the game over message and the amount of lines scored. */
void led_matrix_display_game_over_and_lines(char* message, uint8_t lines);

/** Lets tinygl draw all pixels used by tetrominos. */
void led_matrix_draw(uint8_t* display);

/** Lets tinygl clear the display. */
void led_matrix_clear(void);

#endif