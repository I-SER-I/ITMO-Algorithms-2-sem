#include <fstream>
using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int vertexNum, edgeNum;
    fin >> vertexNum >> edgeNum;
    bool matrix[100][100] = {false};
    for (int i = 0; i < edgeNum; i++) {
        int from, to;
        fin >> from >> to;
        if (matrix[from - 1][to - 1] || matrix[from - 1][to - 1]) {
            fout << "YES";
            return 0;
        }
        matrix[from - 1][to - 1] = true;
    }
    fout << "NO";
    fin.close();
    fout.close();
    return 0;
}
