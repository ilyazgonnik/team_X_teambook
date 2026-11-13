struct SuffixArray {
int n;
vector<int> sa, lcp, rank;
SuffixArray(const string& s) {
    n = s.size();
    string t = s + char(0);
    int N = n + 1;
    vector<int> p(N), c(N), cnt(max(256, N));

    for (unsigned char x : t) cnt[x]++;
    for (int i = 1; i < 256; i++)
        cnt[i] += cnt[i - 1];
    for (int i = 0; i < N; i++)
        p[--cnt[(unsigned char)t[i]]] = i;

    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < N; i++) {
        if (t[p[i]] != t[p[i - 1]]) classes++;
        c[p[i]] = classes - 1;
    }

    vector<int> pn(N), cn(N);
    for (int h = 0; (1LL << h) < N; h++) {
        int len = 1 << h;
        for (int i = 0; i < N; i++)
            pn[i] = (p[i] - len + N) % N;

        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int x : pn) cnt[c[x]]++;
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i - 1];
        for (int i = N - 1; i >= 0; i--)
            p[--cnt[c[pn[i]]]] = pn[i];

        cn[p[0]] = 0;
        int new_classes = 1;
        for (int i = 1; i < N; i++) {
            pair<int,int> a = {
                c[p[i]], c[(p[i] + len) % N]
            };
            pair<int,int> b = {
                c[p[i-1]], c[(p[i-1] + len) % N]
            };
            if (a != b) new_classes++;
            cn[p[i]] = new_classes - 1;
        }
        c.swap(cn);
        classes = new_classes;
    }

    sa.assign(p.begin() + 1, p.end());
    rank.resize(n);
    for (int i = 0; i < n; i++)
        rank[sa[i]] = i;

    lcp.assign(max(0, n - 1), 0);
    int k = 0;
    for (int i = 0; i < n; i++) {
        int r = rank[i];
        if (r == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[r + 1];
        while (i + k < n && j + k < n &&
               s[i + k] == s[j + k]) k++;
        lcp[r] = k;
        if (k) k--;
    }
}
};

/*
Suffix Array - sorted order of all suffixes of a string.
sa[i]   = starting position of the i-th smallest suffix
rank[i] = position of suffix s[i..n-1] in sa
lcp[i]  = LCP of suffixes sa[i] and sa[i+1]
Uses:
- Count distinct substrings: n*(n+1)/2 - sum(lcp)
- Longest repeated substring: max(lcp)
- Find pattern occurrences: binary search over sa
- LCP of any two suffixes: RMQ over lcp using rank
Build: O(n log n), Memory: O(n)
*/

// Example:
// SuffixArray suf("banana");
// suf.sa   = {5, 3, 1, 0, 4, 2};
// suf.lcp  = {1, 3, 0, 0, 2};
// suf.rank[1] == 2; // suffix "anana" has rank 2
//
// long long distinct = 1LL * suf.n * (suf.n + 1) / 2;
// for (int x : suf.lcp) distinct -= x;
// distinct == 15; // number of distinct substrings
