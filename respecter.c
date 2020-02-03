#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int A[24][2]; //ceci est la table de jeux la premiere case indique ce qui se trouve sur la case la seconde indique la presence de moulin
int P[24][5]; //ce tableau presente tous les moulins du jeux tout en donnant les cases voisines
int i; //c'est un compteur qui indique le tour des joueurs
int J[3]; //il indique le nombre de pions restants a chaque joueur

void color(int Texte,int Fond)
{
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,Fond*16+Texte);
}

void afficher()
{
    system("cls");
    color(14,3);
    printf("                                    ____  ____  ____ \n");
    printf("                                   ||J ||||D ||||M || \n");
    printf("                                   ||__||||__||||__||\n");
    printf("                                   |/__\\||/__\\||/__\\|\n\n");
    if (i<18) printf("\t\t\t\tPHASE DE PLACEMENT\n\n");
    else if (J[(i%2)+1]>3) printf("\t\t\t\tPHASE DE MOUVEMENT\n\n");
    else if (J[(i%2)+1]==3) printf("\t\t\t\t  PHASE DE SAUT\n\n");
    printf("\tTOUR %d\n\t\t",((i/2)+1)); //indique le nombre de tours passes
    color(15,3+3*A[0][0]); //permet de colorier la case aux couleur du joueur dessus
    printf("00");
    color(0,3);
    printf("======================");
    color(15,3+3*A[1][0]);
    printf("01");
    color(0,3);
    printf("======================");
    color(15,3+3*A[2][0]);
    printf("02");
    color(0,3);
    //printf(" %d %d  %d %d  %d %d",A[0][0],A[0][1],A[1][0],A[1][1],A[2][0],A[2][1]);
    printf("\n\t\t||\t\t\t||\t\t\t||\n\t\t||\t\t\t||\t\t\t||\n\t\t||      ");
    color(15,3+3*A[3][0]);
    printf("03");
    color(0,3);
    printf("==============");
    color(15,3+3*A[4][0]);
    printf("04");
    color(0,3);
    printf("==============");
    color(15,3+3*A[5][0]);
    printf("05");
    color(0,3);
    printf("      ||");
    //printf(" %d %d  %d %d  %d %d",A[3][0],A[3][1],A[4][0],A[4][1],A[5][0],A[5][1]);
    printf("\n\t\t||      ||              ||              ||      ||\n\t\t||      ||              ||              ||      ||\n\t\t||      ||      ");
    color(15,3+3*A[6][0]);
    printf("06");
    color(0,3);
    printf("======");
    color(15,3+3*A[7][0]);
    printf("07");
    color(0,3);
    printf("======");
    color(15,3+3*A[8][0]);
    printf("08");
    color(0,3);
    printf("      ||      ||");
    //printf(" %d %d  %d %d  %d %d",A[6][0],A[6][1],A[7][0],A[7][1],A[8][0],A[8][1]);
    printf("\n\t\t||      ||      ||              ||      ||      ||\n\t\t||      ||      ||              ||      ||      ||\n\t\t");
    color(15,3+3*A[9][0]);
    printf("09");
    color(0,3);
    printf("======");
    color(15,3+3*A[10][0]);
    printf("10");
    color(0,3);
    printf("======");
    color(15,3+3*A[11][0]);
    printf("11");
    color(0,3);
    printf("              ");
    color(15,3+3*A[12][0]);
    printf("12");
    color(0,3);
    printf("======");
    color(15,3+3*A[13][0]);
    printf("13");
    color(0,3);
    printf("======");
    color(15,3+3*A[14][0]);
    printf("14");
    color(0,3);
    //printf(" %d %d  %d %d  %d %d     %d %d   %d %d  %d %d",A[9][0],A[9][1],A[10][0],A[10][1],A[11][0],A[11][1],A[12][0],A[12][1],A[13][0],A[13][1],A[14][0],A[14][1]);
    printf("\n\t\t||      ||      ||              ||      ||      ||\n\t\t||      ||      ||              ||      ||      ||\n\t\t||      ||      ");
    color(15,3+3*A[15][0]);
    printf("15");
    color(0,3);
    printf("======");
    color(15,3+3*A[16][0]);
    printf("16");
    color(0,3);
    printf("======");
    color(15,3+3*A[17][0]);
    printf("17");
    color(0,3);
    printf("      ||      ||");
    //printf(" %d %d  %d %d  %d %d",A[15][0],A[15][1],A[16][0],A[16][1],A[17][0],A[17][1]);
    printf("\n\t\t||      ||              ||              ||      ||\n\t\t||      ||              ||              ||      ||\n\t\t||      ");
    color(15,3+3*A[18][0]);
    printf("18");
    color(0,3);
    printf("==============");
    color(15,3+3*A[19][0]);
    printf("19");
    color(0,3);
    printf("==============");
    color(15,3+3*A[20][0]);
    printf("20");
    color(0,3);
    printf("      ||");
    //printf(" %d %d  %d %d  %d %d",A[18][0],A[18][1],A[19][0],A[19][1],A[20][0],A[20][1]);
    printf("\n\t\t||\t\t\t||\t\t\t||\n\t\t||\t\t\t||\t\t\t||\n\t\t");
    color(15,3+3*A[21][0]);
    printf("21");
    color(0,3);
    printf("======================");
    color(15,3+3*A[22][0]);
    printf("22");
    color(0,3);
    printf("======================");
    color(15,3+3*A[23][0]);
    printf("23");
    color(0,3);
    //printf(" %d %d  %d %d  %d %d",A[21][0],A[21][1],A[22][0],A[22][1],A[23][0],A[23][1]);
    printf("\n");
}

