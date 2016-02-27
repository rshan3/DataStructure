#include <bits/stdc++.h>
#define EPS 1e-10
#define MAXN 200005
using namespace std;
int n,sz;
double P,Q;
double ans;

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
	Point operator + (Point & other){
		return Point(x+other.x,y+other.y);
	}
	Point operator - (Point & other){
		return Point(x-other.x,y-other.y);
	}
	bool operator < (const Point & other) const{
		return x<other.x || (x==other.x && y<other.y);
	}
}ps[MAXN],hull[2*MAXN];

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

bool intersect1(Point A,Point B,double k){
	return (A.y>A.x*(k+EPS) && B.y>B.x*(k+EPS)) || (A.y<A.x*(k-EPS) && B.y<B.x*(k-EPS));   
}

double intersect2(Point A,Point B,double k){
	double b = (B.y-A.y);
	double a = (B.x-A.x);
	//cout << "a" << a << "b" << b << endl;
	return (a*A.y-b*A.x)/(a*k-b); 
}

void convexHull() {
	if(n<3)
		return;

	sort(ps,ps+n);
	sz=0;
	for(int i=0;i<n;i++){
		while(sz>1 && ccw(hull[sz-2],hull[sz-1],ps[i])<EPS) {
			sz--;
		}
		hull[sz++] = ps[i];
	}

	int t=sz;
	for(int i=n-2;i>=0;i--){
		while(sz>t && ccw(hull[sz-2],hull[sz-1],ps[i])<EPS){
			sz--;
		}
		hull[sz++] = ps[i];
	}
	sz--;
	return;
}

double solve(){
	if(n==4) {
		return max(P/ps[1].x,Q/ps[1].y);
	}
	convexHull();
/*	for(int i=0;i<sz;i++){
		cout << hull[i].x << ' ' << hull[i].y << endl;
	}
	cout << "---" << endl;
	*/
	ans = 2000005;
	for(int i=1;i<sz-1;i++){
		Point sega(hull[i].x,hull[i].y);
		Point segb(hull[i+1].x,hull[i+1].y);
		if(intersect1(sega,segb,Q/P)) continue;
		
		ans = min(ans,P/intersect2(sega,segb,Q/P));
	}
	return ans;
}

int main(){
	int xx,yy;
	cin >> n >> P >> Q;
	double maxx = 0;
	double maxy = 0;
	for(int i=1;i<=n;i++){
		cin >> ps[i].x >> ps[i].y;
		maxx = max(ps[i].x,maxx);
		maxy = max(ps[i].y,maxy);
	}

	ps[0].x = 0;
	ps[0].y = maxy;
	ps[n+1].x = maxx;
	ps[n+1].y = 0;
	ps[n+2].x = 0;
	ps[n+2].y = 0;

	n+=3;
	printf("%.7lf",solve());
	return 0;
}