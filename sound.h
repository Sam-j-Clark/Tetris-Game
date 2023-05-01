/**
    @file   sound.h
    @author Vince Alain W. Verwilligen (vav18), Sam Clark (scl113)
    @date   21 October 2021
    @brief  Controls the audio used in the tetris game.
*/

#ifndef SOUND_H
#define SOUND_H

#define TWEETER_TASK_RATE 10000
#define TUNE_TASK_RATE 200

/** Initializes tweeter pins and melody for tunes. */
void sound_init(void);

/** Lets task scheduler check for updates for the tweeter. */
void sound_update_tweeter(void);

/** Lets task scheduler check for updates for the melody. */
void sound_update_melody(void);

/** Plays the tetris tune. */
void sound_play_tetris_tune(void);

/** Plays the game over tune. */
void sound_play_game_over_tune(void);

/** Plays a note when rotating clockwise. */
void sound_play_rotate_clockwise_tune(void);

/** Plays a note when rotating counterclockwise. */
void sound_play_rotate_counterclockwise_tune(void);

/** Stop playing tunes. */
void sound_stop_tune(void);

#endif