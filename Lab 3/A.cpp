#include <vector>
#include <fstream>
using namespace std;

vector<vector <int>> graph; 

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int vertexNum, edgeNum;
    fin >> vertexNum >> edgeNum;
    graph.resize(vertexNum);
    for (int i = 0; i < edgeNum; i++) {
        int from, to;
        fin >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph[to - 1].push_back(from - 1);
    }
    for (int i = 0; i < vertexNum; i++)
        fout << graph[i].size() << ' ';
    fin.close();
    fout.close();
    return 0;
}