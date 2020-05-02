#include <fstream>
#include <vector>
using namespace std;

int vertexNumFirst, vertexNumSecond, edgeNum;
vector <vector<int>> graph;
vector<int> matching;
vector<bool> visited;
vector<bool> used;

bool kuhn(int from) {
    if (visited[from])
        return false;
    visited[from] = true;
    for (int i = 0; i < graph[from].size(); i++) {
        int to = graph[from][i];
        if (matching[to] == -1 || kuhn(matching[to])) {
            matching[to] = from;
            return true;
        }
    }
    return false;
}

int main() {
    ifstream fin("matching.in");
    ofstream fout("matching.out");
    fin >> vertexNumFirst >> vertexNumSecond >> edgeNum;
    graph.resize(vertexNumFirst, vector<int>());
    matching.resize(vertexNumSecond, -1);
    used.resize(vertexNumFirst);
    visited.resize(vertexNumFirst);
	for (int i = 0; i < edgeNum; i++) {
        int from, to;
        fin >> from >> to;
        graph[from - 1].push_back(to - 1);
    }
    for (int i = 0; i < vertexNumFirst; i++)
        for (int j = 0; j < graph[i].size(); j++)
            if (matching[graph[i][j]] == -1) {
                matching[graph[i][j]] = i;
                used[i] = true;
                break;
            }
    for (int i = 0; i < vertexNumFirst; i++) {
        if (used[i])
            continue;
        for (int j = 0; j < vertexNumFirst; j++)
            visited[j] = false;
        kuhn(i);
    }
    int value = 0;
    for (int i = 0; i < vertexNumSecond; i++)
        if (matching[i] != -1)
            value++;
    fout << value;
	return 0;
}