#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int check(char table[5][5],char k)
{
	int i,j;
	for(i=0;i<5;++i){
	
		for(j=0;j<5;++j)
		{ 
			if(table[i][j]==k)
				return 0;
		}
	}	
	return 1;
}

void inicializarTabela(char mtz[5][5]){
	int i,j;
	for(i=0;i<5;++i){
		for(j=0;j<5;++j)
			mtz[i][j]='0';
	}
}

void imprimirTabela(char mtz[5][5]){
	int i,j;
	
	printf("Tabela Gerada:\n");
	
	for(i=0;i<5;++i)
	{
		for(j=0;j<5;++j)
		{
			printf("%c ",mtz[i][j]);
		}
		printf("\n");
	}
}

void troca(char chave[], int tam){
	int i;
	
	printf("\nO texto substituindo (j com i ) \n");
	
	for(i=-1;i<tam;++i)	{
		if(chave[i]=='j')
			chave[i]='i';
		printf("%c", chave[i]);
	}
	
}

void inserirChaveTabela(char mtz[5][5], char chave[], int tam_chave){
	
	int flag, i, j;
	int count=0;
	for(i=0;i<5;++i)
	{
		for(j=0;j<5;++j)
		{
			flag=0;
			while(flag!=1)
			{
				if(count> tam_chave)
					goto l1; //salto incondicional 
				flag=check(mtz,chave[count]);
				++count;
			}
			mtz[i][j]=chave[(count-1)];
		}
	}
	l1:printf("\n");

}
//inserir alfabeto na tabela
char inserirAlfTabela(char mtz[5][5]){
	
	int val=97;
	int flag, i, j;
	
	for(i=0;i<5;++i)
	{
		for(j=0;j<5;++j)
		{
			if(mtz[i][j]>=97 && mtz[i][j]<=123)
			{}
			else
			{
				flag=0;
				while(flag!=1)
				{
					if('j'==(char)val)
					++val;
					flag=check(mtz, (char)val);
					++val;
				}
				mtz[i][j]=(char)(val-1);
			}
		}
	}
	return mtz;
}

int tamanhoMsg(char msg[], int t){
	int i, tam = 0, cont = 0;

	for(i=-1;i<t;++i)
	{
		if(msg[i]==msg[i+1])
			cont=cont+1;	
	}
	
	if((t+cont)%2!=0)
		tam=(t+cont+1);
	else
		tam =(t+cont);
		
	return tam;
}

void caracterSeparadorMsg(char msg[], int t){
	int ntam = tamanhoMsg(msg,t);
	char nMsg[ntam];
	char tmp ;
	int i, c =0;
	
	for(i=-1;i<t;++i)
	{
		nMsg[c]=msg[i];
		
		if(msg[i]==msg[i+1])
		{
			c=c+1;
		if(msg[i]=='x')
			nMsg[c]='z';
		else
			nMsg[c]='x';
		}
		c=c+1;
	}
//checking for length
	char bogus;
	if((t+ntam)%2!=0)
	{
		if(nMsg[ntam-1]=='x')
			nMsg[ntam]='T';
		else
			nMsg[ntam]='x';
	}
	printf("Texto Final:");
	for(i=0;i<=ntam;++i)
		printf("%c ",nMsg[i]);
}
//


//para criptografar
void cifrarTexto(char msg[], char mtz[5][5], int t){
	int tam = tamanhoMsg(msg,t);
	char cifrar_text[tam];
	
	int lin,lin2,c1,c2;
	int k1, i, j;
	
		for(k1=1;k1<=tam;++k1)
	{
		for(i=0;i<5;++i)
		{
			for(j=0;j<5;++j)
			{
				if(mtz[i][j]==msg[k1])
				{
					lin=i;
					c1=j;
				}
				else 
				if(mtz[i][j]==msg[k1+1])
				{
					lin2=i;
					c2=j;
				}
			}//end of for with j
		}//end of for with i
		
		if(lin==lin2)
		{
			cifrar_text[k1]=mtz[lin][(c1+1)%5];
			cifrar_text[k1+1]=mtz[lin][(c2+1)%5];
		}
		else
		if(c1==c2)
		{
			cifrar_text[k1]=mtz[(lin+1)%5][c1];
			cifrar_text[k1+1]=mtz[(lin2+1)%5][c1];
		}
		else
		{
			cifrar_text[k1]=mtz[lin][c2];
			cifrar_text[k1+1]=mtz[lin2][c1];
		}
		k1=k1+1;
	}
	printf("\n\nTexto Cifrado:\n ");
	for(i=1;i<=tam;++i)
		printf("%c ",cifrar_text[i]);
}

int main(int argc, char *argv[]) {
	
	int i,j,tam_chave,l=0;
	char *matriz;
	char table[5][5];
	
	//inicializar valores da tabela com '0';
	inicializarTabela(table);
//	imprimirTabela(table);
	
	printf("**********Playfair Cipher************\n\n");
	printf("Digite o Tamanho da chave ");
	scanf("%d",&tam_chave);
	
	char chave[tam_chave]; //armazenar chave
	
	printf("Digite a chave. ");
		for(i=-1;i<tam_chave;++i)
		{
			scanf("%c",&chave[i]);		
		}
		troca(chave, tam_chave);
		
	inserirChaveTabela(table,chave, tam_chave);	
	matriz = inserirAlfTabela(table);
	imprimirTabela(table);
	
	printf("\n Insira o comprimento do texto simples. (Sem espacos)");
	scanf("%d",&l);
	printf("\n Insira o texto simples ");
	
	char msg[l];
	
	for(i=-1;i<l;++i)
	{
		scanf("%c",&msg[i]);
	}
	
	troca(msg, l);
	int t = tamanhoMsg(msg, l);
	printf("\n %i", t);
	
	caracterSeparadorMsg(msg, l);
	cifrarTexto(msg,table,l);
	

	//caracterSeparadorMsg(msg,l);
	//cifrarTexto(msg,table,l);
	
		
	return 0;
}
