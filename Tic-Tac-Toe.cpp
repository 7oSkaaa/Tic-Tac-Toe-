#include <bits\stdc++.h>
using namespace std;
#include<conio.h>
#include <windows.h>
#define C GetStdHandle(STD_OUTPUT_HANDLE)


int typeWait = 10; 																		
DWORD WINAPI typingThread(LPVOID lpParameter){
        char *msg = (char *)lpParameter;
        int i;
        for(i=0; msg[i]!='\0'; i++)														
        {
            cout << msg[i];
            cout.flush();																	
            Sleep(typeWait);																 
        }
        return 0;
}

HANDLE typeMessage(string &msg, HANDLE h){
    if(h!=0)
        WaitForSingleObject(h, INFINITE); 
    LPVOID lpString = (LPVOID)msg.c_str();
    HANDLE myHandle = CreateThread(0, 0, typingThread, lpString, 0, 0);
    return myHandle;
}

struct Game {
    vector < string > grid;
    Game(){
        grid.assign(3, string(3, '.'));
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                grid[i][j] = (j + 1 + i * 3) + '0';
    }
};

char Winner(Game& g){
    char w = 'c';
    bool row = false, col = false;
    for(int i = 0; i < 3; i++){
        row |= (g.grid[i][0] == g.grid[i][1] && g.grid[i][1] == g.grid[i][2]);
        if(row) return g.grid[i][0];
    }
    for(int i = 0; i < 3; i++){
        col |= (g.grid[0][i] == g.grid[1][i] && g.grid[1][i] == g.grid[2][i]);
        if(col) return g.grid[0][i];
    }
    if(g.grid[0][0] == g.grid[1][1] && g.grid[1][1] == g.grid[2][2]) w = g.grid[0][0];
    if(g.grid[2][0] == g.grid[1][1] && g.grid[1][1] == g.grid[0][2]) w = g.grid[0][2];
    if(w != 'c') return w;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(g.grid[i][j] >= '1' && g.grid[i][j] <= '9') return 'c';
    return w = 'd';
}

bool play(int num, char p, Game& g){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(g.grid[i][j] == num + '0'){
                g.grid[i][j] = p;
                return true;
            }
    if(num > 9 || num < 1) cout << "\t\t\t\t\tChoose Number from 1:9\n";
    else cout << "\n\t\t\t\t\tThis Cell is Choosen before\n\n";
    return false;
}

bool check(Game& g, int num){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(g.grid[i][j] == num + '0') return true;
    return false;
}

void Print(Game& g){
    SetConsoleTextAttribute(C, 14);
    cout << "\n\n\n";
    cout << "\t\t\t\t\t\t\t+-----------------------------------------------+\n";
    for(int i = 0; i < 3; i++){
        cout << "\t\t\t\t\t\t\t|";
        for(int j = 0; j < 3; j++){
            cout << "\t \t";
            cout <<  "|";
        }
        cout << "\n\t\t\t\t\t\t\t|";
        for(int j = 0; j < 3; j++){
            SetConsoleTextAttribute(C, 4);
            cout << "\t" << g.grid[i][j] << "\t";
            SetConsoleTextAttribute(C, 14);
            cout <<  "|";
        }
        cout << "\n\t\t\t\t\t\t\t|";
        for(int j = 0; j < 3; j++){
            cout << "\t \t";
            cout <<  "|";
        }
        cout << "\n\t\t\t\t\t\t\t+-----------------------------------------------+\n";
    }
    cout << "\n\n";
}

