#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

int abs(int n)
{
    if (n < 0)
        return -n;
    else
        return n;
}

class Split
{
public:
    int bestsolution[20];
    int besta;
    int bestb;
    int bestabs;
    int bestasum;
    int bestlimit;
    int nowsolution[20];
    int nowa;
    int nowb;
    int nowasum;
    int prematrix[20][1000];
    int length;
    int matrix[20][1000];
    void init()
    {
        besta = 0;
        bestb = 0;
        nowa = 0;
        nowb = 0;
        bestabs = 20;
        bestasum = 0;
        length = 1000;
        for(size_t i = 0; i < 20; i++){
            bestasum += i;
            bestsolution[i] = -1;
        }
    }
    void arrange(){
        int nowlength = 0;
        for(size_t i = 0; i < 1000; i++){
            int onenum = 0;
            for(size_t j = 0; j < 20; j++){
                if(prematrix[j][i]==1){
                    onenum ++;
                }
            }
            if (onenum > 1)
            {
                for(size_t j = 0; j < 20; j++){
                    matrix[j][nowlength] = prematrix[j][i];
                }
                nowlength ++;
            }
        }
        length = nowlength;
    }
    int test(int t, int s)
    {
        for (size_t i = 0; i < length; i++)
        {
            if (matrix[t][i] == 1)
            {
                for (size_t j = 0; j < t; j++)
                {
                    if (nowsolution[j] == 1 - s && matrix[j][i] == 1)
                    {
                        return 0;
                    }
                }
            }
        }
        return 1;
    }

    void output(int t){
        for(size_t i = 0; i < 20; i++){
            if(i < t)
                std::cout<<nowsolution[i]<<' ';
            else
                std::cout<<' '<<' ';
        }
        std::cout<<"\t\t\t";
        for(size_t i = 0; i < 20; i++){
            std::cout<<bestsolution[i]<<' ';
        }
        std::cout<<std::endl;
    }
    int cut(int t){
        if (bestabs == 0 && besta == 10){
            if(t < bestlimit){
                int countbesta = 0, countnowa = 0;
                for(size_t i = 0; i < t; i++){
                    if(bestsolution[i] == 0){
                        countbesta++;
                    }
                    if(nowsolution[i] == 0){
                        countnowa++;
                    }
                    if(countbesta == 10 && countnowa <10){
                        return 1;
                    }
                }
            }else{
                int countnowa = 0;
                for (size_t i = 0; i < bestlimit; i++)
                {
                    if(nowsolution[i] == 0){
                        countnowa++;
                    }
                }
                if(countnowa < 10){
                        return 1;
                }
            }
        }
        int rest = 20 - t;
        if (besta + bestb > (nowa + nowb + rest))
        {
            return 1;
        }else if(besta + bestb == (nowa + nowb + rest))
        {
            if (rest < abs(nowa - nowb) - bestabs)
            {
                return 1;
            }else if(rest == abs(nowa - nowb) - bestabs)
            {
                if (nowa + rest < besta)
                {
                    return 1;
                }else if(nowa + rest == besta)
                {
                    if(nowasum > bestasum){
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
    int check(){
        for(size_t i = 0; i < 19; i++){
            for(size_t j = i + 1; j < 20; j++){
                int flag = 1;
                for(size_t k = 0; k < length; k++){
                    if(matrix[i][k]==1 && matrix[j][k]==1){
                        flag = 0;
                    }
                }
                if(flag == 1){
                    return 1;
                }
            }
        }
        return 0;
    }
    void backtrack(int t)
    {
        //output(t);
        if (cut(t) == 1)
        {
            return;
        }
        if (t == 20)
        {
            if(nowa == 0 || nowb == 0){
                return;
            }
            besta = nowa;
            bestb = nowb;
            bestabs = abs(besta - bestb);
            int s = 0, flag = 0;
            if(bestabs == 0){
                flag = 1;
            }
            bestasum = nowasum;
            for (size_t i = 0; i < 20; i++)
            {
                bestsolution[i] = nowsolution[i];
                if(flag == 1 && bestsolution[i] == 0){
                    s++;
                    if(s == 10){
                        bestlimit = i + 1;
                    }
                }
            }
            return;
        }
        else
        {
            if (test(t, 0) == 1)
            {
                nowa++;
                nowasum += t;
                nowsolution[t] = 0;
                backtrack(t + 1);
                nowasum -= t;
                nowa--;
            }
            if (test(t, 1) == 1)
            {
                nowb++;
                nowsolution[t] = 1;
                backtrack(t + 1);
                nowb--;
            }
            nowsolution[t] = -1;
            backtrack(t + 1);
        }
    }
};

int main()
{
    std::ifstream filein;
    std::ofstream fileout;
    filein.open("./exp6_in.txt", std::ios::in);
    fileout.open("./exp6_out.txt", std::ios::out | std::ios::trunc);
    int n;
    Split problem;
    filein >> n;
    for (size_t time = 0; time < n; time++)
    {
        for (size_t j = 0; j < 1000; j++)
        {
            for (size_t i = 0; i < 20; i++)
            {
                filein >> problem.prematrix[i][j];
            }
        }
        problem.init();
        problem.arrange();
        if(problem.check() == 0){
            fileout << std::endl << std::endl;
            continue;
        }
        problem.backtrack(0);
        int flag = 0;
        for (size_t i = 0; i < 20; i++)
        {
            if (problem.bestsolution[i] == 0)
            {
                if(flag != 0){
                    fileout << ' ';
                }
                fileout << i;
                flag++;
            }
        }
        fileout << std::endl;
        flag = 0;
        for (size_t i = 0; i < 20; i++)
        {
            if (problem.bestsolution[i] == 1)
            {
                if(flag != 0){
                    fileout << ' ';
                }
                fileout << i;
                flag++;
            }
        }
        fileout << std::endl;
    }
    filein.close();
    fileout.close();
    return 0;
}
