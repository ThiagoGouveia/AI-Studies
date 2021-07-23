/*
	Autor: Thiago Rodrigues Gouveia da Silva
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
int melhorP1Geral;
void init_Player1() {
	// Determina posicao inicial.
	reinicializa_PosicaoAleatoria();
	
	// Implementacao das rotinas de inicializacao.
	melhorP1 = superf_VerAmbiente();
}

//Simulated annealing
tipo_Movimento run_Player1() {
	tipo_Movimento movimento;
	
	//atualiza o número de iterações
	k = tempoBusca.count;
	kMax = tempoBusca.maximo;
	//calcula temperatura
	temperatura = 1 - ((k+1)/kMax);
	
	// Define o tamanho do passo.
	movimento.passo = 1;
	// Define a direcao do movimento.
	//movimento.direcao = id_Caminhos[rand()%NUMCAMINHOS];
	
	//corrige a situação de platô
	if(superf_VerAmbiente() == 0){
		movimento.passo = 15;
		movimento.direcao = id_Caminhos[rand()%NUMCAMINHOS];
		melhorP1 = superf_VerVizinho(movimento.direcao);
		return movimento;
	}
	
	int i;
	float custo = 0;
	//checa o custo dos vizinhos
	for(i = 0; i < NUMCAMINHOS; i++){
		custo = superf_VerVizinho(id_Caminhos[i]);
		
		float probabilidade = exp((custo - melhorP1)/temperatura);
		
		double r = ((double) rand() / (RAND_MAX));
		//atualiza o melhor custo e o movimento 
		if(custo >= melhorP1 || probabilidade > r){
			melhorP1 = custo;
			movimento.direcao = id_Caminhos[i];
		}
	}
	int chegouMaximo = 0;
	//checa se chegou no pico
	for(i = 0; i < NUMCAMINHOS; i++){
		if(superf_VerVizinho(id_Caminhos[i]) < superf_VerAmbiente()){
			chegouMaximo++;
		}
	}
	//reinicia posição caso tenha chegado no pico, guardando a altura
	if(chegouMaximo == NUMCAMINHOS){
		if(melhorP1Geral < melhorP1){
			melhorP1Geral = melhorP1;
		}
		chegouMaximo = 0;
		reinicializa_PosicaoAleatoria();
		
		melhorP1 = superf_VerAmbiente();
	}

	return movimento;
}
tipo_Valor result_Player1() {
	return melhorP1Geral;
}


// *** 	FUNCOES DE INICIALIZACAO E EXECUCAO DO JOGADOR 2 ***
//	Implementacao da segunda estrategia de jogo.
tipo_Valor melhorP2;
int melhorP2Geral;
void init_Player2() {
	// Determina posicao inicial.
	reinicializa_PosicaoAleatoria();
	
	// Implementacao das rotinas de inicializacao.
	melhorP2 = superf_VerAmbiente();
}

////Random-restart hill-climbing
tipo_Movimento run_Player2() {
	tipo_Movimento movimento;
	
	// Define o tamanho do passo.
	movimento.passo = 1;
	// Define a direcao do movimento.
	//movimento.direcao = id_Caminhos[rand()%NUMCAMINHOS];
	
	//corrige a situação de platô
	if(superf_VerAmbiente() == 0){
		movimento.passo = 15;
		movimento.direcao = id_Caminhos[rand()%NUMCAMINHOS];
		melhorP1 = superf_VerVizinho(movimento.direcao);
		return movimento;
	}

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
		if(melhorP2Geral < melhorP2){
			melhorP2Geral = melhorP2;
		}
		chegouMaximo = 0;
		reinicializa_PosicaoAleatoria();
		
		melhorP2 = superf_VerAmbiente();
	}

	return movimento;
}
tipo_Valor result_Player2() {
	return melhorP2Geral;
}


