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
#include<assert.h>
#include "gnu.h"

using namespace std;


//======================GNUPLOT Functions==================//
gnuplot p;
int gnucount = 1;
int pcount = 0;
void gnuInit(string fname){
    string initline= "set terminal png size 800,800\n";
    p(initline);
    initline= "unset key\n";
    p(initline);
    initline= "set xrange [-50:150]\n";
    p(initline);
    initline= "set yrange [-50:150]\n";
    p(initline);
    initline = "set output \"pics/" + fname + ".png\"\n";
    p(initline);
    initline = "plot \"scatter.txt\" lt 5 lc 9\n";
    p(initline);
}

void gnuStartpoint(string fname){
    string initline= "set terminal png size 800,800\n";
    p(initline);
    initline= "unset k\n";
    p(initline);
    initline= "set xrange [-50:150]\n";
    p(initline);
    initline= "set yrange [-50:150]\n";
    p(initline);
    initline = "set output \"pics/" + fname + ".png\"\n";
    p(initline);
    initline = "plot \"scatter.txt\" lt 5 lc 9, \"startpts.txt\" lw 5 lt 2 lc 10\n";
    p(initline);
}

void checkinside(string fname){
    string initline= "set terminal png size 800,800\n";
    p(initline);
    initline= "unset k\n";
    p(initline);
    initline= "set xrange [-50:150]\n";
    p(initline);
    initline= "set yrange [-50:150]\n";
    p(initline);
    initline = "set output \"pics/" + fname + ".png\"\n";
    p(initline);
    initline = "plot \"CurrentPoint.txt\" lw 5 lt 2 lc 10, \"CurrentCirclePoints.txt\" lt 2 lc 2,\"scatter.txt\" lt 5 lc 9\n";
    p(initline);
}

void gnuTrivialCircle(string fname){
    string initline= "set terminal png size 800,800\n";
    p(initline);
    initline= "unset k\n";
    p(initline);
    initline= "set xrange [-50:150]\n";
    p(initline);
    initline= "set yrange [-50:150]\n";
    p(initline);
    initline = "set output \"pics/" + fname + ".png\"\n";
    p(initline);
    initline = "plot \"CurrentCirclePoints.txt\" lt 2 lc 4,\"scatter.txt\" lt 5 lc 9\n";
    p(initline);
}

void gnuRecCircle(string fname){
    string initline= "set terminal png size 800,800\n";
    p(initline);
    initline= "unset k\n";
    p(initline);
    initline= "set xrange [-50:150]\n";
    p(initline);
    initline= "set yrange [-50:150]\n";
    p(initline);
    initline = "set output \"pics/" + fname + ".png\"\n";
    p(initline);
    initline = "plot \"RecCircle.txt\" lw 1 lt 3 lc 5, \"CurrentCirclePoints.txt\" lt 2 lc 4, \"scatter.txt\" lt 5 lc 9\n";
    p(initline);
}


void gnuFinalCircle(string fname){
    string initline= "set terminal png size 800,800\n";
    p(initline);
    initline= "unset k\n";
    p(initline);
    initline= "set xrange [-50:150]\n";
    p(initline);
    initline= "set yrange [-50:150]\n";
    p(initline);
    initline = "set output \"pics/" + fname + ".png\"\n";
    p(initline);
    initline = "plot \"FinalCircle.txt\" lw 1 lt 3 lc 6, \"scatter.txt\" lt 5 lc 9\n";
    p(initline);
    initline = "set output \"FinalCircle.png\"\n";
    p(initline);
    initline = "plot \"FinalCircle.txt\" lw 1 lt 3 lc 6, \"CurrentCirclePoints.txt\" lt 2 lc 4, \"scatter.txt\" lt 5 lc 9\n";
    p(initline);
}

//===============end of GNUPLOT Functions===================//


