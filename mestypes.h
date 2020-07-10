#ifndef MES_TYPES
#define MES_TYPES
#include <stdio.h>
#include <stdlib.h>

/*--------------------------mestypes------------------------------------------------------------------*/
 #define L_MAX 100
 typedef struct
 {
 	double val;
 	int operand; /*booléen 1 => opérande */
 }Elm;

 typedef struct List_token  List_token;
 struct List_token
 {
	 Elm token;

	  struct List_token *suiv;
	 };
 typedef  List_token*  Llist_token;
;

typedef struct elmPile
{
	Elm info;
	struct elmPile* svt;
}Pile;
typedef struct elmArbre
{
	Elm info;
	struct elmArbre* succ_g;
	struct elmArbre* succ_d;
}Arbre;
typedef struct elmPileArbre
{
	Arbre* info;
	struct elmPileArbre* svt;
}PileAebre;

#endif /* MES_TYPES*/
