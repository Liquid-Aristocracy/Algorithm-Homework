#include <fstream>
#include <iostream>
#include <algorithm>
#include <math.h>

struct Point
{
    double x;
    double y;
};

void calcangle(Point ref, Point prev, Point target, double *res)
{
    Point vectorref, vectorrot;
    vectorref.x = ref.x - prev.x;
    vectorref.y = ref.y - prev.y;
    vectorrot.x = target.x - ref.x;
    vectorrot.y = target.y - ref.y;
    double dotproduct = vectorref.x * vectorrot.x + vectorref.y * vectorrot.y;
    double lenref = pow(vectorref.x, 2) + pow(vectorref.y, 2);
    double lenrot = pow(vectorrot.x, 2) + pow(vectorrot.y, 2);
    double ab = pow(lenref * lenrot, 0.5);
    double costheta = dotproduct / ab;
    res[0] = ab;
    res[1] = costheta;
}

int findlowest(int n, Point *p)
{
    int k = 0;
    for (int i = 1; i < n; i++)
    {
        if (p[i].y < p[k].y)
        {
            k = i;
        }
        else if (p[i].y == p[k].y && p[i].x < p[k].x)
        {
            k = i;
        }
    }
    return k;
}

void convexhull(int n, Point *p)
{
    std::ofstream fileout;
    fileout.open("./vsfiles/exp3(2)_out.txt", std::ios::out | std::ios::app);
    int ref = findlowest(n, p);
    Point prev = p[ref];
    int start = ref;
    prev.x -= 1;
    std::cout << '[';
    fileout << '[';
    do
    {
        if (ref != start)
        {
            std::cout << ", ";
            fileout << ", ";
        }
        std::cout << ref;
        fileout << ref;
        double maxcos = -1;
        double refab;
        int nextref = ref;
        for (int i = 0; i < n; i++)
        {
            if (i != ref)
            {
                double dot[2];
                calcangle(p[ref], prev, p[i], dot);
                double ab = dot[0];
                double costheta = dot[1];
                if (costheta > maxcos)
                {
                    maxcos = costheta;
                    nextref = i;
                    refab = ab;
                }
                else if (costheta == maxcos && ab < refab)
                {
                    nextref = i;
                    refab = ab;
                }
            }
        }
        prev = p[ref];
        ref = nextref;
    } while (ref != start);
    std::cout << ']' << std::endl;
    fileout << ']' << std::endl;
    fileout.close();
}

int main()
{
    std::ifstream filein;
    std::ofstream fileout;
    filein.open("./exp3(2)_in.txt", std::ios::in);
    fileout.open("./exp3(2)_out.txt", std::ios::out);
    fileout.close();
    int n;
    Point *list;
    while (filein >> n)
    {
        list = new Point[n];
        for (int i = 0; i < n; i++)
        {
            filein >> list[i].x >> list[i].y;
        }
        convexhull(n, list);
        delete list;
    }
    filein.close();
}
