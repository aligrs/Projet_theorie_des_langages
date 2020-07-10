#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"mestypes.h"
#include"mes_fontion.h"

/*------------------------expression-------------------------------------------------------------------*/
/*fonction qui permet de tester si notre caractere est une operande.
cette fonction renvoie 0 si notre caractere n'est pas une operande sinon elle renvoie 1.*/

int est_operande(char c)
{
	if ((c >= '0')&&(c <= '9'))
		return 1;
	else
		return 0;
}

/*cette fonction permet de tester si notre caractere appartient bien au lexique de notre
expression arithmetique.*/

int caractere_accepter(char c)
{
	if ( ((c >= '0')&&(c <= '9')) ||
		 (c == '+') || (c == '-') ||
		 (c == '*') || (c == '/')  ||
		 (c == '(') || (c == ')') ||
		 (c == '.'))
			return 1;
	else
		return 0;
}

/* fonction qui permet de tester si notre caractere est un operateur.
	Elle renvoie 0(si operateur)/1 si(pas un operateur)*/

int est_operateur(char c)
{
	if ((c == '+') || (c == '-') ||
		(c == '*') || (c == '/') )
		return 1;
	else
		return 0;
}

//fonction qui permet d'inserer nos tokens à la fin de la liste.
 
Llist_token ajouterEnFin(Llist_token liste, double  valeur,double type)
{
    /* On crée un nouvel élément */
    List_token* nouveltoken = malloc(sizeof(List_token));

    /* On assigne la valeur au nouvel élément */
    nouveltoken->token.val= valeur;
    nouveltoken->token.operand=type;

    /* On ajoute en fin, donc aucun élément ne va suivre */
    nouveltoken->suiv=NULL;

    if(liste == NULL)
    {
        /* Si la liste est videé il suffit de renvoyer l'élément créé */
        return nouveltoken;
    }
    else
    {
        /* Sinon, on parcourt la liste à l'aide d'un pointeur temporaire et on
        indique que le dernier élément de la liste est relié au nouvel élément */
        List_token* temp=liste;
        while(temp->suiv != NULL)
        {
            temp = temp->suiv;
        }
        temp->suiv = nouveltoken;
        return liste;
    }
}

//fonction qui permet d'afficher notre liste

void affichage_liste(Llist_token liste)

{

    List_token* temp=liste;

    /* Tant que l'on n'est pas au bout de la liste */

    while(temp != NULL)

    {

        /* On affiche */

        printf("%.2lf ", temp->token.val);

        /* On avance d'une case */

        temp = temp->suiv;

    }

}

/*fonction qui permet de gérer les espaces au sein de notre expression
   arithmetique d'entrée*/

char * gestion_des_espaces(char*exp,char *NewPhrase){

      int i, j = 0;
int a= strlen(exp);
    if(NewPhrase == NULL)
    {
        exit(0);
     }

    for(i=0;i<a;i++){
        if(exp[i]!=' ')
        {
           NewPhrase[j++] = exp[i];
        }

    }
     return NewPhrase;

}

