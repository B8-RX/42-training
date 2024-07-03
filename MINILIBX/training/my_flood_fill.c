#include <stdio.h>
#include <stdbool.h>

bool	is_target_color(int screen[][6], int row, int col, int x, int y, int target_color, int new_color)
{
	if (x < 0 || x >= row || y < 0 || y >= col || screen[x][y] != target_color || screen[x][y] == new_color)
		return (0);
	return (1);
}

void	flood_fill(int screen[][6], int row, int col, int x, int y, int target_color, int new_color)
{
	typedef struct {
		int x;
		int y;
	} Pair;

	Pair queue[36];
	int front;
	int tail;

	front = 0;
	tail = 0;
	queue[tail++] = (Pair){x, y};
	screen[x][y] = new_color;
	while (front < tail)
	{
		Pair current_pos = queue[front++];
		int pos_x = current_pos.x;
		int pos_y = current_pos.y;

		if(is_target_color(screen, row, col, pos_x + 1, pos_y, target_color, new_color))
		{
			queue[tail++] = (Pair){pos_x + 1, pos_y};
			screen[pos_x + 1][pos_y] = new_color;
		}
		if(is_target_color(screen, row, col, pos_x - 1, pos_y, target_color, new_color))
		{
			queue[tail++] = (Pair){pos_x - 1, pos_y};
			screen[pos_x - 1][pos_y] = new_color;
		}
		if(is_target_color(screen, row, col, pos_x, pos_y + 1, target_color, new_color))
		{
			queue[tail++] = (Pair){pos_x, pos_y + 1};
			screen[pos_x][pos_y + 1] = new_color;
		}
		if(is_target_color(screen, row, col, pos_x, pos_y - 1, target_color, new_color))
		{
			queue[tail++] = (Pair){pos_x, pos_y - 1};
			screen[pos_x][pos_y - 1] = new_color;
		}
	}
}


int	main(void)
{
	int screen[8][6] = { 
		{ 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 1, 1, 0 },
		{ 1, 2, 2, 2, 2, 0 },
		{ 1, 1, 1, 2, 2, 0 },
		{ 1, 1, 1, 2, 2, 2 },
		{ 1, 1, 1, 2, 2, 2 },
		{ 1, 1, 1, 2, 1, 2 }
	};
	int i = 0;
	int j = 0;
	int col = 6;
	int row = 8;
	while (i < row)
	{
		while (j < col)
		{
			printf("%d ", screen[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}


	int x, y, c;

	x = 3;
	y = 3;
	c = 8;
	flood_fill(screen, row, col, x, y, screen[x][y], c);

	i = 0;
	j = 0;
	printf("UPDATED SCREEN\n");
	while (i < row)
	{
		while (j < col)
		{
			printf("%d ", screen[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}

	

	return (0);
}
