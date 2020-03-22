#include <fstream>
#include <vector>

using namespace std;
vector < vector <int> > graph;
vector <bool> visited;
vector <int> companents;
int companentsNum = 0;

void dfs(int v) {
    visited[v] = true;
    companents[v] = companentsNum;
    for (int i = 0; i < graph[v].size(); i++) {
        int to = graph[v][i];
        if (!visited[to])
            dfs(to);
    }
}

int main() {
    ifstream fin("components.in");
    ofstream fout("components.out");
    int vertexNum, edgeNum;
    fin >> vertexNum >> edgeNum;
    graph.resize(vertexNum);
    visited.resize(vertexNum);
    companents.resize(vertexNum);
    for (int i = 0; i < edgeNum; i++) {
        int from, to;
        fin >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph[to - 1].push_back(from - 1);
    }
    for (int i = 0; i < graph.size(); i++)
        if (!visited[i]) {
            companentsNum++;
            dfs(i);
        }
    fout << companentsNum << endl;
    for (int i = 0; i < companents.size(); i++)
        fout << companents[i] << " ";
    fin.close();
    fout.close();
    return 0;
}