void bloquer()
{
    int a=(i%2)+1;
    int s=0;
    for (int w=0;w<24;w++) //on parcourt la table de jeu a la recherche de cases de a dont les voisins sont libre
    {
        if (A[w][0]==a)
        {
            if (A[P[w][1]][0]==0 || A[P[w][2]][0]==0) s++;
            if (P[w][0]==3 && A[P[w][3]][0]==0) s++;
            if (P[w][0]==4 && A[P[w][4]][0]==0) s++;
        }
    }
    if (s==0) J[a]=2; //si aucune case de a n'a de voisin libre il est bloque il a donc perdu
}

void supprimermoulin(int b,int q)
{
    if (A[b][1]!=0) //si b fait parti d'un moulin on le supprime avec b
    {
        A[b][1]=0;
        if (A[P[b][1]][0]==q && A[P[b][3]][0]==q)
        {
            A[P[b][1]][1]--;
            A[P[b][3]][1]--;
        }
        if (A[P[b][2]][0]==q && A[P[b][4]][0]==q)
        {
            A[P[b][2]][1]--;
            A[P[b][4]][1]--;
        }
    }
}

int inclu(int b,int *E,int s,int t)
{
    if (s==0) return(inclu(b,E,t,t)); // si s est nul il cherche si b apparient a E
    for (int w=0;w<s;w++) if (b==E[w]) return(1);
    return(0);
}

