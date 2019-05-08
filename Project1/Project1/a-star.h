#pragma once

#include <array>
#include <deque>
#include <iostream>
#include <list>
#include <unordered_map>
#include <queue>
#include <utility>


template<typename Node, typename Cost, size_t N>
std::list<Node> aStar(
	const Node &START,
	const Node &GOAL,
	const Node vertex[N],
	const Cost graph[N][N],
	Cost(*heuristic)(Node current, Node goal));