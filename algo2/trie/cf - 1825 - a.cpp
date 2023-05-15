#pragma GCC Optimize ("Ofast")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define N '\n'
#define pb push_back
#define pob pop_back
#define ff first
#define ss second
#define bb begin()
#define ee end()
#define fastIO() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
using namespace std;
using namespace __gnu_pbds;
//order_of_key (k) : Number of items strictly smaller than k .
//find_by_order(k) : K-th element in a set (counting from zero).


int main()
{
    fastIO();
    ll t = 1,it;
    cin >> t;
    for(it = 1;it <= t;it++)
    {
        ll n,q,i,j,k,s = 0,x,y,c = -1,d;
        string str;
        cin >> str;
        for(i = 0;i < str.length();i++)
        {
            d = 0;
            for(j = 0,k = i;j < k;j++,k--)
            {
                if(str[j] != str[k])
                {
                    d = 1;
                }
            }
            if(d == 1)
            {
                c = i+1;
            }
        }
        cout << c << N;
    }
    return 0;
}
