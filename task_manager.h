/**
    @file   task_manager.h
    @author Vince Alain W. Verwilligen (vav18), Sam Clark (scl113)
    @date   21 October 2021
    @brief  Runs the tasks required for the tetris game to run.
*/

#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include "tetrion.h"

#define MESSAGE_SIZE 50

/**
    All the possible states the Tetris game can be in.
     - STATE_INIT = when the program is first run used to initialise variables and setup the game for use.
     - STATE_READY = when the game is initialised, waiting for the used to push button to start.
     - STATE_PLAYING =  the main state of a tetris game from when a game is started up until tiles can no longer be placed.
     - STATE_OVER = the game over message shown after a tile can no longer be placed. This displays the score the player got. 
*/
typedef enum { 
    STATE_INIT,
    STATE_READY,
    STATE_PLAYING,
    STATE_OVER
} state_t;

/** 
Game data type used to score the current state of the tetris game. 
     - The state refers to the games current situation eg. STATE_OVER when the game has been lost and the score is being displayed. 
     - The tetrion refers to the board for the current game and stores a tetrion_t type which also stores the current tetromino.
     - The message refers to the message displayed. eg. "Push button to start" when the game is just started.
*/
typedef struct
{
    state_t state;
    tetrion_t tetrion;
    char message[MESSAGE_SIZE];
} game_data_t;

/** Initialises the tasks run throughout a tetris game, and runs them once intialised. */
void task_manager_run(game_data_t* game_data);

#endif // TASK_MANAGER_H