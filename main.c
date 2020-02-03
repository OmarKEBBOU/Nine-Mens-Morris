#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "respecter.c"
#include "ia.c"

/*
main
void menu();
void regles();
void menu_ia();
void main_menu();
*/

/*
respecter
011 void color(int Texte,int Fond) // fonction d'affichage de couleurs
017 void afficher(); //affiche la table de jeu
138 void bloquer(); //verifie que le joueur n'est pas bloque
154 void supprimermoulin(int b,int q) // supprime un moulin au cas ou il est détruit
172 int  inclu(int b,int *E,int s,int t);  //voit si b est inclut dans E[0] .... E[s] avec E de longueur t
179 void capturer();  //supprime un pion du joueur adverse
231 void moulin(int a); //verifie si le joueur a realise un moulin
252 void placement(); //s'occupe de la phase de placement
283 void mouvement(); //s'occupe des phases de mouvement et saut
351 void gagnant(char *a); // affiche a l'ecran le gagnant de la  partie
364 void initialiser(); //permet d'initialiser la table de jeu, le nombre de pions et arranger la table de proximité
520 void pvp(); //fonction globale de joueur contre joueur
*/

/*
ia
006 int  moulinmach(int m);
029 void capturemoyen();
054 void posemoyen(int m);
089 int evaluer(int q, int r);
110 void mouvmoyen();
169 void posefacile();
203 void mouvfacile();
260 void ia(char a);
 */


void menu()
{   printf("                                       __              _        _____         _ _     \n");
    printf("                                    __|  |___ _ _    _| |_ _   |     |___ _ _| |_|___ \n");
    printf("                                   |  |  | -_| | |  | . | | |  | | | | . | | | | |   |\n");
    printf("                                   |_____|___|___|  |___|___|  |_|_|_|___|___|_|_|_|_|\n\n\n\n\n");
    printf("                                        __\n");
    printf("                 ,-_                  (`  ).\n");
    printf("                 |-_'-,              (     ).\n");
    printf("                 |-_'-'           _(        '`.\n");
    printf("        _        |-_'/        .=(`(      .     )\n");
    printf("       /;-,_     |-_'        (     (.__.:-`-_.'\n");
    printf("      /-.-;,-,___|'          `(       ) )                             A/Joueur contre joueur\n");
    printf("     /;-;-;-;_;_/|\\_ _ _ _ _   ` __.:'   )                            B/Joueur contre ordinateur\n");
    printf("        x_( __`|_P_|`-;-;-;,|        `--'                             C/Regles du jeu\n");
    printf("        |\\ \\    _||   `-;-;-'                                         D/Quitter le jeu\n");
    printf("        | \\`   -_|.      '-'\n");
    printf("        | /   /-_| `\n");
    printf("        |/   ,'-_|  \\ \n");
    printf("        /____|'-_|___\\ \n");
    printf(" _..,____]__|_\\-_'|_[___,.._ \n");
    printf("'                          ``'--,..,.\n\n\n\n\n\n");
}

void regles()
{
    system("cls");
    char c;
    printf("1. Le jeu se deroule en deux temps : la pose puis le mouvement.\n\n");
    printf("2. Dans un premier temps, les joueurs posent a tour de role chacun de leurs \n");
    printf("pions sur un point vide (intersection) du plateau.\n");
    printf("Le premier joueur est defini aleatoirement par la machine.\n");
    printf("   Lorsqu'il n'y a plus de pion a poser, les joueurs deplacent leurs pions vers \n");
    printf("une intersection voisine libre en suivant un chemin prevu. L'objectif est de\n");
    printf("former des \" moulins \" ou files de trois pions alignes.\n");
    printf("   Lorsqu'un des joueurs a reussi a realiser un moulin, il peut capturer un pion\n");
    printf("de son choix a l'adversaire, a la condition que ce pion ne fasse pas deja\n");
    printf("partie d'un moulin.\n\n");
    printf("3. Une fois sorti du jeu, un pion ne peut plus y rentrer.\n");
    printf("4. Le jeu s'acheve quand un joueur n'a plus que deux pions ou ne peut plus\n");
    printf("jouer, il est alors le perdant.\n\n");
    printf("5. Le \" double moulin \"  \n\n");
    printf("6. Une regle optionnelle donne une seconde chance a celui qui ne possede plus\n");
    printf("que trois pions : il peut alors se deplacer en sautant ou il veut.\n\n\n\n\n\n\n\n");
    printf("Pour revenir au menu tapez a et entrez. ");
    scanf("%c",&c);
    if (c!='a') regles();
    main_menu();
}

