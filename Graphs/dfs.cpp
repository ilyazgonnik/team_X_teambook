void dfs(int u){
    vis[u]=true;
    time_in[u]=timer++;
    for(auto v: adj[u]){
        if(!vis[v]){
            dfs(v);
        }
    }
    time_out[u]=timer;
}
//u is (some of) parent v iff time_in[v] \in [time_in[u], time_out[u]) 
// intervals [time_in, time_out) are not intersecting or are nesting
//time_in is permutation of [0, n)
//size of subtree from v (including v) = time_out[v]-time_in[v]
//indexes of subtrees are intervals in time_in vector. 
