#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstdio>
#include <ctime>

#include "elementos.hpp"

using namespace std;

/*********************************funçao do jogo*********************************/

class Janela { //janela do jogo
public:
	sf::RenderWindow janela;

	sf::Image icone; //elementos SFML da janela
	sf::Music musica;

	sf::SoundBuffer buffer;
	sf::Sound efeito;

	sf::Sprite spriteFundo;
	sf::Texture texturaFundo;

	sf::Font fonte;

	sf::Text textoPontosJogador;
	sf::Text textoPontosBot;

	int largura; //tamanho da janela
	int altura;

	int limiteQuadros; //limite de fps do jogo

	Jogador jogador; //jogadores do jogo
	Jogador bot;

	bool estaNoMenu;
	bool acabou;

	sf::RectangleShape mensagemFim;
	Botao botaoReiniciar;
	Botao botaoVoltarMenu;

	vector<Quadrado> quadrados; //vetores dos elementos visuais
	vector<Linha> linhasHorizontais;
	vector<Linha> linhasVerticais;
	vector<Bola> bolas;

	Janela(int rLargura, int rAltura) : janela(sf::VideoMode(rLargura, rAltura), "Pontos e Caixas"), jogador("Player"), bot("Bot"), botaoReiniciar(60, 530), botaoVoltarMenu(18, 588){ //inicializa as variaveis da classe e objetos da classe
		largura = rLargura;
		altura = rAltura;
		limiteQuadros = 100;
		estaNoMenu=0;
		acabou=0;

		botaoVoltarMenu.setaTamanho(130, 113);
		botaoReiniciar.setaTamanho(140, 140);
		botaoVoltarMenu.setaCor(0, 0, 0, 0);

		icone.loadFromFile("imagens/icone.png");
		janela.setIcon(icone.getSize().x, icone.getSize().y, icone.getPixelsPtr());

		janela.setFramerateLimit(limiteQuadros);
	}

	void menu() { //funcao responsavel
	    estaNoMenu = 1;
	    musica.stop();
	    sf::RectangleShape nomeJogo;
	    Botao botaoIniciar(313, 483); //coloca os botoes
	    Botao botaoFechar(623, 483);

	    carregaFundo("imagens/telaInicial.png"); //carrega imagem de fundo

	    while (janela.isOpen()) { //eventos do menu
	        sf::Event evento;
	        while (janela.pollEvent(evento)) {
	            if (evento.type == sf::Event::Closed)
	                janela.close();
	        }

	        if (botaoIniciar.clicarBotao(janela)) {
	            loopJogo();
	        }

	        if (botaoFechar.clicarBotao(janela)){
	        	janela.close();
	        }

	        janela.clear();

	        janela.draw(spriteFundo);             // Fundo da imagem
	        janela.draw(botaoIniciar.shape);      // Botao para comecar jogo
	        janela.draw(botaoFechar.shape);		  // Botao para fechar jogo
	        janela.display();
	    }
	}


	void loopJogo() { //loop onde aocntece as etapas do jogo
		estaNoMenu=0;
		carregar(); //carrega os elementos visuais
		while (janela.isOpen()) {
			eventos(); //eventos do jogo
			desenhar (); //desenha os elementos visuais
		}
	}

	void carregar() { //carrega os elementos visuais
		carregaFundo("imagens/telaGame.png");
		carregaMusica();
		carregaTexto();

		quadrados = vector<Quadrado>(25); //inicializa os vectores
		linhasHorizontais = vector<Linha>(30, Linha('h'));
		linhasVerticais = vector<Linha>(30, Linha('v'));
		bolas = vector<Bola>(36);

		jogador.restart();
		bot.restart();
		acabou=0;

		setaPosicaoVectorQuadrado(); //coloca os elementos do vetor em suas posições
		setaPosicaoVectorLinhaHorizontal();
		setaPosicaoVectorVertical();
		setaPosicaoVectorBola();
	}

	void eventos() { //verifica possiveis ações do jogo
		sf::Event event;
		bool fechou=0;
		while (janela.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				janela.close();
			for(unsigned i=0; i<linhasHorizontais.size(); i++){ //primeiro para linhas horizontais
				linhasHorizontais[i].passarLinha(janela); //ve se o mouse passou na linha
				if(linhasHorizontais[i].clicarLinha(janela)){ //se a linha foi clicada
					efeito.play();
					fechou = fecharQuadrado('p'); //verifica de quadrado foi fechado
					fim(); //verifica se o jogo deve acabar
					if(!fechou && !acabou){
						do{ //jogadas do bot
							sf::sleep(sf::seconds(1));
							jogoBot();
							fechou = fecharQuadrado('b');
							desenhar(); //desenha jogada do bot
							fim();
						} while(fechou && !acabou);
					}
				}
				linhasVerticais[i].passarLinha(janela); //depois para verticais
				if(linhasVerticais[i].clicarLinha(janela)){
					efeito.play();
					fechou = fecharQuadrado('p');
					fim();
					if(!fechou && !acabou){
						do{
							sf::sleep(sf::seconds(0.5));
							jogoBot();
							fechou = fecharQuadrado('b');
							desenhar();
							fim();
						} while(fechou && !acabou);
					}
				}
			}
			if(botaoVoltarMenu.clicarBotao(janela)){ //botao de voltar menu
				menu();
			}
			if(acabou){
				if(botaoReiniciar.clicarBotao(janela)){ //botao de reiniciar que aparece após o fim do jogo
					carregar();
				}
			}
		}
	}

