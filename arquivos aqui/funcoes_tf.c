#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_tf.h"

void preenche (struct item **l,int *itens) {//insere na lista de forma ordenada
	struct item *novo,*aux_1,*menor;
	int i = 0;
	  
	if(*l == NULL) {//caso a lista esteja vazia,insere o primeiro elemento na lista
		(*l) = (struct item*) malloc (sizeof(struct item));//aloca espaço para o primeiro elemento da lista
		(*l)->codigo = itens[0];
		(*l)->estoque= itens[1];
		(*l)->valorcompra = itens[2];
		(*l)->margemlucro = itens[3];
		(*l)->prox = NULL;
	}

	else {//caso a lista não esteja vazia
		novo = (struct item*) malloc (sizeof(struct item));
		novo->codigo = itens[0];
		novo->estoque = itens[1];
		novo->valorcompra = itens[2];
		novo->margemlucro = itens[3];
		aux_1 = *l;

		if(novo->codigo < aux_1->codigo){//caso o novo elemento da lista seja menor do que o primeiro 
			
			novo->prox = aux_1;
			*l = novo;

		}
		else{
				for(aux_1 = *l; aux_1->prox != NULL && novo->codigo > aux_1->prox->codigo; aux_1 = aux_1->prox);//pecorre a lista até achar onde colocar o novo nó
						if(aux_1->prox == NULL){//
				
								aux_1->prox = novo;//coloca novo elemento  no final da lista
						}
						else{ //coloca novo elemento no meio da lista  
								novo->prox = aux_1->prox;
								aux_1->prox = novo;
			}
		}
	}

}

void imprime(struct item *l) {//função que imprime os elementos na tela do usuário,essa função não esta sendo utilizada no programa
	struct item *aux;
	// system("clear");
	printf("---------------------------------------\n");
	for(aux= l; aux != NULL; aux = aux->prox) {
		printf("Codigo :       %d \n", aux->codigo);
		printf("Estoque :      %d\n", aux->estoque);
		printf("Valor Compra : %d\n",aux->valorcompra);
		printf("Margem Lucro : %d\n", aux->margemlucro);
		printf("---------------------------------------\n");
	}

}

void register_venda(struct item **lista) {//esta função serve para registrar vendas, decrementando intens de determinado codigo
	int code,quantidade;
	int cont,cont_1,vendas;
	struct item *aux,*aux_1;
	system("clear");
	
	cont = 0;
	cont_1 = 0;
	vendas = 0;
	printf("Digite o codigo do produto: ");
	scanf("%d", &code);

	for(aux = *lista ; aux->prox != NULL ; aux = aux->prox) cont_1++;//este contador impede que aux se torne NULL

	system("clear");

	
	for(aux = *lista; aux->codigo != code && cont < cont_1; aux = aux->prox) cont++;//percorre a lista até encontrar o Código desejado 
	
		if(aux->codigo == code) {//codigo encontrado, vamos realizar a troca dos valores
					printf("Digite a quantidade de produtos vendidos: ");
					scanf("%d",&quantidade);
					if( (aux->estoque - quantidade) >= 0){//checa se ainda há tantos itens no estoque
						aux->estoque -= quantidade;//decrementa os itens de determinado código
						aux->itens_vendidos += quantidade;//incrementa a quantidade de itens vendidos
						printf("%d\n",aux->itens_vendidos );
						system("clear");

				}
				else{//caso o usuário digite um valor inferio a quantidade ainda em estoque

					printf("Existem somente mais %d itens com este codigo no estoque!!!\n",aux->estoque );
					printf("Por favor. Digite um valor adequado!!!\n" );
					scanf("%d",&quantidade);
					aux->estoque -= quantidade;//decrementa os itens de determinado código
					aux->itens_vendidos += quantidade;//incrementa a quantidade de itens vendidos
					printf("%d\n",aux->itens_vendidos );
					system("clear");
				}
				
		}
		//caso o usuario entre com um codigo que ainda não foi adcionado á lista
		else{
			printf("O item com este codigo nao esta registrado na lista!!!\n");
			printf("Por favor use 'a' para registrar este item na lista!!\n");				
		}
}


		

