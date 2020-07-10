#ifndef MES_FONCTION
#define MES_FONCTION
#include <stdio.h>
#include <stdlib.h>
#include"mestypes.h"

int est_operande(char c);
int caractere_accepter(char c);
int est_operateur(char c);
Llist_token ajouterEnFin(Llist_token liste, double  valeur,double type);
void affichage_liste(Llist_token liste);
char * gestion_des_espaces(char*exp,char *NewPhrase);
Llist_token  chaineAuFloat(char *ch, Elm *t, int *n);
int lexiqueJuste(char* exp);
int est_expression_arithmetique_correcte(char* exp);
int operateur(Elm e);
int operande(Elm e);
int priorite(Elm e);
double operation(Elm x1, Elm op, Elm x2);
void afficheElm(Elm e);
void initPile(Pile **p);
int est_vide(Pile* p);
Elm sommet_pile(Pile* p);
void empiler(Pile** p, Elm e);
void depiler(Pile** p, Elm* e);
Pile* passage_infixe_a_postfixe(Elm* t, int n);
int arbreVide(Arbre* a);
int est_feuille(Arbre* a);
Arbre* creation_feuille_arbre(Elm e);
void initialisation_pile_arbre(PileAebre** p);
int creation_pile_vide_arbre(PileAebre* p);
Arbre* sommet_pile_arbre(PileAebre* p);
void empilerA(PileAebre** p, Arbre* a);
void depilerA(PileAebre** p, Arbre** a);
Arbre* construction_arbre(Elm* t, int n);
double calcul_expression_arithmetique(Arbre* a);
void affichage_arbre(Arbre* a);


#endif /* MES_FONCTION*/
