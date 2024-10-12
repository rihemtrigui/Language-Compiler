#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define program 1
#define pv 2 // point virgule
#define p 3 //point
#define var 4
#define dp 5 //2 points
#define id 6
#define v 7 // virgule
#define integer 8
#define rchar 9
#define begin 10
#define end 11
#define opaf 12
#define iff 13
#define then 14
#define elsee 15
#define whilee 16
#define doo 17
#define po 18 //parenthese ouvrant
#define pf 19 //parenthese fermant
#define write 20
#define read 21
#define writeln 22
#define readln 23
#define oprel 24
#define opadd 25
#define opmul 26
#define nb 27
#define ppe 28 
#define dif 29
#define ppq 30
#define pgq 31
#define pge 32
#define ega 33
FILE *fs;  
FILE *fd;  
int indiceTableSymboles= 0;
int sym;   
char mot_cle[20][20]={"program", "begin", "var",
"integer", "char", "end", "then", "if", "else", "read",
"readln", "write", "writeln", "do", "while"}; 
int id_mot_cle[20]={1,10,4,8,9,11,14,13,15,21,23,20,22,17,16}; 
char ch[20]; // chaine pour storer les caract�res parcourus
int z=0 ; 
char tab_iden[100][20]; 
typedef struct token {
    int ul;
    int att;
}token;
token symbole;
/******** Anal Syn + Sem + Gen Code Int ********/

int symbole_suivant(){
    return analyLex();
} 

void erreur(int T)
{
   printf("symbole non accepte !");
} 

void accepter(int T)
{
	if (symbole==T) 
	{
		symbole=symbole_suivant();
	}
	else
	{
		erreur();
	}
}
int compatible(char ch1, char ch2) {
   return(strcmp(ch1,ch2)==0 ) ;

}

char* chercher_type(const char* nom) {
    for (int i = 0; i < nombreSymboles; i++) {

        if (strcmp(tableSymboles[i].nom , nom) == 0) {

            
            return tableSymboles[i].type;
        }
    }
    return NULL;
}

void emettre(char* ch){ 
 FILE* fichier = fopen("codeInterm.txt", "a");

    if (fichier != NULL) {
        fprintf(fichier, "%s\n", ch); 
        fclose(fichier);
    } else {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier 'codeInterm.txt'\n");
        exit(EXIT_FAILURE);
    }
}

void ajouter_type(const char* nom, const char* type) {
    tableSymboles[nombreSymboles].nom = strdup(nom);
    tableSymboles[nombreSymboles].type = strdup(type);
    nombreSymboles++;
}
void P()
{       emettre(6)
        accepter(1); //program
        accepter(6); //id
        accepter(2); //;
        DCL(); //dcl
        Inst_compose();//inst_comps�e
    }

void DCL()
{
    D();
}

void D()
{
    if(sym == 4 )
    {  
        accepter(4);//var
        List_id(); //liste_id
        accepter(5);//:
        ajouter_type(sym,Type());
        accepter(2);//;
        D();
    }
}

void List_id()
{
    if(sym == 6)//id
    {
        accepter(6);
        L();
    }
    else
    {
        printf("id manquant");
    }
}

void L()
{
    if(sym == 7)// virgule
    {
        accepter(7);
        accepter(6);
        L();
    }
}

void Type()
{
    if(sym == 8)// integer
    {
        accepter(8);
    }
    else if(sym == 9) //rchar
    {
        accepter(9);
    }
}

void Inst_compose()
{
    if (sym == 10)//begin
    {
        accepter(10);
        Inst();
        accepter(9);
    }
}

void Inst()
{
    List_inst();
}

void List_inst()
{
    I();
    L_I();
}

void L_I()
{
    if(sym == 2)//;
    {
        accepter(2);
        I();
        L_I();
    }

}

void I()
{
    if (sym == 6)//id
    {
        accepter(6);
        accepter(12);
        Exp_S();
    }
    else if(sym == 13)//if
    {
        accepter(13);
        Exp();
        accepter(14);//then
        I();
        accepter(15);// begin
        I();
    }
    else if(sym == 16)//while
    {
        accepter(16);
        Exp();
        accepter(17);//do
        I();
    }
    else if(sym == 21)//read
    {
        accepter(21);
        accepter(18);//po
        accepter(6);//id
        accepter(19);//pf
    }
    else if (sym == 23)//readln
    {
        accepter(23);
        accepter(18);
        accepter(6);
        accepter(19);
    }
    else if(sym == 20)//write
    {
        accepter(20);
        accepter(18);
        accepter(6);
        accepter(19);
    }
    else if(sym == 22)//writeln
    {
        accepter(22);
        accepter(18);//po
        accepter(6);//id
        accepter(19);//pf
    }
    else if(sym ==11)//end
    {
        accepter(11);
        accepter(3);//.
        printf("FIN DE PROGRAMME!");
        exit(0);


    }
    else
    {
        printf("Syntaxe invalide");
    }

}

void Exp()
{
    Exp_S();
    S();
}

void S()
{
    Exp_S();
}

void Exp_S()
{
    Terme();
    E();
}

void E()
{
    if(sym == 24)//oprel
    {
        accepter(24);
        Exp_S();
        E();
    }
}

void Terme()
{
    Facteur();
    T();
}

void T()
{
    if (sym == 24)//oprel
    {
        accepter(24);
        Facteur();
        T();
    }
}

