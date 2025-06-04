/**--------------------------------------------------------**/
/**       C o n v e r s i o n   Z vers C (Standard)        **/
/**             Realisee par Pr D.E ZEGOUR                 **/
/**                     E S I - Alger                      **/
/**                    Copywrite 2014                      **/
/**--------------------------------------------------------**/

/*---------------------------------------------------------------------------*/
/*                  TP Z Khawarizm : BSTs Manipulation                       */
/*                                                                           */
/*                             Developed by :                                */
/*                        Cheballah Tinhinane  G04                           */
/*                            Kellil Douaa  G05                              */
/*                                                                           */
/*                Supervised by : Prof.Dr Zegour D.Eddine                    */
/*---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define CYAN "\033[36m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define MAGENTA "\033[95m"
#define WHITE "\033[37m"
#define YELLOW "\033[33m"
typedef int bool;
typedef char *string255;

#define True 1
#define False 0

/*--------------------------- File Procedures ---------------------------*/

/** Implementation **\: FICHIER **/

/* Traitement des fichiers ouverts */

struct _Noeud
{
    FILE *Var_fich;
    char *Nom_fich;
    int Sauv_pos;
    struct _Noeud *Suiv;
};

typedef struct _Noeud *_Ptr_Noeud;

_Ptr_Noeud _Pile_ouverts = NULL;

/*---------------------------------------------------------------------------*/

/* Teste si un fichier est ouvert */
_Ptr_Noeud _Ouvert(char *Fp)
{
    _Ptr_Noeud P;
    bool Trouv;
    P = _Pile_ouverts;
    Trouv = False;
    while ((P != NULL) && !Trouv)
        if (strcmp(P->Nom_fich, Fp) == 0)
            Trouv = True;
        else
            P = P->Suiv;
    return P;
}

/*---------------------------------------------------------------------------*/

/* Ajouter un fichier ouvert */
void _Empiler_ouvert(char *Fp, FILE *Fl)
{
    _Ptr_Noeud P;
    P = (_Ptr_Noeud)malloc(sizeof(struct _Noeud));
    P->Nom_fich = Fp;
    P->Var_fich = Fl;
    P->Suiv = _Pile_ouverts;
    _Pile_ouverts = P;
}

/*---------------------------------------------------------------------------*/

/* Supprimer un fichier ouvert et rendre son nom*/
char *_Depiler_ouvert(FILE *Fl)
{
    char *Fp = malloc(100);
    _Ptr_Noeud P, Prec;
    P = _Pile_ouverts;
    Prec = NULL;
    while (P->Var_fich != Fl)
    {
        Prec = P;
        P = P->Suiv;
    }
    strcpy(Fp, P->Nom_fich);
    if (Prec != NULL)
        Prec->Suiv = P->Suiv;
    else
        _Pile_ouverts = P->Suiv;
    free(P);
    return Fp;
}

/*---------------------------------------------------------------------------*/

/** Fichiers **/

typedef char _Tx[255];
/** Types des champs du bloc **/
typedef string255 Typechamp1_ss;
typedef _Tx Typechamp1_ss_Buf;

/** Type du bloc de donnees du fichier **/
typedef struct
{
    Typechamp1_ss_Buf Champ1;
} Typestruct1_ss_Buf;

/** Type de la structure du bloc de donnees du fichier **/
typedef struct
{
    Typechamp1_ss Champ1;
} Typestruct1_ss_;

typedef Typestruct1_ss_ *Typestruct1_ss;

typedef Typestruct1_ss Typestr_Tss;
typedef Typestruct1_ss_ Type_Tss;

Typechamp1_ss Struct1_Tss(Typestruct1_ss Buf)
{
    return Buf->Champ1;
}

/*---------------------------------------------------------------------------*/
/** Manipulation de la structure **/


void Aff_struct1_Tss(Typestruct1_ss Buf, Typechamp1_ss Val)
{
    strcpy(Buf->Champ1, Val);
}

/*---------------------------------------------------------------------------*/

/** Machine abstaite sur les fichiers **/

void Ouvrir_ss(FILE **ss, char *Fp, char *Mode)
{
    _Ptr_Noeud P = _Ouvert(Fp);
    if (P != NULL)
    /* Le fichier est deja ouvert */
    {
        P->Sauv_pos = ftell(P->Var_fich);
        fclose(P->Var_fich);
    }
    /* Le fichier est non ouvert */
    if (strcmp(Mode, "A") == 0)
        *ss = fopen(Fp, "r+b");
    else
        *ss = fopen(Fp, "w+b");
    _Empiler_ouvert(Fp, *ss);
}

/*---------------------------------------------------------------------------*/

void Fermer_ss(FILE *ss)
{
    char *Fp = malloc(100);
    _Ptr_Noeud P;
    strcpy(Fp, _Depiler_ouvert(ss));
    fclose(ss);
    /* Ya-til un fichier ouvert avec le m?me nom ?  */
    /* Si Oui, le Reouvrir a la position sauvegardee */
    P = _Ouvert(Fp);
    if (P != NULL)
    {
        ss = fopen(P->Nom_fich, "r+b");
        fseek(ss, P->Sauv_pos, 0);
    }
}

/*---------------------------------------------------------------------------*/

void Ecrireseq_ss(FILE *ss, Typestruct1_ss Buf)
{
    Typestruct1_ss_Buf Buffer;
    int I, J;
    for (J = 0; J <= strlen(Buf->Champ1); ++J)
        Buffer.Champ1[J] = Buf->Champ1[J];
    fwrite(&Buffer, sizeof(Typestruct1_ss_Buf), 1, ss);
}

/*---------------------------------------------------------------------------*/

void Ecriredir_ss(FILE *ss, Typestruct1_ss Buf, int N)
{
    Typestruct1_ss_Buf Buffer;
    int I, J;
    for (J = 0; J <= strlen(Buf->Champ1); ++J)
        Buffer.Champ1[J] = Buf->Champ1[J];
    fseek(ss, (long)(N - 1) * sizeof(Typestruct1_ss_Buf), 0);
    fwrite(&Buffer, sizeof(Typestruct1_ss_Buf), 1, ss);
}

/*---------------------------------------------------------------------------*/

void Lireseq_ss(FILE *ss, Typestruct1_ss Buf)
{
    Typestruct1_ss_Buf Buffer;
    int I, J;
    if (fread(&Buffer, sizeof(Typestruct1_ss_Buf), 1, ss) != 0)
    {
        for (J = 0; J <= strlen(Buffer.Champ1); ++J)
            Buf->Champ1[J] = Buffer.Champ1[J];
    }
}

/*---------------------------------------------------------------------------*/

void Liredir_ss(FILE *ss, Typestruct1_ss Buf, int N)
{
    Typestruct1_ss_Buf Buffer;
    int I, J;
    fseek(ss, (long)(N - 1) * sizeof(Typestruct1_ss_Buf), 0);
    fread(&Buffer, sizeof(Typestruct1_ss_Buf), 1, ss);
    for (J = 0; J <= strlen(Buffer.Champ1); ++J)
        Buf->Champ1[J] = Buffer.Champ1[J];
}

/*---------------------------------------------------------------------------*/

void Rajouter_ss(FILE *ss, Typestruct1_ss Buf)
{
    Typestruct1_ss_Buf Buffer;
    int I, J;
    for (J = 0; J <= strlen(Buf->Champ1); ++J)
        Buffer.Champ1[J] = Buf->Champ1[J];
    fseek(ss, 0, 2); /* Fin du fichier */
    fwrite(&Buffer, sizeof(Typestruct1_ss_Buf), 1, ss);
}

/*---------------------------------------------------------------------------*/

bool Finfich_ss(FILE *ss)
{
    long K = ftell(ss);
    fseek(ss, 0, 2);     /* Fin du fichier */
    long K2 = ftell(ss); /* position a partir du debut */
    if (K == K2)
    {
        fseek(ss, K, 0);
        return 1;
    }
    else
    {
        fseek(ss, K, 0);
        return 0;
    }
}

/*---------------------------------------------------------------------------*/

int Alloc_bloc_ss(FILE *ss)
{
    long K;
    fseek(ss, 0, 2); /* Fin du fichier */
    K = ftell(ss);   /* position a partir du debut */
    K = K / sizeof(Typestruct1_ss_Buf);
    K++;
    return (K);
}

/*------------------------- Binary Search Trees Abstract Machines & Structures ---------------------------*/

/** Implementation **\: ARBRE BINAIRE DE STRUCTURES**/
typedef struct Ts Type_Ts;
typedef Type_Ts *Typestr_Ts;
typedef string255 Type1_Ts;
struct Ts
{
    Type1_Ts Champ1;
};

Type1_Ts Struct1_Ts(Typestr_Ts S)
{
    return S->Champ1;
}

void Aff_struct1_Ts(Typestr_Ts S, Type1_Ts Val)
{
    strcpy(S->Champ1, Val);
}

/*---------------------------------------------------------------------------*/

/** Arbres de recherche binaire **/

typedef Typestr_Ts Typeelem_ATs;
typedef struct Noeud_ATs *Pointeur_ATs;

struct Noeud_ATs
{
    Typeelem_ATs Val;
    Pointeur_ATs Fg;
    Pointeur_ATs Fd;
    Pointeur_ATs Pere;
};

Typeelem_ATs Info_ATs(Pointeur_ATs P)
{
    return P->Val;
}

Pointeur_ATs Fg_ATs(Pointeur_ATs P)
{
    return P->Fg;
}

Pointeur_ATs Fd_ATs(Pointeur_ATs P)
{
    return P->Fd;
}

Pointeur_ATs Pere_ATs(Pointeur_ATs P)
{
    return P->Pere;
}

