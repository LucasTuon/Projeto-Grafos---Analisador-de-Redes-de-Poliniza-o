/*
Implementacao de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjacencia
e metodos para utilizacao de um grafo dirigido.
*/
#ifndef ___GRAFO_VALORADO_MATRIZ___

#define ___GRAFO_VALORADO_MATRIZ___

#include <iostream>
#include <limits>
#include <vector>
#include <stack>
#include <algorithm> // std::find

// definicao de uma estrutura para armezanar um grafo
class TGrafo{
	private:
		int n; // quantidade de vertices
		int m; // quantidade de arestas
		float **adj; //matriz de adjacencia
		void fechoSucessores(int v, bool marcado[]);
		void fechoPredecessores(int v, bool marcado[]);
		void componentesFortementeConexas(int cfc_id[]);
		int atinge(int vInicio, int vFim);
		int is_f_conexo();
		int is_sf_conexo();
		int is_s_conexo();

	public:
		TGrafo(int n);
		~TGrafo();
		int get_n();
		int get_m();
		float get_peso(int v, int w);
		void show();
		void insereV();
		void insereA(int v, int w, int peso);
		void removeV(int v);
		void removeA(int v, int w);
		int conexidade();
		TGrafo* grafo_reduzido();
};

#endif
