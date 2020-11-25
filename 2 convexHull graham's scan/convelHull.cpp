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
    initline = "plot \"scatter.txt\" lt 5 lc 9, \"currentpt.txt\" lw 5 lt 2 lc 10\n";
    p(initline);
}

void gnuUpdateCycle(string fname){
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
    initline = "plot \"scatter.txt\" lt 5 lc 9, \"currentpt.txt\" lw 5 lt 2 lc 10, \"upperhull.txt\" lt 2 lc 4 w lp,\"lowerhull.txt\" lt 2 lc 3 w lp, \"currentULine.txt\" lt 7 lc 1 w lp,\"currentLLine.txt\" lt 7 lc 1 w lp\n";
    p(initline);
}

void gnuUpdateUpperpoints(string fname){
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
    initline = "plot \"upperhull.txt\" lt 2 lc 4 w lp,\"currentpt.txt\" lw 5 lt 2 lc 10, \"currentULine.txt\" lt 7 lc 1 w lp , \"lowerhull.txt\" lt 2 lc 3 w lp,\"scatter.txt\" lt 5 lc 9\n";
    p(initline);
}

void gnuUpdateLowerpoints(string fname){
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
    initline = "plot \"currentLLine.txt\" lt 7 lc 1 w lp,\"currentpt.txt\" lw 5 lt 2 lc 10,\"lowerhull.txt\" lt 2 lc 3 w lp,\"upperhull.txt\" lt 2 lc 4 w lp, \"scatter.txt\" lt 5 lc 9\n";
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
    initline = "set output \"convexHull.png\"\n";
    p(initline);
    initline = "plot \"upperhull.txt\" lw 4 lt 2 lc 4 w lp, \"lowerhull.txt\" lw 4 lt 2 lc 4 w lp, \"scatter.txt\" lt 5 lc 9\n";
    p(initline);
    initline = "set output \"pics/" + fname + ".png\"\n";
    p(initline);
    initline = "plot \"upperhull.txt\" lw 4 lt 2 lc 4 w lp, \"lowerhull.txt\" lw 4 lt 2 lc 4 w lp, \"scatter.txt\" lt 5 lc 9\n";
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
    bool operator>(const point p)
    {
        //Perform comparision
        point thisp;
        if(thisp.x>p.x)
        return true;
        else
        return false;
    }
    bool operator<(const point p)
    {
        //Perform comparision
        point thisp;
        if(thisp.x<p.x)
        return true;
        else
        return false;
    }
    bool operator<=(const point p)
    {
        //Perform comparision
        point thisp;
        if(thisp.x<=p.x)
        return true;
        else
        return false;
    }
    bool operator>=(const point p)
    {
        //Perform comparision
        point thisp;
        if(thisp.x>=p.x)
        return true;
        else
        return false;
    }
    
};

bool compP(point p1,point p2){
    if (p1.x<p2.x)
    return true;
    else
    return false;
}

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
    void updateline(point p1,point p2){
        pts[0] = p1;
        pts[1] = p2;
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
    lineop.close();
}

//=====================end of FILE IO for generation and outputs===========//

//=====================Main convexHull algo==========================//

