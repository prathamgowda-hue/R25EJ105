#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 40
#define HEIGHT 16
#define MAX_ITEMS 40

typedef enum { LN, RT, TR, CR } Type;

typedef struct {
    int key;
    Type form;
    int x1, y1; 
    int x2, y2; 
    int x3, y3; 
    int r; 
    int live; 
} Item;

char canvas[HEIGHT][WIDTH];
Item list[MAX_ITEMS];
int total = 0;
int count_id = 1;

void reset_canvas() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            canvas[i][j] = '_';
        }
    }
}

void show_canvas() {
    printf("\n--- Visual Canvas ---\n");
    for (int i = 0; i < HEIGHT; i++) {
        printf("|"); 
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("|\n");
}
}

void put_mark(int px, int py) {
    if (px >= 0 && px < WIDTH && py >= 0 && py < HEIGHT) {
        canvas[py][px] = '*';
}
}

void make_line(int xa, int ya, int xb, int yb) {
    int w = abs(xb - xa), sx = xa < xb ? 1 : -1;
    int h = -abs(yb - ya), sy = ya < yb ? 1 : -1;
    int rem = w + h, step;
    while (1) {
        put_mark(xa, ya);
        if (xa == xb && ya == yb) break;
        step = 2 * rem;
        if (step >= h) { rem += h; xa += sx; }
        if (step <= w) { rem += w; ya += sy; }
}
}

void make_circle(int cx, int cy, int rad) {
    int x = 0, y = rad;
    int p = 3 - 2 * rad;
    while (y >= x) {
        put_mark(cx + x, cy + y); put_mark(cx - x, cy + y);
        put_mark(cx + x, cy - y); put_mark(cx - x, cy - y);
        put_mark(cx + y, cy + x); put_mark(cx - y, cy + x);
        put_mark(cx + y, cy - x); put_mark(cx - y, cy - x); x++;
        if (p > 0) { y--; p = p + 4 * (x - y) + 10; }
        else { p = p + 4 * x + 6; }}
}

int main() {
    reset_canvas();
    show_canvas();
    return 0;
}