#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();

	void runGame();
	void Play();
	void Ranking();
	void Author();


protected:
	enum GameState { MENU, GAME, GAME_OVER, END,RANKING,AUTHOR }; //lista wyliczeniowa statusu gry, sluzy do okreslena tego, czy okno ma pokazywac teraz menu, gre itd
	GameState state;

private:
	Font font;
	void menu();

};

