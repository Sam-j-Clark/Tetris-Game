/**
    @file   tetrion.h
    @author Vince Alain W. Verwilligen (vav18), Sam Clark (scl113)
    @date   21 October 2021
    @brief  The tetrion (board) used in the tetris game.
*/

#ifndef H_TETRION
#define H_TETRION

#include "tetromino.h"
#include "tinygl.h"

/**
    The type used to store a tetris games tetrion (board).
     - The display array stores whether each pixel on the board is on (filled)
     - The current tetromino which is active. This changes each time a tetromino reaches the bottom.
     - The lines cleared so far, used to score the game.
     - random_ticks is used to create a new random tetromino.
*/
typedef struct {
    uint8_t display[TINYGL_WIDTH * TINYGL_HEIGHT];
    tetromino_t current_tetromino;
    uint8_t lines;
    uint16_t random_ticks;
} tetrion_t;

/** Creates and empty tetrion (a.k.a. playing field). */
tetrion_t tetrion_create(void);

/** Clears all pixels from the display. Needed for the game over. */
void tetrion_clear(tetrion_t* tetrion);

/** Check if the lines on the tetrion are full lines, then removes the full lines by calling tetrion_clear_line. */
void tetrion_check_lines(tetrion_t* tetrion);

/** Tries to add a new tetromino and displays it. */
bool tetrion_try_add_tetromino(tetrion_t* tetrion);

/** Checks if a tetromino can be placed. */
bool tetrion_can_place_tetromino(tetrion_t* tetrion);

/** Makes the tetromino visible by putting the pixels on. */
void tetrion_display_tetromino(tetrion_t* tetrion);

/** Hides the tetromino by putting the pixels off. */
void tetrion_hide_tetromino(tetrion_t* tetrion);

/**
 * Hides the tetromino, moves it down, checks for collision.
 * If it can't be displayed, moves it back up.
 * Finally displays the tetromino again.
 */
bool tetrion_try_move_down(tetrion_t* tetrion);

/**
 * Hides the tetromino, moves it left, checks for collision.
 * If it can't be displayed, moves it back right.
 * Finally displays the tetromino again.
 */
bool tetrion_try_move_left(tetrion_t* tetrion);

/**
 * Hides the tetromino, moves it right, checks for collision.
 * If it can't be displayed, moves it back left.
 * Finally displays the tetromino again.
 */
bool tetrion_try_move_right(tetrion_t* tetrion);

/**
 * Hides the tetromino, rotates it clockwise, checks for collision.
 * If it can't be displayed, rotates it back counterclockwise.
 * Finally displays the tetromino again.
 */
bool tetrion_try_rotate_clockwise(tetrion_t* tetrion);

/**
 * Hides the tetromino, rotates it counterclockwise, checks for collision.
 * If it can't be displayed, rotates it back clockwise.
 * Finally displays the tetromino again.
 */
bool tetrion_try_rotate_counterclockwise(tetrion_t* tetrion);

/** 
    Checks if a tetromino is outside the LED display (and tetrion board), returns true if
    the tetromino collides, otherwise returns false.
*/
bool tetrion_collide_edges(tetrion_t* tetrion);

#endif