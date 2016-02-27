#include <iostream>
#include <algorithm>
#include <cstdio>
#define MAXN 50005
#define EPS 1e-10
using namespace std;
int n,sz;
struct Point {
	int x,y;
	Point(int x=0,int y=0):x(x),y(y) {}
	Point operator + (Point & other){
		return Point(x+other.x,y+other.y);
	}
	Point operator - (Point & other){
		return Point(x-other.x,y-other.y);
	}
	bool operator < (const Point & other) const{
		return x<other.x || (x==other.x && y<other.y);
	}
}hull[2*MAXN],ps[MAXN];

int Cross(Point A,Point B){
	return A.x*B.y-A.y*B.x;
}

int Dot(Point A,Point B){
	return A.x*B.x+A.y*B.y;
}

int ccw(Point & A,Point & B,Point & C){
	return Cross(B-A,C-A);
}

int len(Point & A,Point & B){
	return Dot(B-A,B-A);
}

void convex_hull(){
	sz=0;
	if(n==1) {
		hull[sz++] = ps[0];
		return;
	}
	if(n==2) {
		hull[sz++] = ps[0];
		hull[sz++] = ps[1];
		return;
	}
	sort(ps,ps+n);
	for(int i=0;i<n;i++){
		while(sz>1 && ccw(hull[sz-2],hull[sz-1],ps[i])<=0){
			sz--;
			//cout <<  ccw(hull[sz-2],hull[sz-1],ps[i]) << endl;
		}
		hull[sz++]=ps[i];
	}

	int t=sz;
	for(int i=n-2;i>=0;i--){
		while(sz>t && ccw(hull[sz-2],hull[sz-1],ps[i])<=0){
			sz--;
		}
		hull[sz++]=ps[i];
	}
	//cout << "sf" << endl;

	sz--;
}

void check(){
	int maxi=0;
	for(int i=0;i<sz;i++){
		for(int j=i+1;j<sz;j++){
			maxi = max(len(hull[i],hull[j]),maxi);
		}
	}
	printf("%d\n",maxi);
}

int main(){
	int x,y;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d%d",&x,&y);
		ps[i].x=x;
		ps[i].y=y; 
		//cout << x << y << endl;
	}

	convex_hull();
//	cout << "sf" << endl;
	check();
	for(int i=0;i<sz;i++)
		cout << hull[i].x << ' ' << hull[i].y << endl;
	cout << sz << endl;
	return 0;
}