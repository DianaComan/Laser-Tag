// Copyright 2017 Coman Diana Stefania
#include "Game.h"
#include "Sort.h"

#include <vector>
#include <string>
#include <algorithm>
#include <functional>

Game::Game() {
	firstTeamScore = 0;
	secondTeamScore = 0;
}

void Game::ReadTeam(int team, int size) {
	for (int i = 0; i < size; i++) {
		std::string name;
		std::cin >> name;

		players.push_back(Player(name, team));
		indexOf[name] = players.size() - 1;
	}
}

void Game::Setup() {
	int n, m;

	std::cin >> n;

	distances.resize(n);
	for (int i = 0; i < n; i++) {
		distances[i].resize(n);

		int j = 0;
		while (j < n) {
			// Daca sunt pe diagonala principala, pun 0
			if (j == i) {
				distances[i][j] = 0;
			} else {
				std::cin >> distances[i][j];
			}
			j++;
		}
	}

	std::cin >> n >> m;
	ReadTeam(FIRST, n);
	ReadTeam(SECOND, m);

	shootsGraph.Resize(n + m);
}

void Game::AddDistance(std::string player, int sensor) {
	int index = indexOf[player];
	int lastSensor = players[index].lastSensor;

	if (lastSensor != NO_SENSOR) {
		players[index].totalDistance += distances[lastSensor][sensor];
	}
	players[index].lastSensor = sensor;

	players[index].uniqueSensors[sensor] = true;
}

void Game::AddShot(std::string firstPlayer, std::string secondPlayer) {
	int index1 = indexOf[firstPlayer];
	int index2 = indexOf[secondPlayer];

	if (players[index1].team != players[index2].team) {
		players[index1].shoots++;
	} else {
		players[index1].friendlyFire++;
	}

	players[index2].lives--;
	if (players[index2].lives == 0) {
		players[index2].alive = false;
	}

	shootsGraph.AddEdge(index1, index2);
}

void Game::Run() {
	std::string line;
	getline(std::cin, line);
	getline(std::cin, line);

	while (line != END) {
		getline(std::cin, line);

		char buf[BUFLEN];
		strncpy(buf, line.c_str(), line.length() + 1);
		char* saveptr;

		char *token = strtok_r(buf, DELIMITERS, &saveptr);

		// Daca sunt la sfarsit de runda
		if (line.find(JOC) != std::string::npos || line.find(END)
												!= std::string::npos) {
			int firstAlive = 0;
			int secondAlive = 0;

			// Numar cati jucatori ramasi in viata sunt in fiecare echipa
			for (int i = 0; i < (int) players.size(); i++) {
				if (players[i].alive) {
					players[i].team == FIRST ? firstAlive++ : secondAlive++;
				}
				players[i].ComputeShooterScore();
				players[i].ComputeExplorerScore();
			}

			if (firstAlive == 0) {
				secondTeamScore++;
			} else if (secondAlive == 0) {
				firstTeamScore++;
			} else {  // Daca sunt la ultima runda
				int bestShooter = players[0].topShooterScore;
				int bestExplorer = players[0].topExplorerScore;

				for (int i = 0; i < (int) players.size(); i++) {
					if (players[i].topShooterScore > bestShooter) {
						bestShooter = players[i].topShooterScore;
					}
					if (players[i].topExplorerScore > bestExplorer) {
						bestExplorer = players[i].topExplorerScore;
					}
				}

				// Calculez winning chance pentru ambele echipe
				double firstWinningChance = 0;
				double secondWinningChance = 0;
				for (int i = 0; i < (int) players.size(); i++) {
					double shooter = bestShooter > 0 ?
						((double)players[i].topShooterScore / bestShooter) : 1;
					double explorer = bestExplorer > 0 ?
						((double)players[i].topExplorerScore / bestExplorer) : 1;
					double sum = players[i].alive * (shooter + explorer);

					if (players[i].team == FIRST) {
						firstWinningChance += sum;
					} else {
						secondWinningChance += sum;
					}
				}

				if (firstWinningChance > secondWinningChance) {
					firstTeamScore++;
				} else {
					secondTeamScore++;
				}
			}

			for (int i = 0; i < (int) players.size(); i++) {
				players[i].NewGame();
			}
			continue;
		}

		// Daca am citit o informatie despre locatie
		if (isdigit(token[0])) {
			int sensor = atoi(token);
			std::string player(strtok_r(NULL, DELIMITERS, &saveptr));
			AddDistance(player, sensor);
			continue;
		}

		// Daca am citit o informatie despre un schimb de focuri
		std::string firstPlayer(token);
		std::string secondPlayer(strtok_r(NULL, DELIMITERS, &saveptr));
		AddShot(firstPlayer, secondPlayer);
	}
}

