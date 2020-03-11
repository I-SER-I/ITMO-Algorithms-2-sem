#include <fstream>
#include <vector>
using namespace std;

enum Game {
	loss,
	win
};

vector<vector <int>> graph;
vector<Game> vertex;
vector<bool> visited;

void dfs(int from) {
	visited[from] = true;
	Game status = loss;
	for (int i = 0; i < graph[from].size(); ++i) {
		int to = graph[from][i];
		if (!visited[to])
			dfs(to);
		if (vertex[to] == loss)
			status = win;
	}
	vertex[from] = status;
}

int main() {
	ifstream fin("game.in");
	ofstream fout("game.out");
	int vertexNum, edgeNum, chip;
	fin >> vertexNum >> edgeNum >> chip;
	graph.resize(vertexNum);
	vertex.resize(vertexNum);
	visited.resize(vertexNum, false);
	for (int i = 0; i < edgeNum; i++) {
		int from, to;
		fin >> from >> to;
		graph[from - 1].push_back(to - 1);	
	}
	dfs(chip - 1);
	if (vertex[chip - 1])
		fout << "First player wins" << endl;
	else
		fout << "Second player wins" << endl;
	fin.close();
	fout.close();
	return 0;
}