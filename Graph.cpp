// Copyright 2017 Coman Diana Stefania
#include "Graph.h"

#include <vector>

Graph::Graph() : adjMatrix(DEFAULT_SIZE, std::vector<int>(DEFAULT_SIZE, 0)) { }

Graph::Graph(int size) : adjMatrix(size, std::vector<int>(size, 0)) { }

void Graph::AddEdge(int u, int v) {
	adjMatrix[u][v]++;
	adjMatrix[v][u]++;
}

void Graph::Resize(int newSize) {
	adjMatrix.resize(newSize);

	for (int i = 0; i < newSize; i++) {
		adjMatrix[i].resize(newSize);
	}
}

// Returneaza schimb-ul de focuri dintre oricare 2 jucatori intr-un vector
// de structuri ce contine cei 2 jucatori si numarul de impuscaturi dintre ei
void Graph::GetFireExchange(const std::vector<Player>& players,
							std::vector<FireExchange>* exchanges) {
	for (int i = 0; i < (int) adjMatrix.size(); i++) {
		for (int j = 0; j < (int) adjMatrix[i].size(); j++) {
			if (adjMatrix[i][j] > 0 && players[i].name < players[j].name) {
				exchanges->push_back({players[i].name, players[j].name, adjMatrix[i][j]});
			}
		}
	}
}
