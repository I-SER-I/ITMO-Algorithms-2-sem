#include <fstream>
#include <vector>
#include <queue>
using namespace std;

vector <bool> island;
vector <pair <long long, long long>> graph[1000000];

long long prim() {
	long long result = 0;
	priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>> vertexQueue;
	vertexQueue.push(make_pair(0, 0));
	while (!vertexQueue.empty()) {
		pair<long long, long long> vertexWeightPair = vertexQueue.top();
		vertexQueue.pop();
		long long fromDis = vertexWeightPair.first;
		long long fromVer = vertexWeightPair.second;
		if (island[fromVer])
			continue;
		island[fromVer] = true;
		result += fromDis;
		for (long long i = 0; i < graph[fromVer].size(); i++) {
			long long toVer = graph[fromVer][i].first;
			long long toDis = graph[fromVer][i].second;
			if (!island[toVer])
				vertexQueue.push(make_pair(toDis, toVer));
		}
	}
	return result;
}

int main() {
	ifstream fin("spantree3.in");
	ofstream fout("spantree3.out");
	long long vertexNum, edgeNum;
	fin >> vertexNum >> edgeNum;
	island.resize(vertexNum, false);
	for (long long i = 0; i < edgeNum; i++) {
		long long from, to, weight;
		fin >> from >> to >> weight;
		graph[from - 1].push_back(make_pair(to - 1, weight));
		graph[to - 1].push_back(make_pair(from - 1, weight));
	}
	fout << prim();
	return 0;
}