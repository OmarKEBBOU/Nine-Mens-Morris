#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int moulinmach(int m)
{
    int e=0; //permet de connaitre le nombre de moulins que vient de realiser la machine
    int a=P[m][1],b=P[m][3],c=P[m][2],d=P[m][4],q; //m,aet b forment un moulin, de m=eme pour m,c et d
    q=(i%2+1); //indice du tour de la machine
    if ((A[a][0]==q)&&(A[b][0]==q))
    {
        A[a][1]++;
        A[b][1]++;
        A[m][1]++;
        e++;
        if (J[3-q]==2) A[c][0]=0;
    }
    if ((A[c][0]==q)&&(A[d][0]==q))
    {
        A[c][1]++;
        A[d][1]++;
        A[m][1]++;
        e++;
    }
    return e;
}

void capturemoyen()
{
    int r=2-(i%2); //indice du joueur
    int a=0,b=-10,c;
    for (int w=0;w<24;w++) //evaluation des cases ennemies
    {
        c=-10;
        if (A[w][0]==r) //on evalue qu'une case qui appartient a l'adversaire
        {
            c=0;
            if (A[w][1]==0) c=c+10; //si la case n'appartient pas a un moulin elle est prioritaire
            if (A[P[w][1]][0]==r || A[P[w][3]][0]==r) c=c+3; //on ajoute des points si elle est alignée avec une autre case
            if (A[P[w][2]][0]==r || A[P[w][4]][0]==r) c=c+3; //de meme
        }
        if (c>b)
        {
            a=w;
            b=c;
        }
    }
    A[a][0]=0;
    supprimermoulin(a,r);
    J[r]--; //on diminue le combre de pions de l'adversaire
}

void posemoyen(int m)
{
    int q=(i%2)+1;
    int a=0,b=-1,c;
    for (int w=0;w<24;w++) //on evalue toutes les cases
    {
        c=0;
        if (A[w][0]!=0) c=-1; //si une case est pleine on ne l'evalue pas
        else
        {
            if (A[P[w][1]][0]==A[P[w][3]][0] && A[P[w][1]][0]!=0)
            {
                if (A[P[w][1]][0]==q) c=c+5; //on privilégie les moulins de la machine a ceux de l'adversaire car on peut les capturer ensuite
                else c=c+2; //on accorde aussi de l'importance à ceux de l'adversaire
            }
            if ((A[P[w][3]][0]==q && A[P[w][1]][0]==0)||(A[P[w][3]][0]==0 && A[P[w][1]][0]==q)) c++; // si aucun moulin n'est au point de se former on tente d'aligner deux cases de la machine en vérifiant que le troisième est vide
            if (A[P[w][2]][0]==A[P[w][4]][0] && A[P[w][2]][0]!=0)
            {
                if (A[P[w][2]][0]==q) c=c+5;
                else c=c+2;
            }
            if ((A[P[w][2]][0]==q && A[P[w][4]][0]==0)||(A[P[w][2]][0]==0 && A[P[w][4]][0]==q)) c++;
        if (w==m) c=-1000; // m est la valeur interdite, elle existe car on sollicite la fonction dans la phase de saut
        }
        if (c>b)
        {
            a=w;
            b=c;
        }
    }
    A[a][0]=q;
    b=moulinmach(a); //b est le nombre de moulins créés par cette action, on les compte pour connaitre le nombre de capture
    for (c=0;c<b;c++) capturemoyen();
}

int evaluer(int s,int t) //évalue le déplacement du pion de la case s à la case voisine t
{
    int a=1;
    int r=2-(i%2); //indice du tour du joueur
    if (A[t][0]!=0) return -1; // si la case est pleine on ne l'évalue pas
    if (A[P[t][1]][0]==A[P[t][3]][0])
    {
        if (A[P[t][1]][0]==(i%2)+1 && P[t][1]!=s && P[t][3]!=s) a=a+5; //on regarde si cette interaction crée ub moulin
        if (A[P[t][1]][0]==2-(i%2)) a=a+3; //on regarde si cette interaction bloque un moulin adverse
    }
    if (A[P[t][2]][0]==A[P[t][4]][0])
    {
        if (A[P[t][2]][0]==(i%2)+1 && P[t][2]!=s && P[t][4]!=s) a=a+5;
        if (A[P[t][2]][0]==2-(i%2)) a=a+3;
    }
    if (A[s][1]!=0 && (P[s][0]==2 || (P[s][0]=3 && P[s][2]==t))) a=a+2; //si la machine possède un moulin elle peut le briser si les autres cases voisines sont vides, elle pourra le recréer le prochain tour
    else if ((A[s][1]!=0) && ((A[P[s][1]][0]!=r && A[P[s][3]][0]!=r) || (A[P[s][2]][0]!=r && A[P[s][4]][0]!=r))) a=a+2;
    if ((A[P[s][1]][0]==r && A[P[s][3]][0]==r) || (A[P[s][2]][0]==r && A[P[s][4]][0]==r)) a--;
    return a;
}

