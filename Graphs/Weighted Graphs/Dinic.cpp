struct Edge_flow {
    int v; // Vertex v (or "to" vertex)
    int flow; // flow of data in edge
    int C; // capacity
    int rev; // To store index of reverse
};

class Graph_flow {
    int V; // number of vertex
    int* level; // stores level of a node
    vector<Edge_flow>* adj;
public:
    Graph_flow(int V)
    {
        adj = new vector<Edge_flow>[V];
        this->V = V;
        level = new int[V];
    }
    void addEdge(int u, int v, int C)
    {
        Edge_flow a{ v, 0, C, (int)adj[v].size() };
        Edge_flow b{ u, 0, 0, (int)adj[u].size() };
        adj[u].push_back(a);
        adj[v].push_back(b); 
    }
    bool BFS_flow(int s, int t);
    int sendFlow(int s, int flow, int t, int ptr[]);
    int DinicMaxflow(int s, int t);
};

bool Graph_flow::BFS_flow(int s, int t)
{
    for (int i = 0; i < V; i++)
        level[i] = -1;
    level[s] = 0; 
    list<int> q;
    q.push_back(s);
    vector<Edge_flow>::iterator i;
    while (!q.empty()) {
        int u = q.front();
        q.pop_front();
        for (i = adj[u].begin(); i != adj[u].end(); i++) {
            Edge_flow& e = *i;
            if (level[e.v] < 0 && e.flow < e.C) {
                level[e.v] = level[u] + 1;
                q.push_back(e.v);
            }
        }
    }
    return level[t] < 0 ? false : true;
}
int Graph_flow::sendFlow(int u, int flow, int t, int start[])
{
    if (u == t)
        return flow;
    for (; start[u] < adj[u].size(); start[u]++) {
        Edge_flow& e = adj[u][start[u]];
        if (level[e.v] == level[u] + 1 && e.flow < e.C) {
            int curr_flow = min(flow, e.C - e.flow);
            int temp_flow = sendFlow(e.v, curr_flow, t, start);
            if (temp_flow > 0) {
                e.flow += temp_flow;
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }
    return 0;
}

int Graph_flow::DinicMaxflow(int s, int t)
{
    if (s == t)
        return -1;
    int total = 0; 
    while (BFS_flow(s, t) == true) {
        int* start = new int[V + 1]{ 0 };
        while (int flow = sendFlow(s, INT_MAX, t, start)) {
            total += flow;
        }
          delete[] start;
    }
    return total;
}

int DINIC(vector<vector<pair<int, int> > >&adj, int s, int t){
    int n=adj.size();
    Graph_flow g(n);
    for(int u=0;u<n;u++){
        for(auto p: adj[u]){
            int v=p.first;
            int w=p.second;
            g.addEdge(u, v, w);
        }
    }
    return g.DinicMaxflow(s, t);
}