void capturer()
{
    int q=2-(i%2); //c'est l'indicateur du joueur ennemi
    int b; //la case du joeur adverse qu'on va supprimer
    int s=0,t; //des compteurs
    int E[J[q]]; //les cases du joueur a
    for (int w=0;w<24;w++)  //les case de a dont l'indice inferieures a s ne font pas partie de moulin
    {
        if ((A[w][0]==q)&&(A[w][1]==0))
        {
            E[s]=w;
            s++;
        }
    }
    t=s;
    for (int w=0;w<24;w++) //les cases de a dont l'indice est compris entre s et t font partie d'un moulin
    {
        if ((A[w][0]==q)&&(A[w][1]!=0))
        {
            E[t]=w;
            t++;
        }
    }  //si s==0 toutes les cases de a font parties d'un moulin donc on peut toutes les supprimer
    afficher();
    printf("Entrez une case de votre adversaire pour la supprimer: ");
    scanf("%d",&b);
    if (b==100)
    {
        J[3-q]=2;
        i=i+20;
        goto L5;
    }
    while (inclu(b,E,s,t)==0) //verifie la validite de la case en deux etapes
    {
        if (inclu(b,E,t,t)!=0) printf("Cette case fait partie d'un moulin vous ne pouvez pas la supprimer; une autre: ");//si elle apartient a a mais fait parti d un moulin
        else printf("Entrez une case valide de votre adversaire: ");//autre
        scanf("%d",&b);
        if (b==100) //on donne la possibilite de quitter la partie
        {
            J[3-q]=2;
            i=i+20;
            goto L5;
        }
    }
    A[b][0]=0;
    supprimermoulin(b,q);
    J[q]--;
    L5:
    q=0;
    afficher();
}

void moulin(int m)
{
    int a=P[m][1],b=P[m][3],c=P[m][2],d=P[m][4],q;
    q=(i%2+1);
    if ((A[a][0]==q)&&(A[b][0]==q)) //a l'aide du tableau P on verifie le moulin 1
    {
        A[a][1]++;
        A[b][1]++;
        A[m][1]++;
        capturer();
        if (J[3-q]==2) A[c][0]=0; //posssibilite de finir la partie
    }
    if ((A[c][0]==q)&&(A[d][0]==q)) //a l'aide du tableau P on verifie le moulin 2
    {
        A[c][1]++;
        A[d][1]++;
        A[m][1]++;
        capturer();
    }
}

void placement()
{
    int a; //la case qu'on veut remplir
    int q=(i%2)+1; //indicateur du joueur actuel
    printf("Entrez 100 si vous voulez quitter la partie\n");
    printf("Entrez la case de votre choix: ");
    scanf("%d",&a);
    if (a==100) //possibilite de quitter la partie
    {
        i=i+20;
        J[q]=2;
        goto L4;
    }
    while (((a<0)||(a>23))||(A[a][0]!=0)) //verifier que la case est libre
    {
        if ((a<0)||(a>23)) printf("Entrez une case valide: ");
        if (A[a][0]!=0) printf("Cette case est pleine choisissez une autre: ");
        scanf("%d",&a);
        if (a==100)
        {
            i=i+20;
            J[q]=2;
            goto L4;
        }
    }
    A[a][0]=(i%2)+1;
    moulin(a);
    L4:
    q=0;
}

void mouvement()
{
    int c,d; //les cases de depart et d'arrive
    int e,f,g,h; //les voisins de la case de depart
    int q=(i%2)+1; //indicateur du joueur actuel
    L2: //la possibilite de retourner changer la case de depart
    printf("Entrez 50 si vous voulez sauter votre tour et 100 si vous voulez quitter la partie\n");
    printf("Entrez la case de depart: ");
    scanf("%d",&c);
    if (c==50) goto L1; //possibilite de passer le tour
    if (c==100) //possibilite de quitter la parie
    {
        J[q]=2;
        goto L1;
    }
    while ((c<0)||(c>23)||(A[c][0]!=q)) //verification que la case apartient a q
    {
        printf("vous devez entrez l'une de vos cases: ");
        scanf("%d",&c);
        if (c==50) goto L1;
        if (c==100)
        {
            J[q]=2;
            goto L1;
        }
    }
    if (J[q]>3) //si le joueur possede strictement plus de 3 pieces les cases de depart et d'arrive doivent etre voisine
    {
        e=P[c][1];
        f=P[c][2];
        g=P[c][1];
        h=P[c][2];
        if (P[c][0]>2)  g=P[c][3];
        if (P[c][0]==4)  h=P[c][4];
        afficher();
        printf("Entrez la case d'arrive sachant que le depart est a %d\n",c);
        printf("Si vous voulez changer de case de depart tapez 24 ");
        scanf("%d",&d);
        if (d==24) goto L2;
        while ((d<0)||(d>24)||((d!=e)&&(d!=f)&&(d!=g)&&(d!=h))||(A[d][0]!=0)) //on verifie que la case d'arrive est libre et voisine
        {
            if ((d<0)||(d>24)||((d!=e)&&(d!=f)&&(d!=g)&&(d!=h))) printf("Entrez un voisin de %d: ",c);
            else printf("Cette case est pleine choisissez une autre: ");
            scanf("%d",&d);
            if (d==24) goto L2;
        }
    }
    if (J[q]==3) //si le joueur a 3 pions disponible il peut se deplacer librement
    {
        printf("%d Entrez librement la case d'arrive \n",c);
        printf("Si vous voulez changer de case de depart tapez 24 ");
        scanf("%d",&d);
        if (d==24) goto L2;
        while ((d<0)||(d>24)||(A[d][0]!=0)) //verifier que la case d'arrive est libre
        {
            printf("%d Entrez une case vide : ",c);
            scanf("%d",&d);
            if (d==24) goto L2;
        }
    }
    A[c][0]=0;
    supprimermoulin(c,q);
    A[d][0]=q;
    moulin(d);
    L1:
    q=0;
}

