#include <bits/stdc++.h>
using namespace std;
#define int long long
template <class T, class V, class Container> basic_ostream <T, V> & operator << (basic_ostream <T, V> & os, Container const& x) { os << "[ "; for (auto& y : x) os << y << " "; return os << "]"; }
template <class T, class V> ostream & operator << (ostream & os, pair<T, V> const& p) { return os << "{" << p.first << "," << p.second << "}"; }
void deb_out() { cerr << endl; }
template <typename Head, typename... Tail> void deb_out(Head H, Tail... T) { cerr << " " << H; deb_out(T...); }
#define deb(...) cerr << "(" << #__VA_ARGS__ << "):", deb_out(__VA_ARGS__)
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast", "O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")
#define all(x) x.begin(), x.end()


int32_t main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
    return 0;
}	