void Aff_info_ATs(Pointeur_ATs P, Typeelem_ATs Val)
{
    Typeelem_ATs _Temp;
    _Temp = malloc(sizeof(Type_Ts));
    _Temp->Champ1 = malloc(255 * sizeof(char));
    /* Affectation globale de structure */
    strcpy(_Temp->Champ1, Val->Champ1);
    Val = _Temp;
    P->Val = Val;
}

void Aff_fg_ATs(Pointeur_ATs P, Pointeur_ATs Q)
{
    P->Fg = Q;
}

void Aff_fd_ATs(Pointeur_ATs P, Pointeur_ATs Q)
{
    P->Fd = Q;
}

void Aff_pere_ATs(Pointeur_ATs P, Pointeur_ATs Q)
{
    P->Pere = Q;
}

void Creernoeud_ATs(Pointeur_ATs *P)
{
    *P = (struct Noeud_ATs *)malloc(sizeof(struct Noeud_ATs));
    (*P)->Val = malloc(sizeof(Type_Ts));
    (*P)->Val->Champ1 = malloc(255 * sizeof(char));
    (*P)->Fg = NULL;
    (*P)->Fd = NULL;
    (*P)->Pere = NULL;
}

void Liberernoeud_ATs(Pointeur_ATs P)
{
    free(P);
}

/*------------------------- Queues Declaration ---------------------------*/

/** Implementation **\: FILE DE ARBRES BINAIRES DE STRUCTURES**/
/** Files d'attente **/

typedef Pointeur_ATs Typeelem_FATs;
typedef struct Filedattente_FATs *Pointeur_FATs;
typedef struct Maillon_FATs *Ptliste_FATs;

struct Maillon_FATs
{
    Typeelem_FATs Val;
    Ptliste_FATs Suiv;
};

struct Filedattente_FATs
{
    Ptliste_FATs Tete, Queue;
};

void Creerfile_FATs(Pointeur_FATs *Fil)
{
    *Fil = (struct Filedattente_FATs *)malloc(sizeof(struct Filedattente_FATs));
    (*Fil)->Tete = NULL;
    (*Fil)->Queue = NULL;
}

bool Filevide_FATs(Pointeur_FATs Fil)
{
    return Fil->Tete == NULL;
}

void Enfiler_FATs(Pointeur_FATs Fil, Typeelem_FATs Val)
{
    Ptliste_FATs Q;

    Q = (struct Maillon_FATs *)malloc(sizeof(struct Maillon_FATs));
    Q->Val = Val;
    Q->Suiv = NULL;
    if (!Filevide_FATs(Fil))
        Fil->Queue->Suiv = Q;
    else
        Fil->Tete = Q;
    Fil->Queue = Q;
}

void Defiler_FATs(Pointeur_FATs Fil, Typeelem_FATs *Val)
{
    if (!Filevide_FATs(Fil))
    {
        *Val = Fil->Tete->Val;
        Fil->Tete = Fil->Tete->Suiv;
    }
    else
        printf("%s \n", "File d'attente vide");
}
/*---------------------------------------------------------------------------*/

/*------------------------- Variables Declaration ---------------------------*/
/*---------------------------------------------------------------------------*/

/** Variables du programme principal **/
FILE *F;
Typestruct1_ss S, S2;
Pointeur_ATs Bst1 = NULL;
Pointeur_ATs Bst2 = NULL;
Pointeur_ATs Bst3 = NULL;
Pointeur_ATs Bst0 = NULL;
Typestr_Ts Snode;
int I;
int J;
int K;
int M = 5;
int N = 10;
int Count_whole_bst1;
int Count_whole_bst2;
int Count_whole_bst3;
int Count_whole_bst0;
int Choice;
string255 Word;
string255 Word1;
string255 Word2;
string255 X;
string255 C;
string255 Y;
string255 Z;
string255 Temp;
Pointeur_ATs Result = NULL;
int _Px1;
string255 _Sx;
Type_Tss S_S;
int _Px2;
int _Px3;
int _Px4;
int _Px5;
int _Px6;
int _Px7;

/*------------------------- Statistics Declaration ---------------------------*/

/*---------------------------------------------------------------------------*/

typedef struct statistics *stat;
struct statistics
{
    int number_of_words;
    int number_of_words_bst1;
    int number_of_words_bst2;
    int number_of_words_bst3;
    int len_search_paths_bst0;
    int len_search_paths_bst1;
    int len_search_paths_bst2;
    int len_search_paths_bst3;
    int len_search_paths_triplet;
};
/*---------------------------------------------------------------------------*/

void init_statistics(stat *s)
{
    *s = (stat)malloc(sizeof(struct statistics));
    (*s)->number_of_words = 0;
    (*s)->number_of_words_bst1 = 0;
    (*s)->number_of_words_bst2 = 0;
    (*s)->number_of_words_bst3 = 0;
    (*s)->len_search_paths_bst0 = 0;
    (*s)->len_search_paths_bst1 = 0;
    (*s)->len_search_paths_bst2 = 0;
    (*s)->len_search_paths_bst3 = 0;
    (*s)->len_search_paths_triplet = 0;
}
stat successful;
stat unsuccessful;
/*---------------------------------------------------------------------------*/

typedef struct statisticsRang
{

    int len_rang_word1;
    int len_rang_word2;
} *statR;
/*---------------------------------------------------------------------------*/

void init_statisticsR(statR *R)
{
    *R = (struct statisticsRang *)malloc(sizeof(struct statisticsRang));

    (*R)->len_rang_word1 = 0;
    (*R)->len_rang_word2 = 0;
};

/*------------------------- Standard Functions ---------------------------*/

/** Fonctions standards **/

int Aleanombre(int N)
{
    return (rand() % N);
}
/*---------------------------------------------------------------------------*/

char *Aleachaine(int N)
{
    int k;
    char *Chaine = malloc(N + 1);

    char Chr1[26] = "abcdefghijklmnopqrstuvwxyz";
    char Chr2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (k = 0; k < N; k++)
        switch (rand() % 2)
        {
        case 0:
            *(Chaine + k) = Chr1[rand() % 26];
            break;
        case 1:
            *(Chaine + k) = Chr2[rand() % 26];
            break;
        }
    Chaine[k] = '\0';
    return (Chaine);
}
/*---------------------------------------------------------------------------*/

char *Caract(string255 Ch, int I)
{
    char *s = malloc(2);
    s[0] = Ch[I - 1];
    s[1] = '\0';
    return s;
}
/*---------------------------------------------------------------------------*/

/** Initialisation d'une structure **/
void Init_struct_Tss(Typestr_Tss S, Type_Tss S_)
{
    S->Champ1 = S_.Champ1;
}
/*---------------------------------------------------------------------------*/

void Init_struct_Ts(Typestr_Ts S, Type_Ts S_)
{
    strcpy(S->Champ1, S_.Champ1);
}

/*---------------------------------------------------------------------------*/
/*--------------------------- Procedures Headers ----------------------------*/
/*---------------------------------------------------------------------------*/
/** Prototypes des fonctions **/

void Research(Pointeur_ATs *Root, Pointeur_ATs *P, Pointeur_ATs *Parent, string255 *Word);
void Construct_bst1(Pointeur_ATs *Root, string255 *Word, int *Count_whole_bst);
void Construct_bst3(Pointeur_ATs *Root, string255 *Word, int *Count_whole_bst);
void Research2(Pointeur_ATs *Root, Pointeur_ATs *P, Pointeur_ATs *Parent, string255 *Word, int *Lengthpath);
void Construct_bst2(Pointeur_ATs *Root, string255 *Word, int *Count_whole_bst2);
void Rotation_bst(Pointeur_ATs *Q, Pointeur_ATs *Parent);
void Right_rotation(Pointeur_ATs *P, Pointeur_ATs *Father);
void Left_rotation(Pointeur_ATs *P, Pointeur_ATs *Father);
void Insert_node(Pointeur_ATs *P, Pointeur_ATs *Father);
void Display_bst(Pointeur_ATs *R);
void Inorder(Pointeur_ATs *R);
void Word_search(string255 *Word);
void Search_in_bst1(Pointeur_ATs *Bst, string255 *Word);
void Search_in_bst2(Pointeur_ATs *Bst, string255 *Word);
void Search_in_bst3(Pointeur_ATs *Bst, string255 *Word);
void Word_search_file(string255 *Word);
void Search_in_bst1_file(Pointeur_ATs *Bst, string255 *Word);
void Search_in_bst2_file(Pointeur_ATs *Bst, string255 *Word);
void Search_in_bst3_file(Pointeur_ATs *Bst, string255 *Word);
void Search_in_bst0(Pointeur_ATs *root, string255 *word);
void Smallestnode(Pointeur_ATs *Root, string255 *Word, Pointeur_ATs *Result, statR R);
void Nextinorder(Pointeur_ATs *Current, Pointeur_ATs *Result, statR R);
void Process(Pointeur_ATs *Node);
void Rangquery(Pointeur_ATs *Root, string255 *Word1, string255 *Word2, statR R, int *found);
void Menu(int *M);
void Process2(Pointeur_ATs *Ptr);
void Postorder(Pointeur_ATs *Root);
void Freetree(Pointeur_ATs *Root1, Pointeur_ATs *Root2, Pointeur_ATs *Root3, Pointeur_ATs *Root4);
void Construct_bst0(Pointeur_ATs *Root, string255 *Word, int *Count_whole_bst);
void gen_file_F(char *filename);
void gen_file_F2(char *filename);
void search_in_file(char *filename);
void init_statisticsR(statR *R);
int MINTOTAL(int totalbst1, int totalbst2, int totalbst3);

