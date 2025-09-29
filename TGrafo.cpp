/*
Integrantes:
Lucas Tuon de Matos - 10417987
Eduardo Oliveira Carvalho - 10417170
*/

#include "TGrafo.h"

// variavel global que representa infinito positivo
float infinito = std::numeric_limits<float>::infinity();

// Construtor do TGrafo, responsável por 
// Criar a matriz de adjacência v x v do Grafo
TGrafo::TGrafo( int n ){
    this->n = n;
    // No início dos tempos não há arestas
    this->m = 0; 
    // aloca da matriz do TGrafo
    float **adjac = new float*[n];
    for(int i = 0; i < n; i++)
    	adjac[i]= new float[n];
    adj = adjac;
    // Inicia a matriz com zeros
	for(int i = 0; i< n; i++)
		for(int j = 0; j< n; j++)
			adj[i][j] = infinito;
}

// Destructor, responsável por
// liberar a memória alocada para a matriz
TGrafo::~TGrafo(){
	n = 0;  // vertices
	m = 0;  // arestas
	delete [] *adj;
}

// getters 
int TGrafo::get_n() {
    return n;
}

int TGrafo::get_m() {
    return m;
}

float TGrafo::get_peso(int v, int w) {
    return adj[v][w];
}

// Apresenta o Grafo contendo
// número de vértices, arestas
// e a matriz de adjacência obtida
void TGrafo::show(){
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for( int i=0; i < n; i++){
        std::cout << "\n";
        for( int w=0; w < n; w++)
            if(adj[i][w] !=  infinito)
                std::cout << adj[i][w] << " ";
            else std::cout << "i ";
    }
    std::cout << std::endl << std::endl;
}

// insere um vértice no grafo de modo que o novo
// vertice v sera o ultimo elemento na matriz 
int TGrafo::insereV() {
    int novo_n = n + 1;

    // Cria a nova matriz com tamanho aumentado
    float **nova_adj = new float*[novo_n];
    for(int i = 0; i < novo_n; i++) {
        nova_adj[i] = new float[novo_n];
    }
    // Copia os dados da matriz antiga para a nova
    for (int i = 0; i < novo_n; i++) {
        for (int j = 0; j < novo_n; j++) {
            if (i == novo_n-1 || j == novo_n-1) {
                nova_adj[i][j] = infinito;
            }
            else {
                nova_adj[i][j] = adj[i][j];
            }
        }
    }

    // desaloca a matriz original
    delete[] *adj;

    // atualiza o grafo
    n = novo_n;
    adj = nova_adj;
    return novo_n-1;
}
 
// Insere uma aresta no Grafo tal que
// v é adjacente a w
void TGrafo::insereA(int v, int w, int peso){
    // testa se nao temos a aresta
    if(adj[v][w] == infinito){
        adj[v][w] = peso;
        m++; // atualiza qtd arestas
    }
}

// remove um vertice v do Grafo
void TGrafo::removeV(int v){

    int novo_n = n - 1;
    
    // Cria a nova matriz com tamanho reduzido
    float **nova_adj = new float*[novo_n];
    for(int i = 0; i < novo_n; i++) {
        nova_adj[i] = new float[novo_n];
    }

    // preenche a matriz com infinito
    for (int i = 0; i < novo_n; i++) {
        for (int j = 0; j < novo_n; j++) {
            nova_adj[i][j] = infinito;
        }
    }
    
    // Copia os dados da matriz antiga para a nova, pulando o vértice 'v'
    int novaLinha = 0;
    for(int i = 0; i < n; i++) {

        if (i == v) {   // Caso seja a linha do vertice removido
            continue;
        }
        int novaColuna = 0;
        for(int j = 0; j < n; j++) {
            
            if (j == v) {   // Caso seja a coluna do vertice removido
                continue;
            }

            nova_adj[novaLinha][novaColuna] = adj[i][j];   // Passa o valor da matriz antiga para a nova
            novaColuna++;
        }
        novaLinha++;
    }

    // desaloca a matriz original
    delete[] *adj;
    
    // atualiza o grafo
    n = novo_n;
    adj = nova_adj;
    
    // Recalcula o valor de m
    m = 0;
    for(int i = 0; i < n; i++) {    
        for(int j = 0; j < n; j++) {
            if(adj[i][j] != infinito) {
                m++;
            }
        }
    }
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w){
    // testa se temos a aresta
    if(adj[v][w] != infinito){
        adj[v][w] = infinito;
        m--; // atualiza qtd arestas
    }
}

// Funcao que usa o DFS para verificar se um vertice atinge outro
int TGrafo::atinge(int vInicio, int vFim) {
    if (n == 0) return 0;  // grafo vazio

    int* verticesMarcados = new int[n];
    for (int i = 0; i < n; i++) {
        verticesMarcados[i] = 0;  // inicializa como não visitado
    }

    std::stack<int> P;
    P.push(vInicio);
    verticesMarcados[vInicio] = 1;

    while (!P.empty()) {
        int atual = P.top();
        P.pop();

        if (atual == vFim) {
            delete[] verticesMarcados;
            return 1; // encontrou o vFim
        }

        for (int v = 0; v < n; v++) {
            if (adj[atual][v] != infinito && verticesMarcados[v] == 0) {
                P.push(v);
                verticesMarcados[v] = 1;
            }
        }
    }

    delete[] verticesMarcados;
    return 0; // vFim não alcançável
}

