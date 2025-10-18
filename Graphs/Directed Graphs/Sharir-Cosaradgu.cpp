void dfsS_C1(int u, vector<vector<int> > &g, vector<int> &order, vector<bool> &vis){
    vis[u] = true;
	for (auto v: g[u]){
		if (!vis[v]){
			dfsS_C1 (v, g, order, vis);
		}
	}
	order.push_back(u);
}
void dfsS_C2 (int u, vector<vector<int> > &gr, vector<bool>&vis, vector<int> &component, int &C){
	vis[u] = true;
	component[u]=C;
	for (auto v: gr[u]){
		if (!vis[v]){
			dfsS_C2 (v, gr, vis, component, C);
		}
	}
}
vector<int> Sharir_Cosaradgu(vector<vector<int> > &g){
    int n=g.size();
    vector<vector<int> > gr(n);
    vector<int> order(0);
    vector<bool> vis(n);
    vector<int> component(n);
    int C=0;
    for(int i=0;i<n;i++){
        for(auto j: g[i]){
            gr[j].push_back(i);
        }
    }
    for(int i=0;i<n;i++){
        if(!vis[i]){
            dfsS_C1(i, g, order, vis);
        }
    }
    vis.assign(n, false);
    for(int i=0;i<n;i++){
        int v=order[n-i-1];
        if(!vis[v]){
            dfsS_C2(v, gr, vis, component, C);
            C++;
        }
    }
    return component;
}//вектор номеров компонент сильной связности
 
