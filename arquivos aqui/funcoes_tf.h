
struct item{ //codigo,estoque,valorcompra,margemlucro
	int codigo;
	int estoque;
	int valorcompra;
	int margemlucro;
	int itens_vendidos;
	
	struct item *prox; 
};
void preenche (struct item **l,int *itens);//insere na lista de forma ordenada
void imprime(struct item *l);//imprime a lista na tela do usuário
void register_venda(struct item **lista);//registra a venda de um produto 
void  insere_estoque(struct item **l);//insere itens ao estoque
void salva_lista(struct item *l);//salva a lista 
void gera_relatorio(struct item *l);//gera relatório .csv
void free_lista(struct item **l);//retira nó d lista cujo os intens estejam zerados