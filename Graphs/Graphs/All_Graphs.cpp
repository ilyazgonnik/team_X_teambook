class Graph {
    bool tree_loc_help_to_forest(int start, vector<bool> &used);
    bool bipartite_help_local(int start, vector<int> &ans);
    bool try_Kuhn(int v, vector<int> &mt, vector<bool> &vis);
    void dfsS_C1(int u);
    void dfsS_C2(int u, vector<vector<int>> &gr, int C);
    vector<int> order;//топсорт графа, от самых слабых до самых сильных
public:
    int V; // No. of vertices
    int E; // No. of edges
    vector<vector<int> > adj; // A dynamic array of adjacency lists
    Graph(int V); // Constructor
    void addEdge(int v, int w); // function to add an edge to graph
    pair<vector<int>, vector<int> > bfs(int start);//{distance from start, parent} 
    bool connected();//связный ли
    bool tree();//дерево ли
    bool tree_loc(int start);//дерево ли компонента start
    bool forest();//лес ли
    vector<int> diameter_local(int start);//диаметр (последовательно его вершины) в компоненте связности start
    vector<int> diameter;//диаметр (последовательно его вершины) во всём графе
    bool bipartite_local(int start);//двудольность компоненты start
    bool bipartite();//двудольность
    vector<pair<int, int> > Kuhn();//поиск лучшего паросочетания для связных графов
    int number_of_components();//количество компонент
    pair<vector<int>, vector<vector<int> > > connection_vertices();//от вершин к компонентам и обратно
    vector<int> time_in;//время входа dfs
    vector<int> time_out;//время выхода dfs
    vector<bool> dfs_vis;
    int dfs_timer;
    void dfs(int u);
    void Sharir_Cosaradgu();
    vector<int> strong_component;
    vector<int> top_sort();
    vector<vector<pair<int, int> > > bicomponents();
    vector<pair<int, int> > bridges();
    vector<bool> CutPoints();
};

Graph::Graph(int V)
{
    this->V = V;
    this->E = 0;
    adj.resize(0); adj.resize(V);
    time_in.resize(0); time_in.resize(V);
    time_out.resize(0); time_out.resize(V);
    dfs_vis.resize(0); dfs_vis.resize(V);
    dfs_timer=0;
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    E++;
}

pair<vector<int>, vector<int>> Graph::bfs(int start){
    int n=Graph::V;
    vector<int> ans(n, -1);
    vector<int> parent(n);
    queue <int> q;
    ans[start]=0;
    parent[start]=-1;
    q.push(start);
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(auto u: Graph::adj[v]){
            if(ans[u]==-1){
                ans[u]=ans[v]+1;
                q.push(u);
                parent[u]=v;
            }
        }
    }
    return {ans, parent};
}

bool Graph::connected(){
    int n=Graph::V;
    vector<bool> used (n, false);
    queue <int> q;
    q.push(0);
    used[0]=true;
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(auto u: Graph::adj[v]){
            if(!used[u]){
                q.push(u);
            }
            used[u]=true;
        }
    }
    bool is=true;
    for(int i=0;i<n;i++){
        if(!used[i]){
            is=false;
        }
    }
    return is;
}

bool Graph::tree(){
    if(Graph::connected() && Graph::E == (2*Graph::V - 2)){
        return true;
    }
    else{
        return false;
    }
}

bool Graph::tree_loc(int start){
    vector<bool> used(Graph::V, false);
    queue<int> q;
    q.push(start);
    used[start]=true;
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(auto u: Graph::adj[v]){
            if(!used[u]){
                q.push(u);
            }
            used[u]=true;
        }
    }
    int e=0;
    int v=0;
    for(int i=0;i<Graph::V;i++){
        if(used[i]){
            v++;
            e+=Graph::adj[i].size();
        }
    }
    e/=2;
    if(e+1==v){
        return true;
    }
    else{
        return false;
    }
}

