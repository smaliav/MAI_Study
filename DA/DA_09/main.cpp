#include <iostream>
#include <vector>
#include "TGraph.h"

int main(int argc, char *argv[]) {
	int n, m, start, finish;

	std::cin >> n >> m >> start >> finish;
	TGraph graph(std::cin, n, m);

	long long int result = graph.Dijkstra(start, finish);

	if (result < 0) {
		std::cout << "No solution" << std::endl;
	}
	else {
		std::cout << result << std::endl;
	}

	return 0;
}
