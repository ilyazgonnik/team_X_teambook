pair<vector<int>, vector<int>> bfs(int start, vector<vector<int>> &g){
    int n=g.size();
    vector<int> dist(n);
    vector<int> p(n);
    for(int i=0;i<n;i++){
        dist[i]=inf;
    }
    queue <int> q;
    dist[start]=0;
    p[start]=-1;
    q.push(start);
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(auto u: g[v]){
            if(dist[u]==inf){
                dist[u]=dist[v]+1;
                q.push(u);
                p[u]=v;
            }
        }
    }
    return {dist, p};
}
