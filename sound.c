/**
    @file   sound.c
    @author Vince Alain W. Verwilligen (vav18), Sam Clark (scl113)
    @date   21 October 2021
    @brief  Controls the audio used in the tetris game.
*/
#include "sound.h"
#include "mmelody.h"
#include "pio.h"
#include "tweeter.h"

#define TUNE_BPM_RATE 200

#define PIEZO1_PIO PIO_DEFINE(PORT_D, 4)
#define PIEZO2_PIO PIO_DEFINE(PORT_D, 6)

#define EMPTY_TUNE ""
#define ROTATE_CLOCKWISE_TUNE "D,"
#define ROTATE_COUNTERCLOCKWISE_TUNE "E,"

static tweeter_scale_t scale_table[] = TWEETER_SCALE_TABLE(TWEETER_TASK_RATE);
static tweeter_t tweeter;
static mmelody_t melody;
static mmelody_obj_t melody_info;
static tweeter_obj_t tweeter_info;

static const char game_tune[] = {
#include "tetris_melody.mmel"
};

static const char game_over_tune[] = {
#include "imperial_march.mmel"
};


/** Initializes tweeter pins and melody for tunes. */
void sound_init(void)
{
    pio_config_set(PIEZO1_PIO, PIO_OUTPUT_LOW);
    pio_config_set(PIEZO2_PIO, PIO_OUTPUT_LOW);

    tweeter = tweeter_init(&tweeter_info, TWEETER_TASK_RATE, scale_table);
    melody = mmelody_init(&melody_info, TUNE_TASK_RATE, (mmelody_callback_t)tweeter_note_play, tweeter);

    mmelody_speed_set(melody, TUNE_BPM_RATE);
}


/** Lets task scheduler check for updates for the tweeter. */
void sound_update_tweeter(void)
{
    bool state = tweeter_update(tweeter);

    pio_output_set(PIEZO1_PIO, state);
    pio_output_set(PIEZO2_PIO, !state);
}


/** Lets task scheduler check for updates for the melody. */
void sound_update_melody(void)
{
    mmelody_update(melody);
}


/** Plays the tetris tune. */
void sound_play_tetris_tune(void)
{
    mmelody_play(melody, game_tune);
}


/** Plays the game over tune. */
void sound_play_game_over_tune(void)
{
    mmelody_play(melody, game_over_tune);
}


/** Plays a note when rotating clockwise. */
void sound_play_rotate_clockwise_tune(void)
{
    mmelody_play(melody, ROTATE_CLOCKWISE_TUNE);
}


/** Plays a note when rotating counterclockwise. */
void sound_play_rotate_counterclockwise_tune(void)
{
    mmelody_play(melody, ROTATE_COUNTERCLOCKWISE_TUNE);
}


/** Stop playing tunes. */
void sound_stop_tune(void)
{
    mmelody_play(melody, EMPTY_TUNE);
}
