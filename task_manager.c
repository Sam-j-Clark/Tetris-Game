/**
    @file   task_manager.c
    @author Vince Alain W. Verwilligen (vav18), Sam Clark (scl113)
    @date   21 October 2021
    @brief  Runs the tasks required for the tetris game to run.
*/

#include "button.h"
#include "led.h"
#include "led_matrix.h"
#include "navswitch.h"
#include "pacer.h"
#include "pio.h"
#include "sound.h"
#include "system.h"
#include "task.h"
#include "task_manager.h"
#include "tetromino.h"

#define DISPLAY_TASK_RATE 300
#define BUTTON_TASK_RATE 50
#define GAME_TASK_RATE 100
#define DROP_TASK_RATE 100
#define MOVEMENT_SPEED_INCREASE 10
#define FLASH_LED_RATE 100

#define FLASH_RATE 5
#define LED_OFF 0
#define LED_ON 1

#define FLASH_DURATION 20
#define FLASHING_OFF 0
#define FLASHING_ON 1


/**
    Called when the player either starts a game for the first time or retries after a game is lost,
    this function clears the tetrion and display, stops the intro music and adds the first tetromino. 
    The game state is also est to playing so that the tasks can determine the games flow.
 */
static void game_start(game_data_t* game_data)
{
    led_matrix_clear();
    tetrion_clear(&game_data->tetrion);
    sound_stop_tune();
    tetrion_try_add_tetromino(&game_data->tetrion);
    game_data->state = STATE_PLAYING;
}


/**
    Called when the player loses the game, by no longer being able to place a tetromino, this function
    plays game over tune and shows the game over message, with the players score.
 */
static void game_over(game_data_t* game_data)
{
    sound_play_game_over_tune();
    led_matrix_clear();
    led_matrix_display_game_over_and_lines(game_data->message, game_data->tetrion.lines);
    game_data->state = STATE_OVER;
}


/**
 * Is called every time the falling tetromino is going to fall.
 * Once the falling tetromino hit bottom, it sticks and a new tetromino will be shown.
 * If the new tetromino is shown on an already existing tetromino, the game is over.
 * This time reduces to make fitting the tetromino harder.
 */
static void tetromino_drop_handle(game_data_t* game_data)
{
    if (!tetrion_try_move_down(&game_data->tetrion)) {
        tetrion_check_lines(&game_data->tetrion);

        if (!tetrion_try_add_tetromino(&game_data->tetrion)) {
            game_over(game_data);
        }
    }
}


/**
 * Updates the tweeter to turn it on.
 */
static void tweeter_task(__unused__ void* data)
{
    sound_update_tweeter();
}


/**
 * Update the melody to play the right notes.
 */
static void tune_task(__unused__ void* data)
{
    sound_update_melody();
}


/**
 * Updates all texts or tetrominos to the led matrix display.
 */
static void display_task(void* data)
{
    game_data_t* game_data = (game_data_t*) data;

    if (game_data->state == STATE_PLAYING) {
        led_matrix_draw(game_data->tetrion.display);
    }

    led_matrix_update();
}


/**
 * Checks for changes of button1
 * Push - rotates falling tetromino counterclockwise and plays a sound.
 */
static void button_task(void* data)
{
    game_data_t* game_data = (game_data_t*) data;

    button_update();

    if (button_push_event_p(BUTTON1) && game_data->state == STATE_PLAYING) {
        tetrion_try_rotate_counterclockwise(&game_data->tetrion);
        sound_play_rotate_counterclockwise_tune();
    }
}


/**
 * Checks for changes of the navswitch.
 * Push in not playing state - start a new game.
 * Push in playing state - rotates the falling tetromino clockwise and plays a sound.
 * Left - moves the falling tetromino.
 * Right - move the falling tetromino.
 * Buttom - moves the falling tetromino.
 */