void mouvmoyen()
{
    int q=(i%2)+1; //q est l'indice de la machine
    int a=-1,b=100,c,d;
    int e,f,g,h;
    if (J[q]==3)
    {
        for (int w=0;w<24;w++) //pour la phase de saut on n'est pas limité par la proximité, donc on évalue quelle case peut être libérée en causant le moins de dégat
        {
            c=101; //la case à la plus petite valeur est choisie pour être libérée
            if (A[w][0]==q)
            {
                c=0;
                e=P[w][1];
                g=P[w][2];
                f=P[w][3];
                h=P[w][4];
                if (A[e][0]==3-q && A[f][0]==3-q) c=c+3;
                if (A[e][0]==3-q || A[f][0]==3-q) c=c+1;
                if (A[g][0]==3-q && A[h][0]==3-q) c=c+3;
                if (A[g][0]==3-q || A[h][0]==3-q) c=c+1;
            }
            if (c<b)
            {
                b=c;
                a=w;
            }
        }
        A[a][0]=0; // on vide la case de départ
        supprimermoulin(a,q);
        posemoyen(a); //comme on n'est pas limité par la case de départ, on utilise la fonction posemoyen() pour la case d'arrivée en rendant la case de départ interdite
    }
    else
    {
        b=-2;
        for (int w=0;w<24;w++)
        {
            if (A[w][0]==q) // on n'évalue que les cases de la machine
            {
                for (int x=1;x<P[w][0];x++)
                {
                    c=evaluer(w,P[w][x]);
                    if (c>b)
                    {
                        b=c;
                        a=w;
                        d=P[w][x];
                    }
                }
            }
        }
        A[a][0]=0;
        supprimermoulin(a,q);
        A[d][0]=q;
        b=moulinmach(d);
        for (int w=0;w<b;w++) capturemoyen();
    }
}

void posefacile()
{
    int m;
    int q=(i%2)+1;
    m=rand()%24; // on donne une valuer aleatoire
    while (A[m][0]!=0) m=(m+1)%24; //si la case n'est pas vide on prend al suivante
    A[m][0]=q;
    int e=moulinmach(m);
    J[3-q]=J[3-q]-e; //on eneleve a l'adversaire autant qu'on a de pions
    int w=0;
    L11:
    while (e>0 && w<24) //la capture est aleatoire donc on n'a besoin que d'une fonction simple
    {
        if (A[w][0]==3-q && A[w][1]==0)// on parcourt toutes les cases jusqu'a trouver un pion de l'adversaire sans moulin
        {
            A[w][0]=0;
            e--;
        }
        w++;
    }
    w=0;
    while (e>0 && w<24) //si l'ennemi ne possede que des moulins on supprime un pion de moulin
    {
        if (A[w][0]==3-q) //on a besoin uniquement d'un pion adverse
        {
            A[w][0]=0;
            e--;
            supprimermoulin(w,3-q);
            goto L11;
        }
        w++;
    }
}

void mouvfacile()
{
    int q=(i%2)+1; //indicateur de la machine
    int e,f,g,h; //les cases voisines de celle choisie
    int x; //on commence par une valeur aléatoire
    x=rand()%24;
    while (x<24)
    {
        if (A[x][0]==q)
        {
            e=P[x][1];
            f=P[x][1];
            g=P[x][2];
            h=P[x][2];
            if (P[x][0]>2)  g=P[x][3];
            if (P[x][0]==4)  h=P[x][4];
            if (A[e][0]==0 || A[f][0]==0 || A[g][0]==0 || A[h][0]==0)
            {
                if (A[f][0]==0) g=f;
                else if (A[e][0]==0) g=e;
                else if (A[h][0]==0) g=h;
                f=x;
                x=25;
            }
        }
        if (x!=25) x=(x+1)%24;
    }
    A[f][0]=0;
    supprimermoulin(f,q);
    A[g][0]=q;
    e=moulinmach(g);
    J[3-q]=J[3-q]-e;//on enlève autant de pions aux joueurs que la machine possède de moulin
    int w=0;
    L12:
    while (e>0 && w<24) //suppression aléatoire de pion du joueur, si il a des pièces hors moulin
    {
        if (A[w][0]==3-q && A[w][1]==0)
        {
            A[w][0]=0;
            e--;
        }
        w++;
    }
    w=0;
    while (e>0 && w<24) //suppression aléatoire de pion du joueur, si toutes les cases sont en moulin
    {
        if (A[w][0]==3-q)
        {
            A[w][0]=0;
            e--;
            supprimermoulin(w,3-q);
            goto L12;
        }
        w++;
    }
}