bool Graph::tree_loc_help_to_forest(int start, vector<bool> &used){
    int n=Graph::V;
    vector<int> new_comp(0);
    queue<int> q;
    q.push(start);
    used[start]=true;
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(auto u: Graph::adj[v]){
            if(!used[u]){
                q.push(u);
            }
            used[u]=true;
        }
        new_comp.push_back(v);
    }
    int e=0;
    int v=new_comp.size();
    for(auto i: new_comp){
        e+=Graph::adj[i].size();
    }
    e/=2;
    if(e+1==v){
        return true;
    }
    else{
        return false;
    }
}

bool Graph::forest(){
    vector<bool> used(Graph::V, false);
    bool is_forest=true;
    int start=0;
    while(start<Graph::V){
        if(!used[start]){
            if(!Graph::tree_loc_help_to_forest(start, used)){
                is_forest=false;
                break;
            }
        }
        start++;
    }
    return is_forest;
}//лес ли? 

vector<int> Graph::diameter_local(int start){
    int n=Graph::V;
    auto ti=Graph::bfs(start);
    vector<int> res=ti.first;
    int maximum=-1; int ind;
    for(int i=0;i<n;i++){
        if(res[i]>maximum){
            ind=i;
            maximum=max(maximum, res[i]);
        }
    }
    ti=Graph::bfs(ind);
    res=ti.first;
    vector<int> parent=ti.second;
    maximum=-1;
    for(int i=0;i<n;i++){
        if(res[i]>maximum){
            ind=i;
            maximum=max(maximum, res[i]);
        }
    }
    vector<int> diametr(0);
    while(ind!=-1){
        diametr.push_back(ind);
        ind=parent[ind];
    }
    return diametr;
}//диаметр (последовательно его вершины) в компоненте связности start

bool Graph::bipartite_local(int start){
    int n=Graph::V;
    vector<int> ans(n, -1);
    queue <int> q;
    ans[start]=0;
    q.push(start);
    bool bipart_loc_ans=true;
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(auto u: Graph::adj[v]){
            if(ans[u]==-1){
                ans[u]=ans[v]+1;
                q.push(u);
            }
            else{
                if(ans[u]%2==ans[v]%2){
                    bipart_loc_ans=false;
                }
            }
        }
    }
    return bipart_loc_ans;
}//двудольность компоненты start

bool Graph::bipartite_help_local(int start, vector<int> &ans){
    int n=Graph::V;
    queue <int> q;
    ans[start]=0;
    q.push(start);
    bool bipart_loc_ans=true;
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(auto u: Graph::adj[v]){
            if(ans[u]==-1){
                ans[u]=ans[v]+1;
                q.push(u);
            }
            else{
                if(ans[u]%2==ans[v]%2){
                    bipart_loc_ans=false;
                }
            }
        }
    }
    return bipart_loc_ans;
}

bool Graph::bipartite(){
    vector<int> ans(Graph::V, -1);
    bool bipartite_ans=true;
    int start=0;
    while(start<Graph::V){
        if(ans[start]==-1){
            if(!Graph::bipartite_help_local(start, ans)){
                bipartite_ans=false;
                break;
            }
        }
        start++;
    }
    return bipartite_ans;
}//двудольный ли

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

vector<pair<int, int> > Graph::Kuhn(){
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
    vector<int> mt(n, -1);//заполняется толкьо для правой доли
    vector<bool> vis(n);//заполняется только для левой доли
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
}//может работать только для связных графов

int Graph::number_of_components(){
    int ans=0;
    int n=Graph::V;
    vector<bool> vis(n);
    int start=0;
    while(start<n){
        if(!vis[start]){
            ans++;
            queue<int> q; q.push(start); vis[start]=true;
            while(!q.empty()){
                int v=q.front();
                q.pop();
                for(auto u: Graph::adj[v]){
                    if(!vis[u]){
                        q.push(u);
                        vis[u]=true;
                    }
                }
            }
        }
        start++;
    }
    return ans;
}

