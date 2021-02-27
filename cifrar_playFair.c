#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "cifrar_playFair.h"

void gerarTabaleChave(char chave[], int ks, char chaveT[5][5]) { 
    int i, j, k, flag = 0, *alf; 

    // Armazenar alfabeto
    alf = (int*)calloc(26, sizeof(int)); 
    for (i = 0; i < ks; i++) { 
        if (chave[i] != 'j') 
            alf[chave[i] - 97] = 2; 
    } 
  
    alf['j' - 97] = 1; 
  
    i = 0; 
    j = 0; 
  
    for (k = 0; k < ks; k++) { 
        if (alf[chave[k] - 97] == 2) { 
            alf[chave[k] - 97] -= 1; 
            chaveT[i][j] = chave[k]; 
            j++; 
            if (j == 5) { 
                i++; 
                j = 0; 
            } 
        } 
    } 
  
    for (k = 0; k < 26; k++) { 
        if (alf[k] == 0) { 
            chaveT[i][j] = (char)(k + 97); 
            j++; 
            if (j == 5) { 
                i++; 
                j = 0; 
            } 
        } 
    } 
} 

void buscarPosicao(char chaveT[5][5], char a, char b, int arr[]){ 
    int i, j; 
  
    if (a == 'j')
        a = 'i'; 
    else if (b == 'j') 
        b = 'i'; 
  
    for (i = 0; i < 5; i++) { 
  
        for (j = 0; j < 5; j++) { 
  
            if (chaveT[i][j] == a) { 
                arr[0] = i; 
                arr[1] = j; 
            } 
            else if (chaveT[i][j] == b) { 
                arr[2] = i; 
                arr[3] = j; 
            } 
        } 
    } 
} 

int mod5(int a){ 
    return (a % 5); 
} 

void convertMinusc(char txtPlano[], int ps){ 
    int i; 
    for (i = 0; i < ps; i++) { 
        if (txtPlano[i] > 64 && txtPlano[i] < 91) 
            txtPlano[i] += 32; 
    } 
}

int removeEspaco(char* txtPlano, int ps){ 
    int i, cont = 0; 
    for (i = 0; i < ps; i++) 
        if (txtPlano[i] != ' ') 
            txtPlano[cont++] = txtPlano[i]; 
    txtPlano[cont] = '\0'; 
    return cont; 
} 

int prepararTxt(char msg[], int ptrs){ 
    if (ptrs % 2 != 0) { 
        msg[ptrs++] = 'z'; 
        msg[ptrs] = '\0'; 
    } 
    return ptrs; 
} 

void encryptar(char msg[], char chaveT[5][5], int ps){ 
    int i, a[4]; 
  
    for (i = 0; i < ps; i += 2) { 
  
        buscarPosicao(chaveT, msg[i], msg[i + 1], a); 
  
        if (a[0] == a[2]) { 
            msg[i] = chaveT[a[0]][mod5(a[1] + 1)]; 
            msg[i + 1] = chaveT[a[0]][mod5(a[3] + 1)]; 
        } 
        else if (a[1] == a[3]) { 
            msg[i] = chaveT[mod5(a[0] + 1)][a[1]]; 
            msg[i + 1] = chaveT[mod5(a[2] + 1)][a[1]]; 
        } 
        else { 
            msg[i] = chaveT[a[0]][a[3]]; 
            msg[i + 1] = chaveT[a[2]][a[1]]; 
        } 
    } 
}

void encryptByPlayfairCipher(char msg[], char chave[]){ 
    char ps, ks, chaveT[5][5]; 
  
    // chave 
    ks = strlen(chave);
    ks = removeEspaco(chave, ks); 
    convertMinusc(chave, ks); 
  
    // texto plano
    ps = strlen(msg);
    convertMinusc(msg, ps); 
    ps = removeEspaco(msg, ps); 
  
    ps = prepararTxt(msg, ps);   
    gerarTabaleChave(chave, ks, chaveT); 
  
    encryptar(msg, chaveT, ps); 
}

void imprimeVetor(char vetor[]){
	int i;
	char t = strlen(vetor);
		
	for(i=0; i<t; i++){
		printf("%c", vetor[i]);
	}
}


///funções para decifragem de mensagens

void decriptar(char msg[], char chaveT[5][5], int ps){ 
    int i, a[4]; 
    for (i = 0; i < ps; i += 2) { 
        buscarPosicao(chaveT, msg[i], msg[i + 1], a); 
        if (a[0] == a[2]) { 
            msg[i] = chaveT[a[0]][mod5(a[1] - 1)]; 
            msg[i + 1] = chaveT[a[0]][mod5(a[3] - 1)]; 
        } 
        else if (a[1] == a[3]) { 
            msg[i] = chaveT[mod5(a[0] - 1)][a[1]]; 
            msg[i + 1] = chaveT[mod5(a[2] - 1)][a[1]]; 
        } 
        else { 
            msg[i] = chaveT[a[0]][a[3]]; 
            msg[i + 1] = chaveT[a[2]][a[1]]; 
        } 
    } 
} 
  
//// decriptar
void decryptByPlayfairCipher(char msg[], char chave[]){ 
    char ps, ks, chaveT[5][5]; 
  
    // chave 
    ks = strlen(chave);
    ks = removeEspaco(chave, ks); 
    convertMinusc(chave, ks); 
  
    // texto cifrado
    ps = strlen(msg);
    convertMinusc(msg, ps); 
    //ps = removeEspaco(msg, ps); 
  
    ps = prepararTxt(msg, ps);   
    gerarTabaleChave(chave, ks, chaveT); 
  
    decriptar(msg, chaveT, ps); 
} 



