// Copyright 2017 Coman Diana Stefania
#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

#include "Player.h"
#include "FireExchange.h"

#define DEFAULT_SIZE 1000

class Graph {
	private:
	std::vector<std::vector<int> > adjMatrix;

	public:
	Graph();
	explicit Graph(int size);
	void Resize(int size);

	void AddEdge(int u, int v);
	void GetFireExchange(const std::vector<Player>& players,
								std::vector<FireExchange>* exchanges);
};

#endif  // GRAPH_H
