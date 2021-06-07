#include <bits\stdc++.h>
#include<conio.h>
#include <windows.h>
using namespace std;

// hello my name is mina
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
    if(num > 9 || num < 1) cout << "Choose Number from 1:9\n";
    else cout << "This Cell is Choosen before\n";
    return false;
}

bool check(Game& g, int num){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(g.grid[i][j] == num + '0') return true;
    return false;
}

void Print(Game& g){
    cout << "-------------\n";
    for(int i = 0; i < 3; i++){
        cout << "| ";
        for(int j = 0; j < 3; j++){
            cout << g.grid[i][j] << " | ";
        }
        cout << "\n-------------\n";
    } 
}

void one_vs_one(){
    Game g;
    system("cls");
    HANDLE h;
    string wel = "Who Will Start X or O ? ";
    h = typeMessage(wel, h);
    char option;
    cin >> option;
    char player1 = option, player2 = (toupper(option) == 'X' ? 'O' : 'X');
    player1 = toupper(player1);
    bool turn = true;
    while(Winner(g) == 'c'){
        system("cls");
        Print(g);
        int cell;
        string who = (turn ? "Player 1 turn ....\n" : "Player 2 turn ....\n");
        string pl = "Choose a number of cell that you want to play in it: ";
        h = typeMessage(who, h);
        h = typeMessage(pl, h);
        cin >> cell;
        turn = (play(cell, turn ? player1 : player2, g) ? !turn : turn);
        string con = "Press any key to continue...\n";
        h = typeMessage(con, h);
        getch();
    }
    char w = Winner(g);
    string mg_1 = "Winner Winner Chiken Dinner .. Player 1 Wins\n";
    string mg_2 = "Winner Winner Chiken Dinner .. Player 2 Wins\n";
    string mg_die = "ooh Die !\n";
    system("cls");
    Print(g);
    h = typeMessage((w == player1 ? mg_1 : (w == player2 ? mg_2 : mg_die)), h);
    h = typeMessage((w == player1 ? mg_1 : (w == player2 ? mg_2 : mg_die)), h);
}

void one_vs_pc(){
    Game g;
    system("cls");
    HANDLE h;
    string wel = "Choose X or O to Start: ";
    h = typeMessage(wel, h);
    char option;
    cin >> option;
    char player1 = option, player2 = (toupper(option) == 'X' ? 'O' : 'X');
    player1 = toupper(player1);
    bool turn = true;
    while(Winner(g) == 'c'){
        system("cls");
        Print(g);
        int cell;
        string who = (turn ? "Player 1 turn ....\n" : "Player 2 turn ....\n");        
        h = typeMessage(who, h);
        if(turn) {
            string pl = "Choose a number of cell that you want to play in it: ";
            h = typeMessage(pl, h);
            cin >> cell;
            turn = (play(cell, player1, g) ? !turn : turn);
        }
        else {
            do {
                cell = 1 + rand() % 9;
            } while(!check(g, cell));
            play(cell, player2, g);
            turn = !turn;
        }
        string con = "Press any key to continue...\n";
        h = typeMessage(con, h);
        getch();
    }
    string mg_1 = "Winner Winner Chiken Dinner .. Player 1 Wins\n";
    string mg_2 = "Winner Winner Chiken Dinner .. Player 2 Wins\n";
    string mg_die = "ooh Die !\n";
    system("cls");
    Print(g);
    char w = Winner(g);
    h = typeMessage((w == player1 ? mg_1 : (w == player2 ? mg_2 : mg_die)), h);
    string con = "Press any key to Exit...\n";
    h = typeMessage(con, h);
    getch();
}

int main(){
    cout << "-------------------------------------\n";
    cout << "1 -> Play One Vs One\n";
    cout << "2 -> Play One Vs PC\n";
    cout << "3 -> Exit\n";
    cout << "-------------------------------------\n";
    cout << "Enter Your Choice: ";
    int choice;
    cin >> choice;
    if(choice == 1){
        one_vs_one();
    }else if(choice == 2){
        one_vs_pc();
    }else if(choice == 3){
        HANDLE h;
        string con = "Press any key to Exit...\n";
        h = typeMessage(con, 0);
        getch();
    }else {
        cout << "Error !!";
    }
}

// Ahmed Hossam Khalil
