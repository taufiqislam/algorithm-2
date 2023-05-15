#include<bits/stdc++.h>
#define ll long long
#define N '\n'
using namespace std;

class Graph {
        ll V;
        vector<vector<ll> > adj;
        vector<vector<pair<ll,ll> > > cap;
public:
    Graph(ll V)
    {
        this->V = V;
        adj.resize(V);
        cap.resize(V,vector<pair<ll,ll> >(V));
    }
    void addEdge(ll u, ll v, ll capacity)
    {
        adj[u].push_back(v);
        cap[u][v].first = 0;
        cap[u][v].second += capacity;
        adj[v].push_back(u);
        cap[v][u].first = 0;
        cap[v][u].second = 0;
    }
    bool bfs(ll s, ll t, vector<ll>& parent)
    {
        vector<bool> visited(V, false);
        queue<ll> q;
        q.push(s);

        visited[s] = true;
        parent[s] = -1;
        while (!q.empty())
        {
            ll u = q.front();
            q.pop();
            for (ll i = 0; i < (ll)adj[u].size(); i++)
            {
                ll v = adj[u][i];
                ll x = cap[u][v].second - cap[u][v].first;
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
    ll fordFulkerson(ll s, ll t)
    {
        ll maxFlow = 0;
        vector<ll> parent(V);
        while (bfs(s, t, parent))
        {
            ll pathFlow = LLONG_MAX;
            for (ll v = t; v != s; v = parent[v])
            {
                ll u = parent[v];
                pathFlow = min(pathFlow, cap[u][v].second-cap[u][v].first);
            }
            for (ll v = t; v != s; v = parent[v])
            {
                ll u = parent[v];
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
    ll V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;
    Graph g(V+5);
    cout << "Enter the edges and their capacity:\n";
    for (ll i = 0; i < E; i++)
    {
        ll u, v, capacity;
        cin >> u >> v >> capacity;
        g.addEdge(u, v, capacity);
    }
    ll s, t;
    cout << "Enter Source node: ";
    cin >> s;
    cout << "Enter Sink node: ";
    cin >> t;
    cout << "Maxflow: " << g.fordFulkerson(s, t) << endl;
    return 0;
}