pair<vector<int>, vector<vector<int> > > Graph::connection_vertices(){
    int ans=0;
    int n=Graph::V;
    vector<vector<int> > c_to_v(0);
    vector<int> v_to_c(n);
    vector<bool> vis(n);
    int start=0;
    while(start<n){
        if(!vis[start]){
            c_to_v.resize(ans+1);
            queue<int> q; q.push(start); vis[start]=true;
            while(!q.empty()){
                int v=q.front();
                q.pop();
                for(auto u: Graph::adj[v]){
                    if(!vis[u]){
                        q.push(u);
                        vis[u]=true;
                    }
                }
                c_to_v[ans].push_back(v);
                v_to_c[v]=ans;
            }
            ans++;
        }
        start++;
    }
    return {v_to_c, c_to_v};
}//выдает связь компонент - вершин. От вершины к компоненте и от компоненты к вершине

void Graph::dfs(int u){
    dfs_vis[u]=true;
    time_in[u]=dfs_timer++;
    for(auto v: Graph::adj[u]){
        if(!dfs_vis[v]){
            dfs(v);
        }
    }
    time_out[u]=dfs_timer++;
}//time_in, time_out

void Graph::dfsS_C1(int u){
    Graph::dfs_vis[u] = true;
	for (auto v: Graph::adj[u]){
		if (!Graph::dfs_vis[v]){
			Graph::dfsS_C1 (v);
		}
	}
	Graph::order.push_back(u);
}

void Graph::dfsS_C2 (int u, vector<vector<int> > &gr, int C){
	Graph::dfs_vis[u] = true;
	Graph::strong_component[u]=C;
	for (auto v: gr[u]){
		if (!Graph::dfs_vis[v]){
			Graph::dfsS_C2 (v, gr, C);
		}
	}
}

void Graph::Sharir_Cosaradgu(){
    int n=Graph::V; Graph::dfs_vis.assign(n, false); Graph::strong_component.resize(n);
    vector<vector<int> > gr(n);
    Graph::order.clear();
    int C=0;
    for(int i=0;i<n;i++){
        for(auto j: Graph::adj[i]){
            gr[j].push_back(i);
        }
    }
    for(int i=0;i<n;i++){
        if(!Graph::dfs_vis[i]){
            Graph::dfsS_C1(i);
        }
    }
    Graph::dfs_vis.assign(n, false);
    for(int i=0;i<n;i++){
        int v=order[n-i-1];
        if(!Graph::dfs_vis[v]){
            Graph::dfsS_C2(v, gr, C);
            C++;
        }
    }
    Graph::dfs_vis.assign(n, false);
}//записывает результат в вектор strong_component

vector<int> Graph::top_sort(){
    int n=Graph::V; Graph::dfs_vis.assign(n, false);
    for(int i=0;i<n;i++){
        if(!Graph::dfs_vis[i]){
            Graph::dfsS_C1(i);
        }
    }
    Graph::dfs_vis.assign(n, false);
    return Graph::order;
}//от самых слабых к самым сильным

vector<vector<pair<int, int> > > Graph::bicomponents(){
    int n=Graph::V;
    int m=Graph::E;
    vector <vector <int> > dfstree(n);
    vector <int> used(n), cut(n), h(n), up(n);
    
    auto findCutPoints = [&] (auto self, int u) -> void {
      used[u] = 1;
      up[u] = h[u];
      for (int v : Graph::adj[u]) {
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
        for(auto v: Graph::adj[u]){
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

vector<pair<int, int> >  Graph::bridges (){
    auto dv = Graph::bicomponents();
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

vector<bool> Graph::CutPoints(){
    int n=Graph::V;
    auto dv=Graph::bicomponents();
    map<pair<int, int>, int> e;//по вершинам - номер ребра 
    int m=0;
    for(int u=0;u<n;u++){
        for(auto v: Graph::adj[u]){
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
        int mine=dv.size();//=inf
        int maxe=-dv.size();//=-inf
        for(auto j: Graph::adj[i]){
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