/*---------------------------------------------------------------------------*/
/*------------------------------- Procedures  -------------------------------*/
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             Research in BST                               */
/*---------------------------------------------------------------------------*/
// Searches for a word in the BST
void Research(Pointeur_ATs *Root, Pointeur_ATs *P, Pointeur_ATs *Parent, string255 *Word)
{
    /** Variables locales **/
    bool Found;

    /** Corps du module **/
    Found = False;
    *Parent = NULL;
    *P = *Root;
    while ((*P != NULL) && (!Found))
    {
        if (strcmp(Struct1_Ts(Info_ATs(*P)), *Word) == 0)
        {
            ;
            Found = True;
        }
        else
        {
            *Parent = *P;
            if (strcmp(*Word, Struct1_Ts(Info_ATs(*P))) > 0)
            {
                *P = Fd_ATs(*P);
            }
            else
            {
                *P = Fg_ATs(*P);
            }
        }
    }
}
/*---------------------------------------------------------------------------*/
/*                          Research for BST2                                */
/*---------------------------------------------------------------------------*/
// Like Research, but also counts the path length (for BST2).

void Research2(Pointeur_ATs *Root, Pointeur_ATs *P, Pointeur_ATs *Parent, string255 *Word, int *Lengthpath)
{
    /** Variables locales **/
    bool Found;

    /** Corps du module **/
    Found = False;
    *Parent = NULL;
    *P = *Root;
    *Lengthpath = 0;
    while ((*P != NULL) && (!Found))
    {
        *Lengthpath = *Lengthpath + 1;
        if (strcmp(Struct1_Ts(Info_ATs(*P)), *Word) == 0)
        {
            ;
            Found = True;
        }
        else
        {
            *Parent = *P;
            if (strcmp(*Word, Struct1_Ts(Info_ATs(*P))) > 0)
            {
                *P = Fd_ATs(*P);
            }
            else
            {
                *P = Fg_ATs(*P);
            }
        }
    };
    if (!Found)
    {
        ;
        *Lengthpath = *Lengthpath + 1;
    };
}
/*---------------------------------------------------------------------------*/
/*                             Construct BST0                                */
/*---------------------------------------------------------------------------*/
// Inserts a word into BST0 

void Construct_bst0(Pointeur_ATs *Root, string255 *Word, int *Count_whole_bst)
{
    Pointeur_ATs P = NULL;
    Pointeur_ATs Q = NULL;
    Pointeur_ATs Parent = NULL;
    Type_Ts S_Snode;

    Research(Root, &P, &Parent, Word);
    if ((P == NULL))
    {
        Creernoeud_ATs(&Q);
        S_Snode.Champ1 = malloc(255 * sizeof(char));
        strcpy(S_Snode.Champ1, *Word);
        Init_struct_Ts(Snode, S_Snode);
        Aff_info_ATs(Q, Snode);

        if (Parent == NULL)
        {
            *Root = Q;
        }
        else
        {
            Insert_node(&Q, &Parent);
        }
        (*Count_whole_bst)++;
    }
}
/*---------------------------------------------------------------------------*/
/*                             Construct BST1                                */
/*---------------------------------------------------------------------------*/
// Inserts a word into BST0 and performs a rotation if the word is one of X, Y, or Z.
void Construct_bst1(Pointeur_ATs *Root, string255 *Word, int *Count_whole_bst)
{
    /** Variables locales **/
    Pointeur_ATs P = NULL;
    Pointeur_ATs Q = NULL;
    Pointeur_ATs Parent = NULL;
    Type_Ts S_Snode;

    /** Corps du module **/
    Research(&*Root, &P, &Parent, &*Word);
    if ((P == NULL))
    {
        Creernoeud_ATs(&Q);
        S_Snode.Champ1 = malloc(255 * sizeof(char));
        strcpy(S_Snode.Champ1, *Word);
        Init_struct_Ts(Snode, S_Snode);
        Aff_info_ATs(Q, Snode);
        if (Parent == NULL)
        {
            if ((strcmp(Caract(*Word, 1), Caract(X, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Y, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Z, 1)) == 0))
            {
                *Count_whole_bst = *Count_whole_bst + 1;
            };
            *Root = Q;
        }
        else
        {
            Insert_node(&Q, &Parent);
            if ((strcmp(Caract(*Word, 1), Caract(X, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Y, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Z, 1)) == 0))
            {
                *Count_whole_bst = *Count_whole_bst + 1;
                Rotation_bst(&Q, &Parent);
                *Root = Q;
            }
        }
    };
}
/*---------------------------------------------------------------------------*/
/*                             Construct BST2                                */
/*---------------------------------------------------------------------------*/
// Inserts a word into BST2, rotates halfway if word starts with X, Y, or Z.
void Construct_bst2(Pointeur_ATs *Root, string255 *Word, int *Count_whole_bst2)
{
    /** Variables locales **/
    Pointeur_ATs P = NULL;
    Pointeur_ATs Q = NULL;
    Pointeur_ATs Parent = NULL;
    int Lengthpath;
    int Demilengthpath;
    Type_Ts S_Snode;

    /** Corps du module **/
    Research2(&*Root, &P, &Parent, &*Word, &Lengthpath);
    if ((P == NULL))
    {
        Creernoeud_ATs(&Q);
        S_Snode.Champ1 = malloc(255 * sizeof(char));
        strcpy(S_Snode.Champ1, *Word);
        Init_struct_Ts(Snode, S_Snode);
        Aff_info_ATs(Q, Snode);
        if (Parent == NULL)
        {
            if ((strcmp(Caract(*Word, 1), Caract(X, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Y, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Z, 1)) == 0))
            {
                *Count_whole_bst2 = *Count_whole_bst2 + 1;
            };
            *Root = Q;
        }
        else
        {
            Insert_node(&Q, &Parent);
            if ((strcmp(Caract(*Word, 1), Caract(X, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Y, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Z, 1)) == 0))
            {
                *Count_whole_bst2 = *Count_whole_bst2 + 1;
                Demilengthpath = Lengthpath / 2;
                for (K = 1; K <= Demilengthpath; ++K)
                {
                    Rotation_bst(&Q, &Parent);
                    Parent = Pere_ATs(Q);
                    if (Pere_ATs(Q) == NULL)
                    {
                        *Root = Q;
                    };
                }
            }
        }
    }
}
/*---------------------------------------------------------------------------*/
/*                             Construct BST3                                */
/*---------------------------------------------------------------------------*/
// Inserts a word into BST3, rotates to root if word doesn't start with X, Y, or Z

void Construct_bst3(Pointeur_ATs *Root, string255 *Word, int *Count_whole_bst)
{
    /** Variables locales **/
    Pointeur_ATs P = NULL;
    Pointeur_ATs Q = NULL;
    Pointeur_ATs Parent = NULL;
    Type_Ts S_Snode;

    /** Corps du module **/
    Research(&*Root, &P, &Parent, &*Word);
    if ((P == NULL))
    {
        Creernoeud_ATs(&Q);
        S_Snode.Champ1 = malloc(255 * sizeof(char));
        strcpy(S_Snode.Champ1, *Word);
        Init_struct_Ts(Snode, S_Snode);
        Aff_info_ATs(Q, Snode);
        if (Parent == NULL)
        {
            if ((strcmp(Caract(*Word, 1), Caract(X, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Y, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Z, 1)) == 0))
            {
                *Count_whole_bst = *Count_whole_bst + 1;
            };
            *Root = Q;
        }
        else
        {
            Insert_node(&Q, &Parent);
            if ((strcmp(Caract(*Word, 1), Caract(X, 1)) != 0) && (strcmp(Caract(*Word, 1), Caract(Y, 1)) != 0) && (strcmp(Caract(*Word, 1), Caract(Z, 1)) != 0))
            {
                Rotation_bst(&Q, &Parent);
                *Root = Q;
            }
            else
            {
                *Count_whole_bst = *Count_whole_bst + 1;
            }
        }
    };
}

/*---------------------------------------------------------------------------*/
/*                             Rotation BST                                  */
/*---------------------------------------------------------------------------*/
// Rotates node up to the root of the BST

void Rotation_bst(Pointeur_ATs *Q, Pointeur_ATs *Parent)
{
    /** Variables locales **/
    Pointeur_ATs Sub_tree = NULL;
    Pointeur_ATs Grandparent = NULL;

    /** Corps du module **/
    while ((Pere_ATs(*Q) != NULL))
    {
        *Parent = Pere_ATs(*Q);
        if ((Fg_ATs(*Parent) == *Q))
        {
            Right_rotation(&*Q, &*Parent);
        }
        else
        {
            Left_rotation(&*Q, &*Parent);
        }
    }
}
/*---------------------------------------------------------------------------*/
/*                             Right rotation                                */
/*---------------------------------------------------------------------------*/
// right rotation on node

void Right_rotation(Pointeur_ATs *P, Pointeur_ATs *Father)
{
    /** Variables locales **/
    Pointeur_ATs Grandparent = NULL;
    Pointeur_ATs Sub_tree = NULL;

    /** Corps du module **/
    Grandparent = Pere_ATs(*Father);
    Sub_tree = Fd_ATs(*P);
    Aff_fd_ATs(*P, *Father);
    Aff_fg_ATs(*Father, Sub_tree);
    if ((Sub_tree != NULL))
    {
        Aff_pere_ATs(Sub_tree, *Father);
    };
    Aff_pere_ATs(*Father, *P);
    Aff_pere_ATs(*P, Grandparent);
    if ((Grandparent != NULL))
    {
        if (Fg_ATs(Grandparent) == *Father)
        {
            Aff_fg_ATs(Grandparent, *P);
        }
        else
        {
            Aff_fd_ATs(Grandparent, *P);
        }
    }
}
/*---------------------------------------------------------------------------*/
/*                             Left rotation                                 */
/*---------------------------------------------------------------------------*/
// left rotation on node

