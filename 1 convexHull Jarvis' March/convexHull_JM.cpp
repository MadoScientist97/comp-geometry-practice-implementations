#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<random>
#include<cstdlib>
#include<algorithm>
#include<iterator>
#include<unistd.h>
#include<sys/stat.h>
#include "gnu.h"

using namespace std;
//======================GNUPLOT Functions==================//
gnuplot p;
void gnuInit(string fname){
    string initline= "set terminal png size 800,600\n";
    p(initline);
    initline= "unset key\n";
    p(initline);
    initline= "set xrange [-20:120]\n";
    p(initline);
    initline= "set yrange [-20:120]\n";
    p(initline);
    initline = "set output \"pics/" + fname + ".png\"\n";
    p(initline);
    initline = "plot \"scatter.txt\" lt 5 lc 9\n";
    p(initline);
}

void gnuStartpoint(string fname){
    string initline= "set terminal png size 800,600\n";
    p(initline);
    initline= "unset k\n";
    p(initline);
    initline= "set xrange [-20:120]\n";
    p(initline);
    initline= "set yrange [-20:120]\n";
    p(initline);
    initline = "set output \"pics/" + fname + ".png\"\n";
    p(initline);
    initline = "plot \"scatter.txt\" lt 5 lc 9, \"startpt.txt\" lw 5 lt 2 lc 10\n";
    p(initline);
}

void gnuUpdateNewpoint(string fname, int check){
    string initline= "set terminal png size 800,600\n";
    p(initline);
    initline= "unset k\n";
    p(initline);
    initline= "set xrange [-20:120]\n";
    p(initline);
    initline= "set yrange [-20:120]\n";
    p(initline);
    initline = "set output \"pics/" + fname + ".png\"\n";
    p(initline);
    if (check<1)
    initline = "plot \"currentLine.txt\" lt 7 lc 1 w lp,\"currentpoint.txt\" lw 5 lt 2 lc 10,\"scatter.txt\" lt 5 lc 9\n";
    else
    initline = "plot \"currentLine.txt\" lt 7 lc 1 w lp, \"currentpoint.txt\" lw 5 lt 2 lc 10, \"convexHull.txt\" lt 2 lc 4 w lp,\"scatter.txt\" lt 5 lc 9\n";
    p(initline);
}

void gnuFinalHull(string fname){
    string initline= "set terminal png size 800,600\n";
    p(initline);
    initline= "unset k\n";
    p(initline);
    initline= "set xrange [-20:120]\n";
    p(initline);
    initline= "set yrange [-20:120]\n";
    p(initline);
    initline = "set output \"pics/" + fname + ".png\"\n";
    p(initline);
    initline = "plot \"convexHull.txt\" lw 4 lt 2 lc 4 w lp, \"scatter.txt\" lt 5 lc 9\n";
    p(initline);
    initline = "set output \"convexHull.png\"\n";
    p(initline);
    initline = "plot \"convexHull.txt\" lw 4 lt 2 lc 4 w lp, \"scatter.txt\" lt 5 lc 9\n";
    p(initline);
}

//===============end of GNUPLOT Functions===================//


//==============Point and line classes and helper=============/
struct point{
    float x;
    float y;
    bool operator==(const point p)
    {
        //Perform comparision
        point thisp;
        if(thisp.x==p.x && thisp.y==p.y)
        return true;
        else
        return false;
    }
    bool operator!=(const point p)
    {
        //Perform comparision
        point thisp;
        if(thisp.x==p.x && thisp.y==p.y)
        return false;
        else
        return true;
    }
};

class line{
    point pts[2];
    public:
    line(point x1){
        pts[0].x = 0.0;
        pts[0].y = 0.0;
        pts[1] = x1;
    }
    line(point x1,point x2){
        pts[0] = x1;
        pts[1] = x2;
    }
    point* retpoints(){
        return pts;
    }
    point retpoint(char coord){
        if (coord=='x' || coord=='X')
        return pts[0];
        else
        return pts[1];
    }
    void updateline(point newpoint){
        pts[1] = newpoint;
    }
    int orientationCheck(point p){
        float det = (pts[0].x*(pts[1].y - p.y)) + (-pts[0].y*(pts[1].x-p.x)) + ((pts[1].x*p.y) - (p.x*pts[1].y));
        return det;
    }
    void shift(){
        pts[0] = pts[1];
    }
    void printline(){
        cout<<"lineSegment: ";
        cout<<"\nPoint 1:("<<pts[0].x<<","<<pts[0].y<<")";
        cout<<"\nPoint 2:("<<pts[1].x<<","<<pts[1].y<<")\n";
    }
};

