// Copyright 2017 Coman Diana Stefania
#include <iostream>

#include "Game.h"

int main() {
	Game game;

	game.Setup();
	game.Run();
	game.PrintTopShooters();
	game.PrintTopExplorers();
	game.PrintTopFireExchange();
	game.PrintFinalScore();

	return 0;
}
