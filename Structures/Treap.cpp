struct Treap {
struct Node {
int val, sz = 1;
uint32_t prior;
long long sum, add = 0;
bool rev = false;
Node *l = nullptr, *r = nullptr;
    Node(int v, uint32_t p) : val(v), prior(p), sum(v) {}
};

using T = Node*;
T root = nullptr;
mt19937 rng{712367821};

int sz(T t) { return t ? t->sz : 0; }
long long sum(T t) { return t ? t->sum : 0; }

void apply_add(T t, long long x) {
    if (!t) return;
    t->val += x;
    t->sum += x * sz(t);
    t->add += x;
}

void apply_rev(T t) {
    if (!t) return;
    swap(t->l, t->r);
    t->rev ^= 1;
}

void push(T t) {
    if (!t) return;
    if (t->rev) {
        apply_rev(t->l);
        apply_rev(t->r);
        t->rev = false;
    }
    if (t->add) {
        apply_add(t->l, t->add);
        apply_add(t->r, t->add);
        t->add = 0;
    }
}

void upd(T t) {
    if (t) {
        t->sz = 1 + sz(t->l) + sz(t->r);
        t->sum = t->val + sum(t->l) + sum(t->r);
    }
}

// a = first k elements, b = remaining elements
void split(T t, int k, T &a, T &b) {
    if (!t) { a = b = nullptr; return; }
    push(t);
    if (sz(t->l) >= k) {
        split(t->l, k, a, t->l);
        b = t;
    } else {
        split(t->r, k - sz(t->l) - 1, t->r, b);
        a = t;
    }
    upd(t);
}

T merge(T a, T b) {
    if (!a || !b) return a ? a : b;
    if (a->prior > b->prior) {
        push(a);
        a->r = merge(a->r, b);
        upd(a);
        return a;
    }
    push(b);
    b->l = merge(a, b->l);
    upd(b);
    return b;
}

// All positions are 0-indexed, ranges are [l, r)
void insert(int pos, int val) {
    T a, b;
    split(root, pos, a, b);
    root = merge(merge(a, new Node(val, rng())), b);
}

void erase(int pos) {
    T a, b, c;
    split(root, pos, a, b);
    split(b, 1, b, c);
    delete b;
    root = merge(a, c);
}

void range_add(int l, int r, long long x) {
    T a, b, c;
    split(root, r, b, c);
    split(b, l, a, b);
    apply_add(b, x);
    root = merge(merge(a, b), c);
}

void reverse(int l, int r) {
    T a, b, c;
    split(root, r, b, c);
    split(b, l, a, b);
    apply_rev(b);
    root = merge(merge(a, b), c);
}

long long range_sum(int l, int r) {
    T a, b, c;
    split(root, r, b, c);
    split(b, l, a, b);
    long long ans = sum(b);
    root = merge(merge(a, b), c);
    return ans;
}

int size() { return sz(root); }
};


/*
Implicit Treap - randomized balanced BST representing an array.
Positions are determined by subtree sizes (no explicit keys).
Uses:
- Insert / erase elements at arbitrary positions
- Reverse a subarray
- Add a value to all elements in a range (lazy propagation)
- Query range sums
- Cut, move and concatenate subarrays using split/merge
split(t, k, a, b): first k elements go to a, rest to b
merge(a, b): concatenates two sequences
All ranges are [l, r), 0-indexed.
All operations: expected O(log n), Memory: O(n)
*/

// Example:
// Treap tr;
// for (int x : {1, 2, 3, 4, 5}) tr.insert(tr.size(), x);
// tr.reverse(1, 4);        // [1, 4, 3, 2, 5]
// tr.range_add(1, 3, 10); // [1, 14, 13, 2, 5]
// tr.range_sum(0, 3);     // 28
// tr.insert(2, 7);        // [1, 14, 7, 13, 2, 5]
// tr.erase(0);            // [14, 7, 13, 2, 5]

