struct Dsu {
vector <int> p;
vector <int> r;
int n;
Dsu (int n_) {
n = n_;
p = vector <int> (n);
iota (p.begin (), p.end (), 0);
r = vector <int> (n, 0);
}
int root (int v) {
if (p[v] == v)
return v;
return p[v] = root (p[v]);
}
bool unite (int u, int v) {
 u = root (u);
 v = root (v);
 if (u == v)
 return false;
 if (r[u] > r[v])
 swap (u, v);
 p[u] = v;
 if (r[u] == r[v])
 r[v] += 1;
 return true;
}
 
};


/*example
 int main() {
    // creating DSU for 5 elements (0, 1, 2, 3, 4)
    Dsu dsu(5);
    
    // uniting elements into sets
    dsu.unite(0, 1);  // Creating set {0, 1}
    dsu.unite(2, 3);  // Creating set {2, 3}
    dsu.unite(1, 2);  // Unite {0, 1} and {2, 3} into {0, 1, 2, 3}
    
    // Checking roots
    cout << "Root 0: " << dsu.root(0) << endl;
    return 0;
}*/
