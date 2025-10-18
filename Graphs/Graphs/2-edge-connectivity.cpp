vector<vector<pair<int, int> > > bicomponents(vector<vector<int> >&adj){
    int n=adj.size();
    int m=0;
    for(int i=0;i<n;i++){
        m+=adj[i].size();
    }
    vector <vector <int> > dfstree(n);
    vector <int> used(n), cut(n), h(n), up(n);
    
    auto findCutPoints = [&] (auto self, int u) -> void {
      used[u] = 1;
      up[u] = h[u];
      for (int v : adj[u]) {
        if (!used[v]) {
          dfstree[u].push_back(v);
          h[v] = h[u] + 1;
          self(self, v);
          up[u] = min(up[u], up[v]);
          if (up[v] >= h[u]) {
            cut[v] = 1;
          }
        }
        else {
          up[u] = min(up[u], h[v]);
        }
      }
    };
    
    findCutPoints(findCutPoints, 0);
    vector <vector <int> > tree(n + m);
    vector<int> color(n);color[0]=0;int ptr=n;
    
    auto build = [&] (auto self, int u) -> void {
      for (int v : dfstree[u]) {
        if (cut[v]) {
          color[v]=ptr;++ptr;
          self(self, v);
        }
        else {
          color[v]=color[u];
          self(self, v);
        }
      }
    };
    
    build(build, 0);
    int maxcolor=-1;
    for(auto v: color){
        maxcolor=max(v, maxcolor);
    }maxcolor++;//наверное, достаточно поставить n+m но мне лень об этом думать
    vector<vector<pair<int, int> > > ans1(maxcolor);
    auto edge_component = [&](int a, int b) -> int {
      int x = a, y = b;
      if (h[x] < h[y]){swap(x, y);} // x — нижняя вершина (глубже)
      return color[x];
    };
    for(int u=0;u<n;u++){
        for(auto v: adj[u]){
            int x=edge_component(u, v);
            ans1[x].push_back({u, v});
        }
    }
    vector<vector<pair<int, int> > > ans(0);
    for(auto v: ans1){
        if(v.size()!=0){
            ans.push_back(v);
        }
    }
    return ans;
}//распределение ребер по компонентам двусвязности 
//ребра будут как и uv так и vu 
//только для связных графов--надо менять колво вершин n , колво ребер -- m, find(find, НЕ ТОЛЬКО ОТ 0), аналогично с  build 


vector<pair<int, int> >  bridges (vector<vector<int> > &adj){
    auto dv = bicomponents(adj);
    vector<pair<int, int> > ans;
    for(auto a: dv){
        if(a.size()==2){//тут двойка, потому что uv vu всегда в одной бикомпоненте
            auto b=a[0];
            pair<int, int> c={b.second, b.first};
            ans.push_back(b);
            ans.push_back(c);
        }
    }
    return ans;
}//нахождение всех мостов. оба u--v, v--u будут 
vector<bool> CutPoints(vector<vector<int> > &adj){
    int n=adj.size();
    auto dv=bicomponents(adj);
    map<pair<int, int>, int> e;//по вершинам - номер ребра 
    int m=0;
    for(int u=0;u<n;u++){
        for(auto v: adj[u]){
            e[{u, v}]=m;
            m++;
        }
    }
    vector<int> num_comp(m);
    for(int i=0;i<dv.size();i++){
        for(auto edge: dv[i]){
            num_comp[e[edge]]=i;
        }
    }
    vector<bool> ans(n, false);
    for(int i=0;i<n;i++){
        int mine=inf;
        int maxe=-inf;
        for(auto j: adj[i]){
            mine=min(mine, num_comp[e[{i, j}]]);
            maxe=max(maxe, num_comp[e[{i, j}]]);
        }
        if(mine!=maxe){
            ans[i]=true;
        }
    }
    return ans;
}//изолированные вершины - да 
//лишний log

//для проверки можно использовать 1046-С