void maindispLoop(vector<point> points){
    int gnucount=2;
    vector<point> upperS,lowerS;
    ofstream startpoint,checkUline,checkLline,uhulline,lhullLine,currentPoints;
    sort(points.begin(), points.end(),compP);

    upperS.push_back(points[0]);
    upperS.push_back(points[1]);
    lowerS.push_back(points[0]);
    lowerS.push_back(points[1]);

    startpoint.open("currentpt.txt");
    startpoint<<points[0].x<<" "<<points[0].y<<endl;
    startpoint.close();
    gnuStartpoint(to_string(gnucount));
    sleep(1);
    gnucount++;

    line nextUline = line(*(upperS.rbegin()+1),*(upperS.rbegin()));
    line nextLline = line(*(lowerS.rbegin()+1),*(lowerS.rbegin()));

    for (auto i=points.begin()+2;i<points.end();i++){
        startpoint.open("currentpt.txt");
        startpoint<<(*i).x<<" "<<(*i).y<<endl;
        startpoint.close();

        checkUline.open("currentULine.txt");
        checkLline.open("currentLLine.txt");
        checkUline<<nextUline.retpoint('x').x<<" "<<nextUline.retpoint('x').y<<endl;
        checkUline<<nextUline.retpoint('y').x<<" "<<nextUline.retpoint('y').y<<endl;
        checkLline<<nextLline.retpoint('x').x<<" "<<nextLline.retpoint('x').y<<endl;
        checkLline<<nextLline.retpoint('y').x<<" "<<nextLline.retpoint('y').y<<endl;
        checkUline.close();
        checkLline.close();
        uhulline.open("upperhull.txt");
        for (auto j=upperS.begin();j<upperS.end();j++){
            uhulline<<(*j).x<<" "<<(*j).y<<endl;
        }
        uhulline.close();

        lhullLine.open("lowerhull.txt");
        for (auto j=lowerS.begin();j<lowerS.end();j++){
            lhullLine<<(*j).x<<" "<<(*j).y<<endl;
        }
        lhullLine.close();
        gnuUpdateCycle(to_string(gnucount));
        gnucount++;
        sleep(1);
        while(nextUline.orientationCheck(*i) > 0){
            upperS.pop_back();
            if (upperS.size()>1)
                nextUline.updateline(*(upperS.rbegin()+1),*(upperS.rbegin()));
            else
                nextUline.updateline(*(upperS.rbegin()),*(upperS.rbegin()));
            uhulline.open("upperhull.txt");
            for (auto j=upperS.begin();j<upperS.end();j++){
                uhulline<<(*j).x<<" "<<(*j).y<<endl;
            }
            uhulline.close();
            checkUline.open("currentULine.txt");
            checkUline<<nextUline.retpoint('x').x<<" "<<nextUline.retpoint('x').y<<endl;
            checkUline<<nextUline.retpoint('y').x<<" "<<nextUline.retpoint('y').y<<endl;
            checkUline.close();
            gnuUpdateUpperpoints(to_string(gnucount));
            sleep(1);
            gnucount++;
        }
        upperS.push_back(*i);
        nextUline.updateline(*(upperS.rbegin()+1),*(upperS.rbegin()));
        while(nextLline.orientationCheck(*i) < 0){
            lowerS.pop_back();
            if (lowerS.size()>1)
                nextLline.updateline(*(lowerS.rbegin()+1),*(lowerS.rbegin()));
            else
                nextLline.updateline(*(lowerS.rbegin()),*(lowerS.rbegin()));
                
            lhullLine.open("lowerhull.txt");
            for (auto j=lowerS.begin();j<lowerS.end();j++){
                lhullLine<<(*j).x<<" "<<(*j).y<<endl;
            }
            lhullLine.close();
            
            checkLline.open("currentLLine.txt");        
            checkLline<<nextLline.retpoint('x').x<<" "<<nextLline.retpoint('x').y<<endl;
            checkLline<<nextLline.retpoint('y').x<<" "<<nextLline.retpoint('y').y<<endl;
            checkLline.close();
            gnuUpdateLowerpoints(to_string(gnucount));
            sleep(1);
            gnucount++;
        }
        lowerS.push_back(*i);
        nextLline.updateline(*(lowerS.rbegin()+1),*(lowerS.rbegin()));
    }
    uhulline.open("upperhull.txt");
    for (auto j=upperS.begin();j<upperS.end();j++){
        uhulline<<(*j).x<<" "<<(*j).y<<endl;
    }
    uhulline.close();

    lhullLine.open("lowerhull.txt");
    for (auto j=lowerS.begin();j<lowerS.end();j++){
        lhullLine<<(*j).x<<" "<<(*j).y<<endl;
    }
    lhullLine.close();
    gnuUpdateCycle(to_string(gnucount));
    gnucount++;
    sleep(1);
    gnuFinalHull(to_string(gnucount));
}


//===========================end of convex hull algo====================//

//======================driver code===================//

int main(int argc, char *argv[])
{
    if (mkdir("pics", 0777) == -1) 
        cerr << "Error Couldn't Make Directory! " << endl;  
    vector<point> points;
    vector<line> convexHull;
    cout<<"Generating "<<atoi(argv[1])<<" points!"<<endl;
    generatePoints(atoi(argv[1]));
    string fname = "1";
    gnuInit(fname);
    cout<<"Engine started."<<endl;
    points = getpoints();
    maindispLoop(points);
    system("./gifscript.sh \"./pics/\"");
    cout<<"Done, check for a convexHull.gif and convexHull.png in your working directory!!"<<endl;
    return 0;
}

//====================end of drivercode=====================//