void Left_rotation(Pointeur_ATs *P, Pointeur_ATs *Father)
{
    /** Variables locales **/
    Pointeur_ATs Grandparent = NULL;
    Pointeur_ATs Sub_tree = NULL;

    /** Corps du module **/
    Grandparent = Pere_ATs(*Father);
    Sub_tree = Fg_ATs(*P);
    Aff_fg_ATs(*P, *Father);
    Aff_fd_ATs(*Father, Sub_tree);
    if ((Sub_tree != NULL))
    {
        Aff_pere_ATs(Sub_tree, *Father);
    };
    Aff_pere_ATs(*Father, *P);
    Aff_pere_ATs(*P, Grandparent);
    if ((Grandparent != NULL))
    {
        if (Fd_ATs(Grandparent) == *Father)
        {
            Aff_fd_ATs(Grandparent, *P);
        }
        else
        {
            Aff_fg_ATs(Grandparent, *P);
        }
    }
}
/*---------------------------------------------------------------------------*/
/*                             Insert new node                               */
/*---------------------------------------------------------------------------*/
// Inserts a new node 

void Insert_node(Pointeur_ATs *P, Pointeur_ATs *Father)
{
    /** Variables locales **/
    Pointeur_ATs Temp = NULL;

    /** Corps du module **/
    if (strcmp(Struct1_Ts(Info_ATs(*P)), Struct1_Ts(Info_ATs(*Father))) < 0)
    {
        Aff_fg_ATs(*Father, *P);
        Aff_pere_ATs(*P, *Father);
    }
    else
    {
        Aff_fd_ATs(*Father, *P);
        Aff_pere_ATs(*P, *Father);
    }
}
/*---------------------------------------------------------------------------*/
/*                     Traverse and display the bst                          */
/*---------------------------------------------------------------------------*/
// Displays the BST level by level with show nodes starting with X, Y, or Z at each level

void Display_bst(Pointeur_ATs *R)
{
    /** Variables locales **/
    Pointeur_ATs Current = NULL;
    Pointeur_FATs Queue = NULL;
    int Nb_of_nodes_xyz;
    int Lvl;
    int I;
    int Nodes_in_current_level;
    int Nodes_in_next_level;

    /** Corps du module **/
    Lvl = 0;
    if ((*R == NULL))
    {
        printf("Empty tree");
    };
    Creerfile_FATs(&Queue);
    Enfiler_FATs(Queue, *R);
    Lvl = 0;
    Nb_of_nodes_xyz = 0;
    Nodes_in_current_level = 1;
    Nodes_in_next_level = 0;
    printf(BOLD BLUE "*-*-*-*-*-*-*-*-*-* level %d *-*-*-*-*-*-*-*-*-*\n", Lvl, RESET);
    while ((!Filevide_FATs(Queue)))
    {
        Defiler_FATs(Queue, &Current);
        if ((strcmp(Caract((Struct1_Ts(Info_ATs(Current))), 1), Caract(X, 1)) == 0) || (strcmp(Caract((Struct1_Ts(Info_ATs(Current))), 1), Caract(Y, 1)) == 0) || (strcmp(Caract((Struct1_Ts(Info_ATs(Current))), 1), Caract(Z, 1)) == 0))
        {
            Nb_of_nodes_xyz = Nb_of_nodes_xyz + 1;
        };
        if ((Fg_ATs(Current) != NULL))
        {
            Enfiler_FATs(Queue, Fg_ATs(Current));
            Nodes_in_next_level = Nodes_in_next_level + 1;
        };
        if ((Fd_ATs(Current) != NULL))
        {
            Enfiler_FATs(Queue, Fd_ATs(Current));
            Nodes_in_next_level = Nodes_in_next_level + 1;
        };
        Nodes_in_current_level = Nodes_in_current_level - 1;
        if ((Nodes_in_current_level == 0))
        {
            Lvl = Lvl + 1;
            printf(BOLD WHITE "\nThe number of words starting with x or y or z at this level is %d", Nb_of_nodes_xyz, RESET);
            printf("\n\n");
            Nb_of_nodes_xyz = 0;
            if ((!Filevide_FATs(Queue)))
            {
                printf(BOLD BLUE "*-*-*-*-*-*-*-*-*-* level %d *-*-*-*-*-*-*-*-*-*\n", Lvl, RESET);
            };
            Nodes_in_current_level = Nodes_in_next_level;
            Nodes_in_next_level = 0;
        };
    };
    printf(BOLD GREEN "The total depth is : %d", Lvl, RESET);
    printf("\n\n");
}
/*---------------------------------------------------------------------------*/
/*                             Inorder Traversal                             */
/*---------------------------------------------------------------------------*/
// Inorder traversal of the BST, prints each node

void Inorder(Pointeur_ATs *R)
{
    /** Variables locales **/
    Pointeur_ATs _Px1 = NULL;
    Pointeur_ATs _Px2 = NULL;

    /** Corps du module **/
    if (*R != NULL)
    {
        _Px1 = Fg_ATs(*R);
        Inorder(&_Px1);
        printf("%s%s%s%s", BOLD, WHITE, Struct1_Ts(Info_ATs(*R)), RESET);
        printf("\n");
        _Px2 = Fd_ATs(*R);
        Inorder(&_Px2);
    }
}
/*---------------------------------------------------------------------------*/
/*                             Search for a word                             */
/*---------------------------------------------------------------------------*/
// Searches for a word in the appropriate BST based on its first character

void Word_search(string255 *Word)
{

    /** Corps du module **/
    if (((strcmp(Caract(*Word, 1), Caract(X, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Y, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Z, 1)) == 0)))
    {
        Search_in_bst1(&Bst1, &*Word);
    }
    else
    {
        if ((strcmp(Caract(*Word, 1), Caract(X, 1)) > 0) || (strcmp(Caract(*Word, 1), Caract(Y, 1)) > 0) || (strcmp(Caract(*Word, 1), Caract(Z, 1)) > 0))
        {
            Search_in_bst2(&Bst2, &*Word);
        }
        else
        {
            Search_in_bst3(&Bst3, &*Word);
        }
    }
}
/*---------------------------------------------------------------------------*/
/*                        Search for a word in BST1                          */
/*---------------------------------------------------------------------------*/
// Search word in tree 1 (for X, Y, Z)

void Search_in_bst1(Pointeur_ATs *Bst, string255 *Word)
{
    /** Variables locales **/
    Pointeur_ATs P = NULL;
    bool Found;
    bool Stop;
    string255 Word_p;

    /** Corps du module **/
    Word_p = malloc(255 * sizeof(char));
    Found = False;
    Stop = False;
    P = *Bst;
    while ((!Found) && (!Stop) && (P != NULL))
    {
        if (strcmp(Struct1_Ts(Info_ATs(P)), *Word) == 0)
        {
            Found = True;
        }
        else
        {
            if (strcmp(*Word, Struct1_Ts(Info_ATs(P))) > 0)
            {
                P = Fd_ATs(P);
                if ((P != NULL))
                {
                    strcpy(Word_p, Struct1_Ts(Info_ATs(P)));
                    if ((strcmp(Caract(Word_p, 1), Caract(X, 1)) != 0) && (strcmp(Caract(Word_p, 1), Caract(Y, 1)) != 0) && (strcmp(Caract(Word_p, 1), Caract(Z, 1)) != 0))
                    {
                        Stop = True;
                    }
                }
            }
            else
            {
                P = Fg_ATs(P);
                if ((P != NULL))
                {
                    strcpy(Word_p, Struct1_Ts(Info_ATs(P)));
                    if ((strcmp(Caract(Word_p, 1), Caract(X, 1)) != 0) && (strcmp(Caract(Word_p, 1), Caract(Y, 1)) != 0) && (strcmp(Caract(Word_p, 1), Caract(Z, 1)) != 0))
                    {
                        Stop = True;
                    }
                }
            }
        };
    };
    if ((Found))
    {
        printf("\n");
        printf(BOLD GREEN "The word is found in BST1" RESET);
    }
    else
    {
        printf("\n");
        printf(BOLD RED "The word is not found in BST1" RESET);
    };
}
/*---------------------------------------------------------------------------*/
/*                        Search for a word in BST2                          */
/*---------------------------------------------------------------------------*/
// Search word in tree 2

void Search_in_bst2(Pointeur_ATs *Bst, string255 *Word)
{
    /** Variables locales **/
    Pointeur_ATs P = NULL;
    bool Found;
    bool Stop;
    string255 Word_p;

    /** Corps du module **/
    Word_p = malloc(255 * sizeof(char));
    Found = False;
    Stop = False;
    P = *Bst;
    while ((!Found) && (!Stop))
    {
        if (strcmp(Struct1_Ts(Info_ATs(P)), *Word) == 0)
        {
            Found = True;
        }
        else
        {
            if (strcmp(*Word, Struct1_Ts(Info_ATs(P))) > 0)
            {
                P = Fd_ATs(P);
                if ((P == NULL))
                {
                    Stop = True;
                }
            }
            else
            {
                P = Fg_ATs(P);
                if ((P == NULL))
                {
                    Stop = True;
                }
            }
        };
    };
    if ((Found))
    {
        printf("\n");
        printf(BOLD GREEN "The word is found in BST2" RESET);
    }
    else
    {
        printf("\n");
        printf(BOLD RED "The word is not found in BST2" RESET);
    }
}
/*---------------------------------------------------------------------------*/
/*                        Search for a word in BST3                          */
/*---------------------------------------------------------------------------*/
// Search word in tree 3 (stop if X, Y, Z)

