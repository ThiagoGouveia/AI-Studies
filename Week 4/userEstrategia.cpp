/*
	Autor: Luis Otavio Rigo Junior
	Objetivo:
		Implementacao das estrategias definidas pelo programador.
*/
// *** 	FUNCOES DE INICIALIZACAO E EXECUCAO DO JOGADOR 1 ***
// Funcao de inicializacao e execucao da estrategia 1.
#include <vector>
#include <algorithm>
tipo_Valor melhorP1;
float temperatura;
float k;
float kMax;
vector<int> melhorP1Historico;
void init_Player1() {
	// Determina posicao inicial.
	reinicializa_PosicaoAleatoria();
	
	// Implementacao das rotinas de inicializacao.
	melhorP1 = superf_VerAmbiente();
}

tipo_Movimento run_Player1() {
	tipo_Movimento movimento;

	k = tempoBusca.count;
	kMax = tempoBusca.maximo;
	temperatura = 1 - ((k+1)/kMax);
	
	
	// Define a direcao do movimento.
	//movimento.direcao = id_Caminhos[rand()%NUMCAMINHOS];
	
	// Define o tamanho do passo.
	movimento.passo = 1;
	
	
	int i;
	float custo = 0;
	for(i = 0; i < NUMCAMINHOS; i++){
		
		custo = superf_VerVizinho(id_Caminhos[i]);
		
		float probabilidade = exp((custo - melhorP1)/temperatura);
		
		double r = ((double) rand() / (RAND_MAX));
		if(custo >= melhorP1 || probabilidade > r){
			melhorP1 = custo;
			movimento.direcao = id_Caminhos[i];
		}
	}
	int chegouMaximo = 0;
	for(i = 0; i < NUMCAMINHOS; i++){
		if(superf_VerVizinho(id_Caminhos[i]) < superf_VerAmbiente()){
			chegouMaximo++;
		}
	}
	
	if(chegouMaximo == NUMCAMINHOS){
		chegouMaximo = 0;
		reinicializa_PosicaoAleatoria();
		melhorP1Historico.push_back(melhorP1);
		melhorP1 = superf_VerAmbiente();
	}

	return movimento;
}
tipo_Valor result_Player1() {
	sort(melhorP1Historico.begin(), melhorP1Historico.end());
	melhorP1 = melhorP1Historico.back();
	return melhorP1;
}


// *** 	FUNCOES DE INICIALIZACAO E EXECUCAO DO JOGADOR 2 ***
//	Implementacao da segunda estrategia de jogo.
tipo_Valor melhorP2;
vector<int> melhorP2Historico;
void init_Player2() {
	// Determina posicao inicial.
	reinicializa_PosicaoAleatoria();
	
	// Implementacao das rotinas de inicializacao.
	melhorP2 = superf_VerAmbiente();
}
tipo_Movimento run_Player2() {
	tipo_Movimento movimento;
	
	// Define o tamanho do passo.
	movimento.passo = 1;
	
	int i;
	float custo = 0;
	for(i = 0; i < NUMCAMINHOS; i++){
		
		custo = superf_VerVizinho(id_Caminhos[i]);

		if(custo >= melhorP2){
			melhorP2 = custo;
			movimento.direcao = id_Caminhos[i];
		}
	}

	int chegouMaximo = 0;
	for(i = 0; i < NUMCAMINHOS; i++){
		if(superf_VerVizinho(id_Caminhos[i]) < superf_VerAmbiente()){
			chegouMaximo++;
		}
	}
	
	if(chegouMaximo == NUMCAMINHOS){
		chegouMaximo = 0;
		reinicializa_PosicaoAleatoria();
		melhorP2Historico.push_back(melhorP2);
		melhorP2 = superf_VerAmbiente();
	}

	return movimento;
}
tipo_Valor result_Player2() {
	sort(melhorP2Historico.begin(), melhorP2Historico.end());
	melhorP2 = melhorP2Historico.back();
	return melhorP2;
}