//==============Point and line classes and helper=============//
struct point{
    float x;
    float y;
    point(){
        x=0.0;
        y=0.0;
    }
    point(float ix, float iy)
    {
        x = ix;
        y = iy;
    }
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

float euclidDist(point x1,point x2){
    return sqrt(pow((x1.y-x2.y),2) + pow((x1.x-x2.x),2));
}

class circle{
    point pts[3],center;
    float radius,g,f,c;
    public:
    circle(){
        center.x = 0.0;
        center.y = 0.0;
        radius = 0.0;
    }
    circle(float rad){
        center.x = 0.0;
        center.y = 0.0;
        radius = rad;
        convToPts();
    }
    circle(float rad, point c){
        center = c;
        radius = rad;
        convToPts();
    }
    circle(point x1,point x2, point x3){
        pts[0] = x1;
        pts[1] = x2;
        pts[2] = x3;
        calcCoeff();
    }
    circle(point x1, point x2){
        radius = euclidDist(x1,x2)/2.0;
        center.x = (x1.x+x2.x)/2.0;
        center.y = (x1.y+x2.y)/2.0;
        convToPts();
    }
    void setpoints(point x1,point x2, point x3){
        pts[0] = x1;
        pts[1] = x2;
        pts[2] = x3;
    }
    void convToPts(){
        g = -1*center.x;
        f = -1*center.y;
        c = pow(center.y,2) + pow(center.x,2) - pow(radius,2);
    }
    void calcCoeff() {
        { 
            float x12 = pts[0].x - pts[0].x; 
            float x13 = pts[0].x - pts[2].x; 
        
            float y12 = pts[0].y - pts[1].y; 
            float y13 = pts[0].y - pts[2].y; 
        
            float y31 = pts[2].y - pts[0].y; 
            float y21 = pts[1].y - pts[0].y; 
        
            float x31 = pts[2].x - pts[0].x; 
            float x21 = pts[1].x - pts[0].x; 
        
            // x1^2 - x3^2 
            float sx13 = pow(pts[0].x, 2) - pow(pts[2].x, 2); 
        
            // y1^2 - y3^2 
            float sy13 = pow(pts[0].y, 2) - pow(pts[2].y, 2); 
        
            float sx21 = pow(pts[1].x, 2) - pow(pts[0].x, 2); 
            float sy21 = pow(pts[1].y, 2) - pow(pts[0].y, 2); 
        
            f = ((sx13) * (x12) 
                    + (sy13) * (x12) 
                    + (sx21) * (x13) 
                    + (sy21) * (x13)) 
                    / (2 * ((y31) * (x12) - (y21) * (x13))); 
            g = ((sx13) * (y12) 
                    + (sy13) * (y12) 
                    + (sx21) * (y13) 
                    + (sy21) * (y13)) 
                    / (2 * ((x31) * (y12) - (x21) * (y13))); 
        
            c = -pow(pts[0].x, 2) - pow(pts[0].y, 2) - 2 * g * pts[0].x - 2 * f * pts[0].y; 
            // eqn of circle be x^2 + y^2 + 2*g*x + 2*f*y + c = 0 
            // where centre is (h = -g, k = -f) and radius r 
            // as r^2 = h^2 + k^2 - c 
            float h = -g; 
            float k = -f; 
            float sqr_of_r = h * h + k * k - c; 
            center.x = -g;
            center.y = -f;
            // r is the radius 
            radius = sqrt(sqr_of_r); 
        }    
    }

    float p_getY1 (float x){
        float y = 0;
        float discr = sqrt((4*f*f - 4*(x*x + 2*g*x +c)));
        y = (-2*f + discr)/2;
        return y;
    }

    float p_getY2 (float x){
        float y = 0;
        float discr = sqrt((4*f*f - 4*(x*x + 2*g*x +c)));
        y = (-2*f - discr)/2;
        return y;
    }

    bool isInside(point p){
        if (euclidDist(p,center) > radius)
            return false;
        else
            return true;
    }