void Search_in_bst3(Pointeur_ATs *Bst, string255 *Word)
{
    /** Variables locales **/
    Pointeur_ATs P = NULL;
    bool Found;
    bool Stop;
    string255 Word_p;

    /** Corps du module **/
    Word_p = malloc(255 * sizeof(char));
    Found = False;
    Stop = False;
    P = *Bst;
    while ((!Found) && (!Stop) && (P != NULL))
    {
        if (strcmp(Struct1_Ts(Info_ATs(P)), *Word) == 0)
        {
            Found = True;
        }
        else
        {
            if (strcmp(*Word, Struct1_Ts(Info_ATs(P))) > 0)
            {
                P = Fd_ATs(P);
                if ((P != NULL))
                {
                    strcpy(Word_p, Struct1_Ts(Info_ATs(P)));
                    if ((strcmp(Caract(Word_p, 1), Caract(X, 1)) == 0) || (strcmp(Caract(Word_p, 1), Caract(Y, 1)) == 0) || (strcmp(Caract(Word_p, 1), Caract(Z, 1)) == 0))
                    {
                        Stop = True;
                    }
                }
            }
            else
            {
                P = Fg_ATs(P);
                if ((P != NULL))
                {
                    strcpy(Word_p, Struct1_Ts(Info_ATs(P)));
                    if ((strcmp(Caract(Word_p, 1), Caract(X, 1)) == 0) || (strcmp(Caract(Word_p, 1), Caract(Y, 1)) == 0) || (strcmp(Caract(Word_p, 1), Caract(Z, 1)) == 0))
                    {
                        Stop = True;
                    }
                }
            }
        };
    };
    if ((Found))
    {
        printf("\n");
        printf(BOLD GREEN "The word is found in BST3" RESET);
    }
    else
    {
        printf("\n");
        printf(BOLD RED "The word is not found in BST3" RESET);
    };
}
/*---------------------------------------------------------------------------*/
/*                       Search for a word from file                         */
/*---------------------------------------------------------------------------*/
// Search word from file using the right tree

void Word_search_file(string255 *Word)
{

    /** Corps du module **/
    if (((strcmp(Caract(*Word, 1), Caract(X, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Y, 1)) == 0) || (strcmp(Caract(*Word, 1), Caract(Z, 1)) == 0)))
    {
        Search_in_bst1_file(&Bst1, &*Word);
    }
    else
    {
        if ((strcmp(Caract(*Word, 1), Caract(X, 1)) > 0) || (strcmp(Caract(*Word, 1), Caract(Y, 1)) > 0) || (strcmp(Caract(*Word, 1), Caract(Z, 1)) > 0))
        {
            Search_in_bst2_file(&Bst2, &*Word);
        }
        else
        {
            Search_in_bst3_file(&Bst3, &*Word);
        }
    }
    Search_in_bst0(&Bst0, &*Word);
    successful->len_search_paths_triplet = successful->len_search_paths_bst1 + successful->len_search_paths_bst2 + successful->len_search_paths_bst3;
    unsuccessful->len_search_paths_triplet = unsuccessful->len_search_paths_bst1 + unsuccessful->len_search_paths_bst2 + unsuccessful->len_search_paths_bst3;
}
/*---------------------------------------------------------------------------*/
/*                    Search for a word from file in BST1                    */
/*---------------------------------------------------------------------------*/
// Search word from file in tree 1 and track steps

void Search_in_bst1_file(Pointeur_ATs *Bst, string255 *Word)
{
    /** Variables locales **/
    Pointeur_ATs P = NULL;
    bool Found;
    bool Stop;
    string255 Word_p;
    int search_path = 1;
    /** Corps du module **/
    Word_p = malloc(255 * sizeof(char));
    Found = False;
    Stop = False;
    P = *Bst;
    while ((!Found) && (!Stop) && (P != NULL))
    {
        if (strcmp(Struct1_Ts(Info_ATs(P)), *Word) == 0)
        {
            Found = True;
        }
        else
        {
            if (strcmp(*Word, Struct1_Ts(Info_ATs(P))) > 0)
            {
                P = Fd_ATs(P);
                search_path++;
                if ((P != NULL))
                {
                    strcpy(Word_p, Struct1_Ts(Info_ATs(P)));
                    if ((strcmp(Caract(Word_p, 1), Caract(X, 1)) != 0) && (strcmp(Caract(Word_p, 1), Caract(Y, 1)) != 0) && (strcmp(Caract(Word_p, 1), Caract(Z, 1)) != 0))
                    {
                        Stop = True;
                    }
                }
            }
            else
            {
                P = Fg_ATs(P);
                search_path++;
                if ((P != NULL))
                {
                    strcpy(Word_p, Struct1_Ts(Info_ATs(P)));
                    if ((strcmp(Caract(Word_p, 1), Caract(X, 1)) != 0) && (strcmp(Caract(Word_p, 1), Caract(Y, 1)) != 0) && (strcmp(Caract(Word_p, 1), Caract(Z, 1)) != 0))
                    {
                        Stop = True;
                    }
                }
            }
        };
    };
    if ((Found))
    {
        successful->number_of_words_bst1++;
        successful->len_search_paths_bst1 = successful->len_search_paths_bst1 + search_path;
    }
    else
    {
        unsuccessful->number_of_words_bst1++;
        unsuccessful->len_search_paths_bst1 = unsuccessful->len_search_paths_bst1 + search_path;
    };
}
/*---------------------------------------------------------------------------*/
/*                    Search for a word from file in BST2                    */
/*---------------------------------------------------------------------------*/
// Search word from file in tree 2 and track steps

void Search_in_bst2_file(Pointeur_ATs *Bst, string255 *Word)
{
    /** Variables locales **/
    Pointeur_ATs P = NULL;
    bool Found;
    bool Stop;
    string255 Word_p;
    int search_path = 1;
    /** Corps du module **/
    Word_p = malloc(255 * sizeof(char));
    Found = False;
    Stop = False;
    P = *Bst;
    while ((!Found) && (!Stop))
    {
        if (strcmp(Struct1_Ts(Info_ATs(P)), *Word) == 0)
        {
            Found = True;
        }
        else
        {
            if (strcmp(*Word, Struct1_Ts(Info_ATs(P))) > 0)
            {
                P = Fd_ATs(P);
                search_path++;
                if ((P == NULL))
                {
                    Stop = True;
                }
            }
            else
            {
                P = Fg_ATs(P);
                search_path++;
                if ((P == NULL))
                {
                    Stop = True;
                }
            }
        };
    };
    if ((Found))
    {
        successful->number_of_words_bst2++;
        successful->len_search_paths_bst2 = successful->len_search_paths_bst2 + search_path;
    }
    else
    {
        unsuccessful->number_of_words_bst2++;
        unsuccessful->len_search_paths_bst2 = unsuccessful->len_search_paths_bst2 + search_path;
    }
}
/*---------------------------------------------------------------------------*/
/*                    Search for a word from file in BST3                    */
/*---------------------------------------------------------------------------*/
// Search word from file in tree 3 and track steps

void Search_in_bst3_file(Pointeur_ATs *Bst, string255 *Word)
{
    /** Variables locales **/
    Pointeur_ATs P = NULL;
    bool Found;
    bool Stop;
    string255 Word_p;
    int search_path = 1;

    /** Corps du module **/
    Word_p = malloc(255 * sizeof(char));
    Found = False;
    Stop = False;
    P = *Bst;
    while ((!Found) && (!Stop) && (P != NULL))
    {
        if (strcmp(Struct1_Ts(Info_ATs(P)), *Word) == 0)
        {
            Found = True;
        }
        else
        {
            if (strcmp(*Word, Struct1_Ts(Info_ATs(P))) > 0)
            {
                P = Fd_ATs(P);
                search_path++;
                if ((P != NULL))
                {
                    strcpy(Word_p, Struct1_Ts(Info_ATs(P)));
                    if ((strcmp(Caract(Word_p, 1), Caract(X, 1)) == 0) || (strcmp(Caract(Word_p, 1), Caract(Y, 1)) == 0) || (strcmp(Caract(Word_p, 1), Caract(Z, 1)) == 0))
                    {
                        Stop = True;
                    }
                }
            }
            else
            {
                P = Fg_ATs(P);
                search_path++;
                if ((P != NULL))
                {
                    strcpy(Word_p, Struct1_Ts(Info_ATs(P)));
                    if ((strcmp(Caract(Word_p, 1), Caract(X, 1)) == 0) || (strcmp(Caract(Word_p, 1), Caract(Y, 1)) == 0) || (strcmp(Caract(Word_p, 1), Caract(Z, 1)) == 0))
                    {
                        Stop = True;
                    }
                }
            }
        };
    };
    if ((Found))
    {
        successful->number_of_words_bst3++;
        successful->len_search_paths_bst3 = successful->len_search_paths_bst3 + search_path;
    }
    else
    {
        unsuccessful->number_of_words_bst3++;
        unsuccessful->len_search_paths_bst3 = unsuccessful->len_search_paths_bst3 + search_path;
    };
}
/*---------------------------------------------------------------------------*/
/*                    Search for a word from file in BST0                    */
/*---------------------------------------------------------------------------*/
void Search_in_bst0(Pointeur_ATs *root, string255 *word)
{
    Pointeur_ATs p = NULL;

    bool found = False;
    int search_path = 1;

    p = *root;

    while ((!found) && (p != NULL))
    {
        if (strcmp(Struct1_Ts(Info_ATs(p)), *word) == 0)
        {
            found = True;
        }
        else if (strcmp(Struct1_Ts(Info_ATs(p)), *word) > 0)
        {
            p = Fg_ATs(p);
            search_path++;
        }
        else
        {
            p = Fd_ATs(p);
            search_path++;
        }
    }

    if ((found))
    {
        successful->number_of_words++;
        successful->len_search_paths_bst0 = successful->len_search_paths_bst0 + search_path;
    }
    else
    {
        unsuccessful->number_of_words++;
        unsuccessful->len_search_paths_bst0 = unsuccessful->len_search_paths_bst0 + search_path;
    }
}
/*---------------------------------------------------------------------------*/
/*                        Find the smallest node                             */
/*---------------------------------------------------------------------------*/

