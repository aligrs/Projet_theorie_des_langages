#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mestypes.h"
#include "mes_fontion.h"



int main(int argc, char *argv[])
{


	if(argc!=2)						/*On verifie qu'on nous donne bien un argument apres l'executable*/
	{
		fprintf(stderr,"Erreur : mauvais usage de l'executable.\nUsage correct : %s \"<expression>\"\n",argv[0]);
        }
        

        Llist_token ma_liste = NULL;
        int n;
        int syn=0, lex;
        Arbre* ar;
        Elm t[100];
	float resultat;
     printf("-------------------> %s \n", argv[1]);
     char *NewPhrase;

    int a= strlen(argv[1]);

    NewPhrase = malloc(a*sizeof(char)+1);
      NewPhrase=gestion_des_espaces( argv[1],NewPhrase);
      a= strlen(NewPhrase);
      printf("-------------------> %s  len:%d , \n",NewPhrase,a);
		syn = lex = 0;
		lex = lexiqueJuste(NewPhrase);
		syn = lex? est_expression_arithmetique_correcte(NewPhrase) : 0;
		if(!lex)
			printf("Expression non correct lexicalement.\n");
		else if(!syn)
			printf( "Expression non correct syntaxiquement.\n");
		else
		{
         printf( "Expression  correct .\n");
   /*ma_liste =chain_token_to_list( NewPhrase);*/
     ma_liste =chaineAuFloat(NewPhrase,t,&n);
    printf("---------afficher Llist_token ----------> \n");
     affichage_liste(ma_liste);
     printf("---------arbre----------> \n");
             ar = construction_arbre(t, n);
					/*affichage de l'arbre*/
					affichage_arbre(ar);
					resultat = calcul_expression_arithmetique(ar);
					  printf("---------Resultat----------> \n");
					printf("Resultat de l'evaluation est: %.3f\n", resultat);
     }
    return 0;
}
