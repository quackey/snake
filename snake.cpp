#include <ctime>
#include <istream>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <string>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif


using namespace std;
char mapimg[24][48];
int pos2[945][2]={{0}},ppos[2],dir=1,points=0;
//defpos: 24,14
bool cont=TRUE,intro=TRUE;

int main();

int block(){
    int i=0;
    for(i=1;i<points;i++){
        if(pos2[0][0]==pos2[i][0] && pos2[0][1]==pos2[i][1]){
            return 1;
        }
    }
    return 0;
}

int createPoint(){
    int i=0;
    srand(time(NULL));
    ppos[0]=rand() % 46 + 1;
    ppos[1]=rand() % 22 + 4;
    for(i=0;i<points;i++){
        if(pos2[i][0]==ppos[0] && pos2[i][1]==ppos[1]){
            createPoint();
        }
    }
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {54, 0});
    cout << "P(" << ppos[0]<< ", " << ppos[1] << ")";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {ppos[0], ppos[1]});
    cout << "@";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {0, 2});
    return 0;
}

char drawBoard(){
    int i=0,j=0;
    for(i=0;i<24;i++){
        for(j=0;j<48;j++){
            cout << mapimg[i][j];
        }
        cout << endl;
    }
    cout << endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {pos2[0][0], pos2[0][1]});
    cout << "O";
    return 0;
}

int checkIfPointScored(){
    if(pos2[0][0]==ppos[0] && pos2[0][1]==ppos[1]){
        createPoint();
        ++points;
        return 0;
    }
    else return 1;
}

int loseGame(){
    char c;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {pos2[0][0], pos2[0][1]});
    cout << "X";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {0, 27});
    cout << "You lost!\nESC - restart\tOthers - Exit";
    c=getch();
    if(c==27){
        main();
    }
    else{
        cont=FALSE;
        return 1;
    }
    return 0;
}

int snakeGoes(){
    int i;

    //to see the variables
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {65, 0});
    cout << "S(" << pos2[0][0] << ", " << pos2[0][1] << ") ";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {76, 0});
    cout << "d:" << dir;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {81, 0});
    cout << "Points: " << points;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {pos2[0][0], pos2[0][1]});
    cout << "O";
    for(i=1;i<points+1;i++){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {pos2[i][0], pos2[i][1]});
        cout << "o";
    }
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {0, 1});
    return 0;
}

int rendez(){
    int i;
    for(i=points;i>0;i--){
        pos2[i][0]=pos2[i-1][0];
        pos2[i][1]=pos2[i-1][1];
    }
}

int drawSnake(int direct, int diff){
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {pos2[points][0], pos2[points][1]});
    cout << " ";
    switch(direct){
        case 1: //up
            {
            if(pos2[0][1]<=4 || block()==1){
                loseGame();
                return 1;
                break;
            }
            else{
                rendez();
                pos2[0][1]--;
                checkIfPointScored();
                snakeGoes();
            }
            break;
            }
        case 2: //left
        {
            if(pos2[0][0]<2 || block()==1){
                loseGame();
                return 1;
            }
            else{
                rendez();
                pos2[0][0]--;
                checkIfPointScored();
                snakeGoes();
            }
            break;
        }
        case 3://down
        {
            if(pos2[0][1]>=25 || block()==1){
                loseGame();
                return 1;
            }
            else{
                rendez();
                pos2[0][1]++;
                checkIfPointScored();
                snakeGoes();
            }
            break;
            }
        case 4://right
        {
            if(pos2[0][0]>=46 || block()==1){
                loseGame();
                return 1;
            }
            else{
                rendez();
                pos2[0][0]++;
                checkIfPointScored();
                snakeGoes();
            }
            break;
        }
    }
    Sleep(500-diff*165);
    return 0;
}

int board(){
    int i=0,j=0;
    for(j=0;j<48;j++){
        if(j==0){
            mapimg[0][j]=201;
        }
        else if(j==47){
            mapimg[0][j]=187;
        }
        else{
            mapimg[0][j]=205;
        }
    }
    for(i=1;i<23;i++){
        for(j=0;j<48;j++){
            if(j==0||j==47){
                mapimg[i][j]=186;
            }
            else{
                mapimg[i][j]=32;
            }
        }
    }
    i=23;
    for(j=0;j<48;j++){
        if(j==0){
            mapimg[i][j]=200;
        }
        else if(j==47){
            mapimg[i][j]=188;
        }
        else{
            mapimg[i][j]=205;
        }
    }
    drawBoard();
    return 0;
}

int art(){
    string line;
    ifstream myfile ("snake_art.txt");
    if (myfile.is_open()){
        while (getline(myfile, line)){
            cout << line << endl;
        }
        myfile.close();
    Sleep(2000);
    system(CLEAR);
    }
    else cout << "Unable to locate the file..." << endl;
    return 0;
}

int main(){
    system(CLEAR);
    points=0;
    dir=1;
    int diff;
    pos2[0][0]=24;
    pos2[0][1]=14;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {0, 0});
    if(intro){
        art();
        intro=FALSE;
    }
    cout << "Welcome to Quack Snake 1.1 - Pick difficulty (1-3) ";
    while(diff<1 || diff>3){
        cin >> diff;
        if(diff<1 || diff > 3){
            main();
        }
    }
    cout << endl<<endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {0, 3});
    board();
    --diff;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {0, 1});
    getch();
    createPoint();
    while(cont){
        if(kbhit()){
            switch(getch()){
                case 'w': if(dir!=3){dir=1;} break;
                case 's': if(dir!=1){dir=3;} break;
                case 'a': if(dir!=4){dir=2;} break;
                case 'd': if(dir!=2){dir=4;} break;
                case 72: if(dir!=3){dir=1;} break;
                case 80: if(dir!=1){dir=3;} break;
                case 75: if(dir!=4){dir=2;} break;
                case 77: if(dir!=2){dir=4;} break;
                case 27:
                    pos2[0][0]=24;
                    pos2[0][1]=14;
                    main();
                    break;
            }
        }
        drawSnake(dir,diff);
    }
    return 0;
}