void Smallestnode(Pointeur_ATs *Root, string255 *Word, Pointeur_ATs *Result, statR R)
{
    /** Variables locales **/
    Pointeur_ATs Current = NULL;

    /** Corps du module **/
    Current = *Root;
    *Result = NULL;
    while ((Current != NULL))
    {
        R->len_rang_word1++;
        if (strcmp(Struct1_Ts(Info_ATs(Current)), *Word) >= 0)
        {
            *Result = Current;
            Current = Fg_ATs(Current);
        }
        else
        {
            Current = Fd_ATs(Current);
        }
    }
}
/*---------------------------------------------------------------------------*/
/*                               Next inorder                                */
/*---------------------------------------------------------------------------*/

void Nextinorder(Pointeur_ATs *Current, Pointeur_ATs *Result, statR R)
{
    /** Variables locales **/
    Pointeur_ATs Node = NULL;
    Pointeur_ATs Parentnode = NULL;

    /** Corps du module **/
    *Result = NULL;
    if ((*Current == NULL)) // no inorder successor
    {
        *Result = *Result;
    }
    else
    {
        if (Fd_ATs(*Current) != NULL)
        {
            Node = Fd_ATs(*Current); // left most of the right child (next min )
            while ((Fg_ATs(Node) != NULL) && (Node != NULL))
            {

                Node = Fg_ATs(Node);
                R->len_rang_word2++;
            };
            *Result = Node;
            R->len_rang_word2++;
        }
        else
        { // no right child , go to the next parent
            Parentnode = Pere_ATs(*Current);

            while ((Parentnode != NULL) && (*Current == Fd_ATs(Parentnode)))
            {
                *Current = Parentnode;
                Parentnode = Pere_ATs(Parentnode);

                R->len_rang_word2++;
            };
            *Result = Parentnode;
            if (Parentnode != NULL)
            {
                R->len_rang_word2++;
            }
        }
    }
}
/*---------------------------------------------------------------------------*/
/*                  Process the node for range search                        */
/*---------------------------------------------------------------------------*/

void Process(Pointeur_ATs *Node)
{

    /** Corps du module **/

    if ((*Node != NULL))
    {
        printf("%s%s%s%s", BOLD, WHITE, Struct1_Ts(Info_ATs(*Node)), RESET);
        printf("\n");
    }
}
/*---------------------------------------------------------------------------*/
/*                           Search by range in BST                          */
/*---------------------------------------------------------------------------*/

void Rangquery(Pointeur_ATs *Root, string255 *Word1, string255 *Word2, statR R, int *found)
{
    /** Variables locales **/
    Pointeur_ATs Current2 = NULL;
    Pointeur_ATs Nextnode = NULL;
    *found = 0;
    /** Corps du module **/
    if (strcmp(*Word1, *Word2) >= 0)
    {
        printf(RED BOLD "Error: word1 must be less than word2 for rang query.\n" RESET);
        return;
    }

    else
    {
        Smallestnode(&*Root, &*Word1, &Current2, R);
        printf("\n");
        while ((Current2 != NULL) && (strcmp(Struct1_Ts(Info_ATs(Current2)), *Word2) < 0))
        {
            *found = 1;
            Process(&Current2);
            Nextinorder(&Current2, &Nextnode, R);
            Current2 = Nextnode;
        };
    }
}

/*---------------------------------------------------------------------------*/
/*                               Menu display                                */
/*---------------------------------------------------------------------------*/

void Menu(int *M)
{

    /** Corps du module **/
    printf("\n\n");
    printf(MAGENTA BOLD "+*+*+*+*+*+*+*+*+* M E N U +*+*+*+*+*+*+*+*+*\n" RESET);
    printf("\n");
    printf(WHITE BOLD "  1. Generate BST1, BST2, and BST3\n");
    printf("  2. Display BST1, BST2, and BST3\n");
    printf("  3. Inorder Traversal BST1, BST2, and BST3\n");
    printf("  4. Search a word in the triplet (BST1, BST2, BST3)\n");
    printf("  5. Search for all words within a range in the triplet (BST1, BST2, BST3)\n");
    printf("  6. Search in files F and F2\n");
    printf("  7. Range Statistics for M iterations \n");
    printf("  8. Exit\n" RESET);
    printf("\n\n");
    printf(MAGENTA BOLD "   Please enter your choice --> " RESET);
}
/*---------------------------------------------------------------------------*/
/*                         Decorations for intro                             */
/*---------------------------------------------------------------------------*/
void decoration_intro()
{
    printf("\n\n\n");
    printf(BOLD GREEN " _________        .---\"\"\"      \"\"\"---.              \n");
    printf(":______.-':      :  .--------------.  :             \n");
    printf("| ______  |      | :                : |             \n");
    printf("|:______B:|      | |      TPZ       | |             \n");
    printf("|:______B:|      | |    2024/2025   | |             \n");
    printf("|:______B:|      | |                | |             \n");
    printf("|:______B:|      | |   Cheballah    | |             \n");
    printf("|:______B:|      | | Tinhinane  G04 | |             \n");
    printf("|         |      | |                | |             \n");
    printf("|         |      | |     Kellil     | |             \n");
    printf("|:_____:  |      | |   Douaa  G05   | |             \n");
    printf("|    ==   |      | :                : |             \n");
    printf("|       O |      :  '--------------'  :             \n");
    printf("|       o |      :'---...______...---'              \n");
    printf("|       o |-._.-i___/'             \\._              \n");
    printf("|'-.____o_|   '-.   '-...______...-'  `-._          \n");
    printf(":_________:      `.____________________   `-.___.-. \n");
    printf("                 .'.eeeeeeeeeeeeeeeeee.'.      :___:\n");
    printf("               .'.eeeeeeeeeeeeeeeeeeeeee.'.         \n");
    printf("              :____________________________:        \n", RESET);
    printf("\n\n\n");
}
/*---------------------------------------------------------------------------*/
/*                         Decorations for outro                             */
/*---------------------------------------------------------------------------*/
void decoration_outro()
{
    printf(BOLD MAGENTA "  ||*\\_/*|________                     " WHITE "______________________                 " MAGENTA "||*\\_/*|________\n");
    printf("  ||_/-\\_|______  |                   " WHITE "|+*+*+ END OF TPZ +*+*+|                " MAGENTA "||_/-\\_|______  |\n");
    printf("  | |           | |                   " WHITE "|                      |                " MAGENTA "| |           | |\n");
    printf("  | |   0   0   | |                   " WHITE "|     DEVELOPED BY     |                " MAGENTA "| |   0   0   | |\n");
    printf("  | |     -     | |                   " WHITE "|  CHEBALLAH TINHINANE |                " MAGENTA "| |     -     | |\n");
    printf("  | |   \\___/   | |                   " WHITE "|         G04          |                " MAGENTA "| |   \\___/   | |\n");
    printf("  | |___________| |                   " WHITE "|     KELLIL DOUAA     |                " MAGENTA "| |___________| |\n");
    printf("  |_______________|                   " WHITE "|         G05          |        	      " MAGENTA "|_______________|\n");
    printf("   _|________|_                       " WHITE "|______________________|                 " MAGENTA "_|________|_\n");
    printf("   / ********** \\                                                              / ********** \\\n");
    printf(" /  ************  \\                                                          /  ************  \\\n");
    printf("--------------------                                                        --------------------" RESET "\n");
}
/*---------------------------------------------------------------------------*/
/*                  Process the node for freeing BST                         */
/*---------------------------------------------------------------------------*/
void Process2(Pointeur_ATs *Ptr)
{

    /** Corps du module **/
    Liberernoeud_ATs(*Ptr);
}
/*---------------------------------------------------------------------------*/
/*                           Postorder Traversal                             */
/*---------------------------------------------------------------------------*/
void Postorder(Pointeur_ATs *Root)
{
    /** Variables locales **/
    Pointeur_ATs _Px1 = NULL;
    Pointeur_ATs _Px2 = NULL;

    /** Corps du module **/
    if ((*Root != NULL))
    {
        _Px1 = Fg_ATs(*Root);
        Postorder(&_Px1);
        _Px2 = Fd_ATs(*Root);
        Postorder(&_Px2);
        Process2(&*Root);
    }
}
/*---------------------------------------------------------------------------*/
/*                               Free the BSTs                                */
/*---------------------------------------------------------------------------*/
void Freetree(Pointeur_ATs *Root1, Pointeur_ATs *Root2, Pointeur_ATs *Root3, Pointeur_ATs *Root4)
{

    /** Corps du module **/
    Postorder(&*Root1);
    Postorder(&*Root2);
    Postorder(&*Root3);
    Postorder(&*Root4);
}
/*---------------------------------------------------------------------------*/
/*                 Generate a file F with random words                       */
/*---------------------------------------------------------------------------*/

void gen_file_F(char *filename)
{
    Ouvrir_ss(&F, filename, "N");
    for (I = 1; I <= N; ++I)
    {
        J = Aleanombre(5);
        if (J == 0)
        {
            strcpy(_Sx, X);
            strcpy(Word, strcat(_Sx, Aleachaine(Aleanombre(3) + 3)));
        }
        else
        {
            if (J == 1)
            {
                strcpy(_Sx, Y);
                strcpy(Word, strcat(_Sx, Aleachaine(Aleanombre(3) + 3)));
            }
            else
            {
                if (J == 2)
                {
                    strcpy(_Sx, Z);
                    strcpy(Word, strcat(_Sx, Aleachaine(Aleanombre(3) + 3)));
                }
                else
                {
                    strcpy(Word, Aleachaine(Aleanombre(3) + 3));
                };
            };
        };
        S_S.Champ1 = malloc(255 * sizeof(char));
        strcpy(S_S.Champ1, Word);
        Init_struct_Tss(S, S_S);
        Ecrireseq_ss(F, S);

        strcpy(Word, Struct1_Tss(S));
        Construct_bst1(&Bst1, &Word, &Count_whole_bst1);
        Construct_bst2(&Bst2, &Word, &Count_whole_bst2);
        Construct_bst3(&Bst3, &Word, &Count_whole_bst3);
        Construct_bst0(&Bst0, &Word, &Count_whole_bst0);
    };
    Fermer_ss(F);
}