	void desenhar() { //desenha os elementos na tela
		janela.clear();
		if(!estaNoMenu && !acabou){
			janela.draw(spriteFundo);
			for (unsigned i = 0; i < quadrados.size(); i++) {
				janela.draw(quadrados[i].shape);
			}
			for (unsigned i = 0; i < linhasHorizontais.size(); i++) { //linhas e bolas
				janela.draw(linhasHorizontais[i].shape);
			}
			for (unsigned i = 0; i < linhasVerticais.size(); i++) {
				janela.draw(linhasVerticais[i].shape);
			}
			for (unsigned i = 0; i < bolas.size(); i++) {
				janela.draw(bolas[i].shape);
			 }
			janela.draw(textoPontosJogador);
			janela.draw(textoPontosBot);
			janela.draw(botaoVoltarMenu.shape);
		}

		if(acabou){ //tela final
			janela.draw(spriteFundo);
			janela.draw(botaoReiniciar.shape);
		}
		janela.display();
	}

	void carregaFundo(string arquivo){ //carrega fundo do jogo
		if(texturaFundo.loadFromFile(arquivo)) {
		    sf::Vector2u tamanhoImagem = texturaFundo.getSize();
		    float escalaX = 947.0f / tamanhoImagem.x;
		    float escalaY = 720.0f / tamanhoImagem.y;
		    spriteFundo.setScale(escalaX, escalaY);
			spriteFundo.setTexture(texturaFundo);
		}else{
			std::cerr << "Erro ao carregar imagem de fundo\n";
			exit(3);
		}
	}

	void carregaMusica(){
	    if (musica.openFromFile("sons/trilhaSonora.ogg")) {
	    	musica.setVolume(30);
		    musica.setLoop(true);
		    musica.play();
			buffer.loadFromFile("sons/efeito.wav");
			efeito.setBuffer(buffer);
			efeito.setVolume(40);
	    }else{
	        std::cout << "Erro ao carregar mÃºsica\n";
	        exit(4);
	    }
	}

	void carregaTexto(){

		fonte.loadFromFile("fonte/fonte.ttf");

		textoPontosJogador.setFont(fonte);
		textoPontosBot.setFont(fonte);

		textoPontosJogador.setCharacterSize(40);
		textoPontosBot.setCharacterSize(40);

		textoPontosJogador.setColor(sf::Color::Black);
		textoPontosBot.setColor(sf::Color::Black);

		textoPontosJogador.setString("0");
		textoPontosBot.setString("0");

		textoPontosJogador.setPosition(210, 30);
		textoPontosBot.setPosition(705, 30);
	}

