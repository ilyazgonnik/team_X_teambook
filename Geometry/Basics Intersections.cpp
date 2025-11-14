struct pt{
  int x;
  int y;
};

int D_area(pt a, pt b, pt c){
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
} 

bool on_line(pt a, pt b, pt c){
    if(D_area(a, b, c)==0){
        return true;
    }
    else{
        return false;
    }
}

bool clockwise (pt a, pt b, pt c){
	return D_area (a, b, c) < 0;
}

bool intersect_1 (int a, int b, int c, int d) {
	if (a > b)  swap (a, b);
	if (c > d)  swap (c, d);
	return max(a,c) <= min(b,d);
}

bool intersect_seg (pt a, pt b, pt c, pt d) {
	return intersect_1 (a.x, b.x, c.x, d.x) && intersect_1 (a.y, b.y, c.y, d.y) && (D_area(a,b,c) * D_area(a,b,d) <= 0) && (D_area(c,d,a) * D_area(c,d,b) <= 0);
}//AB intersect with CD

struct line {
	long double a, b, c;
}; 

const long double EPS = 1e-9;

long double det (long double a, long double b, long double c, long double d) {
	return a * d - b * c;
}

bool intersect_line (line m, line n, pt & res) {
	double zn = det (m.a, m.b, n.a, n.b);
	if (abs (zn) < EPS)
		return false;
	res.x = - det (m.c, m.b, n.c, n.b) / zn;
	res.y = - det (m.a, m.c, n.a, n.c) / zn;
	return true;
}//if intersecting, then results is in res! genious! 
 
bool parallel (line m, line n) {
	return abs (det (m.a, m.b, n.a, n.b)) < EPS;
}//equals lines are parallel
 
bool equivalent (line m, line n) {
	return abs (det (m.a, m.b, n.a, n.b)) < EPS
		&& abs (det (m.a, m.c, n.a, n.c)) < EPS
		&& abs (det (m.b, m.c, n.b, n.c)) < EPS;
}

line line_from_points(pt a, pt b){
    line ans;
    ans.a = a.y - b.y;
    ans.b = b.x - a.x;
    ans.c = - ans.a*a.x - ans.b*a.y;
    return ans;
}
