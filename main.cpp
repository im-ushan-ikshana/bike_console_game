

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
void checkLevelPass(int value);
void draw_lv1();
// void draw_lv2();
// void draw_lv3();
// void draw_lv4();
void input();
void logic();
bool draw_bike(int draw_x, int draw_y, int currentX, int currentY);
bool draw_enemy(int draw_x, int draw_y, int currentX, int currentY);
bool isGameOver(int enemyX, int enemyY, int x, int y);
void credits();

// init-Variables
bool gameOver = true;
bool quit = false;
bool bikeCord = false;
int mapX = 60, mapY = 30;
int bike_health = 100;
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

std::string overIcon = R"(
     .d8888b.                                          .d88888b.
    d88P  Y88b                                        d88P" "Y88b
    888    888                                        888     888
    888         8888b.  88888b.d88b.   .d88b.         888     888 888  888  .d88b.  888d888
    888  88888     "88b 888 "888 "88b d8P  Y8b        888     888 888  888 d8P  Y8b 888P"
    888    888 .d888888 888  888  888 88888888 888888 888     888 Y88  88P 88888888 888
    Y88b  d88P 888  888 888  888  888 Y8b.            Y88b. .d88P  Y8bd8P  Y8b.     888
     "Y8888P88 "Y888888 888  888  888  "Y8888          "Y88888P"    Y88P    "Y8888  888
    )";

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
            gameOver = isGameOver(enemyX, enemyY, x, y);
            draw_lv1();
            input();
            logic();
            Sleep(16);
            if(gameOver){
                system("cls");
                std::cout<<"\n\n\n"<<overIcon;
                std::cout<<"\n\n\t\t\t\t\tYour Score : "<<score;
                Sleep(2000);
            }
        }
    }

    if (quit)
    {
        system("cls");
        std::cout << "\n\n\t\t##########################################\n\n\t\tProudly Presented by Programming Group 16.\n\n\t\t##########################################\n\n\n\n";
        std::cout << "\n\n"
                  << bikeObj << "\n\n";
        Sleep(1500);
        system("exit");
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

    enemyX = wallSize + rand() % static_cast<int>(mapX - ((2 * wallSize) + 2));
    enemyY = 3;
}

void menu()
{
    /*
        @return void;

        - main-menu-of-the-game
    */

    std::string menuIcon = R"(
    888b     d888          888                    .d8888b.  8888888b.
    8888b   d8888          888                   d88P  Y88b 888   Y88b
    88888b.d88888          888                   888    888 888    888
    888Y88888P888  .d88b.  888888 .d88b.         888        888   d88P
    888 Y888P 888 d88""88b 888   d88""88b        888  88888 8888888P"
    888  Y8P  888 888  888 888   888  888 888888 888    888 888
    888   "   888 Y88..88P Y88b. Y88..88P        Y88b  d88P 888
    888       888  "Y88P"   "Y888 "Y88P"          "Y8888P88 888
    )";

    system("cls");
    std::cout << "\t" << menuIcon;
    std::cout << std::endl;
    std::cout << "\t\t\t Sri-Lankan-Version" << std::endl;
    std::cout << std::endl;
    int choise;
    std::cout << "\t\t1. New Game \n\t\t2. Instructions \n\t\t3.Quit \n\n\t>>";
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
    bool condition1 = (enemyX <= x && enemyX + 7 >= x) && (enemyY <= y && enemyY + 4 >= y);
    bool condition2 = (enemyX <= x + 7 && enemyX + 7 >= x + 7) && (enemyY <= y && enemyY + 4 >= y);
    if (condition1 || condition2)
    {
        return true;
    }
    return false;
}

void checkLevelPass(int value, int level)
{
    std::string lv_1 = R"(
    db      d88888b db    db d88888b db                        db
    88      88'     88    88 88'     88                       o88
    88      88ooooo Y8    8P 88ooooo 88                        88
    88      88~~~~~ `8b  d8' 88~~~~~ 88           C8888D       88
    88booo. 88.      `8bd8'  88.     88booo.                   88
    Y88888P Y88888P    YP    Y88888P Y88888P                   VP
    )";

    std::string lv_2 = R"(
    db      d88888b db    db d88888b db                       .d888b.
    88      88'     88    88 88'     88                       VP  `8D
    88      88ooooo Y8    8P 88ooooo 88                          odD'
    88      88~~~~~ `8b  d8' 88~~~~~ 88           C8888D       .88'
    88booo. 88.      `8bd8'  88.     88booo.                  j88.
    Y88888P Y88888P    YP    Y88888P Y88888P                  888888D
    )";

    std::string lv_3 = R"(
    db      d88888b db    db d88888b db                       d8888b.
    88      88'     88    88 88'     88                       VP  `8D
    88      88ooooo Y8    8P 88ooooo 88                         oooY'
    88      88~~~~~ `8b  d8' 88~~~~~ 88           C8888D        ~~~b.
    88booo. 88.      `8bd8'  88.     88booo.                  db   8D
    Y88888P Y88888P    YP    Y88888P Y88888P                  Y8888P'
    )";

    if (value <= 100 && level == 1)
    {
        level++;
    }
    if (value <= 200 && level == 2){
        level++;
    }
    if (value <= 300 && level == 3){
        level++;
    }
    if(level == 4){
        credits();
    }
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

void credits(){
    std::cout<<"Ushan Ikshana";
}