void gagnant(char *a)
{
    system("mode con LINES=15 COLS=99");
    color(14,3);
    printf("\n\n\n\n          _/_/_/    _/_/      _/_/    _/_/_/          _/_/_/    _/_/    _/      _/  _/_/_/_/\n");
    printf("       _/        _/    _/  _/    _/  _/    _/      _/        _/    _/  _/_/  _/_/  _/\n");
    printf("      _/  _/_/  _/    _/  _/    _/  _/    _/      _/  _/_/  _/_/_/_/  _/  _/  _/  _/_/_/ \n");
    printf("     _/    _/  _/    _/  _/    _/  _/    _/      _/    _/  _/    _/  _/      _/  _/  \n");
    printf("      _/_/_/    _/_/      _/_/    _/_/_/          _/_/_/  _/    _/  _/      _/  _/_/_/_/\n\n");
    color(15,3+3*((i%2)+1));
    printf("\t\t\t\t\t%s a gagne",a);
}

void initialiser()
{
    P[0][0]=2; //la case P[a][0] contient le nombre de voisins de a
    P[0][1]=1; //la case P[a][1] contient une voisine de a
    P[0][2]=9; //la case P[a][2] contient une voisine de a
    P[0][3]=2; //si P[a][0]>=3 la case P[a][3] contient une voisine de a sinon a et P[a][3] partagent un moulin sans etre vosines
    P[0][4]=21; //si P[a][0]=4 la case P[a][4] contient une voisine de a sinon a et P[a][4] partagent un moulin sans etre vosines

    P[1][0]=3;
    P[1][1]=0;
    P[1][2]=4;
    P[1][3]=2;
    P[1][4]=7;

    P[2][0]=2;
    P[2][1]=1;
    P[2][2]=14;
    P[2][3]=0;
    P[2][4]=23;

    P[3][0]=2;
    P[3][1]=4;
    P[3][2]=10;
    P[3][3]=5;
    P[3][4]=18;

    P[4][0]=4;
    P[4][1]=3;
    P[4][2]=1;
    P[4][3]=5;
    P[4][4]=7;

    P[5][0]=2;
    P[5][1]=4;
    P[5][2]=13;
    P[5][3]=3;
    P[5][4]=20;

    P[6][0]=2;
    P[6][1]=7;
    P[6][2]=11;
    P[6][3]=8;
    P[6][4]=15;

    P[7][0]=3;
    P[7][1]=6;
    P[7][2]=4;
    P[7][3]=8;
    P[7][4]=1;

    P[8][0]=2;
    P[8][1]=7;
    P[8][2]=12;
    P[8][3]=6;
    P[8][4]=17;

    P[9][0]=3;
    P[9][1]=0;
    P[9][2]=10;
    P[9][3]=21;
    P[9][4]=11;

    P[10][0]=4;
    P[10][1]=3;
    P[10][2]=9;
    P[10][3]=18;
    P[10][4]=11;

    P[11][0]=3;
    P[11][1]=6;
    P[11][2]=10;
    P[11][3]=15;
    P[11][4]=9;

    P[12][0]=3;
    P[12][1]=8;
    P[12][2]=13;
    P[12][3]=17;
    P[12][4]=14;

    P[13][0]=4;
    P[13][1]=5;
    P[13][2]=12;
    P[13][3]=20;
    P[13][4]=14;

    P[14][0]=3;
    P[14][1]=2;
    P[14][2]=13;
    P[14][3]=23;
    P[14][4]=12;

    P[15][0]=2;
    P[15][1]=11;
    P[15][2]=16;
    P[15][3]=6;
    P[15][4]=17;

    P[16][0]=3;
    P[16][1]=15;
    P[16][2]=19;
    P[16][3]=17;
    P[16][4]=22;

    P[17][0]=2;
    P[17][1]=12;
    P[17][2]=16;
    P[17][3]=8;
    P[17][4]=15;

    P[18][0]=2;
    P[18][1]=10;
    P[18][2]=19;
    P[18][3]=3;
    P[18][4]=20;

    P[19][0]=4;
    P[19][1]=16;
    P[19][2]=18;
    P[19][3]=22;
    P[19][4]=20;

    P[20][0]=2;
    P[20][1]=13;
    P[20][2]=19;
    P[20][3]=5;
    P[20][4]=18;

    P[21][0]=2;
    P[21][1]=9;
    P[21][2]=22;
    P[21][3]=0;
    P[21][4]=23;

    P[22][0]=3;
    P[22][1]=21;
    P[22][2]=19;
    P[22][3]=23;
    P[22][4]=16;

    P[23][0]=2;
    P[23][1]=22;
    P[23][2]=14;
    P[23][3]=21;
    P[23][4]=2;

    J[1]=9; //on attribue on joueur 1 9pions
    J[2]=9; //on attribue au joueur 2 9pions

    for (int w=0;w<24;w++) //on vide la table de jeu
    {
        A[w][0]=0;
        A[w][1]=0;
    }
}