void one_vs_one(){
    Game g;
    system("cls");
    SetConsoleTextAttribute(C, 2);
    HANDLE h;
    string wel = "\n\n\t\t\t\t\t\tWho Will Start X or O ? ";
    h = typeMessage(wel, h);
    char option;
    cin >> option;
    char player1 = option, player2 = (toupper(option) == 'X' ? 'O' : 'X');
    player1 = toupper(player1);
    bool turn = true;
    while(Winner(g) == 'c'){
        system("cls");
        Print(g);
        SetConsoleTextAttribute(C, 15);
        int cell;
        string who = (turn ? "\t\t\t\t\tPlayer 1 turn ....\n" : "\t\t\t\t\tPlayer 2 turn ....\n");
        string pl = "\t\t\t\t\tChoose a number of cell that you want to play in it: ";
        h = typeMessage(who, h);
        h = typeMessage(pl, h);
        cin >> cell;
        turn = (play(cell, turn ? player1 : player2, g) ? !turn : turn);
        string con = "\n\t\t\t\t\tPress any key to continue...\n";
        h = typeMessage(con, h);
        getch();
    }
    char w = Winner(g);
    SetConsoleTextAttribute(C, 3);
    string mg_1 = "\t\t\t\t\tWinner Winner Chiken Dinner .. Player 1 Wins\n";
    string mg_2 = "\t\t\t\t\tWinner Winner Chiken Dinner .. Player 2 Wins\n";
    string mg_die = "\t\t\t\t\tooh Die !\n";
    system("cls");
    Print(g);
    SetConsoleTextAttribute(C, 3);
    h = typeMessage((w == player1 ? mg_1 : (w == player2 ? mg_2 : mg_die)), h);
    h = typeMessage((w == player1 ? mg_1 : (w == player2 ? mg_2 : mg_die)), h);
}

void one_vs_pc(){
    Game g;
    system("cls");
    SetConsoleTextAttribute(C, 2);
    HANDLE h;
    string wel = "\n\n\t\t\t\t\t\tChoose X or O to Start: ";
    h = typeMessage(wel, h);
    char option;
    cin >> option;
    char player1 = option, player2 = (toupper(option) == 'X' ? 'O' : 'X');
    player1 = toupper(player1);
    bool turn = true;
    while(Winner(g) == 'c'){
        system("cls");
        Print(g);
        SetConsoleTextAttribute(C, 15);
        int cell;
        string who = (turn ? "\t\t\t\t\tPlayer 1 turn ....\n" : "\t\t\t\t\tPlayer 2 turn ....\n");        
        h = typeMessage(who, h);
        if(turn) {
            string pl = "\t\t\t\t\tChoose a number of cell that you want to play in it: ";
            h = typeMessage(pl, h);
            cin >> cell;
            turn = (play(cell, player1, g) ? !turn : turn);
             string con = "\n\t\t\t\t\tPress any key to continue...\n";
            h = typeMessage(con, h);
            getch();
        }
        else {
            srand(time(0));
            do {
                cell = 1 + rand() % 9;
            } while(!check(g, cell));
            play(cell, player2, g);
            turn = !turn;
            string pl = "\t\t\t\t\tPlayer 2 Choose ";
            pl.push_back(cell + '0');
            pl.push_back('\n');
            h = typeMessage(pl, h);
            string con = "\n\t\t\t\t\tPress any key to continue...\n";
            h = typeMessage(con, h);
            getch();
        }
    }
    string mg_1 = "\t\t\t\t\tWinner Winner Chiken Dinner .. Player 1 Wins\n";
    string mg_2 = "\t\t\t\t\tWinner Winner Chiken Dinner .. Player 2 Wins\n";
    string mg_die = "\t\t\t\t\tooh Die !\n";
    system("cls");
    Print(g);
    SetConsoleTextAttribute(C, 3);
    char w = Winner(g);
    h = typeMessage((w == player1 ? mg_1 : (w == player2 ? mg_2 : mg_die)), h);
    string con = "\n\t\t\t\t\tPress any key to Exit...\n";
    h = typeMessage(con, h);
    getch();
}

int main(){
    system("Color 8");
    SetConsoleTextAttribute(C, 5);
    cout << "\t\t\t\t\t\t-------------------------------------\n";
    cout << "\t\t\t\t\t\t\t1 -> Play One Vs One\n";
    cout << "\t\t\t\t\t\t\t2 -> Play One Vs PC\n";
    cout << "\t\t\t\t\t\t\t3 -> Exit\n";
    cout << "\t\t\t\t\t\t-------------------------------------\n";
    cout << "\t\t\t\t\t\t\tEnter Your Choice: ";
    int choice;
    cin >> choice;
    if(choice == 1){
        one_vs_one();
    }else if(choice == 2){
        one_vs_pc();
    }else if(choice == 3){
        HANDLE h;
        string con = "\n\t\t\t\t\tPress any key to Exit...\n";
        h = typeMessage(con, 0);
        getch();
    }else {
        cout << "\t\t\t\t\tError !!";
    }
}