//============end of classes and helpers==============//

//===========start of file IO for generation and reading=======//

vector<point> getpoints()
{;
    vector<point> points;
    ifstream myfile;
    int noPoints = 0;
    myfile.open ("points.txt");
    myfile >> noPoints;
    for (int i=0;i<noPoints;i++){
        point p;
        myfile>>p.x>>p.y;
        points.push_back(p);
    }
    myfile.close();
    return points;
}

void generatePoints (int N){
  ofstream myfile,forgnuplot;
  myfile.open ("points.txt");
  forgnuplot.open("scatter.txt");
  myfile << N<<endl;
  default_random_engine generator;
  uniform_real_distribution<double> distribution(0.0,1.0);

  for (int i=0;i<N;i++){
    double randx = distribution(generator)*100;
    double randy = distribution(generator)*100;
    myfile<<randx<<" "<<randy<<endl;
    forgnuplot<<randx<<" "<<randy<<endl;
  }
  forgnuplot.close();
  myfile.close();
}

void writeConvexHull(vector<line> cvexHull){
    ofstream lineop;
    lineop.open("convexHull.txt");
    for (auto i=cvexHull.begin();i<cvexHull.end();i++){
        point temp;
        temp = (*i).retpoint('x');
        lineop << temp.x <<" "<< temp.y<<endl;
        temp = (*i).retpoint('y');
        lineop << temp.x <<" "<< temp.y<<endl;
    }
}

//=====================end of FILE IO for generation and outputs===========//

//=====================Main convexHull algo==========================//

vector<line> maindispLoop(vector<point> points){
    int gnucount=2;
    ofstream startpoint,checkline,checknewpoint,hullLine;
    point tempp;
    for (auto i=points.begin()+1;i<points.end();i++){
        if ((*i).y<points[0].y){
            tempp = points[0];
            points[0] = (*i);
            (*i) = tempp;
        }
    }
    startpoint.open("startpt.txt");
    startpoint<<points[0].x<<" "<<points[0].y<<endl;
    startpoint.close();

    gnuStartpoint(to_string(gnucount));
    sleep(1);
    gnucount++;

    vector<line> convexHull;
    line nextline = line(points[0],points[1]);
    bool notdone = true;
    while (notdone){
        for (int i=0;i<points.size();i++){

            checkline.open("currentLine.txt");
            checkline<<nextline.retpoint('x').x<<" "<<nextline.retpoint('x').y<<endl;
            checkline<<nextline.retpoint('y').x<<" "<<nextline.retpoint('y').y<<endl;
            checkline.close();
            checknewpoint.open("currentpoint.txt");
            checknewpoint<<points[i].x<<" "<<points[i].y<<endl;
            checknewpoint.close();
            gnuUpdateNewpoint(to_string(gnucount),convexHull.size());
            sleep(1);
            gnucount++;
            if(nextline.orientationCheck(points[i])>0 && nextline.retpoint('x')!=points[i] && nextline.retpoint('y')!=points[i]){
                nextline.updateline(points[i]);
            }
        }
        convexHull.push_back(nextline);
        //gnuplot for the next convex hull line
        writeConvexHull(convexHull);

        if (nextline.retpoint('y').x == convexHull[0].retpoint('x').x && nextline.retpoint('y').y == convexHull[0].retpoint('x').y){
            notdone=false;
            break;
        }
        nextline.shift();
        for (auto i=points.begin();i<points.end();i++){
            point nextpoint = (*i);
            if (nextpoint != nextline.retpoint('x')){
                nextline.updateline(nextpoint);
                break;
            }
        }
    }
    writeConvexHull(convexHull);
    gnuFinalHull(to_string(gnucount));
    return convexHull;
}

//===========================end of convex hull algo====================//

//======================driver code===================//

int main(int argc, char *argv[])
{
    if (mkdir("pics", 0777) == -1)
        cerr << "Error, couldn't make directory!"<< endl;
    vector<point> points;
    vector<line> convexHull;
    cout<<"Generating "<<atoi(argv[1])<<" points!"<<endl;
    generatePoints(atoi(argv[1]));
    sleep(1);
    string fname = "1";
    gnuInit(fname);
    cout<<"Engine started."<<endl;
    sleep(1);
    points = getpoints();
    convexHull = maindispLoop(points);
    system("./gifscript.sh \"./pics/\"");
    cout<<"Done, check for a convexHull.gif in your working directory!!"<<endl;
    return 0;
}

//====================end of drivercode=====================//
