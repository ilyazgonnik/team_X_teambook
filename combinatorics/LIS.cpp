vector<int> findLIS_fast(vector<int> a) {
    int n = a.size();
    vector<int> d(n+1, INT_MAX), p(n+1, -1), pr(n, -1);
    int len = 0;

    d[0] = INT_MIN;
    p[0] = -1;

    for(int i = 0; i < n; i++) {
        int j = upper_bound(d.begin(), d.end(), a[i]) - d.begin();

        if(d[j-1] < a[i] && a[i] < d[j]) {
            d[j] = a[i];
            p[j] = i;
            pr[i] = p[j-1];
            len = max(len, j);
        }
    }
    vector<int> res;
    int cur = p[len];
    while(cur != -1) {
        res.push_back(a[cur]);
        cur = pr[cur];
    }
    reverse(res.begin(), res.end());
    return res;
}
