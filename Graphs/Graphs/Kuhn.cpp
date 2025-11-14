bool try_Kuhn (int v, vector<int> &mt, vector<bool> &vis, vector<vector<int> > &adj){
	if (vis[v])  {return false;}
	vis[v] = true;
	for (auto to: adj[v]) {
		if (mt[to] == -1 || try_Kuhn (mt[to], mt, vis, adj)) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}


vector<pair<int, int> > Kuhn(vector<vector<int> > &adj){
    int n=adj.size();
    auto [dist, o]=bfs(0, adj);
    int odd=0;
    int even=0;
    vector<bool> left(n);
    for(int i=0;i<n;i++){
        if(dist[i]%2==0){
            even++;
            left[i]=true;
        }
        else{
            odd++;
        }
    }
    if(odd<even){
        for(int i=0;i<n;i++){
            left[i]=(!left[i]);
        }
    }
    vector<int> mt(n, -1);//For right part
    vector<bool> vis(n);//For left part
    for(int v=0;v<n;v++){
        if(left[v]){
            vis.assign(n, false);
            try_Kuhn(v, mt, vis, adj);
        }
    }
    vector<pair<int, int> > ans(0);
    for(int i=0;i<n;i++){
        if((!left[i])  &&  (mt[i]!=-1)){
            ans.push_back({mt[i], i});
        }
    }
    return ans;
}//Maybe only for connected graphs
