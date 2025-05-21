#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
//Classes
class Bola {
public:
	sf::CircleShape shape;
	int positionX;
	int positionY;

	int radius;
	int tam;

	Bola() {
		shape.setFillColor(sf::Color::White);
		tam = 10;
		radius = tam * 2;
		shape.setRadius(tam);
		positionX = 0;
		positionY = 0;
	}

	void setaPosicao(int x, int y) {
		positionX = x;
		positionY = y;
		shape.setPosition(x, y);
	}

};

bool isMult(int num, int mult) {
	if (num % mult == 0) {
		return 1;
	} else {
		return 0;
	}
}

void setaPosicaoVector(vector<Bola> *bolas) {
	int cont = 0;
	int xOrigem = 194;
	int yOrigem = 104;
	cout << "Abriu a função" << endl;
	int espacoX = 107;
	int espacoY = 107;
	int xBola = xOrigem;
	int yBola = yOrigem;
	for (int i = 0; i < bolas->size(); i++) {
		if (i != 0) {
			if (isMult(i, 6)) {
				xBola = xOrigem;
				yBola = yOrigem;
				cont++;
				yBola += espacoY* cont;
			}else{
				xBola += espacoX;
			}
			//(*bola).setaPosicao();
			(*bolas)[i].setaPosicao(xBola, yBola);
		} else {
			(*bolas)[i].setaPosicao(xOrigem, yOrigem);
		}
	}
}

//Funções

int main() {
	setbuf(stdout, NULL);
	// Cria a janela
	sf::RenderWindow window(sf::VideoMode(950, 720), "Bola Branca - SFML");
	std::cout << "rodou" << std::endl;
	//Bola de teste

	vector<Bola> bolasJogo(36);

	setaPosicaoVector(&bolasJogo);

	// Loop principal
	sf::Clock fpsClock;
	window.setFramerateLimit(100); //limite de fps

	while (window.isOpen()) { //evenmtos
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//impressão
		window.clear(sf::Color::Black); // fundo preto
		for (int i = 0; i < bolasJogo.size(); i++) {
			window.draw(bolasJogo[i].shape);
		}
		window.display();

	}
	return 0;
}
