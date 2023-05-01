/**
    @file   tetris.c
    @author Vince Alain W. Verwilligen (vav18), Sam Clark (scl113)
    @date   21 October 2021
    @brief  A tetris game with sound effects

    @defgroup tetris A simple tetris game for the Atmega32u2.
*/

#include "task_manager.h"
#include <stdlib.h>


/** Main function where everything is set up for the tetris game. */
int main(void)
{
    game_data_t game_data = 
    {
        .state = STATE_INIT,
        .tetrion = tetrion_create()
    };

    task_manager_run(&game_data);

    return EXIT_SUCCESS;
}