static void navswitch_task(void* data)
{
    game_data_t* game_data = (game_data_t*) data;

    navswitch_update();

    if (navswitch_push_event_p(NAVSWITCH_PUSH) && (game_data->state == STATE_READY || game_data->state == STATE_OVER)) {
       game_start(game_data);
    }

    if(game_data->state == STATE_PLAYING) {

        if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
            tetrion_try_rotate_clockwise(&game_data->tetrion);
            sound_play_rotate_clockwise_tune();
        }

        if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            tetrion_try_move_down(&game_data->tetrion);
        }

        if (navswitch_push_event_p(NAVSWITCH_WEST)) {
            tetrion_try_move_left(&game_data->tetrion);
        }

        if (navswitch_push_event_p(NAVSWITCH_EAST)) {
            tetrion_try_move_right(&game_data->tetrion);
        }
    }
}


/**
 * Is responsible for starting and ending the game.
 */
static void game_init_task(void* data)
{
    game_data_t* game_data = (game_data_t*) data;
    if (game_data->state == STATE_INIT) {
        led_matrix_display_start();
        sound_play_tetris_tune();
        game_data->state = STATE_READY;
    }
}


/**
 * A timer is used to count ticks, which is used for the falling block and the randomness of new tetromino.
 */
static void drop_tetromino_task(void* data)
{
    game_data_t* game_data = (game_data_t*) data;

    static uint8_t level;
    static uint8_t drop_rate;
    static uint16_t tetrion_ticks;
    static uint16_t random_ticks;

    level = game_data->tetrion.lines / MOVEMENT_SPEED_INCREASE;
    drop_rate = (DROP_TASK_RATE - (MOVEMENT_SPEED_INCREASE * level));
    if (game_data->state == STATE_PLAYING && tetrion_ticks % drop_rate == 0) {
        tetromino_drop_handle(game_data);
        tetrion_ticks = 0;
    }

    game_data->tetrion.random_ticks = random_ticks;

    tetrion_ticks++;
    random_ticks++;
}


/**
    Responsible for flashing the blue LED whenever a line is removed from the tetrion
*/
static void flash_led_task(void* data)
{
    game_data_t* game_data = (game_data_t*) data;
    
    static uint8_t lines;
    static uint16_t led_flashing_ticks;

    static uint16_t led_ticks;
    static bool flashing = FLASHING_OFF;
    static bool led_state = LED_OFF;

    if (game_data->state == STATE_PLAYING) {

        // Start flashing LED
        if (flashing == FLASHING_OFF && game_data->tetrion.lines > lines) {
            flashing = FLASHING_ON;
            led_ticks = 0;
            lines = game_data->tetrion.lines;
        }

        // Stop LED from flashing
        if (flashing == FLASHING_ON && led_ticks > FLASH_DURATION) {
            flashing = FLASHING_OFF;
            led_set(LED1, LED_OFF);
        }

        // Flashing LED
        if (flashing == FLASHING_ON && led_ticks % FLASH_RATE == 0) {
            led_set(LED1, led_state);
            led_state = !led_state;
            led_flashing_ticks = 0;
        }
    }

    led_ticks++;
    led_flashing_ticks++;
}


/**
    Initialises the tasks run throughout a tetris game, and runs them once intialised.
*/
void task_manager_run(game_data_t* game_data) {

    system_init();
    sound_init();
    button_init();
    navswitch_init();
    led_matrix_init(DISPLAY_TASK_RATE);
    led_init();
    led_set(LED1, LED_OFF);

    task_t tasks[] = {

        { .func = tweeter_task, .period = TASK_RATE / TWEETER_TASK_RATE, .data = game_data },
        { .func = tune_task, .period = TASK_RATE / TUNE_TASK_RATE, .data = game_data },
        { .func = display_task, .period = TASK_RATE / DISPLAY_TASK_RATE, .data = game_data },
        { .func = navswitch_task, .period = TASK_RATE / BUTTON_TASK_RATE, .data = game_data },
        { .func = button_task, .period = TASK_RATE / BUTTON_TASK_RATE, .data = game_data },
        { .func = game_init_task, .period = TASK_RATE / GAME_TASK_RATE, .data = game_data },
        { .func = drop_tetromino_task, .period = TASK_RATE / DROP_TASK_RATE, .data = game_data },
        { .func = flash_led_task, .period = TASK_RATE / FLASH_LED_RATE, .data = game_data } 
    };

    task_schedule(tasks, ARRAY_SIZE(tasks));
}