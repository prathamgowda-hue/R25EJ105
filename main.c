#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Canvas size
#define HEIGHT 20
#define WIDTH 60
#define MAX_SHAPES 50

// Drawing area
char screen[HEIGHT][WIDTH];

// Shape information
typedef struct
{
    int type;   // 1-Rectangle 2-Line 3-Triangle 4-Circle
    int a, b, c, d;
} Object;

// Store all objects
Object objects[MAX_SHAPES];
int objectCount = 0;

// Clear the screen
void clearScreen()
{
    for(int row = 0; row < HEIGHT; row++)
    {
        for(int col = 0; col < WIDTH; col++)
        {
            screen[row][col] = '_';
}
}
}

// Display the screen
void showScreen()
{
    for(int row = 0; row < HEIGHT; row++)
    {
        for(int col = 0; col < WIDTH; col++)
        {
            printf("%c", screen[row][col]);
        }
        printf("\n");
}
}

// Draw rectangle
void drawRect(int x, int y, int width, int height)
{
    for(int row = y; row < y + height && row < HEIGHT; row++)
    {
        for(int col = x; col < x + width && col < WIDTH; col++)
        {
            if(row == y || row == y + height - 1 ||
               col == x || col == x + width - 1)
            {
                screen[row][col] = '*';
            }
    }
}
}

// Draw line using Bresenham algorithm
void drawLineShape(int startX, int startY, int endX, int endY)
{
    int dx = abs(endX - startX);
    int dy = abs(endY - startY);

    int stepX = (startX < endX) ? 1 : -1;
    int stepY = (startY < endY) ? 1 : -1;

    int error = dx - dy;

    while(1)
    {
        if(startX >= 0 && startX < WIDTH &&
           startY >= 0 && startY < HEIGHT)
        {
            screen[startY][startX] = '*';
        }

        if(startX == endX && startY == endY)
            break;

        int temp = 2 * error;

        if(temp > -dy)
        {
            error -= dy;
            startX += stepX;
        }

        if(temp < dx)
        {
            error += dx;
            startY += stepY;
        }
    }
}

// Draw triangle
void drawTri(int centerX, int topY, int height)
{
    for(int i = 0; i < height; i++)
    {
        if(topY + i < HEIGHT)
        {
            if(centerX - i >= 0)
                screen[topY + i][centerX - i] = '*';

            if(centerX + i < WIDTH)
                screen[topY + i][centerX + i] = '*';
        }
    }

    drawLineShape(centerX - height + 1,
                  topY + height - 1,
                  centerX + height - 1,
                  topY + height - 1);
}

// Draw circle
void drawCircleShape(int centerX, int centerY, int radius)
{
    for(int row = 0; row < HEIGHT; row++)
    {
        for(int col = 0; col < WIDTH; col++)
        {
            int dx = col - centerX;
            int dy = row - centerY;

            double distance = sqrt(dx * dx + dy * dy);

            if(distance >= radius - 0.5 &&
               distance <= radius + 0.5)
            {
                screen[row][col] = '*';
            }
        }
    }
}

// Redraw all objects
void refreshScreen()
{
    clearScreen();

    for(int i = 0; i < objectCount; i++)
    {
        switch(objects[i].type)
        {
            case 1:
                drawRect(objects[i].a,
                         objects[i].b,
                         objects[i].c,
                         objects[i].d);
                break;

            case 2:
                drawLineShape(objects[i].a,
                              objects[i].b,
                              objects[i].c,
                              objects[i].d);
                break;

            case 3:
                drawTri(objects[i].a,
                        objects[i].b,
                        objects[i].c);
                break;

            case 4:
                drawCircleShape(objects[i].a,
                                objects[i].b,
                                objects[i].c);
                break;
        }
    }
}

// Show all objects
void showObjects()
{
    printf("\nObjects List:\n");

    for(int i = 0; i < objectCount; i++)
    {
        printf("%d. ", i + 1);

        switch(objects[i].type)
        {
            case 1:
                printf("Rectangle\n");
                break;

            case 2:
                printf("Line\n");
                break;

            case 3:
                printf("Triangle\n");
                break;

            case 4:
                printf("Circle\n");
                break;
        }
    }

    if(objectCount == 0)
    {
        printf("No objects available.\n");
    }
}

// Remove an object
void removeObject(int index)
{
    if(index < 0 || index >= objectCount)
    {
        printf("Invalid object number!\n");
        return;
    }

    for(int i = index; i < objectCount - 1; i++)
    {
        objects[i] = objects[i + 1];
    }

    objectCount--;
    refreshScreen();
}

// Edit an object
void editObject(int index)
{
    if(index < 0 || index >= objectCount)
    {
        printf("Invalid object number!\n");
        return;
    }

    Object *obj = &objects[index];

    switch(obj->type)
    {
        case 1:
            printf("Enter new x y width height: ");
            scanf("%d%d%d%d",
                  &obj->a, &obj->b,
                  &obj->c, &obj->d);
            break;

        case 2:
            printf("Enter new x1 y1 x2 y2: ");
            scanf("%d%d%d%d",
                  &obj->a, &obj->b,
                  &obj->c, &obj->d);
            break;

        case 3:
            printf("Enter new x y height: ");
            scanf("%d%d%d",
                  &obj->a, &obj->b,
                  &obj->c);
            break;

        case 4:
            printf("Enter new center_x center_y radius: ");
            scanf("%d%d%d",
                  &obj->a, &obj->b,
                  &obj->c);
            break;
    }

    refreshScreen();
}

int main()
{
    int choice;

    clearScreen();

    while(1)
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");
        printf("1. Add Rectangle\n");
        printf("2. Add Line\n");
        printf("3. Add Triangle\n");
        printf("4. Add Circle\n");
        printf("5. Delete Object\n");
        printf("6. Modify Object\n");
        printf("7. List Objects\n");
        printf("8. Display Canvas\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if(choice == 0)
            break;

        Object newObj;
        int objectNumber;

        switch(choice)
        {
            case 1:
                newObj.type = 1;
                printf("Enter x y width height: ");
                scanf("%d%d%d%d",
                      &newObj.a, &newObj.b,
                      &newObj.c, &newObj.d);

                objects[objectCount++] = newObj;
                refreshScreen();
                break;

            case 2:
                newObj.type = 2;
                printf("Enter x1 y1 x2 y2: ");
                scanf("%d%d%d%d",
                      &newObj.a, &newObj.b,
                      &newObj.c, &newObj.d);

                objects[objectCount++] = newObj;
                refreshScreen();
                break;

            case 3:
                newObj.type = 3;
                printf("Enter x y height: ");
                scanf("%d%d%d",
                      &newObj.a, &newObj.b,
                      &newObj.c);

                objects[objectCount++] = newObj;
                refreshScreen();
                break;

            case 4:
                newObj.type = 4;
                printf("Enter center_x center_y radius: ");
                scanf("%d%d%d",
                      &newObj.a, &newObj.b,
                      &newObj.c);

                objects[objectCount++] = newObj;
                refreshScreen();
                break;

            case 5:
                showObjects();
                printf("Enter object number to delete: ");
                scanf("%d", &objectNumber);

                removeObject(objectNumber - 1);
                break;

            case 6:
                showObjects();
                printf("Enter object number to modify: ");
                scanf("%d", &objectNumber);

                editObject(objectNumber - 1);
                break;

            case 7:
                showObjects();
                break;

            case 8:
                showScreen();
                break;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}