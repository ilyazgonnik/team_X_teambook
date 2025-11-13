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


//примеры

int main() {
    // Создаем DSU для 5 элементов (0, 1, 2, 3, 4)
    Dsu dsu(5);
    
    // Объединяем элементы в множества
    dsu.unite(0, 1);  // Создаем множество {0, 1}
    dsu.unite(2, 3);  // Создаем множество {2, 3}
    dsu.unite(1, 2);  // Объединяем {0, 1} и {2, 3} в {0, 1, 2, 3}
    
    // Проверяем корни
    cout << "Корень 0: " << dsu.root(0) << endl;
    cout << "Корень 1: " << dsu.root(1) << endl;
    cout << "Корень 2: " << dsu.root(2) << endl;
    cout << "Корень 3: " << dsu.root(3) << endl;
    cout << "Корень 4: " << dsu.root(4) << endl;
    
    return 0;
}
