#include <stdio.h>
#include <stdbool.h>

// Function that returns true if the given pixel is valid
bool isValid(int screen[][8], int m, int n, int x, int y, int prevC, int newC) {
    if (x < 0 || x >= m || y < 0 || y >= n || screen[x][y] != prevC || screen[x][y] == newC)
        return false;
    return true;
}

// Structure to store coordinates of the screen
typedef struct {
    int x, y;
} Pair;

// FloodFill function
void floodFill(int screen[][8], int m, int n, int x, int y, int prevC, int newC) {
    // Create a queue for flood fill using an array
    Pair queue[64]; // Maximum size of the queue (8x8 grid)
    int front = 0, rear = 0;

    // Append the position of starting pixel of the component
    Pair p = {x, y};
    queue[rear++] = p;

    // Color the pixel with the new color
    screen[x][y] = newC;

    // While the queue is not empty
    while (front < rear) {
        // Dequeue the front node
        Pair currPixel = queue[front++];
        int posX = currPixel.x;
        int posY = currPixel.y;
		printf("loop: %d\n", front);
		printf("posX: %d\n", posX);
		printf("posY: %d\n", posY);
		printf("\n");

        // Check if the adjacent pixels are valid
        if (isValid(screen, m, n, posX + 1, posY, prevC, newC)) {
            screen[posX + 1][posY] = newC;
            queue[rear++] = (Pair){posX + 1, posY};
        }
        if (isValid(screen, m, n, posX - 1, posY, prevC, newC)) {
            screen[posX - 1][posY] = newC;
            queue[rear++] = (Pair){posX - 1, posY};
        }
        if (isValid(screen, m, n, posX, posY + 1, prevC, newC)) {
            screen[posX][posY + 1] = newC;
            queue[rear++] = (Pair){posX, posY + 1};
        }
        if (isValid(screen, m, n, posX, posY - 1, prevC, newC)) {
            screen[posX][posY - 1] = newC;
            queue[rear++] = (Pair){posX, posY - 1};
        }
    }
}

int main() {
    int screen[8][8] = {
        { 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 0, 0 },
        { 1, 0, 0, 1, 1, 0, 1, 1 },
        { 1, 2, 2, 2, 2, 0, 1, 0 },
        { 1, 1, 1, 2, 2, 0, 1, 0 },
        { 1, 1, 1, 2, 2, 2, 2, 0 },
        { 1, 1, 1, 1, 1, 2, 1, 1 },
        { 1, 1, 1, 1, 1, 2, 2, 1 }
    };

    // Row of the display
    int m = 8;

    // Column of the display
    int n = 8;

    // Co-ordinate provided by the user
    int x = 4;
    int y = 4;

    // Current color at that co-ordinate
    int prevC = screen[x][y];

    // New color that has to be filled
    int newC = 3;
    floodFill(screen, m, n, x, y, prevC, newC);

    // Printing the updated screen
    printf("Updated screen:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", screen[i][j]);
        }
        printf("\n");
    }

    return 0;
}
