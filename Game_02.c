#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
//Playing field size
#define width 65
#define height 25

// Structure Racket
typedef struct{
    int x, y;
    int w;
} TRacket;
// Structure Ball
typedef struct{
    float x, y;
    int ix, iy;
    float alpha;
    float speed;
} TBall;


// Field in matrix
char mas[height][width+1];
// Creating objects racket, ball
TRacket racket;
TBall ball;
// Creating var hitCnt, maxHitCnt
int hitCnt = 0;
int maxHitCnt = 0;


// Add ball in matrix
void putBall(){
    mas[ball.iy][ball.ix] = '*';
}

// Movement of ball
void moveBall(float x, float y){
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

// Initialization ball
void initBall(){
    moveBall(2,2);
    ball.alpha = -1;
    ball.speed = 0.5;
}



// Auto movement of ball
void autoMoveBall(){
    if (ball.alpha < 0) ball.alpha += M_PI*2;
    if (ball.alpha > M_PI*2) ball.alpha -= M_PI*2;

    TBall bl = ball;

    moveBall(ball.x + cos(ball.alpha) * ball.speed
             ,ball.y + sin(ball.alpha) * ball.speed);

    if ((mas[ball.iy][ball.ix] == '#') || (mas[ball.iy][ball.ix] == '@'))
    {
        if (mas[ball.iy][ball.ix] == '@')
            hitCnt+=1;
        if ((ball.ix != bl.ix) && (ball.iy != bl.iy))
        {
            if (mas[bl.iy][ball.ix] == mas[ball.iy][bl.ix])
                bl.alpha = bl.alpha + M_PI;
            else
            {
                if (mas[bl.iy][ball.ix] == '#')
                    bl.alpha = (2*M_PI - bl.alpha) + M_PI;
                else
                    bl.alpha = (2*M_PI - bl.alpha);
            }
        }
        else if (ball.iy == bl.iy)
            bl.alpha = (2*M_PI - bl.alpha) + M_PI;
        else
            bl.alpha = (2*M_PI - bl.alpha);


        ball = bl;
        autoMoveBall();
    }


}

// Initialization racket
void initRacket(){
    racket.w = 7;
    racket.x = (width - racket.w) / 2;
    racket.y = height - 1;
}

// Add racket in matrix
void putRacket(){
    for (int i=racket.x; i<racket.x+racket.w; i++)
        mas[racket.y][i] = '@';
}

// Initialization field
void init(){
    for(int i=0; i<width; i++)
        mas[0][i] = '#';
    mas[0][width] = '\0';

    strncpy(mas[1], mas[0], width+1);
    for(int i=1; i<width-1; i++)
        mas[1][i] = ' ';

    for(int i=2; i<height; i++)
        strncpy(mas[i], mas[1], width+1);
}

// Drawing field
void show(){
    for(int i=0; i<height; i++)
    {
        printf("%s", mas[i]);
        if (i == 3)
            printf("  hit %i    ", hitCnt);
        if (i == 4)
            printf("  max %i    ", maxHitCnt);
        if (i < height - 1)
            printf("\n");
    }
    //moveBall(racket.x + racket.w/2, racket.y-1);
}
// Movement of racket
void moveRacket(int x){
    racket.x = x;
    if (racket.x + racket.w >= width)
        racket.x = width-1-racket.w;
    if(racket.x < 1)
        racket.x = 1;
}
// Set a cursor position
// Need to prevent screen from flickering
void setcur(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Main func
int main()
{
    // If ball on racket - false (at start on racket)
    BOOL run = FALSE;
    // At first init ball and racket
    initRacket();
    initBall();
    // After start loop, where:
    do
    {
        // Set cur pos at top left cornet
        setcur(0,0);
        if (run)
            autoMoveBall();
        if (ball.iy > height)
        {
            run = FALSE;
            if (hitCnt > maxHitCnt)
                maxHitCnt = hitCnt;
            hitCnt = 0;
        }
        // Init field
        init();
        // Adding in field racket, ball
        putRacket();
        putBall();
        // Show field
        show();
        // Push test of keys
        if (GetKeyState('A') < 0) moveRacket(racket.x - 1);
        if (GetKeyState('D') < 0) moveRacket(racket.x + 1);
        if (GetKeyState('W') < 0) run = TRUE;
        // At start ball should be on racket
        if (!run)
            moveBall(racket.x + racket.w / 2, racket.y-1);
        // Its so fast, so it need sleep
        Sleep(10);

    }
    // Stop loop
    while (GetKeyState(VK_ESCAPE) >= 0);

    return 0;
}