void Facteur()
{
    if(sym == 6)//id
    {
        accepter(6);
    }
    else if( sym == 27)//nb
    {
        accepter(27);
    }
    else if(sym == 18)//po
    {
        accepter(18);
        Exp_S();
        accepter(19);
    }

}

/****** Anal Lexical ********/

char carSuivant(){
    return(fgetc(fs));
} //lire le carct�re suivant d'un fichier

void Reculer(int k)
{
    fseek(fs, -k, SEEK_CUR);
} //permet de ce reculer le pointeur du fichier du k bits

int UniLexId()
{
    int k=0;
    int i=0;
    while (i<14&&(!k)) {
        if(strcmp(mot_cle[i],ch)== 0){
            k=1;
        }else{
           i++;
        }
    }
    if (k==1){
        return id_mot_cle[i];
    }
    else {
        return id;
    }
}

int RangerId(int k, int* c)
{
    int s=0;
    if (k == id) {
    while ((strcmp(tab_iden[s], ch) != 0) && (s < (*c)))
        s++;
    if (s < *c) {
        return s;
    } else {
        (*c)++;
         strcpy(tab_iden[*c], ch);
         return *c;
    }}
    else{
       return 0;
        }
}
int analyLex() {
    int etat = 0;
    char car ;
    int colonne = 0, ligne = 1;
    while (1) {
        switch (etat) {
            case 0:
                car = carSuivant();
                int k;
                if (car == ' ') {
                    colonne++;
                    etat = 0;
                } else if (car == '\n') {
                    ligne++;
                    colonne = 0;
                    etat = 0;
                }else if(car=='\t'){
                    colonne+=3;
                    etat=0;
                }
                else if (isalpha(car)){
                    z=0;
                    ch[0]=car;
                    etat=1;
                }
                else if (isdigit(car)) {
                    etat = 3;
                } else if (car == '<') {
                    etat = 5;
                } else if (car == '>') {
                    etat = 10;
                } else if (car == '=') {
                    etat = 9;
                } else if (car == '$') {
                    printf("end of file ");
                    etat = 13;
                }else if(car==';'){
                    etat=15;
                }
                else if (car==',')
                    etat=16;
                else if (car=='(')
                    etat=17;
                else if (car==':')
                    etat=18;
                else if (car==')')
                    etat=19;
                else {
                    etat = 14;
                }
                break;
            case 1:
                car = carSuivant();
                if (isalpha(car) || isdigit(car)) {
                    z++;
                    ch[z] = car;
                } else {
                    etat = 2;
                    ch[z + 1] = '\0';
                    printf(ch);
                    z = 0;
                }
                break;
            case 2:
                Reculer(1);
                symbole.ul = UniLexId();
                symbole.att = RangerId(symbole.ul, &ch);
                return symbole.ul ;
            case 3:
                Reculer(1);
                car = carSuivant();
                if (isdigit(car)) {
                    z++;
                    ch[z] = car;
                } else {
                    etat = 4;
                    ch[z + 1] = '\0';
                    z = 0;
                }
                break;
            case 4:
                Reculer(1);
                symbole.ul = nb;
                symbole.att = atoi(ch);
                return symbole.ul;
            case 5:
                car = carSuivant();
                switch (car) {
                    case '=':
                        etat = 6;
                        break;
                    case '>':
                        etat = 7;
                        break;
                    default:
                        etat = 8;
                }
                break;
            case 9:
                symbole.ul = oprel;
                symbole.att = oprel;
                return symbole.ul;
            case 10:
                Reculer(1);
                car = carSuivant();
                if (car == '=') {
                    etat = 11;
                } else {
                    symbole.ul = oprel;
                    symbole.att = oprel;
                    return symbole.ul;
                }
            case 11:
                symbole.ul = oprel;
                symbole.att = oprel;
                return symbole.ul;
            case 6:
                symbole.ul = oprel;
                symbole.att = oprel;
                return symbole.ul;
            case 7:
                symbole.ul = oprel;
                symbole.att = oprel;
                return symbole.ul;
            case 8:
                Reculer(1);
                symbole.ul = oprel;
                symbole.att = oprel;
                return symbole.ul;
            case 12:
                symbole.ul = oprel;
                symbole.att = oprel;
                return symbole.ul;
            case 13:
                symbole.ul = 100;
                symbole.att = 0;
                return symbole.ul;
            case 14:
                printf("Erreur : caract�re inattendu � la ligne %d, colonne %d\n", ligne, colonne);
                etat=0;
                break;
            case 15:
                symbole.ul=pv;
                symbole.att=0;
                return symbole.ul;
            case 16:
                symbole.ul=v;
                symbole.att=0;
                return symbole.ul;
            case 17:
                symbole.ul=po;
                symbole.att=0;
                return symbole.ul;
            case 18:
                ch[0]=car;
                car=carSuivant();
                if (car=='='){
                    symbole.ul=opaf;
                    symbole.att=0;
                    return symbole.ul;
                } else{
                    etat=20;
                }
            case 19:
                symbole.ul=pf;
                symbole.att=0;
                return symbole.ul;
            case 20:
                Reculer(1);
                symbole.ul=dp;
                symbole.att=0;
                return symbole.ul;
}
}
}

/****** Main ********/
int main()
{
    fs = fopen("codeSource.txt","rt");
    fd = fopen("codeInterm.txt","wt");
    P();
    fclose(fs);
    fclose(fd);
    return 0;
}
