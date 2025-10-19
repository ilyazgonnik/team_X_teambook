int l;//определить величины так: l = 1; while ((1<<l) <= n){l++;}
vector < vector<int> > up;//определить величины так: for (int i=0; i<n; ++i){  up[i].resize (l+1);}
//бинподъем up[i][j]=2^j-ый предок вершины i 
void dfs_bin_up (int v, int p = 0) {
	time_in[v] = timer++;
	up[v][0] = p;
	for (int i=1; i<=l; ++i){
		up[v][i] = up[up[v][i-1]][i-1];
	}
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to != p){
			dfs_bin_up (to, v);
		}
	}
	time_out[v] = timer;
}

bool upper (int a, int b) {
	return time_in[a] <= time_in[b] && time_in[b]<time_out[a];
}//a - предок b

int lca (int a, int b) {
	if (upper (a, b))  return a;
	if (upper (b, a))  return b;
	for (int i=l; i>=0; --i){
		if (! upper (up[a][i], b)){
			a = up[a][i];
		}
	}
	return up[a][0];
}
//использовать:dfs_bin_up(0);
