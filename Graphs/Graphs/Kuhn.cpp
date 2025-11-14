bool Graph::try_Kuhn (int v, vector<int> &mt, vector<bool> &vis){
	if (vis[v])  {return false;}
	vis[v] = true;
	for (auto to: Graph::adj[v]) {
		if (mt[to] == -1 || Graph::try_Kuhn (mt[to], mt, vis)) {
			mt[to] = v;
			return true;
		}
	}
	return false;
}


vector<pair<int, int> > Kuhn(){
    int n=Graph::V;
    auto ti=Graph::bfs(0);
    vector<int> dist=ti.first;
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
            try_Kuhn(v, mt, vis);
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
