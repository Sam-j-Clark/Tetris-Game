/**
    @file   tetromino.c
    @author Vince Alain W. Verwilligen (vav18), Sam Clark (scl113)
    @date   21 October 2021
    @brief  Creates tetromino (tetris tile) functions for moving and rotating the active tiles in the tetris game.
*/

#include "tetromino.h"
#include "tinygl.h"
#include <stdlib.h>

#define START_POSITION {1, 0}


/** Takes a pointer to a tetromino tile and shifts the position up one tile. */
void tetromino_move_up(tetromino_t* tetromino)
{
    tetromino->position.y--;
}


/** Takes a pointer to a tetromino tile and shifts the position down one tile. */
void tetromino_move_down(tetromino_t* tetromino)
{
    tetromino->position.y++;
}


/** Takes a pointer to a tetromino tile and shifts the position left one tile. */
void tetromino_move_left(tetromino_t* tetromino)
{
    tetromino->position.x--;
}


/** Takes a pointer to a tetromino tile and shifts the position right one tile. */
void tetromino_move_right(tetromino_t* tetromino)
{
    tetromino->position.x++;
}


/** Takes a pointer to a tetromino tile and rotates the tile 90 degrees clockwise about the tiles (0,0) pixel. */
void tetromino_rotate_clockwise(tetromino_t* tetromino) 
{
    int8_t x;

    for (uint8_t i = 0; i < MAX_PIXELS; i++) {
        
        x = -1 * tetromino->pixels[i].x;
        tetromino->pixels[i].x = tetromino->pixels[i].y;
        tetromino->pixels[i].y = x;
    }   
}


/** Takes a pointer to a tetromino tile and rotates the tile 90 degrees counterclockwise about the tiles (0,0) pixel. */
void tetromino_rotate_counterclockwise(tetromino_t* tetromino) 
{
    int8_t y;

    for (uint8_t i = 0; i < MAX_PIXELS; i++) {
        
        y = -1 * tetromino->pixels[i].y;
        tetromino->pixels[i].y = tetromino->pixels[i].x;
        tetromino->pixels[i].x = y;
    }      
}


/**
    Takes a pointer to a tetromino tile, and index in the range 0 - MAX_PIXELS, a pointer to some x value and a pointer to some y value.
    The x and y values are set to the position of the pixel on the tetrion, by using the tetrominos position and the postion of the specific pixel.
 */
void tetromino_get_actual_position(tetromino_t* tetromino, uint8_t index, int8_t* x, int8_t* y)
{
    *x = tetromino->position.x + tetromino->pixels[index].x;
    *y = tetromino->position.y + tetromino->pixels[index].y;
}


/**
    o tetromino
    ------------
    01
    23
*/
static void tetromino_create_o(tetromino_t* tetromino)
{
    tetromino_t new_tetromino = {
        .pixels={
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
        }, 
        .position = START_POSITION
    };

    *tetromino = new_tetromino;
}


/**
    i tetromino
    ------------
    0123    0
            1 
            2
            3
*/
static void tetromino_create_i(tetromino_t* tetromino)
{
    tetromino_t new_tetromino = {
        .pixels={
            {-1, 0},
            {0, 0},
            {1, 0},
            {2, 0}
        }, 
        .position = START_POSITION
    };

    *tetromino = new_tetromino;
}


/**
    t tetromino
    ------------
    0   1 012 0 
    123 02  3  13
        3     2  
*/
static void tetromino_create_t(tetromino_t* tetromino) 
{ 
    tetromino_t new_tetromino = {
        .pixels={
            {-1, 0},
            {0, 0},
            {1, 0},
            {0, 1}
        },  
        .position = START_POSITION
    };

    *tetromino = new_tetromino;
}


/**
    s tetramino 
    ------------
     23 0
    01  12
         3
*/
static void tetromino_create_s(tetromino_t* tetromino) 
{ 
    tetromino_t new_tetromino = {
        .pixels={
            {-1, 1},
            {0, 1},
            {0, 0},
            {1, 0}
        }, 
        .position = START_POSITION
    };

    *tetromino = new_tetromino;
}


/**
    z tetramino
    ------------
    01   3
     23 02
        1
*/
static void tetromino_create_z(tetromino_t* tetromino) 
{ 
    tetromino_t new_tetromino = {
        .pixels={
            {-1, 0},
            {0, 0},
            {0, 1},
            {1, 1}
        }, 
        .position = START_POSITION
    };

    *tetromino = new_tetromino;
}


/**
    l tetramino
    ------------
         01       0
      3   2  012  1
    012   3  3    23
*/
static void tetromino_create_l(tetromino_t* tetromino) 
{ 
    tetromino_t new_tetromino = {
        .pixels={
            {-1, 0},
            {-1, 1},
            {0, 0},
            {1, 0}
        }, 
        .position = START_POSITION
    };

    *tetromino = new_tetromino;
}


/**
    j tetramino
    ------------
        01      0
    0   2  012  1
    123 3    3 23
*/
static void tetromino_create_j(tetromino_t* tetromino) 
{ 
    tetromino_t new_tetromino = {
        .pixels={
            {-1, 0},
            {0, 0},
            {1, 0},
            {1, 1}
        }, 
        .position = START_POSITION
    };

    *tetromino = new_tetromino;
}


/**
    Chooses a random number in the range 0 - 6 and uses that number to create a new current tetromino. 
    The random number determines which shape tetromino the new tetromino will be gfrom the standard 7 tetris tiles.
*/
void tetromino_create_random(tetromino_t* tetromino, uint16_t random_ticks)
{
    switch (random_ticks % MAX_TETROMINO_TYPES)
    {
        case TETROMINO_TYPE_O :
            tetromino_create_o(tetromino);
            break;
        case TETROMINO_TYPE_I :
             tetromino_create_i(tetromino);
            break;
        case TETROMINO_TYPE_T :
            tetromino_create_t(tetromino);
            break;
        case TETROMINO_TYPE_S :
            tetromino_create_s(tetromino);
            break;
        case TETROMINO_TYPE_Z :
            tetromino_create_z(tetromino);
            break;
        case TETROMINO_TYPE_L :
            tetromino_create_l(tetromino);
            break;
        case TETROMINO_TYPE_J :
            tetromino_create_j(tetromino);
            break;
    }
}