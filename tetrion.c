/**
    @file   tetrion.c
    @author Vince Alain W. Verwilligen (vav18), Sam Clark (scl113)
    @date   21 October 2021
    @brief  The tetrion (board) used in the tetris game.
*/

#include "tetrion.h"
#include "tetromino.h"
#include "system.h"


/** Creates and empty tetrion (a.k.a. playing field). */
tetrion_t tetrion_create(void)
{
    tetrion_t tetrion = {};

    return tetrion;
}


/** Clears all pixels from the display. Needed for the game over. */
void tetrion_clear(tetrion_t* tetrion)
{
    uint8_t i;

    for (i = 0; i < ARRAY_SIZE(tetrion->display); i++)
        tetrion->display[i] = PIXEL_OFF;
}


/**
    Removes the full line and lets all pixels drop. This function is passed the index (height) of a line that is full and needs removing.
    Full lines are determined in the tetrion_check_lines function which calls this function on all lines which are full.
 */
static void tetrion_clear_line(tetrion_t* tetrion, uint8_t index)
{
    int8_t i;
    int8_t j;
    static uint8_t lines = 0;

    for (i = index; i > 0; i--) {
        for (j = 0; j < TINYGL_WIDTH; j++) {
            tetrion->display[(i) * TINYGL_WIDTH + j] = tetrion->display[(i - 1) * TINYGL_WIDTH + j];
        }
    }

    // empty top line
    for (j = 0; j < TINYGL_WIDTH; j++) {
        tetrion->display[j] = PIXEL_OFF;
    }

    lines++;
    tetrion->lines = lines;
}


/** Check if the lines on the tetrion are full lines, then removes the full lines by calling tetrion_clear_line. */
void tetrion_check_lines(tetrion_t* tetrion)
{
    uint8_t i;
    uint8_t j;
    bool full_line;

    for (i = 0; i < TINYGL_HEIGHT; i++) {
        full_line = true;
        for (j = 0; j < TINYGL_WIDTH; j++) {
            if (tetrion->display[i * TINYGL_WIDTH + j] == PIXEL_OFF) {
                full_line = false;
                break;
            }
        }

        if (full_line) {
            tetrion_clear_line(tetrion, i);
        }
    }
}


/** Tries to add a new tetromino and displays it. */
bool tetrion_try_add_tetromino(tetrion_t* tetrion)
{
    bool can_place;

    tetromino_create_random(&tetrion->current_tetromino, tetrion->random_ticks);
    can_place = tetrion_can_place_tetromino(tetrion);
    tetrion_display_tetromino(tetrion);

    return can_place;
}


/** Checks if a tetromino can be placed. */
bool tetrion_can_place_tetromino(tetrion_t* tetrion)
{
    uint8_t i;
    int8_t x;
    int8_t y;

    for (i = 0; i < MAX_PIXELS; i++) {
        tetromino_get_actual_position(&tetrion->current_tetromino, i, &x, &y);

        if (tetrion->display[x + y * TINYGL_WIDTH] == PIXEL_ON) {
            return false;
        }
    }

    return true;
}


/** Makes the tetromino visible by putting the pixels on. */
void tetrion_display_tetromino(tetrion_t* tetrion)
{
    uint8_t i;
    int8_t x;
    int8_t y;


    for (i = 0; i < MAX_PIXELS; i++) {
        tetromino_get_actual_position(&tetrion->current_tetromino, i, &x, &y);

        if (x < TINYGL_WIDTH && y < TINYGL_HEIGHT) {
            tetrion->display[x + y * TINYGL_WIDTH] = PIXEL_ON;
        }
    }

}


/** Hides the tetromino by putting the pixels off. */
void tetrion_hide_tetromino(tetrion_t* tetrion)
{
    uint8_t i;
    int8_t x;
    int8_t y;

    for (i = 0; i < MAX_PIXELS; i++) {
        tetromino_get_actual_position(&tetrion->current_tetromino, i, &x, &y);

        if (x < TINYGL_WIDTH && y < TINYGL_HEIGHT) {
            tetrion->display[x + y * TINYGL_WIDTH] = PIXEL_OFF;
        }
    }
}