void menu_ia()
{
    system("cls");
    char l=0;
    printf("                                            ____  _  _   ___  \n");
    printf("                                           (  _ \\/ )( \\ / __) \n");
    printf("                                            ) __/\\ \\/ /( (__\n");
    printf("                                           (__)   \\__/  \\___)\n\n\n\n\n");
    printf("                                        __\n");
    printf("                 ,-_                  (`  ).\n");
    printf("                 |-_'-,              (     ).\n");
    printf("                 |-_'-'           _(        '`.\n");
    printf("        _        |-_'/        .=(`(      .     )\n");
    printf("       /;-,_     |-_'        (     (.__.:-`-_.'\n");
    printf("      /-.-;,-,___|'          `(       ) )                             A/Mode facile\n");
    printf("     /;-;-;-;_;_/|\\_ _ _ _ _   ` __.:'   )                             B/Mode moyen\n");
    printf("        x_( __`|_P_|`-;-;-;,|        `--'                             \n"); //C/Mode difficile\n");
    printf("        |\\ \\    _||   `-;-;-'                                         D/Retourner au menu\n");
    printf("        | \\`   -_|.      '-'\n");
    printf("        | /   /-_| `\n");
    printf("        |/   ,'-_|  \\ \n");
    printf("        /____|'-_|___\\ \n");
    printf(" _..,____]__|_\\-_'|_[___,.._ \n");
    printf("'                          ``'--,..,.\n\n\n\n\n\n");
    printf("Selectionnez votre choix et entrez: ");
    scanf("%c",&l);
    printf("\n");
    while (l!='A' && l!='B' && l!='C' && l!='D' && l!='a' && l!='b' && l!='c' && l!='d')
    {
        menu_ia();
        printf("Votre choix doit faire parti de ceux presentes: ");
        scanf("%c",&l);
    }
    if (l=='D' || l=='d') main_menu();
    else ia(l);
}

void main_menu()
{
    system("cls");
    char c=0;
    menu();
    printf("Selectionnez votre choix et entrez: ");
    scanf("%c",&c);
    printf("\n");
    while (c!='A' && c!='B' && c!='C' && c!='D' && c!='a' && c!='b' && c!='c' && c!='d')
    {
        menu();
        printf("Votre choix doit faire parti de ceux presentes: ");
        scanf("%c",&c);
    }
    if (c=='D' || c=='d') exit(EXIT_SUCCESS);
    if (c=='C' || c=='c') regles();
    if (c=='B' || c=='b') menu_ia();
    if (c=='A' || c=='a') pvp();
}

int main()
{
    system("mode con LINES=30 COLS=115");
    system("color 3F");
    char c;
    printf("\n\n\n\n\n\n\n\n\n\n        888888                             888               888b     d888                   888 d8b \n");
    printf("          \"88b                             888               8888b   d8888                   888 Y8P     \n");
    printf("           888                             888               88888b.d88888                   888              \n");
    printf("           888  .d88b.  888  888       .d88888 888  888      888Y88888P888  .d88b.  888  888 888 888 88888b.  \n");
    printf("           888 d8P  Y8b 888  888      d88\" 888 888  888      888 Y888P 888 d88\"\"88b 888  888 888 888 888 \"88b \n");
    printf("           888 88888888 888  888      888  888 888  888      888  Y8P  888 888  888 888  888 888 888 888  888 \n");
    printf("           88P Y8b.     Y88b 888      Y88b 888 Y88b 888      888   \"   888 Y88..88P Y88b 888 888 888 888  888 \n");
    printf("           888  \"Y8888   \"Y88888       \"Y88888  \"Y88888      888       888  \"Y88P\"   \"Y88888 888 888 888  888 \n");
    printf("         .d88P                                                                                                \n");
    printf("       .d88P\"                                                                                                 \n");
    printf("       888P\"                                                                                                \n");
    scanf("%c",&c);
    if (c!=0) system("cls");
    c=0;
    main_menu();
}
