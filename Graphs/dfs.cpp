void dfs(int u){
    vis[u]=true;
    time_in[u]=timer++;
    for(auto v: adj[u]){
        if(!vis[v]){
            dfs(v);
        }
    }
    time_out[u]=timer++;
}
