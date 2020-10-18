#include <iostream>
#include <cstdlib>
#include <time.h>

unsigned int randseed = time(NULL);
int valuemax = 10000;

unsigned int myRand()
{
    unsigned int r;
    r = randseed = randseed * 1103515245 + 12345;
    return (r << 16 | (r >> 16) & 0xFFFF);
}

struct Thing
{
    int value;
    double weight;
};

void swap(Thing *a, int x, int y)
{
    Thing t;
    t = a[x];
    a[x] = a[y];
    a[y] = t;
}

void selectSort(Thing *a, int p, int r)
{
    int min;
    for (int i = p; i < r; i++)
    {
        min = i;
        for (int j = i + 1; j <= r; j++)
        {
            if (a[j].value < a[min].value)
            {
                min = j;
            }
        }
        swap(a, i, min);
    }
}

int findMedian(Thing *a, int p, int r)
{
    double sum;
    for (int i = p; i <= r; i++)
    {
        sum += a[i].weight;
        if (sum >= 0.5)
        {
            sum -= a[i].weight;
            std::cout << "weight sum smaller than median: " << sum << std::endl;
            double sum2 = 0;
            for (int j = i + 1; j <= r; j++)
            {
                sum2 += a[j].weight;
            }
            std::cout << "weight sum bigger than median: " << sum2 << std::endl;
            return i;
        }
    }
}

int partition(Thing *a, int p, int r, int x)
{
    int i = p;
    int j = r;
    Thing pivot = a[x];
    while (true)
    {
        while (a[i].value < pivot.value && i < r)
        {
            i++;
        }
        while (a[j].value > pivot.value)
        {
            j--;
        }
        if (i >= j)
        {
            break;
        }
        swap(a, i, j);
    }
    return j;
}

int select(Thing *a, int p, int r, int k)
{
    if (r - p < 5)
    {
        selectSort(a, p, r);
        return p + k - 1;
    }
    for (int i = 0; i <= (r - p - 4) / 5; i++)
    {
        selectSort(a, p + 5 * i, p + 5 * i + 4);
        swap(a, p + i, p + 5 * i + 2);
    }
    int x = select(a, p, p + (r - p - 4) / 5, (r - p + 6) / 10);
    int i = partition(a, p, r, x), j = i - p + 1;
    if (k <= j)
    {
        return select(a, p, i, k);
    }
    else
    {
        return select(a, i + 1, r, k - j);
    }
}

int weightedSelect(Thing *a, int p, int r)
{
    if (r - p < 5)
    {
        selectSort(a, p, r);
        return findMedian(a, p, r);
    }
    for (int i = 0; i <= (r - p - 4) / 5; i++)
    {
        selectSort(a, p + 5 * i, p + 5 * i + 4);
        swap(a, p + i, p + 5 * i + 2);
    }
    int x = select(a, p, p + (r - p - 4) / 5, (r - p + 6) / 10);
    int i = partition(a, p, r, x), j = i - p + 1;
    double sumleft = 0, sumright = 0;
    for (int j = p; j < i; j++)
    {
        sumleft += a[j].weight;
    }
    for (int j = i + 1; j <= r; j++)
    {
        sumright += a[j].weight;
    }
    if (sumleft < 0.5 && sumright < 0.5)
    {
        std::cout << "weight sum smaller than median: " << sumleft << std::endl
                  << "weight sum bigger than median: " << sumright << std::endl;
        return i;
    }
    else if (sumleft >= sumright)
    {
        a[i].weight += sumright;
        return weightedSelect(a, p, i);
    }
    else
    {
        a[i].weight += sumleft;
        return weightedSelect(a, i, r);
    }
}

void printArray(Thing *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << a[i].value << '\t' << a[i].weight << std::endl;
    }
    std::cout << std::endl;
}

int main()
{
    int n;
    std::cout << "Please input n: ";
    std::cin >> n;
    std::cout << std::endl
              << "Generated list:" << std::endl;
    Thing *a = new Thing[n];
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        a[i].value = myRand() % valuemax + 1;
        for (int j = 0; j < i; j++)
        {
            if (a[i].value == a[j].value)
            {
                a[i].value++;
            }
        }
        a[i].weight = myRand() % 100 + 1;
        sum += a[i].weight;
    }
    for (int i = 0; i < n; i++)
    {
        a[i].weight = (double)a[i].weight / sum;
    }
    printArray(a, n);
    int i = weightedSelect(a, 0, n - 1);
    std::cout << "The weighted median of the list: " << a[i].value << std::endl << std::endl;
    system("pause");
    return 0;
}