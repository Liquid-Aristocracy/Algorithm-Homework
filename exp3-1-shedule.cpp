#include <fstream>
#include <algorithm>
#include <iostream>

int minindex(int *a, int n){
    int k = 0;
    for(int i = 1; i < n; i++){
        if(a[i] < a[k]){
            k = i;
        }
    }
    return k;
}

int allocation(int n, int m, int *t){
    std::sort(t, t + n);
    int *worktime = new int[m];
    for (int i = 0; i < m; i++)
    {
        worktime[i] = 0;
    }
    
    int waitingsum = 0;
    for(int i = 0; i < n; i++){
        int machine = minindex(worktime, m);
        waitingsum += worktime[machine];
        worktime[machine] += t[i];
    }
    delete worktime;
    return waitingsum;
}

int main()
{
    std::ifstream filein;
    std::ofstream fileout;
    filein.open("./files/exp3(1)_in.txt", std::ios::in);
    fileout.open("./files/exp3(1)_out.txt", std::ios::out | std::ios::trunc);
    int n, m, *t;
    while (filein >> n)
    {
        filein >> m;
        t = new int[n];
        for (int i = 0; i < n; i++)
        {
            filein >> t[i];
        }
        int output = allocation(n, m, t);
        std::cout<< output << std::endl;
        fileout << output << std::endl;
        delete t;
    }
}