/**
 * Hides the tetromino, moves it down, checks for collision.
 * If it can't be displayed, moves it back up.
 * Finally displays the tetromino again.
 */
bool tetrion_try_move_down(tetrion_t* tetrion)
{
    bool success = true;

    tetrion_hide_tetromino(tetrion);
    tetromino_move_down(&tetrion->current_tetromino);

    if (tetrion_collide_edges(tetrion) || !tetrion_can_place_tetromino(tetrion)) {
        success = false;
    }

    if (!success) {
        tetromino_move_up(&tetrion->current_tetromino);
    }

    tetrion_display_tetromino(tetrion);

    return success;
}


/**
 * Hides the tetromino, moves it left, checks for collision.
 * If it can't be displayed, moves it back right.
 * Finally displays the tetromino again.
 */
bool tetrion_try_move_left(tetrion_t* tetrion)
{
    bool success = true;

    tetrion_hide_tetromino(tetrion);
    tetromino_move_left(&tetrion->current_tetromino);

    if (tetrion_collide_edges(tetrion) || !tetrion_can_place_tetromino(tetrion)) {
        success = false;
    }

    if (!success) {
        tetromino_move_right(&tetrion->current_tetromino);
    }

    tetrion_display_tetromino(tetrion);

    return success;
}


/**
 * Hides the tetromino, moves it right, checks for collision.
 * If it can't be displayed, moves it back left.
 * Finally displays the tetromino again.
 */
bool tetrion_try_move_right(tetrion_t* tetrion)
{
    bool success = true;

    tetrion_hide_tetromino(tetrion);
    tetromino_move_right(&tetrion->current_tetromino);

    if (tetrion_collide_edges(tetrion) || !tetrion_can_place_tetromino(tetrion)) {
        success = false;
    }
        
    if (!success) {
        tetromino_move_left(&tetrion->current_tetromino);
    }

    tetrion_display_tetromino(tetrion);

    return success;
}


/**
 * Hides the tetromino, rotates it clockwise, checks for collision.
 * If it can't be displayed, rotates it back counterclockwise.
 * Finally displays the tetromino again.
 */
bool tetrion_try_rotate_clockwise(tetrion_t* tetrion)
{
    bool success = true;

    tetrion_hide_tetromino(tetrion);
    tetromino_rotate_clockwise(&tetrion->current_tetromino);

    if (tetrion_collide_edges(tetrion) || !tetrion_can_place_tetromino(tetrion)) {
        success = false;
    }
        
    if (!success) {
        tetromino_rotate_counterclockwise(&tetrion->current_tetromino);
    }

    tetrion_display_tetromino(tetrion);

    return success;
}


/**
 * Hides the tetromino, rotates it counterclockwise, checks for collision.
 * If it can't be displayed, rotates it back clockwise.
 * Finally displays the tetromino again.
 */
bool tetrion_try_rotate_counterclockwise(tetrion_t* tetrion)
{
    bool success = true;

    tetrion_hide_tetromino(tetrion);
    tetromino_rotate_counterclockwise(&tetrion->current_tetromino);

    if (tetrion_collide_edges(tetrion) || !tetrion_can_place_tetromino(tetrion)) {
        success = false;
    }
        
    if (!success) {
        tetromino_rotate_clockwise(&tetrion->current_tetromino);
    }

    tetrion_display_tetromino(tetrion);

    return success;
}


/** 
    Checks if a tetromino is outside the LED display (and tetrion board), returns true if
    the tetromino collides, otherwise returns false.
*/
bool tetrion_collide_edges(tetrion_t* tetrion)
{
    uint8_t i;
    int8_t x;
    int8_t y;

    for (i = 0; i < MAX_PIXELS; i++) {
        tetromino_get_actual_position(&tetrion->current_tetromino, i, &x, &y);

        if (x < 0 || x >= TINYGL_WIDTH || y < 0 || y >= TINYGL_HEIGHT) {
            return true;
        }
    }

    return false;
}