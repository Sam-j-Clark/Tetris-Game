/**
    @file   tetromino.h
    @author Vince Alain W. Verwilligen (vav18), Sam Clark (scl113)
    @date   21 October 2021
    @brief  Creates tetromino (tetris tile) functions for moving and rotating the active tiles in the tetris game.
*/
#ifndef H_TETROMINO
#define H_TETROMINO

#include "system.h"

#define PIXEL_OFF 0
#define PIXEL_ON 1

#define MAX_PIXELS 4

#define MAX_TETROMINO_TYPES 7

/** Enum type containing all the posible tetromino tiles that can be created using the tetromino_create_random function. */
typedef enum { 
    TETROMINO_TYPE_O,
    TETROMINO_TYPE_I, 
    TETROMINO_TYPE_T,
    TETROMINO_TYPE_S, 
    TETROMINO_TYPE_Z, 
    TETROMINO_TYPE_L, 
    TETROMINO_TYPE_J 
} tetromino_type_t;

/** The pixel location for each pixel of a tetromino, relative to the center of the tile. */
typedef struct {
    int8_t x;
    int8_t y;
} pixel_t;

/** The position of the tetromino's (0,0) pixel on the tetrion */
typedef struct {
    int8_t x;
    int8_t y;
} tetromino_pos_t;


/** 
    Tetromino type used for the tiles in a tetris game. This type is broken into:
     - the pixels which determines the shape of the tile. 
     - the position which determines when on the tetrion (board) the tile is
*/
typedef struct {
    pixel_t pixels[MAX_PIXELS];
    tetromino_pos_t position;
} tetromino_t;

/**
    Chooses a random number in the range 0 - 6 and uses that number to create a new current tetromino. 
    The random number determines which shape tetromino the new tetromino will be gfrom the standard 7 tetris tiles.
*/
void tetromino_create_random(tetromino_t* tetromino, uint16_t random_ticks);

/** Takes a pointer to a tetromino tile and shifts the position up one tile. */
void tetromino_move_up(tetromino_t* tetromino);

/** Takes a pointer to a tetromino tile and shifts the position down one tile. */
void tetromino_move_down(tetromino_t* tetromino);

/** Takes a pointer to a tetromino tile and shifts the position left one tile. */
void tetromino_move_left(tetromino_t* tetromino);

/** Takes a pointer to a tetromino tile and shifts the position right one tile. */
void tetromino_move_right(tetromino_t* tetromino);

/** Takes a pointer to a tetromino tile and rotates the tile 90 degrees clockwise about the tiles (0,0) pixel. */
void tetromino_rotate_clockwise(tetromino_t* tetromino);

/** Takes a pointer to a tetromino tile and rotates the tile 90 degrees counterclockwise about the tiles (0,0) pixel. */
void tetromino_rotate_counterclockwise(tetromino_t* tetromino);

/**
    Takes a pointer to a tetromino tile, and index in the range 0 - MAX_PIXELS, a pointer to some x value and a pointer to some y value.
    The x and y values are set to the position of the pixel on the tetrion, by using the tetrominos position and the postion of the specific pixel.
 */
void tetromino_get_actual_position(tetromino_t* tetromino, uint8_t index, int8_t* x, int8_t* y);

#endif