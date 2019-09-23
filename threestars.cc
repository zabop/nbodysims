#include<iostream>
#include<fstream>
#include<cfloat>
#include<cstdlib>
#include<cmath>
#include<vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream> // for ostringstream

using namespace std;

int N = 3;

struct xyvect{
 double x,y;
 xyvect(): x(), y() {}
 xyvect(double xx, double yy): x(xx), y(yy) {}
 double normsq() const {return x*x + y*y;}
 double norm() const {return sqrt(normsq());}
 double ang() const {return atan2(y,x);}
  xyvect& operator+=(const xyvect& r){
   x += r.x;
   y += r.y;
   return *this;}

 xyvect& operator-=(const xyvect& r){
   x -= r.x;
   y -= r.y;
   return *this;}

 xyvect& operator*=(double r){
   x *= r;
   y *= r;
   return *this;}

 xyvect& operator/=(double r){
   x /= r;
   y /= r;
   return *this;}
};

xyvect operator-(const xyvect& l, const xyvect& r){
   	return xyvect(l.x-r.x, l.y-r.y);
     	 }
     	 xyvect operator+(const xyvect& l, const xyvect& r){
   	return xyvect(l.x+r.x, l.y+r.y);
     	 }
     	 xyvect operator* (double d, const xyvect& v){
 xyvect a(v);
 a*=d;
 return a;}

xyvect operator* (const xyvect& v, double d){
 xyvect a(v);
 a*=d;
 return a;}

xyvect operator/ (const xyvect& v, double d){
 xyvect a(v);
 a/=d;
 return a;}

struct impact{};

const double G = 1; // gravitational constant
const double M = 1; // mass of sun

double t;
void t_inc(double dt){t += dt;}

class particle{

public:

 double m;
 xyvect x;
 xyvect v;
 xyvect a;

 double r() const {return x.norm();} //distance from sun
 particle(){}  // null constructor

 particle(double mass, xyvect x0, xyvect v0):
   m(mass), x(x0), v(v0), a(){}
 void x_inc(double dt){x += v * dt;} // step x in the direction of v.
 void v_inc(double dt){v += a * dt;} // step v in the direction of the acceleration.  
};

void euler_step(particle* p, int size, double dt)
{particle pnew[N];

for(int i=0; i<size; i++){
   xyvect acc(0,0); // find the acceleration
   for(int j=0; j<size; j++){if (i!=j){
       double distsq = (p[j].x.x-p[i].x.x)*(p[j].x.x-p[i].x.x)+(p[j].x.y-p[i].x.y)*(p[j].x.y-p[i].x.y);
       if (distsq < DBL_EPSILON) throw impact();
       acc+=G*(p[j].m)*(p[j].x-p[i].x)/pow(distsq, 1.5);
      }}          pnew[i]=particle(p[i].m, p[i].x+p[i].v*dt, p[i].v+acc*dt);
   }//its approximately good provided dt is small
   for(int i=0; i<N; i++){p[i]=pnew[i];}
}

void simulate(particle* p, void(step)(particle*, int, double),
double t, int n, int frames, ostream& of)
{ // number of steps made is n (total duration is t)
 // number of frames written out is frames
 const double dt = t / n;

ofstream ofss[N];
for (int i=0; i<N; i++){
string Result;          // string which will contain the result
ostringstream convert;   // stream used for the conversion
convert << i;      // insert the textual representation of 'Number' in the characters in the stream
Result = convert.str(); //
ofss[i].open(Result.c_str());
}
    ofstream fout1;
 fout1.open("particle120.dat");

for(int i=0;i<frames-1;++i){
// print current state
for(int i =0; i<N; i++) {ofss[i] <<p[i].x.x<<" "<<p[i].x.y<<" "<<p[i].v.x<<" "<<p[i].v.y<<" " << endl;}

  fout1 <<p[0].x.x<<" "<<p[0].x.y<<" "<<p[0].v.x<<" "<<p[0].v.y<<" " << endl;
   for(int j=0;j<n/frames;++j){
      step(p, N, dt); // between outputs, position needs to be calculated j/frames times
   	double xcom=0; double ycom=0;
   	for(int k=0; k<N; k++){xcom+=p[k].x.x; ycom+=p[k].x.y;}
   	//cout << "xcom: " << xcom << " ycom: " << ycom <<endl;
   }
 }
}

int main()
{
 double time = 1000; // time to simulate
 int n = 5000000;      // total number of steps to make
 int frames = 5000; // number of frames to record
 double m = 1;

 particle p[N];

 const xyvect v0((pow(12,-0.25)),0.0);
 const xyvect x0(0.0,2.0);
 p[0]=particle(1,x0,v0);

 const xyvect v1(-0.5*pow(12,-0.25),-pow(12,-0.25)*pow(3,0.5)*0.5);
 const xyvect x1(pow(3,0.5),-1);
 p[1]=particle(1,x1,v1);

 const xyvect v2(-0.5*pow(12,-0.25),pow(12,-0.25)*pow(3,0.5)*0.5);
 const xyvect x2(-pow(3,0.5),-1);
 p[2]=particle(1,x2,v2);

   try{
   simulate(p,euler_step,time,n,frames,cout);
 }catch(impact&){
   cout << "Collision occurredn";
 }
 return 0;
}
