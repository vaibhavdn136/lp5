#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <omp.h>

using namespace std;

class Graph{
    private:
        int V;
        vector<vector<int>> adj;
    
    public:

        Graph(int vertices): V(vertices){
            adj.resize(V);
        }

        void addEdge(int u, int v){
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        void dfs(int source){
            vector<bool> visited(V,false);

            stack<int> s;
            s.push(source);

            while(!s.empty()){
                int u = s.top();
                s.pop();

                if(!visited[u]){
                    visited[u] = true;
                    cout<<u<<" ";

                    #pragma omp parallel for
                    for(int v: adj[u]){

                        #pragma omp critical
                        if(!visited[v]){
                            s.push(v);
                        }
                    }
                }
                

            }
        }
};

int main() {
    // Create a graph with 7 vertices
    Graph graph(7);

    // Add edges
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 5);
    graph.addEdge(2, 6);

    cout << "DFS traversal starting from node 0: ";
    graph.dfs(0);
    cout << endl;

    return 0;
}