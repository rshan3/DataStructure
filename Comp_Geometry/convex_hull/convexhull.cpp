#include <bits/stdc++.h>
#define EPS 1e-10
#define MAXN 10000
using namespace std;
int n;
struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
	Point operator + (Point & other){
		return Point(x+other.x,y+other.y);
	}
	Point operator - (Point & other){
		return Point(x-other.x,y-other.y);
	}
	Point operator * (Point & A, double p) {
		return Point(p*A.x, p*A.y);
	}
	Point operator / (Point & A, double p) {
		return Point(A.x/p, A.y/p);
	}
	bool operator < (const Point & other) const{
		return x<other.x || (x==other.x && y<other.y);
	}
	bool operator == (const Point & a,const Point & b){
		return fabs(a.x-b.x)<EPS && fabs(a.y-b.y)<EPS;
	}
}ps[MAXN],hull[MAXN];

double Dot(Point A, Point B){
	return A.x*B.x + A.y*B.y;
}
double Cross(Point A, Point B){
	return A.x*B.y - A.y*B.x;
}
// Whether if A->B->C is counter clock wised; positive,true;negative no;zero co-line.
double ccw(Point A,Point B,Point C){
	return Cross(B-A,C-A);
}

int convexHull() {
	if(n<3)
		return 0;

	sort(ps,ps+n);
	sz=0;
	for(int i=0;i<n;i++){
		while(sz>1 && ccw(hull[sz-2],hull[sz-1],ps[i])<EPS) 
			sz--;
		hull[sz++] = ps[i];
	}

	int t=sz;
	for(int i=n-2;i>=0;i--){
		while(sz>t && ccw(hull[sz-2],hull[sz-1],ps[i])<EPS)
			sz--;
		hull[sz++] = ps[i];
	}

	sz--;
	return sz;
}

int main(){
	n = 100;
}