// Verifica se eh C3
int TGrafo::is_f_conexo(){

    if(n <= 1) return 1;
    

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            
            if(i == j) continue;

            // Verifica se existe caminho de i pra j e de j pra i
            if (atinge(i, j) == 0 || atinge(j, i) == 0) {
                return 0;
            }
        }
        
    }
    // Se todos os pares foram verificados e os caminhos existem, é C3
    return 1;
}

// Verifica se eh C2
int TGrafo::is_sf_conexo(){

    if (n <= 1) {
        return 1;
    }

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            
            if(i == j) continue;

            if (atinge(i,j) == 0 && atinge(j,i) == 0) {
                return 0; // Se nao ha caminho em nenhuma das direcoes, nao eh C2
            }

        }
        
    }
    
    return 1;
}

// Verifica se eh C1 ou C0 (seguindo modelo do slide)
int TGrafo::is_s_conexo() {

    // Transforma a matriz do grafo G em simetrica
    int** tempAdj = new int*[n];
    for (int i = 0; i < n; i++) {
        tempAdj[i] = new int[n];
        for (int j = 0; j < n; j++) {
            tempAdj[i][j] = (adj[i][j] == 1 || adj[j][i] == 1) ? 1 : 0;
        }
    }

    std::stack<int> P;
    int verticesMarcados[n] = {0};
    int contador = 0;
    int vInicio = 0;

    if (n > 0) {
        verticesMarcados[vInicio] = 1;
        P.push(vInicio);
        contador++;
    }

    int noAtual;
    while (!P.empty()) {
        noAtual = P.top();
        P.pop();

        for (int v = 0; v < n; v++) {
            if (tempAdj[noAtual][v] == 1 && verticesMarcados[v] == 0) {
                verticesMarcados[v] = 1;
                P.push(v);
                contador++;
            }
        }
    }

    // Libera a memória alocada para a matriz temporaria
    delete[] tempAdj;

    if(contador == n){
        return 1; // Se a busca encontrou todos os vertices, eh C1
    }

    return 0; // Caso contrario, ele eh C0
}

int TGrafo::conexidade(){
    if (n <= 1) return 3; 
    
    // Verifica se o grafo eh C3
    if (is_f_conexo()) return 3;

    // Se nao for C3, verifica se eh C2
    if (is_sf_conexo()) return 2;

    // Se nao for C2, verifica se eh C1
    if (is_s_conexo()) return 1;
    
    // Se nao for nenhum dos anteriores, eh C0
    return 0;
}

// Fecho de sucessores (R+)
void TGrafo::fechoSucessores(int v, bool marcado[]) {
    std::stack<int> P;
    marcado[v] = true;
    P.push(v);

    while (!P.empty()) {
        int u = P.top();
        P.pop();

        for (int j = 0; j < n; j++) {
            if (adj[u][j] != infinito && !marcado[j]) {
                marcado[j] = true;
                P.push(j);
            }
        }
    }
}

// Fecho de predecessores (R-)
void TGrafo::fechoPredecessores(int v, bool marcado[]) {
    std::stack<int> P;
    marcado[v] = true;
    P.push(v);

    while (!P.empty()) {
        int u = P.top();
        P.pop();

        for (int i = 0; i < n; i++) {
            if (adj[i][u] != infinito && !marcado[i]) {
                marcado[i] = true;
                P.push(i);
            }
        }
    }
}

// Algoritmo das Componentes Fortemente Conexas (CFCs)
void TGrafo::componentesFortementeConexas(int cfc_id[]) {
    // Aloca o array 'visitado' dinamicamente no heap.
    bool* visitado = new bool[n];
    for (int i = 0; i < n; i++) {
        visitado[i] = false;
    }

    int cfc_contador = 0;

    for (int v = 0; v < n; v++) {
        if (!visitado[v]) {
            bool* Rmais = new bool[n];
            bool* Rmenos = new bool[n];
            for (int i = 0; i < n; i++) {
                Rmais[i] = false;
                Rmenos[i] = false;
            }

            fechoSucessores(v, Rmais);
            fechoPredecessores(v, Rmenos);

            for (int i = 0; i < n; i++) {
                if (Rmais[i] && Rmenos[i]) {
                    cfc_id[i] = cfc_contador;
                    visitado[i] = true;
                }
            }
            cfc_contador++;

            // Libera a memória alocada para Rmais e Rmenos.
            delete[] Rmais;
            delete[] Rmenos;
        }
    }

    // Libera a memória alocada para 'visitado' antes de sair da função.
    delete[] visitado;
}

TGrafo* TGrafo::grafo_reduzido() {
    int cfc_id[100];
    
    // Encontra as CFCs e preenche o array de IDs
    componentesFortementeConexas(cfc_id);
    
    // Descobre o número total de CFCs
    int num_cfcs = 0;
    for (int i = 0; i < n; i++) {
        if (cfc_id[i] > num_cfcs) {
            num_cfcs = cfc_id[i];
        }
    }
    num_cfcs++; // Ajusta para o total de CFCs

    // Cria o novo grafo reduzido
    TGrafo* grafoReduzido = new TGrafo(num_cfcs);
    
    // Percorre o grafo original para encontrar as arestas entre CFCs
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (adj[u][v] != infinito) { // Se existe uma aresta (u, v) no grafo original
                int id_u = cfc_id[u];
                int id_v = cfc_id[v];

                // Se a aresta conecta duas CFCs diferentes, adicione a aresta no grafo reduzido
                if (id_u != id_v) {
                    grafoReduzido->insereA(id_u, id_v, 1);
                }
            }
        }
    }
    return grafoReduzido;
}
