#include <iostream>
#include <thread>
#include <chrono>

#define L 1000
#define N 1000

using namespace std;
using namespace chrono;

void print_matrix(int **a, int m, int n);
void matrix_multiple(int ** a, int ** b, int ** c, int m_a, int n_a, int m_b, int n_b, int pr_tmp, int tmp);
void best_vinograd(int ** a, int ** b, int ** c, int m_a, int n_a, int m_b, int n_b, int pr_tmp, int tmp);
void zero_matrix(int ** a, int l, int n);

int main()
{
    int **a = new int* [L];
    int **b = new int* [L];
    int **c = new int* [L];
    
    for (int i = 0; i < L; i++)
    {
        a[i] = new int [N];
        b[i] = new int [N];
        c[i] = new int [N];
        for (int j = 0; j < N; j++)
        {
            a[i][j] = i + j;
            b[i][j] = i - j;
            c[i][j] = 0;
        }
    }
    
    int thr = 1;
    thread * threads = new thread[thr];
    float k = L / thr; //5 = m_a
    int tmp = (int)k;
    int pr_tmp = 0;

    //vinograd
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int i = 0; i < thr; i++)
    {
        threads[i] = thread(best_vinograd, a, b, c, L, N, L, N, pr_tmp, tmp);
        tmp += (int)k;
        pr_tmp += (int)k;
    }
    for (int i = 0; i < thr; i++)
        threads[i].join();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    
    auto duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Threads: " << thr << " Time: " << duration << " Data: " << L << "x" << N << endl;
    //cout <<  duration << endl;
    print_matrix(c, L, N);
    zero_matrix(c, L, N);
    
    //multiple matrix
    tmp = (int)k;
    pr_tmp = 0;
    t1 = high_resolution_clock::now();
    for (int i = 0; i < thr; i++)
    {
        threads[i] = thread(matrix_multiple, a, b, c, L, N, L, N, pr_tmp, tmp);
        tmp += (int)k;
        pr_tmp += (int)k;
    }
    for (int i = 0; i < thr; i++)
        threads[i].join();
    t2 = high_resolution_clock::now();
    
    duration = duration_cast<microseconds>( t2 - t1 ).count();
    cout << "Threads: " << thr << " Time: " << duration << " Data: " << L << "x" << N << endl;
    //cout <<  duration << endl;
    
    
    return 0;
    
}

void zero_matrix(int ** a, int l, int n)
{
    for (int i = 0; i < l; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = 0;
}

void print_matrix(int **a, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
    cout << "\n";
}

void matrix_multiple(int ** a, int ** b, int ** c, int m_a, int n_a, int m_b, int n_b, int pr_tmp, int tmp)
{
    for (int i = pr_tmp; i < tmp; i++)
        for (int j = 0; j < n_b; j++)
            for (int k = 0; k < m_a; k++)
                c[i][j] += a[i][k] * b[k][j];
}

void best_vinograd(int ** a, int ** b, int ** c, int m_a, int n_a, int m_b, int n_b, int pr_tmp, int tmp)
{
    div_t d = div(m_b, 2);
    int row[m_a];
    int column[n_b];
    int index;
    for (int i = 0; i < L; i++)
    {
        row[i] = 0;
        column[i] = 0;
    }
    for (int i = 0; i < m_a; i++)
        for (int j = 0; j < d.quot; j++)
        {
            row[i] += a[i][2 * j] * a[i][2 * j + 1];
        }
    
    for (int i = pr_tmp; i <= tmp; i++) //k1 = 0 k2 = n_b
        for (int j = 0; j < d.quot; j++)
        {
            column[i] += b[2 * j][i] * b[2 * j + 1][i];
        }
    
    for (int i = 0; i < m_a; i++)
        for (int j = pr_tmp; j <= tmp; j++)
        {
            c[i][j] = -row[i] - column[j];
            for (int k = 0; k < d.quot; k++)
            {
                index = 2 * k;
                c[i][j] += (a[i][index] + b[index + 1][j]) * (a[i][index + 1] + b[index][j]);
            }
        }
    
    if (d.rem > 0)
    {
        for (int i = 0; i < m_a; i++)
            for (int j = pr_tmp; j <= tmp; j++)
                c[i][j] += a[i][m_b - 1] * b[m_b - 1][j];
    }
}