Llist_token  chaineAuFloat(char *ch, Elm *t, int *n)
{
     Llist_token ma_liste = NULL;
	 int iCh, iT,i, iC;
    char c[100];
    for(iCh = 0, iT =0; (iCh < 100)&&(ch[iCh] != '\0'); iT++)
	{
		if(ch[iCh] == '(')
		{ /*insertion du Elm de la '(' 6 : 0 */
			t[iT].val = 6.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if (ch[iCh] == ')')
		{/*insertion du Elm de la ')' 7 : 0 */
			t[iT].val = 7.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if (ch[iCh] == '*')
		{/*insertion du Elm de la '*' 1 : 0 */
			t[iT].val = 1.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if (ch[iCh] == '/')
		{/*insertion du Elm de la '/' 2 : 0 */
			t[iT].val = 2.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if (ch[iCh] == '%')
		{/*insertion du Elm de la '%' 3 : 0 */
			t[iT].val = 3.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if (ch[iCh] == '+')
		{/*insertion du Elm de la '+' 4 : 0 */
			t[iT].val = 4.0;
			t[iT].operand = 0;
			iCh++;
		}
		else if ((ch[iCh] == '-')&&(iCh > 0)&&(!est_operateur(ch[iCh-1]))&&(ch[iCh-1] != '('))
		{/*insertion du Elm de la '-' 5 : 0 */
			t[iT].val = 5.0;
			t[iT].operand = 0;
			iCh++;
		}
		else
		{ /*nous avons un opérande */
			/*récupérer tout l'opérande dans la chaîne c*/
			for(iC = 0; (ch[iCh] != '\0'); iC++, iCh++)
			{
				/*on arrête a la rencontre d'un opérande suivi par un opérateur ou une ')'*/
				if((est_operande(ch[iCh - 1]))&&((est_operateur(ch[iCh]))||(ch[iCh] == ')')))
					break;
				c[iC] = ch[iCh];
			}
			/*finir la chaîne c par '\0' */
			c[iC] = '\0';
			/*transformer la chaîne c on float et la stocker dans le tableau */
			t[iT].val = atof(c);
			t[iT].operand = 1;
		}
	}
	/*récupérer le nombre d'élément dans n*/
	*n = iT;
	for(i=0;i<iT;i++){

	 ma_liste = ajouterEnFin(ma_liste,  t[i].val,t[i].operand );

	}
return ma_liste;
}

/*fonction qui permet de tester la validité des caracteres 
 qui constitue notre expression  arithmetique d'entrée
 elle retourne un booléen:0(faux):1(vrai).*/

int lexiqueJuste(char* exp)
{
	int i;
	/*vérifier si tout les caractères sont admis*/
	for(i = 0; (i < 100)&&(exp[i] != '\0'); i++)
		if ( !caractere_accepter(exp[i]) )
			return 0;
	return 1;
}

//fonction qui verifie si notre expression arithmetique est bien formée,correcte.

int est_expression_arithmetique_correcte(char* exp)
{
	int i;
	 /*nombre de parenthèses ouvrantes et fermentes*/
	int nbParO = 0, nbParF = 0;
	/*début de l'expression doit être un opérande ou signe - ou '(' sinon je retourne 0*/
	if (!est_operande(exp[0])&&(exp[0] != '-')&&(exp[0]!='('))
		return 0;
	/*return 0 si 2 signes '-' au début*/
	if ((exp[0] == '-')&&(exp[1] == '-'))
		return 0;
	/*incrémenter nbParO si on commence par '('*/
	if (exp[0] == '(')
		nbParO++;
	/*vérifier le reste*/
	for(i = 1; (i < L_MAX-1) && (exp[i] != '\0'); i++)
	{
		/*return 0 si exp[i] un opérateur et ch[i+1] est ni opérande ni signe '-' ni '('
			on ne peut pas avoir deux opérateurs successive */
		if((est_operateur(exp[i]))&&(!est_operande(exp[i+1]))&&(exp[i+1] != '(')&&(exp[i+1] != '-'))
			return 0;
		/*return 0 si exp[i] est '(' et ch[i+1] est ni opérande ni signe '-' ni '('
			on ne peut pas avoir deux opérateurs successive */
		if((exp[i] == '(')&&(!est_operande(exp[i+1]))&&(exp[i+1] != '(')&&(exp[i+1] != '-'))
			return 0;
		/*return 0 si exp[i] est une ')' et exp[i+1] n'est pas un opérateur
		   on ne peut pas avoir une '(' suivie par une opérande */
		if ((exp[i] == ')')&&(exp[i+1] != ')')&&(exp[i+1] != '\0')&&(!est_operateur(exp[i+1])))
			return 0;
		/*return 0 si exp[i] est un opérande et exp[i+1] est '('
			un opérande ne peut pas être suivi par '('*/
		if((est_operande(exp[i]))&&(exp[i+1] == '('))
			return 0;
		/*return 0 si plus de 3 signe '-' successive
		   on accepte le cas de a--y <=> a - (-y) */
		if((exp[i-1] == '-')&&(exp[i] == '-')&&(exp[i+1] == '-'))
			return 0;
		/*return 0 si . après pas un chiffre (opérande) */
		if((exp[i] == '.')&&(!est_operande(exp[i+1])))
			return 0;
		/*calcule de nombre de '(' et ')' */
		if (exp[i] == '(')
			nbParO++;
		else if (exp[i] == ')')
			nbParF++;
	}
	/*À la sortie de la boucle*/
	/*vérifier le nombre de parenthèse ouvrante et fermente*/
	if (nbParO != nbParF)
		return 0;
	/*il n'y a aucune erreur */
	return 1;
}






int operateur(Elm e)
{
	/*opérateur déférant de opérande et déférant de '(' et de ')'*/
	if( (!e.operand)&&(e.val != 6.0)&&(e.val != 7.0))
		return 1;
	else
		return 0;
}

int operande(Elm e)
{
	return e.operand;
}

int priorite(Elm e)
{

	if ((e.val == 1.0)||(e.val == 2.0)||(e.val == 3.0))
		return 1;
	else
		return 2;
}

double operation(Elm x1, Elm op, Elm x2)
{
	if(op.val == 1.0)
		return x1.val * x2.val;
	else if(op.val == 2.0)
		return x1.val / x2.val;
	else if(op.val == 3.0)
		return (double)((int)(x1.val) % (int)(x2.val));
	else if(op.val == 4.0)
		return x1.val + x2.val;
	else /*op.val == 5.0*/
		return x1.val - x2.val;

}


void afficheElm(Elm e)
{
	if(operande(e))
	{/*si e est un operande on affiche 3 chifre apres la virgule*/
		printf("[%.3f]", e.val);
	}
	else
	{/*si c'est deferant de l'operande en affiche son code entaire*/
	    if(e.val==2)
		printf("[/]");
		else if(e.val==1)
		printf("[*]");
		else if(e.val==4)
		printf("[+]");
		else if(e.val==5)
		printf("[-]");
	}
}







/*----------------------------------pile-----------------------------------------------------------*/


/*fonction d'initialisation de notre pile
  retourne NULL.*/
  
void initialisation_pile(Pile **p)
{
	(*p) = NULL;
}


/*fonction qui verifie si notre pile est vide.
retourne un booleen.*/

int est_vide(Pile* p)
{
	if ( p == NULL)
		return 1;
	else
		return 0;
}

//fonction qui retourne le sommet de la pile
Elm sommet_pile(Pile* p)
{
	if (!est_vide(p))
		return p->info;
	else
		printf("erreur: Pile vide");
}

// fonction qui permet d'empiler les elements dans notre pile
void empiler(Pile** p, Elm e)
{
	Pile* q;
	q = (Pile*)malloc(sizeof(Pile));
	q->info = e;
	q->svt = (*p);
	(*p) = q;
}

//fonction qui permet de depiler les elements de notre pile.
void depiler(Pile** p, Elm* e)
{
	Pile *sommet;
	sommet = (*p);
	(*p) = sommet->svt;
	*e = sommet->info;
	free(sommet);
}

/*fonctionn qui permet de passer d'une expression arithmetique postfixe a infixe.
cette fonction necessite utilisation d'une pile*/

Pile* passage_infixe_a_postfixe(Elm* t, int n)
{
	Pile *p, *r;
	Elm x;
	int i;
	initialisation_pile(&p);
	initialisation_pile(&r);
	for(i = 0; i < n; i++)
	{
		if(operande(t[i]))
			empiler(&r, t[i]);
		else if(operateur(t[i]))
		{
			while((!est_vide(p))&&(operateur(sommet_pile(p)))&&(priorite(t[i]) >= priorite(sommet_pile(p))))
			{
				depiler(&p, &x);
				empiler(&r, x);
			}
			empiler(&p, t[i]);
		}
		else if(t[i].val == 6.0)
			empiler(&p, t[i]);
		else
		{
			while((!est_vide(p)) && !((sommet_pile(p).val == 6.0)&&(!sommet_pile(p).operand)))
			{
				depiler(&p, &x);
				empiler(&r, x);
			}
			depiler(&p, &x);
		}
	}
	while(!est_vide(r))
	{
		depiler(&r, &x);
		empiler(&p, x);
	}
	return p;
}
/*----------------------------------------arbre----------------------------------------*/

//fonction qui verifie si notre pile d'arbre est vide.
int est_vide_arbre(Arbre* a)
{
	if (a == NULL)
		return 1;
	else
		return 0;
}

// fonction qui retourne le fils gauche de arbre donner en parametre.
Arbre* fils_gauche(Arbre* a)
{
	return a->succ_g;
}

//fonction qui retourne le fils droit de arbre donner en parametre.
Arbre* fils_droit(Arbre* a)
{
	return a->succ_d;
}

//fonction qui verifie si un element de notre arbre est une feuille.
int est_feuille(Arbre* a)
{
	if (( fils_droit(a) == NULL )&&( fils_gauche(a) == NULL ))
		return 1;
	else
		return 0;
}

//fonction qui creer une feuille dans notre arbre.
Arbre* creation_feuille_arbre(Elm e)
{
	Arbre* a;
	a = (Arbre*)malloc(sizeof(Arbre));
	a->info = e;
	a->succ_g = NULL;
	a->succ_d = NULL;
	return a;
}

//fonction qui initialise notre pile d'arbre.
void initialisation_pile_arbre(PileAebre** p)
{
	(*p) = NULL;
}

/*fonction qui creer une pile vide d'arbre .
cette fonction return NULL*/
int creation_pile_vide_arbre(PileAebre* p)
{
	return p == NULL;
}

//fonction qui renvoie le sommet de notre pile d'arbre
Arbre* sommet_pile_arbre(PileAebre* p)
{
	return p->info;
}

//fonction qui empile les elements dans notre pile d'arbre.
void empilerA(PileAebre** p, Arbre* a)
{
	PileAebre* q;
	q = (PileAebre*)malloc(sizeof(PileAebre));
	q->info = a;
	q->svt = (*p);
	(*p) = q;
}
//fonction qui depile les elements dans notre pile d'arbre.
void depilerA(PileAebre** p, Arbre** a)
{
	PileAebre* q;
	q = (*p);
	(*p) = q->svt;
	(*a) = q->info;
	free(q);
}

//fonction qui permet de creer notre arbre.
Arbre* construction_arbre(Elm* t, int n)
{
	/*Transformation de forme infixée au forme postfixée*/
	Pile *p;
	initialisation_pile(&p);
	p = passage_infixe_a_postfixe(t, n);
	/*création de l'arbre*/
	Arbre* f;
	Arbre* f1;
	Arbre* f2;
	/*initialiser la pile des Arbres*/
	PileAebre* pArbre;
	initialisation_pile_arbre(&pArbre);

	Elm x;
	while(!est_vide(p))
	{
		depiler(&p, &x);
		if(operande(x))
		{
			f = creation_feuille_arbre(x);
			empilerA(&pArbre, f);
		}
		else
		{
			/*construire une sous arbre*/
			f = creation_feuille_arbre(x);
			depilerA(&pArbre, &f1);
			depilerA(&pArbre, &f2);
			f->succ_d = f1;
			f->succ_g = f2;
			empilerA(&pArbre, f);
		}
	}
	/*la racine de l'arbre se trouve a la pile des arbres et la pile p est vide*/
	return sommet_pile_arbre(pArbre);
}

/*fonction qui permet d'evaluer notre expression arithmetique representer par un arbre.
cette fonction renvoie le calcul de notre expression arithmetique*/

double calcul_expression_arithmetique(Arbre* a)
{
	Elm x, y;
	if(!est_vide_arbre(a))
	{
		if(operateur(a->info))
		{
			x.val = calcul_expression_arithmetique(fils_gauche(a));
			y.val = calcul_expression_arithmetique(fils_droit(a));
			return operation(x, a->info, y);
		}
		else
			return a->info.val;
	}
}

//fonction qui permet d 'aaficher notre arbre

void affichage_arbre(Arbre* a)
{
	if(!est_vide_arbre(a))
	{
        printf("noeud actuelle: ");
        afficheElm(a->info);
        printf(".....fils gauche: ");
        if(fils_gauche(a))
			afficheElm(fils_gauche(a)->info);
		else
			printf("[NULL]");
        printf(".....fils droit: ");
        if(fils_droit(a))
			afficheElm(fils_droit(a)->info);
		else
			printf("[NULL]");
        printf("\n");
        affichage_arbre(fils_gauche(a));
        affichage_arbre(fils_droit(a));
	}
}

