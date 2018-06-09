
#include "playerRecord.h"
extern P_record_count;
int read_player_record(FILE *file, PlayerRecord P_record[])//读取玩家信息然后返回玩家数
{
	char name[STRING_LENGTH + 1];
	int i = 0;
	fgets(name, STRING_LENGTH + 1, file);
	while (i < MAX_PLAYERS && !feof(file))
	{
		name[strlen(name) - 1] = '\0';
		P_record[i].name = (char*)malloc(strlen(name) * sizeof(char));
		strcpy(P_record[i].name, name);
		fscanf(file, "%d %d %d %d %d %d\n", &P_record[i].games_played, &P_record[i].no_won, &P_record[i].no_lost, &P_record[i].no_drawn, &P_record[i].no_chips, &P_record[i].total_score);
		++i;
		fgets(name, STRING_LENGTH + 1, file);
	}
	P_record_count = i;
	fclose(file);
	return i;
}

void display_head()
{
	printf("File : assign.c\n");
	printf("Author : Batman\n");
	printf("This is my own work as defined by the\n");
	printf("University's Academic Misconduct Policy.\n\n\n\n\n\n");
}

void display_command()
{
	printf("Please enter command\n");
	printf("[players, buy, chips, clear, add, remove, play, scores, quit]:");
}

void display_players(PlayerRecord P_record[], int n)
{
	int i = 0;
	printf("|=========================================================|\n");
	printf("|                    Blackjack Players                    |\n");
	printf("|=========================================================|\n");
	printf("|                                                         |\n");
	printf("|  Player Name                P  W  L  D   Chips   Score  |\n");
	printf("|=========================================================|\n");
	if (n == 0)
	{
		printf("|                                                         |\n");
		printf("|                 -- No players in list --                |\n");
		printf("|                                                         |\n");
	}
	while (i < n)
	{
		printf("|  %-25s  %-2d %-2d %-2d %-2d%7d %7d  |\n", P_record[i].name, P_record[i].games_played, P_record[i].no_won, P_record[i].no_lost, P_record[i].no_drawn, P_record[i].no_chips, P_record[i].total_score);
		printf("|---------------------------------------------------------|\n");
		++i;
	}
	printf("|=========================================================|\n");
}

void buy_player_chips(PlayerRecord P_record[], int n)
{
	if (P_record_count == 0)
	{
		printf("No players in list!\n");
		return;
	}
	printf("%s currently han %d chips.\n", P_record[n].name, P_record[n].no_chips);
	int chips;
	while (1)
	{
		printf("How many chips would you like to buy? ");
		scanf("%d", &chips);
		if (chips < 1 || chips>100)
		{
			printf("You may only buy between 1-100 chips at a time!\n");
		}
		else
			break;
	}
	int i ;
	for (i = 0; i < P_record_count; ++i)
	{
		if (i == n)
		{
			P_record[i].no_chips += chips;
			break;
		}
	}
	printf("Successfully updated %s's chip balance to %d\n", P_record[i].name, P_record[i].no_chips);
}

int find_player(char name[], PlayerRecord P_record[], int n)
{
	if (n == 0)
	{
		printf("%s is not found in player list-Please add player to list first!.\n", name);
		return -1;
	}
	int i;
	for (i = 0; i < n; ++i)
	{
		if (!strcmp(name, P_record[i].name))
			break;
	}
	if (i == n)
	{
		printf("%s is not found in player list.\n",name);
			return -1;
	}
	return i;
}

int find_player_search(char name[], PlayerRecord P_record[], int n)
{
	if (n == 0)
	{
		printf("%s is not found in player list-Please add player to list first!.\n", name);
		return -1;
	}
	int i;
	for (i = 0; i < n; ++i)
	{
		if (!strcmp(name, P_record[i].name))
			break;
	}
	if (i == n)
		return -1;
	return i;
}

void Swap(PlayerRecord* P1, PlayerRecord* P2)
{
	PlayerRecord temp ;
	temp = *P1;
	*P1 = *P2;
	*P2 = temp;
}

void Sort_by_score(PlayerRecord P_record[])
{
	int i ;
	int size_record = P_record_count;
	for (i = 0; i < size_record; ++i)
	{
		for (int j = i + 1; j < size_record; ++j)
		{
			if ((P_record[i].total_score < P_record[j].total_score) || ((P_record[i].total_score == P_record[j].total_score) && (P_record[i].games_played > P_record[j].games_played)))
				Swap(&P_record[i], &P_record[j]);
		}
	}
}

