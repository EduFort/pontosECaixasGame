#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Quadrado{ //Classes dos quadrados formados entre linhas e pontos
public:
	sf::RectangleShape shape;
		int posicaoX; //coordanadas do quadrado
		int posicaoY;

		bool fechado; //Verdadeiro quando as linhas em volta sao selecionadas
		sf::Vector2f tam; // vetor com as medidas do quadrado

		Quadrado() { //inicializa as variaveis da classe
			posicaoX=0;
			posicaoY=0;
			fechado=0;

			tam = {95, 95};
			shape.setSize(tam);
			setaCor(100, 250, 100, 0);
		}

		void setaPosicao(int x, int y) { //seta nova posiçao
			posicaoX = x;
			posicaoY = y;
			shape.setPosition(x, y);
		}

		void setaCor(int r, int g, int b, int a) { //seta nova cor
			shape.setFillColor(sf::Color(r, g, b, a));
		}

		void fechar(){ //marca quadrado como fechado
			fechado=1;
		}
};

class Linha { //Classe das linhas clicaveis do jogo
public:
	sf::RectangleShape shape;

	int posicaoX; //coordanadas do quadrado
	int posicaoY;

	char direcao; //direcao da linha

	bool ativo; //Verdadeiro se o mouse esta em cima da linha
	bool escolhido; //Verdadeiro se a linha foi clicada

	sf::Vector2f tam;  //vetor com as medidas do quadrado

	Linha(char rDirecao) { //inicializa as variaveis da classe
		shape.setFillColor(sf::Color(231, 109, 94, 50));
		direcao = rDirecao;
		if (direcao == 'h') {
			tam = { 87, 12 };
		} else if (direcao == 'v') {
			tam = { 12, 87 };
		} else {
			cout << "Error!!!" << endl;
			exit(1);
		}

		shape.setSize(tam);
		posicaoX = 0;
		posicaoY = 0;
		ativo = 0;
		escolhido = 0;
	}

	Linha(int altura, int largura, int x, int y){ //Inicializa uso da classe para fins esteticos
		shape.setFillColor(sf::Color(0, 0, 0, 255));
		tam={altura, largura};
		shape.setSize(tam);
		posicaoX = x;
		posicaoY = y;
		direcao='0';
		ativo=0;
		escolhido=0;
	}

	void setaPosicao(int x, int y) { //seta nova posição
		posicaoX = x;
		posicaoY = y;
		shape.setPosition(x, y);
	}

	void setaCor(int r, int g, int b, int a) { //seta nova cor
		shape.setFillColor(sf::Color(r, g, b, a));
	}

	bool emCima(sf::RenderWindow& janela){ //verifica se mouse eesta em cima da linha
		sf::Vector2i posicao = sf::Mouse::getPosition(janela);
		int x = posicao.x; //posições x y do mouse
		int y = posicao.y;

		bool emCima = (x > posicaoX) && (x < posicaoX+tam.x) && (y > posicaoY) && (y < posicaoY+tam.y);
		return  emCima;
	}

	void passarLinha(sf::RenderWindow &janela) { //ativa a linha (muda a cor) quando o mouse esta em cima
		if (!escolhido) {
			if (emCima(janela)) {
				setaCor(231, 109, 94, 255);
				ativo = 1;
			} else if (ativo && !emCima(janela)) {
				setaCor(231, 109, 94, 50);
				ativo = 0;
			}
		}
	}

	bool clicarLinha(sf::RenderWindow& janela){ //ve se a linha foi clicada, e caso sim, a ativa quando a linha é clicada
		if(!escolhido){
			if(emCima(janela)){
				if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					setaCor(231, 109, 94, 255);
					escolhido=1;
					return escolhido;
				}
			}
		}
		return 0;
	}

	bool clicarLinhaBot() { //clique de linha feito pelo bot
		if(!escolhido){
			setaCor(59, 12, 5, 255);
			escolhido = 1;
			return 1;
		}
		return 0;
	}

	int pegaX() { //retorno posiçao x
		return posicaoX;
	}

	int pegaY() { //retorno posiçao y
		return posicaoY;
	}

};

class Bola { //classe das bolas que aparecem na tela
public:
	sf::CircleShape shape;
	int posicaoX; //posiçoes x e y da bola
	int posicaoY;

	int radius; //raio e tamanho
	int tam;

	Bola() { //inicializa as variaveis s da classe
		shape.setFillColor(sf::Color::White);
		radius = 10;
		tam = radius * 2;
		shape.setRadius(radius);
		posicaoX = 0;
		posicaoY = 0;
	}

	void setaPosicao(int x, int y) { //seta nova posiçoes da bola
		posicaoX = x;
		posicaoY = y;
		shape.setPosition(x, y);
	}

	int pegaX() { //retorno posiçoes x
		return posicaoX;
	}

	int pegaY() { //retorno posiçoes y
		return posicaoY;
	}

};

class Botao{ //Classes dos botoes em geral
public:
	sf::RectangleShape shape;

	int posicaoX;
	int posicaoY;

	sf::Vector2f tam;

	Botao(int x, int y) { //inicializa as variaveis s da classee
		setaCor(255, 255, 0, 0);
		posicaoX=x;
		posicaoY=y;
		setaPosicao(posicaoX, posicaoY);
		tam = {235, 93};
		shape.setSize(tam);
	}


	void setaPosicao(int x, int y) { //seta nova posição
		posicaoX = x;
		posicaoY = y;
		shape.setPosition(x, y);
	}

	void setaTamanho(float largura, float altura){ //seta novo tamanho
		tam={largura, altura};
		shape.setSize(tam);
	}

	void setaCor(int r, int g, int b, int a) { //seta nova cor
		shape.setFillColor(sf::Color(r, g, b, a));
	}

	bool emCima(sf::RenderWindow& janela){ //verifica se mouse esta em cima da linha
		sf::Vector2i posicao = sf::Mouse::getPosition(janela);
		int x = posicao.x; //posição x y do mouse
		int y = posicao.y;

		bool emCima = (x > posicaoX) && (x < posicaoX+tam.x) && (y > posicaoY) && (y < posicaoY+tam.y);
		return  emCima;
	}

	bool clicarBotao(sf::RenderWindow& janela) { //ativa evento quando clicada
		if(emCima(janela)){
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				return 1;
			}
		}
		return 0;
	}


	int pegaX() { //retorno posição x
		return posicaoX;
	}

	int pegaY() { //retorno posição y
		return posicaoY;
	}
};

class Jogador{ //classe dos jogadores da partida
public:
	string nome; //nome do jogador

	int pontos; //quantidade de pontos

	Jogador(string rNome) { //inicializa as variaveis da classee
		nome = rNome;
		pontos = 0;
	}

	void restart(){ //reinicia os pontos
		pontos=0;
	}

	void adicionaPonto(){ //adiciona um ponto ao jogador
		pontos++;
	}


};

//Funcoes
bool eMultiplo(int num, int mult) { //verifica se um numero é multiplo do outro
	if (num % mult == 0) {
		return 1;
	} else {
		return 0;
	}
}