void Game::PrintTopShooters() {
	std::vector<Player> shooters(players);

	// Sortez jucatorii in functie de top_shooter_score
	std::function<bool(const Player& left, const Player& right)> compare;
	compare = [](const Player& first, const Player& second) {
		if (first.topShooterScore == second.topShooterScore) {
			return first.name < second.name;
		}
		return first.topShooterScore > second.topShooterScore;
	};

	MergeSort<Player>(&shooters, 0, shooters.size() - 1, compare);

	int count = 0;
	if (shooters.size() < TOP) {
		count = shooters.size();
	} else {
		count = TOP;
		while (count < (int) shooters.size() && shooters[count].topShooterScore
			   == shooters[count - 1].topShooterScore) {
			count++;
		}
	}

	std::cout << "I. Top shooters" << "\n";
	for (int i = 0; i < count; i++) {
		std::cout << i + 1 << ". " << shooters[i].name << " "
			<< shooters[i].topShooterScore << "p\n";
	}

	std::cout << "\n";
}

void Game::PrintTopExplorers() {
	std::vector<Player> explorers(players);

	// Sortez jucatorii in functie de top_explorer_score
	std::function<bool(const Player& left, const Player& right)> compare;
	compare = [](Player first, Player second) {
		if (first.topExplorerScore == second.topExplorerScore) {
			return first.name < second.name;
		}
		return first.topExplorerScore > second.topExplorerScore;
	};

	MergeSort<Player>(&explorers, 0, explorers.size() - 1, compare);

	int count = 0;
	if (explorers.size() < TOP) {
		count = explorers.size();
	} else {
		count = TOP;
		while (count < (int) explorers.size()
				&& explorers[count].topExplorerScore ==
				explorers[count - 1].topExplorerScore) {
			count++;
		}
	}

	std::cout << "II. Top explorers" << "\n";
	for (int i = 0; i < count; i++) {
		std::cout << i + 1 << ". " << explorers[i].name << " "
			<< explorers[i].topExplorerScore << "p\n";
	}

	std::cout << "\n";
}

void Game::PrintTopFireExchange() {
	std::vector<FireExchange> exchanges;
	shootsGraph.GetFireExchange(players, &exchanges);

	// Sortez perechile de jucatori in functie de cate impuscaturi au schimbat
	std::function<bool(const FireExchange& left,
			const FireExchange& right)> compare;
	compare = [](FireExchange first, FireExchange second) {
		if (first.shoots == second.shoots) {
			return (first.firstPlayer + first.secondPlayer)
				< (second.firstPlayer + second.secondPlayer);
		}
		return first.shoots > second.shoots;
	};

	MergeSort<FireExchange>(&exchanges, 0, exchanges.size() - 1, compare);

	int count = 0;
	if (exchanges.size() < TOP) {
		count = exchanges.size();
	} else {
		count = TOP;
		while (count < (int) exchanges.size() && exchanges[count].shoots
			   == exchanges[count - 1].shoots) {
			count++;
		}
	}

	std::cout << "III. Top fire exchange\n";
	for (int i = 0; i < count; i++) {
		std::cout << i + 1 << ". " << exchanges[i].firstPlayer << " - "
		   << exchanges[i].secondPlayer << " " << exchanges[i].shoots << "\n";
	}

	std::cout << "\n";
}

void Game::PrintFinalScore() {
	std::cout << "IV. Final score" << "\n";
	std::cout << firstTeamScore << " - " << secondTeamScore << "\n\n";
}
