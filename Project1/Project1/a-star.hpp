#pragma once

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include <utility>


using namespace std;

template<typename Node, typename Cost, size_t N>
std::list<Node> aStar(
	const Node &START,
	const Node &GOAL,
	const Node vertex[N],
	Cost **graph,
	Cost **sw,
	int &distance,
	Cost(*heuristic)(Node current, Node goal, Cost **sw));

template<typename T>
bool contains(std::deque<T> queue, T node) {
	for (auto item : queue) {
		if (item == node) {
			return true;
		}
		else { return false; }
	}
}

template<typename Node, size_t N>
size_t index_of(Node node, const Node nodes[N]) {
	for (size_t n = 0; n < N; n++) {
		if (nodes[n] == node) { return n; }
	}
}


template<typename T>
bool check(priority_queue<T, std::vector<T>, std::greater<T>> frontier, int test) {
	int temp = frontier.size();
	for (int i = 0; i <temp; i++) {
		if (test == frontier.top().second) return true;
		frontier.pop();
	}
	return false;
}

template<typename Node, typename Cost, size_t N>
std::list<Node> aStar(
	const Node &START,
	const Node &GOAL, 
	const Node vertex[N],
	Cost **graph,
	Cost **sw,
	int &distance,
	Cost(*heuristic)(Node current, Node goal, Cost **sw))
{
	int i = 0;
	typedef std::pair<Cost, size_t> El;
	std::priority_queue<El, std::vector<El>, std::greater<El>> frontier, temp;
	frontier.emplace(0, index_of<Node, N>(START, vertex));

	std::deque<size_t> explored;

	std::unordered_map<size_t, size_t> parent;

	std::unordered_map<size_t, Cost> aggregateCost;
	aggregateCost[frontier.top().second] = 0;

	size_t current;

	while (!frontier.empty()) {
		current = frontier.top().second;
		if (vertex[current] == GOAL) {
			std::list<Node> path;
	
			while (vertex[current] != START) {
				path.push_front(vertex[current]);
				distance += graph[current][parent[current]];
				current = parent[current];
			}
			path.push_front(START);
			return path;
		}

		explored.push_front(frontier.top().second);
		frontier.pop();

		for (size_t n = 0; n < N; n++) {

			if (graph[current][n] == 0 || contains(explored,n)) { continue; }

			Cost cost = aggregateCost[current] + graph[current][n];

			if (aggregateCost.find(n)==aggregateCost.end() || cost < aggregateCost[n]) {
				parent[n] = current;
				aggregateCost[n] = cost;
				if (!check<El>(frontier, n)) {
					frontier.emplace(cost + heuristic(vertex[n], GOAL, sw), n);
				}
			}
		}
		i++;
	}
	list<Node> a;
	return a;
}