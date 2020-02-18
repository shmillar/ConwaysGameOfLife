//Conways Game of Life by Sam Millar.
#include <vector>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
using namespace std;

const int WIDTH = 30;
const int HEIGHT = 30;
int run_number = 1;

vector<vector<bool> > current_run;
vector<vector<bool> > next_run;

void print()
{
    cout << "Run # " << run_number << endl;
    for(int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            if(current_run[i][j] == true)
            {
                cout << "# ";
            }
            else
            {
                cout << ". ";
            }
            
        }
        cout << endl;
    }
    run_number++;
    this_thread::sleep_for(chrono::milliseconds(500));
}

int check_neighbors(int x, int y)
{
    int num_of_neighbors = 0;
    for(int i = -1; i <=1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if(x+i >= 0 && y+j >= 0 && x+i < WIDTH && y+j < HEIGHT)
            {
                if(i != 0 || j != 0)
                {
                    if(current_run[x+i][y+j] == true)
                    {
                        num_of_neighbors++;
                    }
                }
            }
        }
    }
    return num_of_neighbors;
}

bool run()
{
    int still_alive = 0;

    for(int i = 0; i < HEIGHT; i++)
    {
        for(int j = 0; j < WIDTH; j++)
        {
            if(current_run[i][j] == true)
            {
                int num_of_neighbors = check_neighbors(i,j);
                //Rule 1
                if(num_of_neighbors < 2)
                {
                    next_run[i][j] = false;
                }
                //Rule 2
                if(num_of_neighbors == 2 || num_of_neighbors == 3)
                {
                    next_run[i][j] = true;
                    still_alive++;
                }
                //Rule 3
                if(num_of_neighbors > 3)
                {
                    next_run[i][j] = false;
                }
            }
            else
            {
                int num_of_neighbors = check_neighbors(i,j);
                //Rule 4
                if(num_of_neighbors == 3)
                {
                    next_run[i][j] = true;
                    still_alive++;
                }
                else
                {
                    next_run[i][j] = false;
                }
                
            }
            
        }
    }
    current_run = next_run;
    print();
    if(still_alive == 0)
    {
        //Game Over
        return false;
    }
    return true;
}

int main()
{
    vector<bool> push;
    for(int i = 0; i < HEIGHT; i++)
    {
        current_run.push_back(push);
        next_run.push_back(push);
        for(int j = 0; j < WIDTH; j++)
        {
            current_run[i].push_back(false);
            next_run[i].push_back(false);
        }
    }
    srand(time(NULL));
    for(int k = 0; k < 250; k++)
    {
        int x = rand()%WIDTH;
        int y = rand()%HEIGHT;
        if(current_run[x][y] == true)
        {
            //already alive
            k--;
        }
        else
        {
            //dead
            current_run[x][y] = true;
        }
    }
    print();
    while(run() && run_number < 101);
}