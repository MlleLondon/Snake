#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define N 20
#define M 40

int i,j,Terrain[N][M],x,y,Gy,Tete,Queue,Jeu,Pommes,a,b,var,dir,score,HighScore,Vitesse, compteur=0;
void GameOver();
FILE *f;

void snakeInitialization(){ //Permet d'initialiser le serpent en début de partie
    f=fopen("highscore.txt","r");
    //Récupère le Highscore stocké dans highscore.txt
    fscanf(f,"%d",&HighScore);
    fclose(f);

    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            Terrain[i][j]=0;
        }
    }

    x=N/2;y=M/2; Gy = y; Tete = 5; Queue =1; Jeu = 0,Pommes = 0,dir='d',score=0,Vitesse = 99;

    for(i=0;i<Tete;i++){
        Gy++;
        Terrain[x][Gy-Tete] = i+1;
    }
}

void print(){  //Fonction 'dessinant' les terrain de jeu
    for(i=0;i<=M+1;i++){
        if(i==0){
            printf("%c",201);
        }else if(i==M+1){
            printf("%c",187);
        }else{
            printf("%c",205);
        }
    }
    printf("   Score: %d  HighScore: %d",score,HighScore);
    printf("\n");

    for(i=0;i<N;i++){
        printf("%c",186);

        for(j=0;j<M;j++){
            if(Terrain[i][j]==0) printf(" ");
            if(Terrain[i][j]>0 && Terrain[i][j]!=Tete) printf("%c",176);
            if(Terrain[i][j]==Tete) printf("%c",178);
            if(Terrain[i][j]==-1) printf("%c",15);
            if(j==M-1) printf("%c\n",186);
        }
    }

    for(i=0;i<=M+1;i++){
        if(i==0){
            printf("%c",200);
        }else if(i==M+1){
            printf("%c",188);
        }else{
            printf("%c",205);
        }
    }
}
void ResetScreenPosition(){
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut,Position);
}

//Pommes
void Random(){
    srand(time(0));
    a = 1+ rand() % 18;
    b = 1 + rand() % 38;

    if(Pommes == 0 && Terrain[a][b]==0){
        Terrain[a][b]= -1;
        Pommes = 1;
        if(Vitesse>10 && score!=0) Vitesse = Vitesse - 5;
    }
}

int getch_noblock(){
    if(_kbhit())
        return _getch();
    else
        return -1;
}

void movement(){ //Function qui permet de déplacer le serpent avec le clavier
    var = getch_noblock();
    var = tolower(var);

    if(((var=='d'||var=='a')||(var=='w'||var=='s')) &&(abs(dir-var)>5)) dir = var;
    if(dir =='d'){
        y++;
        if(y==M-1) y=0;
        if(Terrain[x][y]!=0 && Terrain[x][y]!=-1) GameOver();
        if(Terrain[x][y]==-1){
            Pommes = 0;
            score+=5;
            compteur++;
            if(compteur==3){
                Queue-=1;
                compteur=0;
            }
        }

        Tete++;
        Terrain[x][y] = Tete;
    }

    if(dir =='a'){
        y--;
        if(y==0) y = M-1;
        if(Terrain[x][y]!=0 && Terrain[x][y]!=-1) GameOver();
        if(Terrain[x][y]==-1){
            Pommes = 0;
            score+=5;
            compteur++;
            if(compteur==3){
                Queue-=1;
                compteur=0;
            }
        }
        Tete++;
        Terrain[x][y] = Tete;
    }

    if(dir =='w'){
        x--;
        if(x==-1) x = N-1;
        if(Terrain[x][y]!=0 && Terrain[x][y]!=-1) GameOver();
        if(Terrain[x][y]==-1){
            Pommes = 0;
            score+=5;
            compteur++;
            if(compteur==3){
                Queue-=1;
                compteur=0;
            }
        }
        Tete++;
        Terrain[x][y] = Tete;
    }

    if(dir =='s'){
        x++;
        if(x==N-1) x = 0;
        if(Terrain[x][y]!=0 && Terrain[x][y]!=-1) GameOver();
        if(Terrain[x][y]==-1){
            Pommes = 0;
            score+=5;
            compteur++;
            if(compteur==3){
                Queue-=1;
                compteur=0;
            }
        }
        Tete++;
        Terrain[x][y] = Tete;
    }
}

void TailRemove(){ 
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            if(Terrain[i][j]==Queue){
                Terrain[i][j] = 0;
            }
        }
    }
    Queue++;
}

void GameOver(){ //En cas de GameOver afficher le Highscore marque le Highscore s'il y en a un et propose de rejouer ou non
    printf("\a");
    Sleep(1500);
    system("Cls");

    if(score>HighScore){
        printf("  New HighScore %d!!!!!!\n\n",score);
        system("pause");
        f=fopen("highscore.txt","w");
        fprintf(f,"%d",score);
        fclose(f);
    }

    system("Cls");
    printf("\n\n         GAME OVER !!!!!!\n");
    printf("             Score : %d \n\n",score);
    printf("             Appuie sur ENTER pour recommencer, ou ESC pour quitter ... \n");


    while(1){
        var = getch_noblock();
        if(var == 13){
            Jeu = 0;
            snakeInitialization();
            break;
        }else if(var == 27){
            Jeu = 1;
            break;
        }
    }
    system("Cls");
}
void main(){
    snakeInitialization();

    while(Jeu == 0){
        print();
        ResetScreenPosition();
        Random();
        movement();
        TailRemove();
        Sleep(Vitesse);
    }
}
