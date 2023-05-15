#include <bits/stdc++.h>
using namespace std;
class Graph {
        int V;
        vector<vector<int> > adj;
        vector<vector<pair<int,int> > > cap;
public:
    Graph(int V) 
    {
        this->V = V;
        adj.resize(V);
        cap.resize(V,vector<pair<int,int> >(V));
    }
    void addEdge(int u, int v, int capacity) 
    {
        adj[u].push_back(v);
        cap[u][v].first = 0;
        cap[u][v].second = capacity;
        adj[v].push_back(u);
        cap[v][u].first = 0;
        cap[v][u].second = 0;
        // adj[u][adj[u].size() - 1] = adj[v].size() - 1;
        // adj[v][adj[v].size() - 1] = adj[u].size() - 2;
    }
    bool bfs(int s, int t, vector<int>& parent) 
    {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(s);

        visited[s] = true;
        parent[s] = -1;
        while (!q.empty()) 
        {
            int u = q.front();
            q.pop();
            for (int i = 0; i < adj[u].size(); i++) 
            {
                int v = adj[u][i];
                int x = cap[u][v].second - cap[u][v].first;
                if (!visited[v] && x > 0) 
                {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
        return (visited[t] == true);
    }
    int fordFulkerson(int s, int t) 
    {
        int maxFlow = 0;
        vector<int> parent(V);
        while (bfs(s, t, parent)) 
        {
            int pathFlow = INT_MAX;
            for (int v = t; v != s; v = parent[v]) 
            {
                int u = parent[v];
                pathFlow = min(pathFlow, cap[u][v].second);
            }
            for (int v = t; v != s; v = parent[v]) 
            {
                int u = parent[v];
                cap[u][v].first += pathFlow;
                cap[v][u].first -= pathFlow;
            }
            maxFlow += pathFlow;
        }
        return maxFlow;
    }
};
int main() 
{
    int V, E;
    cin >> V >> E;
    Graph g(V);
    for (int i = 0; i < E; i++) 
    {
        int u, v, capacity;

        cin >> u >> v >> capacity;
        g.addEdge(u, v, capacity);
    }
    int s, t;
    cin >> s >> t;
    cout << "Maximum flow: " << g.fordFulkerson(s, t) << endl;
    return 0;
}