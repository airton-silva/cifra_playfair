#include <stdio.h>
#include <stdlib.h>
#include "cifrar_playFair.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	

	int i, j, tam_chave, tam_msg, opc = 0;
		printf("\n\t*******************************************************************\t\t\n");
		printf("\n\t************************ CIFRA DE PLAYFAIR ************************\t\t\n");
		printf("\n\t*******************************************************************\t\t\n");
		
			printf("\n\t\tDigite o Tamanho da Chave \n\t\t");
				scanf("%i", &tam_chave);
			printf("\n\t\tDigite a Chave\n\t\t");
			
			char chave[tam_chave]; 
			
			for(i=-1; i<tam_chave; i++){
				scanf("%c", &chave[i]);
			}
			
			printf("\n\t\tDigite o Tamanho da Mensagem\n\t\t ");
			scanf("%i", &tam_msg);
			
			printf("\n\t\tDigite a Mensagem\n\t\t");
			
		    char msg[tam_msg]; 
		    
		  	for(j=-1; j<tam_msg; j++){
				scanf("%c", &msg[j]);
			}
		system("cls");
		printf("\n\t*******************************************************************\t\t\n");
		printf("\n\t************************ CIFRA DE PLAYFAIR ************************\t\t\n");
		printf("\n\t*******************************************************************\t\t\n");
		
		printf("\t\t Digite 1 para Cifra uma Mensagem.\t\t\n");
		printf("\t\t Digite 2 para Decifra uma Mensagem.\t\t\n"); 
		printf("\t\t Digite 3 para sair\n\t\t");
		scanf("%i", &opc);
		
	 switch ( opc )
	  {
	    case 1 :
	    	printf("\t\tEncriptar Texto\n\t\t");
	    	encryptByPlayfairCipher(msg, chave);
	    	imprimeVetor(msg);
	    	fflush(stdin);
	    break;
	    
	    case 2 :
	    	printf ("\t\tDecriptar Texto\n\t\t");
	    	decryptByPlayfairCipher(msg,chave);
	    	imprimeVetor(msg);
	    	fflush(stdin);
	    break;
	    
	    case 3 :
	    	printf("\t\tbye bye! ;-)");
	   		 exit(0);
	    break;

	    
	    default :
	    printf ("\t\tValor invalido!\n");
	}
	
  
	return 0;
}