void free_lista(struct item **l){//remove todos os produtos que não possuem mais itens em estoque
	struct item *aux,*aux_1;
	int cont,cont_1;
	cont_1 = 0;
	cont = 0;
	system("clear");

	for(aux = *l ; aux->prox != NULL ; aux = aux->prox) cont++;//diz o tamanho ta lista para a remoção de todos os nós com estoque zerado

	for(int i = 0; i < cont ; i++){	
		for( aux_1 = *l ; aux_1->estoque > 0 && aux_1->prox != NULL; aux_1 = aux_1->prox) cont_1++;//procura o nó com estoque zerado

			if(aux_1->estoque == 0) {//quando estoque igual a 0 remove ele da lista

				if( cont_1 != 0 ){//remove nó do inicio da lista
					aux = *l;
					aux_1 = aux->prox;

					while((aux_1 != NULL) && (aux_1->estoque > 0)){	//remove elementos do meio da lista e do final				
						aux = aux_1;
						aux_1 = aux_1->prox;
				 	}
				 	if (aux_1 != NULL){
				  		aux->prox = aux_1->prox;
				  		free(aux_1);
				  	} 
				}	//imprime(&lista);
			cont_1 = 0;
			for(aux = *l ; aux_1->estoque != 0 && aux->prox != NULL ; aux = aux->prox) cont_1++;
			if(cont_1 == 0){//remove ultimo nó da lista
				(*l) = aux->prox;
				free(aux);
			}
		}
	}
}

	

void insere_estoque(struct item **l){//está função serve para adicionar itens no sistema
	struct item *aux,*aux_1;
	int quantidade;
	int vet[4],i=0,cont_1=0;
	int code;
	aux_1 = *l;
	system("clear");
	printf("Digite o codigo do produto : ");
    scanf("%d", &code);
    vet[0] = code;


	for(aux = *l ; aux->prox != NULL ; aux = aux->prox) cont_1++;//contador que serve de limite para impedir que aux se torne NULL mais prente
	for(aux = *l; aux->codigo != code && i< cont_1; aux = aux->prox) i++;//percorre a lista até achar o codigo 	
	
		if(aux->codigo == code) {//caso o código ja esteja no sistema
			printf("O produto com este codigo esta no sistema.Informe quantidade de itens a ser adicionado!\n");
			scanf("%d",&quantidade);
			aux->estoque += quantidade;
		}

		else{//caso o codigo nao esteja na lista,esse else vai adciona-lo na lista
			printf("Este codigo de produto nao esta no sistema!!\n");
			printf("Vamos inserilo na lista!\n");
			printf("Digite a quantidade de itens adquiridos : ");
			scanf("%d",&vet[1]);
			printf("Qual o custo da compra : ");
			scanf("%d",&vet[2]);
			printf("Digite a margem de Lucro : ");
			scanf("%d",&vet[3]);

			preenche(l,vet);//chama a funão prenche pra adcionar novo item a lista encadeada 

		}
	system("clear");
}

void salva_lista(struct item *l){//função que salva lista
	struct item *aux;
	FILE *input;
	system("cp estoque.txt estoque.bak ");//salva os antigos valores do estoque em um novo arquivo .bak
	input = fopen("estoque.txt", "w");//abre o antigo arquivo em modo de leitura pra registrar as mudanças feitas no estoque
	system("clear");
	if ( input == NULL){//para previnair erros caso o arquivo não seja carregado om sucesso
		printf("Não foi possivel abril o arquivo ! \n ");
		printf("Saindo do programa!!\n");
		fclose( input );
		exit(1);
	}
	else printf("Arquivo carregado com sucesso!!\n");


	aux = l;
	while(aux != NULL){
			if(aux->estoque > 0){//imprime na lista os produtos com os códigos que não tenham os itens em seu estoque zerado
					fprintf(input, "%d,%d,%d,%d,\n",aux->codigo,aux->estoque,aux->valorcompra,aux->margemlucro);
					
			}
			aux = aux->prox;
	}
		
	fclose(input);//fecha o arquivo carregado onde foram salvas as mudanças
}
/*Gerar relatório de vendas: criar um arquivo que contenha,
um item por linha, o estrato das vendas realizadas, informando,
para cada item a quantidade ainda em estoque,
a quantidade vendida e o valor arrecadado.
Todas as informações separadas por virgulas.*/
void gera_relatorio(struct item *l){//item ,quantidade vendida,valor arrecadado
	struct item *aux;
	FILE *rel;
	rel = fopen("relatório.csv","w");//carrega um arquivo .csv. Caso ele não exista a função "w" quiva um arquivo novo
	system("clear");
	if ( rel == NULL){
		printf("Não foi possivel abril o arquivo ! \n ");
		printf("Saindo do programa!!\n");
		fclose( rel );
		exit(1);
	}
	else printf("Arquivo carregado com sucesso!!\n");
	//imprime no arquivo aberto CODIGO,Quantidade ainda em estoque,quantidade vendida,valor arrecadado
		int x = 0;
		char introducao[] = "CODIGO,Quantidade ainda em estoque,quantidade vendida,valor arrecadado,";
		fprintf(rel, "%s\n", introducao );

	for(aux = l ; aux != NULL ; aux = aux->prox){//codigo,estoque,valorcompra,margemlucro
				x =  (aux->itens_vendidos * (( aux->valorcompra * aux->margemlucro ) / 100 ) );
				fprintf(rel, "%d,%d,%d,%d,\n",aux->codigo,aux->estoque,aux->itens_vendidos, x );
	}
	fclose(rel);//fecha o aquivo aberto
}
