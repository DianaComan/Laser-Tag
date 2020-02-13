// Copyright 2017 Coman Diana Stefania
#include "Player.h"

#include <string>

Player::Player() { }

Player::Player(std::string name, int team) {
	this->name = name;
	this->team = team;

	topExplorerScore = 0;
	topShooterScore = 0;
	NewGame();
}

void Player::NewGame() {
	totalDistance = 0;
	shoots = 0;
	friendlyFire = 0;
	alive = true;
	lives = 2;
	lastSensor = NO_SENSOR;
	uniqueSensors.clear();
}

void Player::ComputeShooterScore() {
	topShooterScore += 2 * shoots - 5 * friendlyFire;
}

void Player::ComputeExplorerScore() {
	topExplorerScore += totalDistance + 3 * uniqueSensors.size();
}
