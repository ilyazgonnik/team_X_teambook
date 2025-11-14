pair<vector<int>, vector<int>> dijkstra(vector<vector<pair<int, int>>>& g, int start) {
    int n = g.size();
    vector<int> d(n, INF);
    vector<int> p(n, -1);
    
    d[start] = 0;
    priority_queue<pair<int, int>> pq;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int cur = pq.top().second;
        int curd = -pq.top().first;
        pq.pop();
        
        if (curd > d[cur]) {
            continue;
        }
        
        for (auto edge : g[cur]) {
            int to = edge.first;
            int w = edge.second;
            

            if (d[cur] + w < d[to]) {
                d[to] = d[cur] + w;
                p[to] = cur;
                pq.push({-d[to], to});
            }
        }
    }
    
    return {d, p};
}