void ia(char l)
{
    system("mode con LINES=32 COLS=83");
    initialiser(); //on initialise la table de jeu
    char c; //permet de sortir du jeu a sa toute fin
    int m;
    char b[50]; //le nom du joueur
    afficher();
    printf("Veuillez entrer votre nom: ");
    scanf("%s",&b);
    m=rand();
    for (i=0;i<18;i++) //phase de mouvement
    {
        afficher();
        if ((m%2)==1) // pour le tour du joueur on utilise les fonctions joueur contre joueur
        {
            printf("C'est le tour de %s ",b);
            if ((i%2)==0) printf("jaune \n");
            else printf("bleu \n");
            placement();
        }
        else
        {
            printf("La machine joue");
            if (l=='a' || l=='A') posefacile();
            if (l=='b' || l=='B') posemoyen(30);
        }
        m++;
        if (J[1]==2 || J[2]==2) m=1;
    }
    while (J[1]>2 && J[2]>2) //phases de mouvement et saut
    {
        bloquer();
        if (J[(i%2)+1]==2) goto L3;
        afficher();
        if ((m%2)==1)
        {
            printf("C'est le tour de %s ",b);
            if ((i%2)==0) printf("jaune \n");
            else printf("bleu \n");
            mouvement();
        }
        else
        {
            printf("La machine joue");
            if (l=='a' || l=='A') mouvfacile();
            if (l=='b' || l=='B') mouvmoyen();
        }
        if ((i%2)==0) printf("jaune \n");
        else printf("bleu \n");
        m++;
        L3:
        i++;
    }
    color(14,3);
    if (m%2==0) //ecran victoire humain
    {
        system("mode con LINES=15 COLS=91");
        printf("\n\n\n\n       :::   :::  ::::::::  :::    :::       :::       ::: ::::::::::: ::::    ::: \n");
        printf("       :+:   :+: :+:    :+: :+:    :+:       :+:       :+:     :+:     :+:+:   :+: \n");
        printf("        +:+ +:+  +:+    +:+ +:+    +:+       +:+       +:+     +:+     :+:+:+  +:+ \n");
        printf("         +#++:   +#+    +:+ +#+    +:+       +#+  +:+  +#+     +#+     +#+ +:+ +#+ \n");
        printf("          +#+    +#+    +#+ +#+    +#+       +#+ +#+#+ +#+     +#+     +#+  +#+#+# \n");
        printf("          #+#    #+#    #+# #+#    #+#        #+#+# #+#+#      #+#     #+#   #+#+# \n");
        printf("          ###     ########   ########          ###   ###   ########### ###    #### \n\n");
        printf("\t\t\t\t\t%s a is the best",b);
    }
    else //écran victoire machine
    {
        system("mode con LINES=15 COLS=105");
        printf("\n\n\n\n     :::   :::  ::::::::  :::    :::       :::        ::::::::   ::::::::   ::::::::  :::::::::: \n");
        printf("     :+:   :+: :+:    :+: :+:    :+:       :+:       :+:    :+: :+:    :+: :+:    :+: :+:        \n");
        printf("      +:+ +:+  +:+    +:+ +:+    +:+       +:+       +:+    +:+ +:+    +:+ +:+        +:+        \n");
        printf("       +#++:   +#+    +:+ +#+    +:+       +#+       +#+    +:+ +#+    +:+ +#++:++#++ +#++:++#   \n");
        printf("        +#+    +#+    +#+ +#+    +#+       +#+       +#+    +#+ +#+    +#+        +#+ +#+        \n");
        printf("        #+#    #+#    #+# #+#    #+#       #+#       #+#    #+# #+#    #+# #+#    #+# #+#        \n");
        printf("        ###     ########   ########        ########## ########   ########   ########  ########## \n\n");
        printf("\t\t\t\t\t%s maybe next time",b);
    }
    scanf("%c",&c);
    scanf("%c",&c);
    if (c!=0) system("cls");
    main(); //fin du jeu et retour a l'ecran titre
}
