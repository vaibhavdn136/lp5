#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>
using namespace std;

class Graph{
    private:
        int V;
        vector<vector<int> > adj;

    
    public:
        Graph(int vertices): V(vertices){
            adj.resize(V);
        }

        void addedge(int u,int v){
            adj[u].push_back(v);
            adj[v].push_back(u);
        }


        void bfs(int source){
            vector<bool> visited(V,false);
            queue<int> q;

            visited[source] = true;
            q.push(source);

            while(!q.empty()){
                int u = q.front();
                cout<<u<<" ";
                q.pop();
                #pragma omp parallel for
                for(int v: adj[u]){
                    if(!visited[v]){
                        #pragma omp critical
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
        }

};

int main(){
    Graph graph(7);

    graph.addedge(0,1);
    graph.addedge(0,2);
    graph.addedge(1,3);
    graph.addedge(1,4);
    graph.addedge(2,5);
    graph.addedge(2,6);

    cout<<"BFS traversal starting from node 0: "<<endl;
    graph.bfs(0);
    cout<<endl;

}
