#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_tf.h"

int main(){
	char x[100];
	FILE *arq;
	arq = fopen("estoque.txt","r");     //abre o arquivo onde estão os dados de estoque
	if ( arq == NULL){                  //garantir que o seja carregado com sucesso
		printf("Nao foi possivel abril o arquivo ! \n ");
		printf("saindo do programa!!\n");
		fclose( arq );
		exit(1);
	}
	else printf("Arquivo carregado com sucesso!!\n"); //mensaguem ao usário de que o arquivo foi carregado com sucesso


	struct item *lista;//struct onde será armazenado a lista encadeada
	int aux1,vet[4],cont,i;// auxilares 


	lista = NULL;

	char *aux;
	while(fscanf(arq ,"%s" , x) != EOF){ //laço para pegar as linhas do arquivo e guarda-las em uma string
		//printf("\n");
		cont=0;
		aux = strtok(x , ",");//aux será uma string até uma posição antes da ,
		while (aux != NULL){ //Enquanto houver frases      
		
			aux1 = atoi(aux);//atoi tranforma aux de um char para inteiro e repassa para aux_1
			vet[cont] = aux1;//o novo inteiro será armazenado em um vetor;
			cont++;
			aux = strtok(NULL, ",");//oque tinha antes da virgula em aux será NULL
		}
		 preenche(&lista,vet);//manda a lista e os vetor com os valores para por em lista encadeada
	}
	fclose(arq);//depois dos intens salvos, fecha o arquivo aberto 
	system("clear");//limpa a tela do usuário

	// imprime(lista);//caso o professor queira ver a lista na tela é só decomentar a função imprime 
	
	char comando;
	int valores;

	//menu
	printf("\t\t\t\t\t\t*****WELCOME TO STOCK DATE BASE******\n\n");
	printf("\tEscolha uma opção no menu \n\n[v]: registrar venda de um produto\n");
    printf("[a]: adicionar itens ao estoque\n");
    printf("[s]: salvar a lista\n");
    printf("[r]: gerar relatório de vendas\n");
    printf("[x]: salvar a lista, gerar relatório e sair do programa\n");
    printf("\nEscolha a sua opção : ");

	scanf("%c",&comando);

	while(comando != 'x') {//executa o menu enquanto o usuario não digitar x
    
    switch(comando) {


    case 'v':
   		register_venda(&lista);//quando o usuário quiser registrar a venda de um produto
   		//imprime(lista);
    break;

    case 'a': 
    	
    	insere_estoque(&lista);//quando o usuário quiser inserir itens no estoque
		//imprime(lista);    
    break;

    case 's': 
    	salva_lista(lista);//quando o usuário  quiser salvar a lista
    	//free_lista(&lista);
    break;

    case 'r': 
    	gera_relatorio(lista);//quando o usuário quiser gerar um relatório de vendas
    break;

    
    default:
    	system("clear"); 
    	printf("Esta opção não esta disponivel!!!\n\n\n"); 
    break;
    
	}
	//imprime(lista);
	printf("\tEscolha uma opção no menu \n\n[v]: registrar venda de um produto\n");
    printf("[a]: adicionar itens ao estoque\n");
    printf("[s]: salvar a lista\n");
    printf("[r]: gerar relatório de vendas\n");
    printf("[x]: salvar a lista, gerar relatório e sair do programa\n");
    printf("\nEscolha a sua opção : ");
    scanf(" %c",&comando);

    
}
	if( comando == 'x') {//Sair do programa: salvar a lista e gerar o relatório de vendas. Então sair do programa.
	gera_relatorio(lista);
	free_lista(&lista);//retira da lista um nó cujo a quantidade de itens em estoque esteja zerado
	salva_lista(lista);
	free(lista);
	}

	return 0;
}