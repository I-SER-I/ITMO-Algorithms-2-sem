#include <fstream>
#include <vector>
using namespace std;

enum Color {
	white,
	black
};
vector<vector <int>> graph;
vector<Color> color;
bool isBigraph = true;

Color revers(Color color){
	if (color)
		return white;
	else
		return black;
}

void dfs(int from, Color vertexColor) {
	color[from] = vertexColor;
	for (int i = 0; i < graph[from].size(); i++) {
		int to = graph[from][i];
		if (color[to] == white)
			dfs(to, revers(vertexColor));
		else if (color[to] == vertexColor){
			isBigraph = false;
			return;
		}
	}
}

int main() {
	ifstream fin("bipartite.in");
	ofstream fout("bipartite.out");
	int vertexNum, edgeNum;
	fin >> vertexNum >> edgeNum;
	graph.resize(vertexNum);
	color.resize(vertexNum, white);
	for (int i = 0; i < edgeNum; i++) {
		int from, to;
		fin >> from >> to;
		graph[from - 1].push_back(to - 1);
		graph[to - 1].push_back(from - 1);
	}
	for (int i = 0; i < vertexNum; i++)
		if (color[i] == white) {
			dfs(i, white);
			if (!isBigraph) {
				fout << "NO";
				return 0;
			}
		}
	fout << "YES";
	fin.close();
	fout.close();
	return 0;
}