/*---------------------------------------------------------------------------*/
/*                 Generate a file F2 with random words                      */
/*---------------------------------------------------------------------------*/
void gen_file_F2(char *filename)
{
    Ouvrir_ss(&F, filename, "N");
    for (I = 1; I <= N; ++I)
    {
        J = Aleanombre(5);
        if (J == 0)
        {
            strcpy(_Sx, X);
            strcpy(Word, strcat(_Sx, Aleachaine(Aleanombre(3) + 3)));
        }
        else
        {
            if (J == 1)
            {
                strcpy(_Sx, Y);
                strcpy(Word, strcat(_Sx, Aleachaine(Aleanombre(3) + 3)));
            }
            else
            {
                if (J == 2)
                {
                    strcpy(_Sx, Z);
                    strcpy(Word, strcat(_Sx, Aleachaine(Aleanombre(3) + 3)));
                }
                else
                {
                    strcpy(Word, Aleachaine(Aleanombre(3) + 3));
                };
            };
        };
        S_S.Champ1 = malloc(255 * sizeof(char));
        strcpy(S_S.Champ1, Word);
        Init_struct_Tss(S, S_S);
        Ecrireseq_ss(F, S);
    };
    Fermer_ss(F);
}
/*---------------------------------------------------------------------------*/
/*                          Word Search in a file                            */
/*---------------------------------------------------------------------------*/
void search_in_file(char *filename)

{
    string255 mot;
    Ouvrir_ss(&F, filename, "A");
    I = 0;
    while (!Finfich_ss(F))
    {
        I++;
        Lireseq_ss(F, S);
        mot = S->Champ1;
        Word_search_file(&mot);
    }
    Fermer_ss(F);
}

/*---------------------------------------------------------------------------*/
/*                     Search by range from file in BST                      */
/*---------------------------------------------------------------------------*/
// This function performs a range search in the BST based on two words read from a file generated
void Rangquery2(Pointeur_ATs *Root, string255 *Word1, string255 *Word2, statR R, int *found)
{
    /** Variables locales **/
    Pointeur_ATs Current2 = NULL;
    Pointeur_ATs Nextnode = NULL;
    *found = 0;
    /** Corps du module **/
    if (strcmp(*Word1, *Word2) >= 0)
    {
        return;
    }

    else
    {
        Smallestnode(&*Root, &*Word1, &Current2, R);

        while ((Current2 != NULL) && (strcmp(Struct1_Ts(Info_ATs(Current2)), *Word2) < 0))
        {
            *found = 1;

            Nextinorder(&Current2, &Nextnode, R);
            Current2 = Nextnode;
        };
    }
}

/*---------------------------------------------------------------------------*/
/*                     Search by range from file in BST                      */
/*---------------------------------------------------------------------------*/
// This function reads pairs of words from a file and performs a range search in the BST

int RANG(Pointeur_ATs *Bst, char *filename, statR R)
{

    string255 mot1 = malloc(255 * sizeof(char));
    string255 mot2 = malloc(255 * sizeof(char));
    int total = 0;
    int totalall = 0;
    int found = 0;
    Ouvrir_ss(&F, filename, "A");

    while (!Finfich_ss(F))
    {
        Lireseq_ss(F, S);
        strcpy(mot1, S->Champ1); // lire the first word

        if (Finfich_ss(F))
        {
            break;
        } // no second word, exit loop

        Lireseq_ss(F, S);
        strcpy(mot2, S->Champ1); // lire the second word

        if (strcmp(mot1, mot2) > 0)
        {
            continue; // Skip this pair, do not add to statistics
        }

        R->len_rang_word1 = 0;
        R->len_rang_word2 = 0;

        Rangquery2(Bst, &mot1, &mot2, R, &found);

        if (found)
        {
            total = R->len_rang_word1 + R->len_rang_word2;

            totalall += total;
        }
    }

    Fermer_ss(F);

    printf(BOLD WHITE "Total nodes traversed for all valid pairs: %d\n", totalall, RESET);
    printf(BOLD CYAN "\n-----------------------------------------------\n" RESET);
    free(mot1);
    free(mot2);

    return totalall;
}
/*---------------------------------------------------------------------------*/
/*                     choose the min of 3 values                            */
/*---------------------------------------------------------------------------*/
// used in statistics to find the minimum total of traversed nodes in all 3 BSTs
int MINTOTAL(int totalbst1, int totalbst2, int totalbst3)
{
    int mintotal = totalbst1;

    if (totalbst2 < mintotal)
        mintotal = totalbst2;
    if (totalbst3 < mintotal)
        mintotal = totalbst3;
    return mintotal;
}

