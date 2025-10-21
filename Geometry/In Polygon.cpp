#define all(x) (x).begin(),(x).end()
using pt = pair<int, int>;
#define x first
#define y second


pt operator-(pt a, pt b) { return {a.x - b.x, a.y - b.y}; }
int operator*(pt p, pt q) {return p.x * q.y - p.y * q.x; }
int operator%(pt a, pt b){return a.x*b.x +a.y+b.y;}

bool in_polygon(vector<pt> &a, pt p){
    int n=a.size();
    auto inT = [&] (pt a, pt b, pt c, pt p) {
      a = a-p; b = b-p; c = c-p;
      int ab = a * b, bc = b * c, ca = c * a;
      return abs(ab)+abs(bc)+abs(ca) == abs(ab+bc+ca);
    };
    auto inP = [&] (pt p) {
    //a must be in counterclockwise order!
    //assuming no three points of a are collinear
      if (n == 1) return p == a[0];
      if (n == 2) return (p-a[0]) * (a[1]-a[0]) == 0 && (p-a[0]) % (p-a[1]) <= 0;
      int l = 1, r = n - 1;
      while (l < r - 1) {
        int m = (l + r) / 2;
        if ((a[m] - a[0]) < (p - a[0])) {
          l = m;
        } else {
          r = m;
        }
      }
      return inT(a[l], a[0], a[r], p);
    };
    return inP(p);
}//нестрого внутри?
//a - обязательно против часовой стрелки!!!!
