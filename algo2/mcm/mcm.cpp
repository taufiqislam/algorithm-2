#include<bits/stdc++.h>
using namespace std;

class MatrixChainMultiplication
{
    public:
    int matrixChainOrder(vector<int>p, int n)
    {
        int m[n][n];
        for (int i = 1; i < n; i++)
        m[i][i] = 0;
        for (int L = 2; L < n; L++)
        {
            for (int i = 1; i < n - L + 1; i++)
            {
                int j = i + L - 1;
                m[i][j] = INT_MAX;
                for (int k = i; k < j; k++)
                {
                    int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                    if (q < m[i][j])
                    m[i][j] = q;
                }
            }
        }
        return m[1][n-1];
    }
};
int main()
{
    MatrixChainMultiplication matrix;
    int i,j,n,c,d;
    cout << "Enter the number of matrices: ";
    cin >> n;
    vector<int>a;
    cout << "Enter the dimensions of the matrices:\n";
    for(i = 0;i < n;i++)
    {
        cin >> c >> d;
        if(i == 0)
        {
            a.push_back(c);
            a.push_back(d);
        }
        else
        {
            a.push_back(d);
        }
    }
    cout << "Minimum number of multiplications is " << matrix.matrixChainOrder(a, n) << endl;
    return 0;
}
