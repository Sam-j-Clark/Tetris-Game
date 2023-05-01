
# Tetris Game on LED matrix

### Background

------

This game was a project for an embedded systems class I took in my second year of university. 
It was one of the most successful pair projects I had at university. 
We made a simple tetris game which could be played on a small microcontroller. 
Notably my partner and I got the highest mark in the class for this project. 

### Key Learnings

 - My first project written in C,
 - My first experience writing a program for an embedded system,
 - Experience with handling different IO operations.

-------

## Original Readme

Game summary
------------

This is a game of Tetris with the original tetrominos (blocks) played on a 5x7 display.

Make as many full lines as possible!


Controls
--------
At the start and at the game over

        Push navswitch          - start the game

While playing

        Move left on navswitch  - move tetromino left
        Move right on navswitch - move tetromino right
        Move down on navswitch  - move tetromino down
        Push navswitch          - rotate tetromino clockwise
        Push button S1          - rotate tetromino counterclockwise


How to play?
------------
A message will be displayed asking the user to **push the button (navswitch) to start the game**. A random block will appear and will move down step by step. Your goal is to place the blocks at the bottom and try to **make as many full lines as possible**. The full lines will disapear to make more space for placing the blocks. Every 10 lines made, **the speed of the dropping block will be increased**. When the new block appears and it hits the any of the already placed blocks, you lose and a Game Over message will be displayed together with your full lines made. If you push the navswitch, you will start a new game.


Tetris terminology
------------------
https://tetris.wiki/Glossary

    Tetrion
        A term used by The Tetris Company for the game object that contains a playfield.
        Different tetrions may implement different variations of the game rules.

    Tetromino
        A piece consisting of four square blocks joined at the sides.
        Precise language uses the letter names, but some players use the color names.
