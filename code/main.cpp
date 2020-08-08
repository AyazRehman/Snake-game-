
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>

using namespace std;

void print_game(int board_width, int board_length, int snake[][2], int fruit[2], int snake_length, int score);//Function that prints board and snake
void input(char& direction);// Function that takes input from user
bool check_member_of_aray(int snake[][2],int first, int second, int start_index, int end_index);// Function returns true if x and y coordinates of snake lies in snake array
int process(int board_width, int board_length, int snake[][2], int& snake_length, int fruit[2], int& score, int direction);// Function containing all the logic of the game
void snake_movement(int snake[][2], int snake_length, int x, int y);//Function that moves the snake

int main()
{
    srand(time(NULL));
    int board_width = 30;
    int board_length = 20;
    bool game_over = false;
    int score = 0;
    char direction = 'n';
    int snake_length = 2;
    int snake[board_width*board_length][2] = {{(board_width)/2, board_length/2},{((board_width)/2)-1, board_length/2}};
    int fruit[2];
    do
    {
        fruit[0] = (rand()%(board_width-2))+1;
        fruit[1] = (rand()%(board_length-2))+1;
    }
    while(check_member_of_aray(snake, fruit[0], fruit[1], 0, snake_length-1));
    while(!game_over)
    {
        print_game(board_width, board_length, snake, fruit, snake_length, score);
        input(direction);
        game_over = process(board_width, board_length, snake, snake_length, fruit, score, direction);
        Sleep(20);
    }
    Sleep(1000);
    return 0;
}

void print_game(int board_width, int board_length, int snake[][2], int fruit[2], int snake_length, int score)
{
    string frame = "";
    system("cls");
    cout << "Snake" << endl;
    cout << "Score = " << score << endl;
    for(int y = 0; y<=board_length-1; y++)
    {
        frame += "                        ";
        if (y == 0 || y == board_length-1 )
        {
            for(int x = 0; x<=board_width-1; x++)
            {
                frame += "=";
            }
        }
        else
        {
            for(int x = 0; x<= board_width-1; x++)
            {
                if (x == 0 || x == board_width-1 )
                {
                    frame += "=";
                }
                else//snake here
                {
                    if(check_member_of_aray(snake, x, y, 0, snake_length-1))
                    {
                        frame += "+";
                    }
                    else if(fruit[0] == x && fruit[1] == y)
                    {
                        frame += "o";
                    }
                    else
                    {
                        frame += " ";
                    }
                }
            }
        }
        frame += "\n";
    }
    cout << frame;
}
void input(char& direction)
{
    if (kbhit())
    {
        switch(getch())
        {
            case 'a':
                if(direction == 'r')
                {
                    break;
                }
                direction = 'l';
                break;
            case 's':
                if(direction == 'u')
                {
                    break;
                }
                direction = 'd';
                break;
            case 'd':
                if(direction == 'l')
                {
                    break;
                }
                direction = 'r';
                break;
            case 'w':
                if(direction == 'd')
                {
                    break;
                }
                direction = 'u';
                break;
        }
        return;
    }
}
bool check_member_of_aray(int snake[][2],int first, int second, int start_index, int end_index)
{
    for(int i = start_index; i <= end_index; i++)
    {
        if(snake[i][0] == first && snake[i][1] == second)
        {
            return true;
        }
    }
    return false;
}
int process(int board_width, int board_length, int snake[][2], int& snake_length, int fruit[2], int& score, int direction)
{
    switch(direction)
    {
        case 'l':
            snake_movement(snake, snake_length,-1,0);
            break;
        case 'd':
            snake_movement(snake, snake_length,0,1);
            break;
        case 'r':
            snake_movement(snake, snake_length,1,0);
            break;
        case 'u':
            snake_movement(snake, snake_length,0,-1);
            break;
    }
    if(snake[0][0] == 0)
    {
        snake[0][0] = snake[0][0]+(board_width-2);
    }
    if(snake[0][0] == board_width-1)
    {
        snake[0][0] = snake[0][0]-(board_width-2);
    }
    if(snake[0][1] == 0)
    {
        snake[0][1] = snake[0][1]+(board_length-2);
    }
    if(snake[0][1] == board_length-1)
    {
        snake[0][1] = snake[0][1]-(board_length-2);
    }
    if(snake[0][0] == fruit[0] && snake[0][1] == fruit[1])
    {
        score++;
        snake_length++;
        snake[snake_length-1][0] = snake[snake_length-2][0];
        snake[snake_length-1][1] = snake[snake_length-2][1];
        do
        {
            fruit[0] = (rand()%(board_width-2))+1;
            fruit[1] = (rand()%(board_length-2))+1;
        }
        while(check_member_of_aray(snake, fruit[0], fruit[1], 0, snake_length-1));
    }
    if(check_member_of_aray(snake, snake[0][0], snake[0][1], 1, snake_length-1))
    {
        return 1;
    }
    return 0;
}
void snake_movement(int snake[][2], int snake_length, int x, int y)
{
    for(int i = snake_length-1; i > 0; i--)
    {
        snake[i][0] = snake[i-1][0];
        snake[i][1] = snake[i-1][1];
    }
    snake[0][0] = snake[0][0]+x;
    snake[0][1] = snake[0][1]+y;
}
