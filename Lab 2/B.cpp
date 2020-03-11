#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
ifstream fin("cycle.in");
ofstream fout("cycle.out");

int cycleStart = -1, cycleEnd;

enum Color {
	white,
	grey,
	black
};

bool dfs(int& from, vector<vector<int>>& graph, vector<Color>& color, vector<int>& parent) {
	color[from] = grey;
	for (int i = 0; i < graph[from].size(); i++) {
		int to = graph[from][i];
		if (color[to] == white) {
			parent[to] = from;
			if (dfs(to, graph, color, parent))
				return true;
		}
		else if (color[to] == grey) {
			cycleStart = to;
			cycleEnd = from;
			return true;
		}
	}
	color[from] = black;
	return false;
}

int main() {
	int vertexNum, edgeNum;
	fin >> vertexNum >> edgeNum;
	vector<vector <int>> graph(vertexNum);
	vector<Color> color(vertexNum, white);
	vector<int> parent(vertexNum, -1);
	for (int i = 0; i < edgeNum; i++) {
		int from, to;
		fin >> from >> to;
		graph[from - 1].push_back(to - 1);
		if (from == to) {
			fout << "YES\n" << to;
			return 0;
		}
	}
	for (int i = 0; i < vertexNum; i++)
		if (color[i] == white && dfs(i, graph, color, parent))
			break;
	if (cycleStart != -1) {
		fout << "YES" << endl;
		vector<int> way;
		for (int cycleNow = cycleEnd; cycleNow != cycleStart; cycleNow = parent[cycleNow])
			way.push_back(cycleNow);
		way.push_back(cycleStart);
		for (int i = way.size() - 1; i >= 0; i--)
			fout << way[i] + 1 << " ";
	}
	else
		fout << "NO";
	fin.close();
	fout.close();
	return 0;
}