/*---------------------------------------------------------------------------*/
/*------------------------------- Main Program ------------------------------*/
/*---------------------------------------------------------------------------*/
int main()
{
    srand(time(NULL));
    S = malloc(sizeof(Typestruct1_ss));
    S->Champ1 = malloc(255 * sizeof(char));
    Snode = malloc(sizeof(Type_Ts));
    Snode->Champ1 = malloc(255 * sizeof(char));
    Word = malloc(255 * sizeof(char));
    Word1 = malloc(255 * sizeof(char));
    Word2 = malloc(255 * sizeof(char));
    X = malloc(255 * sizeof(char));
    C = malloc(255 * sizeof(char));
    Y = malloc(255 * sizeof(char));
    Z = malloc(255 * sizeof(char));
    Temp = malloc(255 * sizeof(char));
    _Sx = malloc(255 * sizeof(char));
    _Px1 = 0;
    init_statistics(&successful);
    init_statistics(&unsuccessful);
    decoration_intro();
    Menu(&_Px1);
    scanf(" %d", &Choice);
    while (Choice != 8)
    {
        if (Choice == 1)
        {
            Bst0 = NULL;
            Bst1 = NULL;
            Bst2 = NULL;
            Bst3 = NULL;
            Count_whole_bst1 = 0;
            Count_whole_bst2 = 0;
            Count_whole_bst3 = 0;
            printf("\n\n");
            printf(BOLD WHITE " %s", "Please enter x : " RESET);
            scanf(" %[^\n]", X);
            printf("\n");
            printf(BOLD WHITE " %s", "Please enter y : " RESET);
            scanf(" %[^\n]", Y);
            printf("\n");
            printf(BOLD WHITE " %s", "Please enter z : " RESET);
            scanf(" %[^\n]", Z);
            printf("\n");
            gen_file_F("F.z");
            printf("\n");
            printf(GREEN BOLD " The triplet is generated successfully !", RESET);
            printf("\n");
            _Px2 = 0;
            Menu(&_Px2);
            scanf(" %d", &Choice);
        };
        if (Choice == 2)
        {
            printf("\n");
            if ((Bst1 == NULL) || (Bst2 == NULL) || (Bst3 == NULL))
            {
                printf(RED BOLD " Please generate the triplet first ", RESET);
                printf("\n");
            }
            else
            {
                printf("\n\n");
                printf(BOLD MAGENTA " ____ ____ _____ _ \n" RESET);
                printf(BOLD MAGENTA "| __ ) ___|_   _/ |\n" RESET);
                printf(BOLD MAGENTA "|  _ \\___ \\ | | | |\n" RESET);
                printf(BOLD MAGENTA "| |_) |__) || | | |\n" RESET);
                printf(BOLD MAGENTA "|____/____/ |_| |_|\n" RESET);
                printf("\n\n");
                printf(BOLD GREEN "The number of words starting with x or y or z in BST1 is  %d", Count_whole_bst1, RESET);
                printf("\n\n");
                Display_bst(&Bst1);
                printf("\n\n");
                printf("\n\n");
                printf(BOLD MAGENTA " ____ ____ _____ ____  \n" RESET);
                printf(BOLD MAGENTA "| __ ) ___|_   _|___ \\ \n" RESET);
                printf(BOLD MAGENTA "|  _ \\___ \\ | |   __) |\n" RESET);
                printf(BOLD MAGENTA "| |_) |__) || |  / __/ \n" RESET);
                printf(BOLD MAGENTA "|____/____/ |_| |_____|\n" RESET);
                printf("\n\n");
                printf(BOLD GREEN "The number of words starting with x or y or z in BST2 is  %d", Count_whole_bst2, RESET);
                printf("\n\n");
                Display_bst(&Bst2);
                printf("\n\n");
                printf("\n\n");
                printf(BOLD MAGENTA " ____ ____ _____ _____ \n" RESET);
                printf(BOLD MAGENTA "| __ ) ___|_   _|___ / \n" RESET);
                printf(BOLD MAGENTA "|  _ \\___ \\ | |   |_ \\ \n" RESET);
                printf(BOLD MAGENTA "| |_) |__) || |  ___) |\n" RESET);
                printf(BOLD MAGENTA "|____/____/ |_| |____/ \n" RESET);
                printf("\n\n");
                printf(BOLD GREEN "The number of words starting with x or y or z in BST3 is  %d", Count_whole_bst3, RESET);
                printf("\n\n");
                Display_bst(&Bst3);
                printf("\n\n");
                printf("\n");
                printf("\n");
            };
            _Px3 = 0;
            Menu(&_Px3);
            scanf(" %d", &Choice);
        };
        if (Choice == 3)
        {
            if ((Bst1 == NULL) || (Bst2 == NULL) || (Bst3 == NULL))
            {
                printf("\n");
                printf(RED BOLD " Please generate the triplet first ", RESET);
                printf("\n");
            }
            else
            {
                printf("\n\n");
                printf(BOLD BLUE "*-*-*-*-*-*-*-*INORDER Traversal BST1*-*-*-*-*-*-*-*\n\n" RESET);
                Inorder(&Bst1);
                printf("\n\n");
                printf(BOLD BLUE "*-*-*-*-*-*-*-*INORDER Traversal BST2*-*-*-*-*-*-*-*\n\n" RESET);
                Inorder(&Bst2);
                printf("\n\n");
                printf(BOLD BLUE "*-*-*-*-*-*-*-*INORDER Traversal BST3*-*-*-*-*-*-*-*\n\n" RESET);
                Inorder(&Bst3);
                printf("\n\n");
            };
            _Px4 = 0;
            Menu(&_Px4);
            scanf(" %d", &Choice);
        };
        if (Choice == 4)
        {
            if ((Bst1 == NULL) || (Bst2 == NULL) || (Bst3 == NULL))

            {
                printf("\n");
                printf(RED BOLD " Please generate the triplet first ", RESET);
                printf("\n");
            }
            else
            {
                printf("\n\n");
                printf(BOLD WHITE "Please enter the word you want to search for : " RESET);
                scanf(" %[^\n]", Word);
                printf("\n");
                Word_search(&Word);
            };
            _Px5 = 0;
            Menu(&_Px5);
            scanf(" %d", &Choice);
        };
        if (Choice == 5)
        {
            int found = 0;
            if ((Bst1 == NULL) || (Bst2 == NULL) || (Bst3 == NULL) || (Bst0 == NULL))
            {
                printf("\n");
                printf(RED BOLD " Please generate the triplet first ", RESET);
                printf("\n");
            }
            else
            {
                statR R;
                init_statisticsR(&R);

                printf(BOLD WHITE "\nPlease enter word1: " RESET);
                scanf(" %[^\n]", Word1);
                printf(BOLD WHITE "\nPlease enter word2: " RESET);
                scanf(" %[^\n]", Word2);
                printf(BOLD BLUE "\nThe result in the triplet (BST1, BST2, BST3) is\n\n" RESET);
                /*We get the same display for each bst search
              so it's enough to display only one*/
                Rangquery(&Bst1, &Word1, &Word2, R, &found);

                printf("\n");
            };
            _Px6 = 0;
            Menu(&_Px6);
            scanf(" %d", &Choice);
        };
        if (Choice == 6)
        {
            Bst0 = NULL;
            Bst1 = NULL;
            Bst2 = NULL;
            Bst3 = NULL;
            Count_whole_bst0 = 0;
            Count_whole_bst1 = 0;
            Count_whole_bst2 = 0;
            Count_whole_bst3 = 0;
            printf("\n\n");
            printf(BOLD WHITE " %s", "Please enter x : " RESET);
            scanf(" %[^\n]", X);
            printf("\n");
            printf(BOLD WHITE " %s", "Please enter y : " RESET);
            scanf(" %[^\n]", Y);
            printf("\n");
            printf(BOLD WHITE " %s", "Please enter z : " RESET);
            scanf(" %[^\n]", Z);
            printf("\n");
            for (int d = 0; d < M; d++)
            {
                printf(BOLD MAGENTA "\n\n\n*-*-*-*-*-*-*-*-*-*- Simulation %d *-*-*-*-*-*-*-*-*-*-*\n", d + 1, RESET);
                init_statistics(&successful);
                init_statistics(&unsuccessful);
                gen_file_F("F.z");
                search_in_file("F.z");
                gen_file_F2("F2.z");
                search_in_file("F2.z");
                printf(BOLD GREEN "\n*-*-*-*-*-*-*-*-*-*- Successful *-*-*-*-*-*-*-*-*-*-*\n", d + 1, RESET);
                printf(WHITE BOLD "words searched in bst0 (total number of words) --> %d\n", successful->number_of_words, RESET);
                printf(WHITE BOLD "words searched in bst1 --> %d\n", successful->number_of_words_bst1, RESET);
                printf(WHITE BOLD "total length of search paths in bst1 --> %d\n", successful->len_search_paths_bst1, RESET);
                printf(WHITE BOLD "words searched in bst2 --> %d\n", successful->number_of_words_bst2, RESET);
                printf(WHITE BOLD "total length of search paths in bst2 --> %d\n", successful->len_search_paths_bst2, RESET);
                printf(WHITE BOLD "words searched in bst3 --> %d\n", successful->number_of_words_bst3, RESET);
                printf(WHITE BOLD "total length of search paths in bst3 --> %d\n", successful->len_search_paths_bst3, RESET);
                printf(GREEN BOLD "total length of search paths in successful searches in triplet --> %d\n", successful->len_search_paths_triplet, RESET);
                printf(GREEN BOLD "total length of search paths in successful searches in bst0 --> %d\n", successful->len_search_paths_bst0, RESET);
                printf(BOLD RED "\n*-*-*-*-*-*-*-*-*-*- Unsuccessful *-*-*-*-*-*-*-*-*-*-*\n", d + 1, RESET);
                printf(WHITE BOLD "words searched in bst0 --> %d\n", unsuccessful->number_of_words, RESET);
                printf(WHITE BOLD "words searched in bst1 --> %d\n", unsuccessful->number_of_words_bst1, RESET);
                printf(WHITE BOLD "total length of search paths in bst1 --> %d\n", unsuccessful->len_search_paths_bst1, RESET);
                printf(WHITE BOLD "words searched in bst2 --> %d\n", unsuccessful->number_of_words_bst2, RESET);
                printf(WHITE BOLD "total length of search paths in bst2 --> %d\n", unsuccessful->len_search_paths_bst2, RESET);
                printf(WHITE BOLD "words searched in bst3 --> %d\n", unsuccessful->number_of_words_bst3, RESET);
                printf(WHITE BOLD "total length of search paths in bst3 --> %d\n", unsuccessful->len_search_paths_bst3, RESET);
                printf(RED BOLD "total length of search paths in unsuccessful searches in triplet --> %d\n", unsuccessful->len_search_paths_triplet, RESET);
                printf(RED BOLD "total length of search paths in unsuccessful searches bst0 --> %d\n", unsuccessful->len_search_paths_bst0, RESET);
            }
            _Px7 = 0;
            Menu(&_Px7);
            scanf(" %d", &Choice);
        }

        if (Choice == 7)
        {
            int x = 0;
            int y = 0;
            int z = 0;
            printf("\n\n");
            printf(BOLD WHITE " %s", "Please enter x : " RESET);
            scanf(" %[^\n]", X);
            printf("\n");
            printf(BOLD WHITE " %s", "Please enter y : " RESET);
            scanf(" %[^\n]", Y);
            printf("\n");
            printf(BOLD WHITE " %s", "Please enter z : " RESET);
            scanf(" %[^\n]", Z);
            printf("\n");
            printf("\n\n");
            printf(BOLD WHITE " %s", "Please enter word1 : " RESET);
            scanf(" %[^\n]", Word1);
            printf("\n");
            printf(BOLD WHITE " %s", "Please enter word2 : " RESET);
            scanf(" %[^\n]", Word2);
            printf("\n");

            for (int d = 0; d < M; d++)
            {

                printf(BOLD CYAN "\n\n\n*-*-*-*-*-*-*-*- Simulation %d *-*-*-*-*-*-*-*-*\n", d + 1, RESET);

                Bst0 = NULL;
                Bst1 = NULL;
                Bst2 = NULL;
                Bst3 = NULL;
                Count_whole_bst0 = 0;
                Count_whole_bst1 = 0;
                Count_whole_bst2 = 0;
                Count_whole_bst3 = 0;

                gen_file_F("F.z");
                gen_file_F2("F2.z");

                statR R0, R1, R2, R3;

                init_statisticsR(&R0);
                init_statisticsR(&R1);
                init_statisticsR(&R2);
                init_statisticsR(&R3);

                printf(BOLD MAGENTA "\nBST0 Range Results:\n" RESET);
                int totalbst0 = RANG(&Bst0, "F2.z", R0);

                printf(BOLD MAGENTA "\nBST1 Range Results:\n" RESET);
                int totalbst1 = RANG(&Bst1, "F2.z", R1);

                printf(BOLD MAGENTA "\nBST2 Range Results:\n" RESET);
                int totalbst2 = RANG(&Bst2, "F2.z", R2);

                printf(BOLD MAGENTA "\nBST3 Range Results:\n" RESET);
                int totalbst3 = RANG(&Bst3, "F2.z", R3);

                printf(BOLD CYAN "\n\n------------------ SUMMARY --------------------\n\n" RESET);
                printf(BOLD GREEN "BST0 total nodes: %d\n" RESET, totalbst0);
                int mintotal = MINTOTAL(totalbst1, totalbst2, totalbst3);
                printf(BOLD YELLOW "Minimum total for triplet: %d\n" RESET, mintotal);
                printf(BOLD CYAN "\n-----------------------------------------------\n" RESET);

                printf(BOLD WHITE "\nDetailed statistics:\n" RESET);
                printf(BOLD BLUE "BST1: %d\n" RESET, totalbst1);
                printf(BOLD BLUE "BST2: %d\n" RESET, totalbst2);
                printf(BOLD BLUE "BST3: %d\n" RESET, totalbst3);
                printf("\n");
                free(R0);
                free(R1);
                free(R2);
                free(R3);
            }
            printf(BOLD WHITE " :) FIN.. ", RESET);
            _Px7 = 0;
            Menu(&_Px7);
            scanf(" %d", &Choice);
            break;
        }
        if ((Choice < 1) || (Choice > 8))
        {
            printf("\n");
            printf(RED BOLD " Please choose a valid option " RESET);
            printf("\n");
            _Px7 = 0;
            Menu(&_Px7);
            scanf(" %d", &Choice);
        };
    }
    Freetree(&Bst1, &Bst2, &Bst3, &Bst0);
    printf(BOLD GREEN "\n\n The triplet (BST1,BST2,BST3) and BST0 are freed successfully !\n\n" RESET);
    printf("\n\n\n\n");
    decoration_outro();
    return 0;
}
/*---------------------------------------------------------------------------*/
/*----------------------------- End of Program ------------------------------*/