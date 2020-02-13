// Copyright 2017 Coman Diana Stefania
#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <unordered_map>

#define NO_SENSOR -1

struct Player {
	std::string name;
	int topExplorerScore;
	int topShooterScore;
	int team;

	int lastSensor;
	std::unordered_map<int, bool> uniqueSensors;
	int totalDistance;

	bool alive;
	int lives;
	int shoots;
	int friendlyFire;

	Player();
	Player(std::string name, int team);
	void NewGame();
	void ComputeShooterScore();
	void ComputeExplorerScore();
};

#endif  // PLAYER_H