void Sort_by_chips(PlayerRecord P_record[])
{
	int i;
	int size_record = P_record_count;
	for (i = 0; i < size_record; ++i)
	{
		for (int j = i + 1; j < size_record; ++j)
		{
			if ((P_record[i].no_chips < P_record[j].no_chips) || ((P_record[i].no_chips == P_record[j].no_chips) && (P_record[i].games_played > P_record[j].games_played)))
				Swap(&P_record[i], &P_record[j]);
		}
	}
}

void display_highest_chips(PlayerRecord P_record[], int n)
{
	Sort_by_chips(P_record);
	printf("Highest Chip Holder = > %s with %d chips!\n", P_record[0].name, P_record[0].no_chips);
}

int clear_player_stats(PlayerRecord P_record[], char name[], int n)
{
	int index = 0;
	if ((index = find_player(name, P_record, n)) != -1)
	{
		P_record[index].games_played = 0;
		P_record[index].no_chips = 0;
		P_record[index].no_drawn = 0;
		P_record[index].no_lost = 0;
		P_record[index].no_won = 0;
		P_record[index].total_score = 0;
		printf("Successfully cleared %s's statistics.\n", P_record[index].name);
		return 1;
	}
	else
		return 0;
}

int add_player(PlayerRecord P_record[], char name[], int *n)
{
	if (*n == MAX_PLAYERS)
	{
		printf("Player list is full - %s can not be added.\n", name);
		return -1;
	}
	int index = find_player_search(name, P_record, *n);
	if (index != -1)
	{
		printf("%s already exists in player list.\n", name);
		return 0;
	}
	else
	{
		P_record[*n].name = (char*)malloc(strlen(name) * sizeof(char));
		strcpy(P_record[*n].name, name);
		P_record[*n].games_played = 0;
		P_record[*n].no_chips = 0;
		P_record[*n].no_drawn = 0;
		P_record[*n].no_lost = 0;
		P_record[*n].no_won = 0;
		P_record[*n].total_score = 0;
		*n += 1;
		printf("Successfully added %s to player list.\n", name);
		return 1;
	}
}

int remove_player(PlayerRecord P_record[], char name[], int *n)
{
	int index = find_player_search(name, P_record, *n);
	int i;
	if (index != -1)//找到了人
	{
		for (i = index; i < *n - 1; ++i)
			P_record[i] = P_record[i + 1];
		P_record[i].name = NULL;
		P_record[i].games_played = 0;
		P_record[i].no_chips = 0;
		P_record[i].no_drawn = 0;
		P_record[i].no_lost = 0;
		P_record[i].no_won = 0;
		P_record[i].total_score = 0;
		*n = *n - 1;
		printf("Successfully removed %s from player list.", name);
		return 1;
	}
	else
		return 0;
}

void play_black_jack_games(Card card[], PlayerRecord P_record[], int n)
{
	char s = 'y';
	int result;
	int bet_mount;
	while (s == 'y')
	{
		bet_mount = 0;
		result = play_one_game(card, P_record[n].no_chips, &bet_mount);
		if (result == 3)//player win;
		{
			++P_record[n].games_played;
			++P_record[n].no_won;
			P_record[n].total_score += result;
			P_record[n].no_chips += bet_mount;
		}
		else if (result == 1)//player draw
		{
			++P_record[n].games_played;
			++P_record[n].no_drawn;
			P_record[n].total_score += result;
			P_record[n].no_chips += bet_mount;
		}
		else
		{
			++P_record[n].games_played;
			++P_record[n].no_lost;
			P_record[n].no_chips += bet_mount;
		}
		printf("Play again [y|n]? ");
		scanf("%c", &s);
		printf("\n");
	}
}

void display_high_scores(PlayerRecord P_record[], int n)
{
	Sort_by_score(P_record);
	display_players(P_record, P_record_count);
}

void write_to_file(PlayerRecord P_record[], int n)
{
	FILE *file = fopen("new_players.txt", "w");
	if (file == NULL)
	{
		printf("Can't open file\n");
		exit(1);
	}
	int i = 0;
	while (i < n )
	{
		fprintf(file, "%s\n", P_record[i].name);
		fprintf(file, "%d %d %d %d %d %d\n", P_record[i].games_played, P_record[i].no_won, P_record[i].no_lost, P_record[i].no_drawn, P_record[i].no_chips, P_record[i].total_score);
		++i;
	}
	fclose(file);
}