	void setaPosicaoVectorQuadrado() {
		int linhasPassadas = 0;
		int xOrigem = 210;
		int yOrigem = 120;
		int espaco = 107;
		int xQuadrado = xOrigem;
		int yQuadrado = yOrigem;
		int quadradosPorLinha=5;
		for (unsigned i = 0; i < quadrados.size(); i++) {
			if (i != 0) {
				if (eMultiplo(i, quadradosPorLinha)) {
					xQuadrado = xOrigem;
					yQuadrado = yOrigem;
					linhasPassadas++;
					yQuadrado += espaco * linhasPassadas;
				} else {
					xQuadrado += espaco;
				}
				quadrados[i].setaPosicao(xQuadrado, yQuadrado);
			} else {
				quadrados[i].setaPosicao(xOrigem, yOrigem);
			}
		}
	}

void setaPosicaoVectorLinhaHorizontal() {
		int linhasPassadas = 0;
		int xOrigem = 194 + bolas[0].tam;
		int yOrigem = 108;
		int espaco = 107;
		int xLinha = xOrigem;
		int yLinha = yOrigem;
		int linhasHorizontaisPorLinha = 5;
		for (unsigned i = 0; i < linhasHorizontais.size(); i++) {
			if (i != 0) {
				if (eMultiplo(i, linhasHorizontaisPorLinha)) {
					xLinha = xOrigem;
					yLinha = yOrigem;
					linhasPassadas++;
					yLinha += espaco * linhasPassadas;
				} else {
					xLinha += espaco;
				}
				//(*bola).setaPosicao();
				linhasHorizontais[i].setaPosicao(xLinha, yLinha);
			} else {
				linhasHorizontais[i].setaPosicao(xOrigem, yOrigem);
			}
		}
	}

void setaPosicaoVectorVertical() {
		int linhasPassadas = 0;
		int xOrigem = 194 + 4;
		int yOrigem = 104 + bolas[0].tam;
		int espaco = 107;
		int xLinha = xOrigem;
		int yLinha = yOrigem;
		int linhasverticaisPorLinha = 6;
		for (unsigned i = 0; i < linhasVerticais.size(); i++) {
			if (i != 0) {
				if (eMultiplo(i, linhasverticaisPorLinha)) {
					xLinha = xOrigem;
					yLinha = yOrigem;
					linhasPassadas++;
					yLinha += espaco * linhasPassadas;
				} else {
					xLinha += espaco;
				}
				linhasVerticais[i].setaPosicao(xLinha, yLinha);
			} else {
				linhasVerticais[i].setaPosicao(xOrigem, yOrigem);
			}
		}
	}

void setaPosicaoVectorBola() {
		int linhasPassadas = 0;
		int xOrigem = 194;
		int yOrigem = 104;
		int espaco = 107;
		int xBola = xOrigem;
		int yBola = yOrigem;
		int bolasPorLinha =6;
		for (unsigned i = 0; i < bolas.size(); i++) {
			if (i != 0) {
				if (eMultiplo(i, bolasPorLinha)) {
					xBola = xOrigem;
					yBola = yOrigem;
					linhasPassadas++;
					yBola += espaco * linhasPassadas;
				} else {
					xBola += espaco;
				}
				bolas[i].setaPosicao(xBola, yBola);
			} else {
				bolas[i].setaPosicao(xOrigem, yOrigem);
			}
		}
	}

	void jogoBot() { //jogada aleatoria do robo/bot

		bool escolheu; //Verdadeiro caso o bot tenha conseguido escolher a linha

		do {
			unsigned linhaEscolhida = rand() % (linhasHorizontais.size() + linhasVerticais.size()); //seleciona linha aleatÃ³ria

			if (linhaEscolhida < linhasHorizontais.size()) {
				if (linhasHorizontais[linhaEscolhida].clicarLinhaBot()) {
					escolheu = 1;
				} else {
					escolheu = 0;
				}
			} else if (linhaEscolhida >= linhasHorizontais.size()) {
				linhaEscolhida -= linhasHorizontais.size();
				if (linhasVerticais[linhaEscolhida].clicarLinhaBot()) {
					escolheu = 1;
				} else {
					escolheu = 0;
				}
			}
		} while (!escolheu);
	}

	bool fecharQuadrado(char quemJogou) { //fecha um quadrado quando as linhas em sua volta s~~ao escolhidas
		int linhasPassadas = 0;
		bool retorno = 0; //retorno da funcao, Verdadeiro quando quadrado sao fechado
		for (unsigned i = 0; i < quadrados.size(); i++) {
			if (eMultiplo(i, 5) && i!=0) {
				linhasPassadas++;
			}

			bool estaFechado = (linhasHorizontais[i].escolhido)
					&& (linhasVerticais[i + linhasPassadas].escolhido)
					&& (linhasHorizontais[i + 5].escolhido
							&& linhasVerticais[i + 1 + linhasPassadas].escolhido); //verifica se linahs ao redor estÃ£o escolhidas

			if (estaFechado && !quadrados[i].fechado) {
				if(quemJogou == 'p'){
					quadrados[i].setaCor(231, 109, 94, 200);
					quadrados[i].fechar();
					jogador.adicionaPonto();
					stringstream textoPontos;
					textoPontos << jogador.pontos;
					textoPontosJogador.setString(textoPontos.str());
				}else if(quemJogou == 'b'){
					quadrados[i].setaCor(59, 12, 5, 200);
					quadrados[i].fechar();
					bot.adicionaPonto();
					stringstream textoPontos;
					textoPontos << bot.pontos;
					textoPontosBot.setString(textoPontos.str());
				}else{
					exit(2);
				}
				retorno=1;
			}
		}
		return retorno;
	}

	void ganhou(){ //verifica se o jogador ganhou ou perdeu
		if(jogador.pontos>bot.pontos){
			carregaFundo("imagens/vitoria.png");
		}else{
			carregaFundo("imagens/derrota.png");
		}
	}

	void fim(){ //verifica se o jogo acabou
		if((jogador.pontos+bot.pontos)==25){
			ganhou();
			acabou = 1;
		}else{
			acabou = 0;
		}
	}
};

int main() {
	setbuf(stdout, NULL); //zera buffer para que o console sempre abra
	std::srand(std::time(NULL)); //define a semente como aleatoria
	Janela jogo(950, 720); //cria janela do jogo

	jogo.menu(); //inicia o loop do jogo

	return 0;
}