    point* retpoints(){
        return pts;
    }
    point getCenter(){
        return center;
    }
    float getRadius(){
        return radius;
    }
    void mergeCircle(circle c2){
        point newCen = c2.getCenter();
        point oldCen = center;
        float newCrad = c2.getRadius();
        center.x = (radius*center.x + newCrad*newCen.x)/(radius+newCrad);
        center.y = (radius*center.y + newCrad*newCen.y)/(radius+newCrad);
        radius = radius + sqrt( pow((oldCen.y-center.y),2) + pow((oldCen.x-center.x),2) );
        convToPts();
    }

    void printCircle(){
        cout<<"Circle is: Center {"<<center.x<<","<<center.y<<"}\nRadius: "<<radius<<endl;
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

void writeFinalGnuCircle(vector<point> c){
    ofstream finalCircle;
    finalCircle.open("FinalCircle.txt");
    for (auto i=c.begin();i<c.end();i++){
        point temp;
        temp = (*i);
        finalCircle << temp.x <<" "<< temp.y<<endl;    
    }
    finalCircle.close();
}

//=====================end of FILE IO for generation and outputs===========//

//=====================Main Minimum Enclosing Circle algo==========================//


bool isInside(circle c, point p){
    return euclidDist(c.getCenter(), p) <= c.getRadius(); 
}


bool is_valid_circle(circle c,vector<point> P){
    for (point& p : P) 
    if (!isInside(c, p)) 
            return false; 
    return true; 
}

circle trivialCase(vector<point> &p){
    ofstream currentCircle;
    assert(p.size()<=3);
    if (p.empty()) { 
        point x1;
        x1.x = 0.0;x1.y=0.0;
        circle ret(x1,x1);
        return ret; 
    } 
    else if (p.size() == 1) { 
        circle ret(0.0,p[0]);
        
        gnucount++; 
        currentCircle.open("CurrentCirclePoints.txt");
        currentCircle<<p[0].x<<" "<<p[0].y<<endl;
        currentCircle.close();
        gnuTrivialCircle(to_string(gnucount));
        sleep(1);

        return ret; 
    } 
    else if (p.size() == 2) { 
        circle ret(p[0], p[1]);

        gnucount++; 
        currentCircle.open("CurrentCirclePoints.txt");
        currentCircle<<p[0].x<<" "<<p[0].y<<endl;
        currentCircle<<p[1].x<<" "<<p[1].y<<endl;
        currentCircle.close();
        gnuTrivialCircle(to_string(gnucount));
        sleep(1);

        return ret;
    } 
    // To check if MEC can be determined 
    // by 2 points only 
    for (int i = 0; i < 3; i++) { 
        for (int j = i + 1; j < 3; j++) { 
            circle c(p[i], p[j]); 
            if (is_valid_circle(c, p)) 
                return c; 
        } 
    } 
    circle ret(p[0], p[1], p[2]); 

        gnucount++; 
        currentCircle.open("CurrentCirclePoints.txt");
        currentCircle<<p[0].x<<" "<<p[0].y<<endl;
        currentCircle<<p[1].x<<" "<<p[1].y<<endl;
        currentCircle<<p[2].x<<" "<<p[2].y<<endl;
        currentCircle.close();
        gnuTrivialCircle(to_string(gnucount));
        sleep(1);

    return ret; 
}


vector<point> generateCirclePoints(circle c){
    vector<point> circlePrintPoints;
    if (c.getRadius()==0){
        circlePrintPoints.push_back(c.getCenter());
        return circlePrintPoints;
    }
    float step = (c.getRadius()*2)/30.0;
    for(int i = 0;i<30;i++){
        point temp1,temp2;
        temp1.x =(c.getCenter().x-c.getRadius()) + i*step;
        temp2.x =temp1.x;
        temp1.y = c.p_getY1(temp1.x);
        temp2.y = c.p_getY2(temp1.x);
        circlePrintPoints.push_back(temp1);
        circlePrintPoints.push_back(temp2);
    }
    point lastpoint;
    lastpoint.x = (c.getCenter().x-c.getRadius()) + 30*step;
    lastpoint.y = c.p_getY1(lastpoint.x);
    circlePrintPoints.push_back(lastpoint);
    return circlePrintPoints;
}

circle welzlRecurse(vector<point>& Pset,vector<point> Boundary, int n) 
{ 
    ofstream currentPoint,circleiter;
    // Base case when all points processed or |R| = 3 
    if (n == 0 || Boundary.size() == 3) { 
        return trivialCase(Boundary); 
    } 
    // Pick a random point randomly 
    int idx = rand() % n; 
    point p = Pset[idx]; 
    // Put the picked point at the end of P 
    // since it's more efficient than 
    // deleting from the middle of the vector 
    swap(Pset[idx], Pset[n - 1]); 
    
    gnucount++; 
    currentPoint.open("CurrentPoint.txt");
    for (int i=pcount-(pcount-n);i<pcount;i++){
        currentPoint<<Pset[i].x<<" "<<Pset[i].y<<endl;
    }
    checkinside(to_string(gnucount));
    currentPoint.close();
    sleep(1);

    // Get the MEC circle d from the 
    // set of points P - {p} 
    circle d = welzlRecurse(Pset, Boundary, n - 1); 
    d.printCircle();
    vector<point> circleVec = generateCirclePoints(d);

    gnucount++; 
    circleiter.open("RecCircle.txt");
    for(auto i=circleVec.begin()+1;i<circleVec.end();i++){
        circleiter<<(*i).x<<" "<<(*i).y<<endl;
    }
    circleiter.close();
    gnuRecCircle(to_string(gnucount));
    sleep(1);

    // If d contains p, return d 
    if (isInside(d, p)) { 
        return d; 
    } 
    // Otherwise, must be on the boundary of the MEC 
    Boundary.push_back(p); 
    // Return the MEC for P - {p} and R U {p} 
    return welzlRecurse(Pset, Boundary, n - 1); 
} 
  
circle welzlStart(const vector<point>& P) 
{ 
    // gnucount++;
    // ofstream startpoint;
    // startpoint.open("startpts.txt");
    // startpoint<<P[0].x<<" "<<P[0].y<<endl;
    // startpoint<<P[1].x<<" "<<P[1].y<<endl;
    // startpoint.close();
    // gnuStartpoint(to_string(gnucount));
    // sleep(1);
    // startpoint.close();

    vector<point> P_copy = P; 
    random_shuffle(P_copy.begin(), P_copy.end()); 
    return welzlRecurse(P_copy, {}, P_copy.size()); 
} 

//===========================end of algo====================//

//======================driver code===================//

int main(int argc, char *argv[])
{
    if (mkdir("pics", 0777) == -1) 
        cerr << "Error : could not create directory!" << endl;  
    vector<point> points,finalCircle;
    circle minSpanCirle;
    cout<<"Generating "<<atoi(argv[1])<<" points!"<<endl;
    generatePoints(atoi(argv[1]));
    pcount = atoi(argv[1]);
    sleep(1);
    string fname = "1";
    gnuInit(fname);
    cout<<"Engine started."<<endl;
    sleep(1);
    points = getpoints();
    minSpanCirle = welzlStart(points);
    finalCircle = generateCirclePoints(minSpanCirle);
    cout<<"The minimum Enclosing circle is: Center {"<<minSpanCirle.getCenter().x<<","<<minSpanCirle.getCenter().y<<"}\nRadius: "<<minSpanCirle.getRadius()<<endl;
    writeFinalGnuCircle(finalCircle);
    gnuFinalCircle(to_string(++gnucount));
    sleep(2);
    system("./gifscript.sh \"./pics/\"");
    cout<<"Done, check for a circle.gif in your working directory!!"<<endl;
    return 0;
}

//====================end of drivercode=====================//