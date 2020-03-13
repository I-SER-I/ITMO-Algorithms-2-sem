#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

struct Point {
    int x;
    int y;
};

int INF = 228228228228228228;
int vertexNum;
vector <Point> points;
vector <bool> visited;
vector <double> distans;
vector <vector <int>> graph;

int dist(Point a, Point b) {
	return ((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

void prim(int start) {
    distans[start] = 0;
	for (int i = 0; i < vertexNum; i++) {
		int v = -1;
		for (int j = 0; j < vertexNum; j++)
			if (!visited[j] && (v == -1 || distans[j] < distans[v]))
				v = j;
		visited[v] = true;
		for (int j = 0; j < vertexNum; j++) 
			if (!visited[j] && graph[v][j] < distans[j] && v != j)
				distans[j] = graph[v][j];
	}
}

int main() {
    ifstream fin("spantree.in");
    ofstream fout("spantree.out");
	fin >> vertexNum;
    points.resize(vertexNum);
    visited.resize(vertexNum, false);
    distans.resize(vertexNum, INF);
	graph.assign(vertexNum, vector<int>(vertexNum));
	for (int i = 0; i < vertexNum; i++)
		fin >> points[i].x >> points[i].y;
    for (int i = 0; i < vertexNum; i++)	
		for (int j = 0; j < vertexNum; j++)
			graph[i][j] = dist(points[i], points[j]);
	prim(0);
	double result = 0;
	for (int i = 0; i < vertexNum; i++)
		result += sqrt(distans[i]);
	fout.precision(10);
	fout << result << "\n";
	return 0;
}