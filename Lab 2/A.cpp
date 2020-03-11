#include <fstream>
#include <vector>
using namespace std;

enum Color {
    white,
    gray,
    black
};

vector< vector <int> > graph;
vector<int> result;
vector<Color> color;
bool cycle = false;

void dfs(int v) {
    color[v] = gray;
    for (int i = 0; i < graph[v].size(); i++) {
        int to = graph[v][i];
        if (color[to] == white)
            dfs(to);
        if (color[to] == gray){
            cycle = true;
            return;
        }
    }
    color[v] = black;
    result.push_back(v);
}

void topsort() {
    for (int i = 1; i < graph.size(); i++)
        color[i] = white;
    result.clear();
    for (int i = 1; i < graph.size(); i++)
        if (color[i] == white)
            dfs(i);
}

int main() {
    ifstream fin("topsort.in");
    ofstream fout("topsort.out");
    int vertexNum, edgeNum;
    fin >> vertexNum >> edgeNum;
    graph.resize(vertexNum + 1);
    color.resize(vertexNum + 1);
    result.resize(vertexNum + 1);
    for (int i = 1; i <= edgeNum; i++) {
        int from, to;
        fin >> from >> to;
        graph[from].push_back(to);
    }
    topsort();
    if (cycle)
        fout << "-1" << endl;
    else
        for (int i = vertexNum - 1; i >= 0; i--)
            fout << result[i] << " ";
    fin.close();
    fout.close();
    return 0;
}