#include <fstream>

void setLength(int n, int seg[], int len[])
{
    for (int i = 0; i < n; i++)
    {
        len[i * n + i] = seg[i];
    }
    for (int r = 1; r < n; r++)
    {
        for (int i = 0; i < n - r; i++)
        {
            int j = i + r;
            len[i * n + j] = len[(i + 1) * n + j] + len[i * n + i];
        }
    }
}

int bestCutting(int n, int len[], int m[])
{
    for (int i = 0; i < n; i++)
    {
        m[i * n + i] = 0;
    }
    for (int r = 1; r < n; r++)
    {
        for (int i = 0; i < n - r; i++)
        {
            int j = i + r;
            m[i * n + j] = m[(i + 1) * n + j] + len[i * n + j];
            for (int k = i + 1; k < j; k++)
            {
                int t = m[i * n + k] + m[(k + 1) * n + j] + len[i * n + j];
                if (t < m[i * n + j])
                {
                    m[i * n + j] = t;
                }
            }
        }
    }
    return m[n - 1];
}

void swap(int *a, int x, int y)
{
    int t;
    t = a[x];
    a[x] = a[y];
    a[y] = t;
}

void selectSort(int *a, int p, int r)
{
    int min;
    for (int i = p; i < r; i++)
    {
        min = i;
        for (int j = i + 1; j <= r; j++)
        {
            if (a[j] < a[min])
            {
                min = j;
            }
        }
        swap(a, i, min);
    }
}

void calcSeg(int k, int L, int point[], int seg[])
{
    selectSort(point, 0, k - 1);
    seg[0] = point[0];
    for (int i = 1; i < k; i++)
    {
        seg[i] = point[i] - point[i - 1];
    }
    seg[k] = L - point[k - 1];
}

int main()
{
    std::ifstream filein;
    std::ofstream fileout;
    filein.open("./files/exp2_in.txt", std::ios::in);
    fileout.open("./files/exp2_out.txt", std::ios::out | std::ios::trunc);
    int L, k, n, *point, *seg, *len, *m;
    while (filein >> L)
    {
        filein >> k;
        point = new int[k];
        n = k + 1;
        seg = new int[n];
        len = new int[n * n];
        m = new int[n * n];
        for (int i = 0; i < k; i++)
        {
            filein >> point[i];
        }
        calcSeg(k, L, point, seg);
        setLength(n, seg, len);
        fileout << bestCutting(n, len, m) << std::endl;
    }
}
