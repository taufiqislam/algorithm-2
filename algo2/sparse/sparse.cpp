#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll sparse[100005][40];

void build(ll ara[],ll n)
{
    ll i,j,l;
    for(i = 1;i <= n;i++)
    {
        sparse[i][0] = ara[i-1];
    }
    l = log2(n);
    for(j = 1;j <= l;j++)
    {
        for(i = 1;i+(1LL<<(j-1)) <= n;i++)
        {
            sparse[i][j] = min(sparse[i][j-1],sparse[i+(1LL<<(j-1))][j-1]);
        }
    }
}

ll query(ll l,ll r)
{
    ll x, y;
    y = r-l+1;
    x = log2(y);
    return min(sparse[l][x],sparse[l + (y-(1LL<<x))][x]);
}

int main()
{
    ll t = 1,it;
    for(it = 1;it <= t;it++)
    {
        ll n,q,i,j,k,s = 0,x,y,c = 0,d,l,r,mid,maxi = LLONG_MIN;
        cout << "Enter the number of elements: ";
        cin >> n;
        ll ara[n];
        cout << "Enter the array elements:\n";
        for(i = 0;i < n;i++)
        {
            cin >> ara[i];
        }
        build(ara,n);
        cout << "Enter the number of queries: ";
        cin >> q;
        cout << "Enter the queries:\n";
        for(i = 1;i <= n;i++)
        {
            cin >> l >> r;
            cout << "Minimum: " << query(l,r) << endl;
        }
    }
    return 0;
}
