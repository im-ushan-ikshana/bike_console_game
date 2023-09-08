

//  d8888b.  .d88b.  db    db d8b   db  .o88b. d88888b
//  88  `8D .8P  Y8. 88    88 888o  88 d8P  Y8 88'
//  88oooY' 88    88 88    88 88V8o 88 8P      88ooooo
//  88~~~b. 88    88 88    88 88 V8o88 8b      88~~~~~
//  88   8D `8b  d8' 88b  d88 88  V888 Y8b  d8 88.
//  Y8888P'  `Y88P'  ~Y8888P' VP   V8P  `Y88P' Y88888P
//
//                    The-Bike-Game

// include-additional libraries

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <string>
#include <cstring>

// init-other-functions

void setup();
void menu();
void draw_lv1();
// void draw_lv2();
// void draw_lv3();
// void draw_lv4();
void input();
void logic();
bool draw_bike(int draw_x, int draw_y, int currentX, int currentY);
bool draw_enemy(int draw_x, int draw_y, int currentX, int currentY);
bool isGameOver(int enemyX, int enemyY, int x, int y);


// init-Variables
bool gameOver = true;
bool quit = false;
bool bikeCord = false;
int mapX = 60, mapY = 30;
int x, y;
int enemyX, enemyY;
int levelPass = 1;
int wallSize = 3;
int score = 0;
enum eDirect
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirect dir;
int spawnX = 5;
int spawnY = mapY / 2;

// Game-objects-enemies-and-traps;
std::string ballObj = "@";
std::string spidObj =
    "  / _ \\\n"
    "\\_\\(_)/_/\n"
    " _//\"\\\\_ \n"
    "  /   \\  \n";

std::string trapObj = "/\\";

std::string bikeObj =
    "                      ;~\\.\n"
    "        .              _._\\\")\n"
    "        I\\___        ,;)))}^\\\n"
    "        I `%%^\\%%%%.::q::    `\\.\n"
    "      .*//*.    OOO  }}} ))    .\\8^8*.\n"
    "   =LIEF()ZIMMERMAN(((((()'    --(*)--\n"
    "      \"*oo*\"                   \"*ooo*\"\n";

// the-main-method

int main()
{

    while (!quit)
    {
        setup();
        while (gameOver && !quit)
        {
            menu();
        }
        while (!gameOver)
        {
            draw_lv1();
            input();
            logic();
            gameOver = isGameOver(enemyX,enemyY,x,y);
            Sleep(16);
        }
    }

    if (quit)
    {
        system("cls");
        std::cout << "\n\n\t\t##########################################\n\n\t\tProudly Presented by Programming Group 16.\n\n\t\t##########################################\n\n\n\n";
        std::cout << "\n\n"
                  << bikeObj << "\n\n";
    }

    return 0;
}

// functions

void setup()
{
    /*
        @return void
        - health
        - postiton
        - points
        - stars (+2 points)
        - animated-objects
        - objects
        - traps (-100 health)
    */

    int health = 100;
    x = mapX / 2;
    y = mapY / 2;

    enemyX = wallSize + rand() % static_cast<int>(mapX - (2 * wallSize));
    enemyY = 3;
}

void menu()
{
    /*
        @return void;

        - main-menu-of-the-game
    */

    std::string menuIcon =
        "\n\n\n  d8888b.  .d88b.  db    db d8b   db  .o88b. d88888b \n"
        "  88  `8D .8P  Y8. 88    88 888o  88 d8P  Y8 88'     \n"
        "  88oooY' 88    88 88    88 88V8o 88 8P      88ooooo \n"
        "  88~~~b. 88    88 88    88 88 V8o88 8b      88~~~~~ \n"
        "  88   8D `8b  d8' 88b  d88 88  V888 Y8b  d8 88.     \n"
        "  Y8888P'  `Y88P'   Y8888P' VP   V8P  `Y88P' Y88888P \n"
        "                                                     \n"
        "                    The-bike-game                  \n";

    std::string overIcon =
        "  dP\"\"b8    db    8b    d8 888888      dP\"Yb  Yb    dP 888888 88\"\"Yb \n"
        " dP   `\"   dPYb   88b  d88 88__       dP   Yb  Yb  dP  88__   88__dP \n"
        " Yb  \"88  dP__Yb  88YbdP88 88\"\"       Yb   dP   YbdP   88\"\"   88\"Yb  \n"
        "  YboodP dP\"\"\"\"Yb 88 YY 88 888888      YbodP     YP    888888 88  Yb \n";

    system("cls");
    std::cout << menuIcon;
    std::cout << std::endl;
    std::cout << std::endl;
    int choise;
    std::cout << "1. New Game \n2. Instructions \n3.Quit \n\n";
    std::cin >> choise;

    if (choise == 1)
        gameOver = false;
    else if (choise == 3)
        quit = true;
    else
    {
        system("cls");
        std::cout << "\n\n\n\n\t----Instructions----\n";
        std::cout << "\t01. W - for Jump. \n";
        std::cout << "\t02. S - for Instant Down. \n";
        std::cout << "\t03. A - for Going Left. \n";
        std::cout << "\t04. D - for Going Right. \n";
        std::cout << "\t05. X - for Froce Stop and Quit Game; ";

        std::cout << "\n\nFor quit : 1 \nFor New Game : 2 \n\n  Answer : ";
        std::cin >> choise;
        if (choise == 1)
        {
            quit = true;
        }
        else if (choise == 2)
        {
            quit = false;
            gameOver = false;
        }
        else
        {
            std::cout << "Invalid Input : Default Opstion is choosen quit.";
            quit = true;
        }
    }
}

