/****
  Programming for Engineers - Assignment, 2018
  File  :  playerRecord.h
  
  DO NOT MODIFY THIS FILE!  
    (You will need to complete the PlayerRecord data structure declaration 
     seen below - this is the ONLY change that is allowed to be made on this file.)
****/

#ifndef PLAYERRECORD_H
#define PLAYERRECORD_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "blackJack.h"
  

#define MAX_PLAYERS    5    /* maximum number of player entries */

#define STRING_LENGTH 25    /* maximum length of strings        */



typedef struct {
  /* You will need to complete this data structure declaration by
     adding the data members as specified in the assignment specs.
  */
	
  char *name;   //or... char  name[STRING_LENGTH+1]; 
  int games_played;
  int no_won;
  int no_lost;
  int no_drawn;
  int no_chips;
  int total_score;
  // :
  // :

} PlayerRecord;



/* All the function prototypes in this file represent functions
   you will need to implement in order to complete this assignment. 
   All functions must be implemented according to the specs provided.
   Function specifications are provided below and in the assignment handout.

   *** IMPORTANT: Please do not alter the function prototypes within this file. 
*/



/* This function takes a file name and reads the contents of
   that file into the array of players passed as a parameter
   into the function.

   The function returns the number of players stored in the file.

   The file will already have been opened for reading before being
   passed into this function.
*/
int read_player_record(FILE *, PlayerRecord []);

/* This function will take the player array and the
   number of players stored in the array and
   will output the contents of the array to the screen.

   This function displays the information to the screen
   in the format specified in the assignment specifications
   under the section - 'Screen Format'.
*/
void display_players(PlayerRecord [], int);


/* This function takes the player array and the
   player's position (index) in the array and updates
   the player's chip balance.
   The function prompts for and reads the number of
   chips the player would like to buy (between 1-100) and
   updates the player's chip balance by that amount.

   A message indicating that this has been done is displayed
   to the screen.

   You should validate the number of chips to ensure the player
   only enters between 1-100.  You should also validate the
   position (index) of the player (second parameter) making sure
   it does not exceed array bounds.  If the position exceeds array
   bounds, an error message is displayed.
*/
void buy_player_chips(PlayerRecord [], int);


/* This function will take the player's name, the array of players and
   the number of players stored in the array and will return the
   position (index) of the player found in the	array of players.

   If the player is not found, the function returns -1.
*/
int find_player (char [], PlayerRecord [], int);


/* This function takes the array of players and the number of players
   stored in the array.  This function displays the player with the
   highest chip balance to the screen.  Where two players have the same
   chip balance, the player with the lower games played value is
   displayed.

   This function displays the information to the screen
   in the format specified in the assignment specifications
   under the section - 'Screen Format'.
*/
void display_highest_chips (PlayerRecord [], int);


/* This function takes the array of players, the player's name,
   and the number of players stored in the array and determines
   whether the player exists in the array of players.

   If the player is found, the player's game statistics (games played,
   number won, number lost, number drawn, player's total score) and
   chip balance are set to zero and the function returns 1 (indicating
   that the player's statistics and chip balance have been set to zero).

   If the player is not found in the player array, the function
   returns 0 (indicating the player's statistics and chip balance have
   not been set to zero).

   Hint:  this function MUST make use of the find_player function
*/
int clear_player_stats (PlayerRecord [], char [], int);


/* This function takes the array of players, the player's name
   and the number of players as a call-by-reference parameter.
   If the player does not already exist (i.e. a match is not found
   on player name), it adds the player into the array of players (note
   that the other data members should be initialised to zero).

   The player must be added after the last player
   entry stored in the array.  You will need to check that you
   are not exceeding array bounds.

   If the array of players is full, the function does not add the
   new player and returns -1.

   If the player name already exists, the function does not add the
   new player and returns 0.

   If the player is successfully added to the array, the function
   returns 1.

   Hint:  this function MUST make use of the find_player function.
*/
int add_player (PlayerRecord [], char [], int *);


/* This function takes the array of players, the player's name
   and the number of players as a call-by-reference parameter and
   determines whether the player exists in the array of players.

   If the player is found, the player is removed from the player
   array at the position returned by function findPlayer and the
   function returns 1 (indicating the player has been successfully removed).

   The information must be removed maintaining the order of the
   player array (Hint: shift all elements one position down the array).

   If the player is not found in the player array, the function
   returns 0 (indicating the player has not been removed).

   Hint:  this function MUST make use of the find_player function.
*/
int remove_player (PlayerRecord [], char [], int *);


/* This function takes the deck of cards, the array of players and
   the position of the player playing the current game (i.e. position
   is the location/index of the player stored in the array of players.
   This is useful so we can update the player's game statistics after
   every game). 

   This function plays Blackjack with the player until he/she 
   enters 'n' when prompted to 'Play again [y|n]?'.

   HINT: This function calls the function play_one_game.

   Algorithm is as follows-

         while (user wishes to continue playing) {
     
	       call function play_one_game

           update player information  Hint: Increment the number of games played; for example:
		                                    if the game result is a win, increment the number of
		                                    wins by one and add PLAYER points to the totalScore, 
					                        update the chip balance by bet amount, etc.

           prompt whether player wishes to 'Play again [y|n]?'
	       read response from player
         }
*/
void play_black_jack_games(Card[], PlayerRecord[], int);


/* This function will take the player array and the
   number of players stored in the array and
   will display the player array in descending order of total score.
   Where two players have the same total score, the player with the
   lower games played value should appear first.  This function 
   MUST NOT modify the player array.  Your solution MUST NOT make use 
   of any of the sort functions available in the C Standard Library.

   This function displays the information to the screen
   in the format specified in the assignment specifications
   under the section - 'Screen Format'.
*/
void display_high_scores(PlayerRecord[], int);


/* This function will output the contents of the player array
   to a file in the same format as the input file.

   The file will need to be opened for writing in this function (and
   of course closed once all writing has been done).
*/
void write_to_file(PlayerRecord[], int);


#endif

