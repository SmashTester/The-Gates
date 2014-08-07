#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAP_WIDTH 80 // Número de colunas
#define MAP_HEIGHT 30 // Número de linhas

// Baseado na tabela de caracteres ASCII padrão do windows.
#define PLAYER_ICON 1   
#define TREE_ICON 6
#define HEALTH_ICON 3
#define BLOCK_ICON 219
#define RIO_ICON 176
#define ROUTE_ICON 178
#define DOOR_ICON  219
#define DEFAULT 177

typedef struct _skills{
    int mana;
    int ataque;
    int defesa;
    int comercio;
}skills;

typedef struct _attributes{
    int forca;
    int sabedoria;
    int agilidade;
    int ingenuidade;
}attributes;

typedef struct _player{
    char nome[20];
    int x;
    int y;
    int nivel;
    int status;
    int vitorias;
    int derrotas;
    int gold;
    int cristais;
    skills habilidades;
    attributes atributos;
}player;


void mensagem(){

	char texto[50] = "oi";
	int size = strlen(texto);
	float i= (76-size)/2, loop=0;


	printf("[");
	for(i;i>=0;i--){
		printf(" ");
		if(i==0 && loop < 1){
			loop++;
			printf("%s", texto);
			i = (78-size)/2;			
		}
	}

	printf("]\n");


}

void imprime(char **mapa){
		
	int x,y;

	for(y=0;y<30;y++){
		for(x=0;x<80;x++){
			switch(mapa[y][x]){
				case 'T': printf("%c", TREE_ICON);
				break;
				case 'X': printf("%c", PLAYER_ICON);
				break;
				case '#': printf("%c", BLOCK_ICON);
				break;
				case 'R': printf("%c", RIO_ICON);
				break;
				case 'C': printf("%c", ROUTE_ICON);
				break;
				case 'P': printf("%c", DOOR_ICON);
				break;
				case ' ': printf("%c", DEFAULT);
				break;
				default:
					printf("%c", mapa[y][x]);
			}
		}
	}
}


// Valida a posição no mapa
// @param char posicao


int valida_posicao(char posicao){

	if(posicao == ' '  || posicao == 'C' )
		return 1;
	else
		return 0;

}

char **load_map(player *jogador){

	int x,y;

	char **mapa = (char**) malloc(MAP_HEIGHT*sizeof(char*));

	FILE *arquivo = fopen("map.txt", "r");

	for(y=0; y<30;y++){
		mapa[y] = (char*) malloc(MAP_WIDTH*sizeof(char));
		for(x=0;x<80;x++){
			mapa[y][x] = fgetc(arquivo);
			if (mapa[y][x] == 'X'){
				jogador->x = x;
				jogador->y = y;
			}
		}
	}

	fclose(arquivo);

	return mapa;
}

void comando(player *jogador, char **mapa){
	
	int x = jogador->x, y = jogador->y;
	char acao;
	
	printf("A, W, D, S e ENTER:\n");
	acao = getchar();
	fflush(stdin);

	switch(acao){
		case 'a': case 'A':
			if(valida_posicao(mapa[y][x-1])){
				mapa[y][x-1] = 'X';
				mapa[y][x] = ' ';
				jogador->x--;
			}
		break;
		case 'w': case 'W':
			if(valida_posicao(mapa[y-1][x])){
				mapa[y-1][x] = 'X';
				mapa[y][x] = ' ';
				jogador->y--;
			}
		break;
		case 'd': case 'D':
			if(valida_posicao(mapa[y][x+1])){
				mapa[y][x+1] = 'X';
				mapa[y][x] = ' ';
				jogador->x++;
			}
		break;
		case 's': case 'S':
			if(valida_posicao(mapa[y+1][x])){
				mapa[y+1][x] = 'X';
				mapa[y][x] = ' ';
				jogador->y++;
			}
		break;
	}
}


int main(){

	player jogador;
	

    system("mode 80,40");
	
	char **mapa = load_map(&jogador); // Define um array bidimensional e chama o carregamento do mapa.

	int zona,i;	

	FILE *arquivo = fopen("arquivo.txt", "r");
	
	fscanf(arquivo, "%d", &zona);
	
	fpos_t local[zona]; // Cria um vetor de posições no de mapas.
	

	while(1){
		system("cls");
		mensagem();
		imprime(mapa);
		comando(&jogador, mapa);

	}
	system("pause");
}
