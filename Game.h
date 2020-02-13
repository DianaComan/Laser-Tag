// Copyright 2017 Coman Diana Stefania
#pragma once

#ifndef GAME_H
#define GAME_H

#ifdef _WIN32
#define strtok_r strtok_s
#endif

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstring>
#include <cctype>
#include <algorithm>

#include "Graph.h"
#include "Player.h"
#include "FireExchange.h"

#define FIRST 1
#define SECOND 2

#define JOC "JOC_"
#define END "END_CHAMPIONSHIP"
#define BUFLEN 100
#define DELIMITERS " :->\n"
#define TOP 5

class Game {
	private:
	std::vector<Player> players;
	std::unordered_map<std::string, int> indexOf;
	std::vector<std::vector<int> > distances;
	Graph shootsGraph;
	int firstTeamScore;
	int secondTeamScore;

	void ReadTeam(int team, int size);
	void AddDistance(std::string player, int sensor);
	void AddShot(std::string firstPlayer, std::string secondPlayer);
	public:
	Game();
	void Setup();
	void Run();
	void PrintTopShooters();
	void PrintTopExplorers();
	void PrintTopFireExchange();
	void PrintFinalScore();
};

#endif  // GAME_H
