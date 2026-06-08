#include <stdio.h>

// NAMING colums and rows
#define COLUMNS 42
#define ROWS 18

char grid[ROWS][COLUMNS];

// Function to clear the grid by filling it with underscores
void clear_grid() {
    int r, c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLUMNS; c++) {
            grid[r][c] = '_';
    }
}
}

void print_grid() {
    int r, c;
    printf("\n---Present Grid---\n");
    for (r = 0; r < ROWS; r++) {
        printf("|"); // Print left border
        for (c = 0; c < COLUMNS; c++) {
            printf("%c", grid[r][c]);
        }
        printf("|\n");
}
}

int main() {
    clear_grid();
    print_grid();
    return 0;
}