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
    int bestc;
    int bestabs;
    int bestasum;
    int bestbsum;
    int bestcsum;
    int bestlimit;
    int nowsolution[20];
    int nowa;
    int nowb;
    int nowc;
    int nowasum;
    int nowbsum;
    int nowcsum;
    int nowrest;
    int prematrix[20][1000];
    int length;
    int matrix[20][1000];
    void init()
    {
        besta = 0;
        bestb = 0;
        bestc = 0;
        nowa = 0;
        nowb = 0;
        nowc = 0;
        bestabs = 40;
        bestasum = 0;
        nowasum = 0;
        bestbsum = 0;
        nowbsum = 0;
        bestcsum = 0;
        nowcsum = 0;
        nowrest = 0;
        length = 1000;
        for(size_t i = 0; i < 20; i++){
            bestasum += i;
            bestbsum += i;
            bestcsum += i;
            nowrest += i;
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
                    if (nowsolution[j] != s && nowsolution[j] != -1 && matrix[j][i] == 1)
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
        /*
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
        }*/
        int rest = 20 - t;
        if (besta + bestb + bestc > (nowa + nowb + nowc + rest))
        {
            return 1;
        }else if(besta + bestb + bestc == (nowa + nowb + nowc + rest))
        {
            if (2 * rest < abs(nowa - nowb) + abs(nowb - nowc) - bestabs)
            {
                return 1;
            }else if(2 * rest == abs(nowa - nowb) + abs(nowb - nowc) - bestabs)
            {
                if(bestasum < nowasum){
                    return 1;
                }else if(bestasum == nowasum){
                    if(bestasum < nowasum){
                        return 1;
                    }else if(bestbsum == nowbsum){
                        if(bestcsum < nowcsum){
                            return 1;
                        }
                    }
                }
            }
        }
        return 0;
    }
    int check(){
        for(size_t m = 0; m < 18; m++){
            for(size_t i = m + 1; i < 19; i++){
                for(size_t j = i + 1; j < 20; j++){
                    int flag = 1;
                    for(size_t k = 0; k < length; k++){
                        if(matrix[i][k]==1 && matrix[j][k]==1 && matrix[m][k]==1){
                            flag = 0;
                        }
                    }
                    if(flag == 1){
                        return 1;
                    }
                }
            }
        }
        return 0;
    }
    void backtrack(int t)
    {
        output(t);
        if (cut(t) == 1)
        {
            return;
        }
        if (t == 20)
        {
            besta = nowa;
            bestb = nowb;
            bestc = nowc;
            bestabs = abs(besta - bestb) + abs(bestb - bestc);
            int s = 0, flag = 0;
            bestasum = nowasum;
            bestbsum = nowbsum;
            bestcsum = nowcsum;
            for (size_t i = 0; i < 20; i++)
            {
                bestsolution[i] = nowsolution[i];
            }
            return;
        }
        else
        {
            if (test(t, 0) == 1)
            {
                nowa++;
                nowasum += t;
                nowrest -= t;
                nowsolution[t] = 0;
                backtrack(t + 1);
                nowrest += t;
                nowasum -= t;
                nowa--;
            }
            if (test(t, 1) == 1)
            {
                nowb++;
                nowbsum += t;
                nowrest -= t;
                nowsolution[t] = 1;
                backtrack(t + 1);
                nowrest += t;
                nowbsum -= t;
                nowb--;
            }
            if (test(t, 2) == 1)
            {
                nowc++;
                nowcsum += t;
                nowrest -= t;
                nowsolution[t] = 2;
                backtrack(t + 1);
                nowrest += t;
                nowcsum -=t;
                nowc--;
            }
            nowsolution[t] = -1;
            nowrest -= t;
            backtrack(t + 1);
            nowrest += t;
        }
    }
};

int main()
{
    std::ifstream filein;
    std::ofstream fileout;
    filein.open("./exp7_in.txt", std::ios::in);
    fileout.open("./exp7_out.txt", std::ios::out | std::ios::trunc);
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
            fileout << std::endl << std::endl << std::endl;
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
        flag = 0;
        for (size_t i = 0; i < 20; i++)
        {
            if (problem.bestsolution[i] == 2)
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
