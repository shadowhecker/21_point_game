/****
  Programming for Engineers - Assignment, 2018
  File  :  assign.c

  Program:  Blackjack game.

  YOU ARE REQUIRED TO MODIFY THIS FILE!
****/


#include "blackJack.h"
#include "playerRecord.h"

#include <stdio.h>

int P_record_count;
int main()
{
	Card deck[MAX_CARDS];
	int result;
	int chips = 100;
	int bet = 0;
	printf("File : assign.c\n");
	printf("Author : Batman\n");//这里要改成你的名字
	printf("This is my own work as defined by the\n");
	printf("University's Academic Misconduct Policy.\n\n\n\n\n\n");
	shuffle_cards(deck);
	char s[10];
	PlayerRecord P_record[MAX_PLAYERS];
	FILE *file = fopen("players.txt", "r");
	if (file == NULL)
	{
		printf("Can't open file\n");
		exit(1);
	}
	read_player_record(file, P_record);
	while (1)
	{
		printf("Please enter command\n");
		printf("[players, buy, chips, clear, add, remove, play, scores, quit]:");
		scanf("%s", &s);
		getchar();
		if (!strcmp(s,"players"))
			display_players(P_record, P_record_count);
		else if (!strcmp(s, "play"))
		{
			char s_name[20];
			printf("Please enter player's name: ");
			gets_s(s_name,20);
			int index = find_player(s_name, P_record, P_record_count);
			if (index == -1)
			{ }
			else
				play_black_jack_games(deck, P_record, index);
		}
		else if (!strcmp(s, "buy"))
		{
			char s_name[20];
			printf("Please enter player's name: ");
			gets_s(s_name, 20);
			int index = find_player(s_name, P_record, P_record_count);
			if (index == -1)
				continue;
			else
				buy_player_chips(P_record, index);
		}
		else if (!strcmp(s, "chips"))
			display_highest_chips(P_record, P_record_count);
		else if (!strcmp(s, "clear"))
		{
			char s_name[20];
			printf("Please enter player's name: ");
			gets_s(s_name, 20);
			clear_player_stats(P_record, s_name, P_record_count);
		}
		else if (!strcmp(s, "add"))
		{
			char s_name[20];
			printf("Please enter player's name: ");
			gets_s(s_name, 20);
			add_player(P_record, s_name, &P_record_count);
		}
		else if (!strcmp(s, "remove"))
		{
			char s_name[20];
			printf("Please enter player's name: ");
			gets_s(s_name, 20);
			remove_player(P_record, s_name, &P_record_count);
		}
		else if (!strcmp(s, "scores"))
			display_high_scores(P_record, P_record_count);
		else if (!strcmp(s, "quit"))
		{
			write_to_file(P_record, P_record_count);
			break;
		}
		else
			printf("Not a valid command - please try again.\n");
	}
	system("pause");
}