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
    //checking if the snake doesnt cross itself, when it does, it calls losegame by return value
    int i=0;
    for(i=1;i<points;i++){
        if(pos2[0][0]==pos2[i][0] && pos2[0][1]==pos2[i][1]){
            return 1;
        }
    }
    return 0;
}

int createPoint(){
    //creating a point
    int i=0;

    //random coordinates on the map
    srand(time(NULL));
    ppos[0]=rand() % 46 + 1;
    ppos[1]=rand() % 22 + 4;
    //check if the coordinates are not occupied by the snake
    for(i=0;i<points;i++){
        if(pos2[i][0]==ppos[0] && pos2[i][1]==ppos[1]){
            createPoint();
        }
    }
    /*to see point coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {54, 0});
    cout << "P(" << ppos[0]<< ", " << ppos[1] << ")";*/

    //draw the point
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {ppos[0], ppos[1]});
    cout << "@";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {0, 2});
    return 0;
}

char drawBoard(){
    //drawing the map
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
    //funct if we cross a point w the snake's head
    if(pos2[0][0]==ppos[0] && pos2[0][1]==ppos[1]){
        createPoint();
        ++points;
        return 0;
    }
    else return 1;
}

int loseGame(){
    //funct when we lose
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

    /*to see the variables
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {65, 0});
    cout << "S(" << pos2[0][0] << ", " << pos2[0][1] << ") ";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {76, 0});
    cout << "d:" << dir;*/
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {81, 0});
    cout << "Points: " << points;

    //draw the first element of the snake
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {pos2[0][0], pos2[0][1]});
    cout << "O";

    //draw as many secondary characters 'o' as many points we have
    for(i=1;i<points+1;i++){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {pos2[i][0], pos2[i][1]});
        cout << "o";
    }
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {0, 1});
    return 0;
}

int rendez(){
    //changint the snake characters with the next one
    int i;
    for(i=points;i>0;i--){
        pos2[i][0]=pos2[i-1][0];
        pos2[i][1]=pos2[i-1][1];
    }
}

int drawSnake(int direct, int diff){
    //moving the snake

    //delete the one before
    if(pos2[points[0]!=0&&pos2[points][1]!=0){
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {pos2[points][0], pos2[points][1]});
        cout << " ";
    }
    //cases with the direction, every if is true, when the snake hits the wall, or itself
    //every else moves the snake's first point to the new coordinate,
    //every element of the snake will be replaced with the one next to it
    //if the snake catches an element it grows
    switch(direct){
        case 1: //up
            {
            if(pos2[0][1]<=4 || block()==1){
                loseGame();
                return 1;
                break;
            }
            else{
                rendez(); //replace the snake elements to with the next one
                pos2[0][1]--; //change the first element of the snake coordinate according to the direction
                checkIfPointScored(); //check if we scored a point, then we grow
                snakeGoes(); //drawing the actual snake
            }
            break;
            }

        //it's the same methodology i used with the first
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
    //drawing the board with a 2D array
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
    //this is the ASCII art appearing only once at execution
    string line;
    //it reads the "image" from snake_art.txt
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
    //clear display
    system(CLEAR);
    //reset points
    points=0;
    //reset direction to upwards
    dir=1;
    int diff;
    //reset init position
    pos2[0][0]=24;
    pos2[0][1]=14;
    //ASCII art is apperaing only once
    if(intro){
        art();
        intro=FALSE;
    }
    cout << "Welcome to Quack Snake 1.3 - Pick difficulty (1-3) ";
    //if difficulty is not 1-3 it's restarting main
    while(diff<1 || diff>3){
        cin >> diff;
        if(diff<1 || diff > 3){
            main();
        }
    }
    cout << endl<<endl;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {0, 3});
    //function to draw the board
    board();
    --diff;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , {0, 1});
    getch();
    //create a point to collect
    createPoint();
    //controlling the snake, somehow arrows are delayed, while WASD is not
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
                case 27: //if ESC then reset
                    pos2[0][0]=24;
                    pos2[0][1]=14;
                    main();
                    break;
            }
        }
        //moving the snake
        drawSnake(dir,diff);
    }
    return 0;
}