bool isGameOver(int enemyX, int enemyY, int x, int y)
{
    if (enemyY + 4 == y && enemyX + 7 >= x)
    {
        return true;
    }
    return false;
}

void draw_lv1()
{
    system("cls");

    // upper-map-frame
    for (int i = 0; i <= mapX; i++)
        std::cout << "#";
    std::cout << std::endl;

    // draw-middle-part
    for (int i = 0; i < mapY; i++)
    {
        // for (int j = 0; j <= mapX; j++)
        // {
        //     if (j == 0)
        //     {
        //         std::cout << "#";
        //     }
        //     if (j == mapX)
        //     {
        //         std::cout << "#";
        //     }
        //     else
        //     {
        //         std::cout << " ";
        //     }
        // }
        // std::cout << std::endl;

        for (int j = 0; j < mapX; j++)
        {
            if (j < wallSize)
            {
                std::cout << "#";
            }
            if (j >= (mapX - wallSize))
            {
                std::cout << "#";
            }
            if (j == wallSize)
            {
                std::cout << " ";
            }
            if (draw_bike(x, y, j, i) || draw_enemy(enemyX, enemyY, j, i))
            {
                std::cout << "#";
            }
            else if (j >= wallSize && j < (mapX - wallSize))
            {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    // lower-map-frame
    for (int i = 0; i <= mapX; i++)
        std::cout << "#";
    std::cout << std::endl;
}

void input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            quit = true;
            break;
        }
    }
}

void logic()
{
    switch (dir)
    {
    case LEFT:
        x = x - 2;
        break;
    case RIGHT:
        x = x + 2;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    if (x >= mapX - (wallSize + 8))
        x = wallSize;
    else if (x < wallSize)
        x = (mapX - wallSize - 8);
    if (y >= mapY)
        y = 0;
    else if (y < 0)
        y = mapY - 1;

    enemyY = enemyY + 2;
    if (enemyY > mapY)
    {
        enemyY = 0;
    }
}

bool draw_bike(int draw_x, int draw_y, int currentX, int currentY)
{
    if (currentX <= (draw_x + 7) && currentY <= (draw_y + 4))
    {
        if (currentX == draw_x + 3 && currentY == draw_y)
        {
            return true;
        }
        if (currentX == draw_x + 4 && currentY == draw_y)
        {
            return true;
        }
        if (currentX == draw_x && currentY == draw_y + 1)
        {
            return true;
        }
        if (currentX == draw_x + 1 && currentY == draw_y + 1)
        {
            return true;
        }
        if (currentX == draw_x + 3 && currentY == draw_y + 1)
        {
            return true;
        }
        if (currentX == draw_x + 4 && currentY == draw_y + 1)
        {
            return true;
        }
        if (currentX == draw_x + 6 && currentY == draw_y + 1)
        {
            return true;
        }
        if (currentX == draw_x + 7 && currentY == draw_y + 1)
        {
            return true;
        }
        if (currentX == draw_x + 3 && currentY == draw_y + 2)
        {
            return true;
        }
        if (currentX == draw_x + 4 && currentY == draw_y + 2)
        {
            return true;
        }
        if (currentX == draw_x + 3 && currentY == draw_y + 3)
        {
            return true;
        }
        if (currentX == draw_x + 4 && currentY == draw_y + 3)
        {
            return true;
        }
        if (currentX == draw_x && currentY == draw_y + 4)
        {
            return true;
        }
        if (currentX == draw_x + 1 && currentY == draw_y + 4)
        {
            return true;
        }
        if (currentX == draw_x + 6 && currentY == draw_y + 4)
        {
            return true;
        }
        if (currentX == draw_x + 7 && currentY == draw_y + 4)
        {
            return true;
        }
        return false;
    }
    return false;
}

bool draw_enemy(int draw_x, int draw_y, int currentX, int currentY)
{
    if (currentX <= (draw_x + 7) && currentY <= (draw_y + 4))
    {
        if (currentX == draw_x && currentY == draw_y)
        {
            return true;
        }
        if (currentX == draw_x + 1 && currentY == draw_y)
        {
            return true;
        }
        if (currentX == draw_x + 6 && currentY == draw_y)
        {
            return true;
        }
        if (currentX == draw_x + 7 && currentY == draw_y)
        {
            return true;
        }
        if (currentX == draw_x + 3 && currentY == draw_y + 1)
        {
            return true;
        }
        if (currentX == draw_x + 4 && currentY == draw_y + 1)
        {
            return true;
        }
        if (currentX == draw_x + 3 && currentY == draw_y + 2)
        {
            return true;
        }
        if (currentX == draw_x + 4 && currentY == draw_y + 2)
        {
            return true;
        }
        if (currentX == draw_x && currentY == draw_y + 3)
        {
            return true;
        }
        if (currentX == draw_x + 1 && currentY == draw_y + 3)
        {
            return true;
        }
        if (currentX == draw_x + 3 && currentY == draw_y + 3)
        {
            return true;
        }
        if (currentX == draw_x + 4 && currentY == draw_y + 3)
        {
            return true;
        }
        if (currentX == draw_x + 6 && currentY == draw_y + 3)
        {
            return true;
        }
        if (currentX == draw_x + 7 && currentY == draw_y + 3)
        {
            return true;
        }
        if (currentX == draw_x + 3 && currentY == draw_y + 4)
        {
            return true;
        }
        if (currentX == draw_x + 4 && currentY == draw_y + 4)
        {
            return true;
        }
        return false;
    }
    return false;
}