void pvp()
{
    initialiser(); //on initialise la table de jeu
    system("mode con LINES=32 COLS=83");
    char a[50],b[50]; //les noms des joueurs
    char c; //permet de sortir du jeu a sa toute fin
    int m;
    afficher();
    printf("Entrez vos noms \nJoueur1: ");
    scanf("%s",&a);
    printf("Joueur2: ");
    scanf("%s",&b);
    m=rand(); //valeur aleatoire pour definir qui va commencer

    for (i=0;i<18;i++) //phase de placement
    {
        afficher();
        if ((m%2)==1) printf("C'est le tour de %s ",a);
        else printf("C'est le tour de %s ",b);
        if ((i%2)==0) printf("jaune \n");
        else printf("bleu \n");
        placement();
        m++;
        if (J[1]==2 || J[2]==2) m++;
    }
    while (J[1]>2 && J[2]>2) //phases de mouvement et saut
    {
        bloquer();
        if (J[(i%2)+1]==2) goto L3;
        afficher();
        if ((m%2)==1) printf("C'est le tour de %s ",a);
        else printf("C'est le tour de %s ",b);
        if ((i%2)==0) printf("jaune \n");
        else printf("bleu \n");
        mouvement();
        m++;
        L3:
        i++;
    }
    if (m%2==0) gagnant(a); //on defini le gagnant et affiche l'ecran de fin
    else gagnant(b);
    scanf("%c",&c);
    scanf("%c",&c);
    if (c!=0) system("cls");
    main(); //fin du jeu et retour a l'ecran titre
}
