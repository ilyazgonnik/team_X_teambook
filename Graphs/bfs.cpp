pair<vector<int>, vector<int>> bfs(int n, int start, vector<vector<int>> &adj){
    vector<int> ans(n);
    vector<int> parent(n);
    for(int i=0;i<n;i++){
        ans[i]=-1;
    }
    queue <int> q;
    ans[start]=0;
    parent[start]=-1;
    q.push(start);
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(auto u: adj[v]){
            if(ans[u]==-1){
                ans[u]=ans[v]+1;
                q.push(u);
                parent[u]=v;
            }
        }
    }
    pair<vector<int>, vector<int>> res;
    res.first = ans;
    res.second = parent;
    return res;
}
