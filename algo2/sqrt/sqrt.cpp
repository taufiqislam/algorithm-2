#include<bits/stdc++.h>
#define ll long long
#define N '\n'
using namespace std;

ll ara[100000];
ll c,d,n;
ll Block[100000];
ll lazy[100000];

void update(ll l,ll r,ll z)
{
    ll lb = (l-1)/c;
    ll rb = (r-1)/c;
    ll i,j;
    ll res = 1000000;
    for(ll i = lb+1;i <= rb-1;i++)
    {
        lazy[i] = z;
    }
    for(ll i = l-1;i < min(r,(lb+1)*c);i++)
    {
        ara[i] = z;
    }

    if(lazy[lb] != 1000000)
    {
        for(i = (lb*c);i < l-1;i++)
        {
            ara[i] = lazy[lb];
        }
    }
    lazy[lb] = 1000000;
    Block[lb]=1000000;
    for(ll i = lb*c;i < (lb+1)*c;i++)
    {
        Block[lb] = min(Block[lb],ara[i]);
    }

    for(ll i = max((rb-1)*c,l-1);i < r;i++)
    {
        ara[i] = z;
    }
    if(lazy[rb] != 1000000)
    {
        for(i = r;i < min(((rb+1)*c),n);i++)
        {
            ara[i] = lazy[rb];
        }
    }
    lazy[rb] = 1000000;
    Block[rb]= 1000000;
    for(ll i = rb*c;i < (rb+1)*c;i++)
    {
        Block[rb] = min(Block[rb],ara[i]);
    }
}

ll query(ll l, ll r)
{
    ll lb = (l-1)/c;
    ll rb = (r-1)/c;

    ll res = 1000000;
    for(ll i = lb+1;i <= rb-1;i++)
    {
        if(lazy[i] == 1000000)
        {
            res = min(res,Block[i]);
        }
        else
        {
            res = min(res,lazy[i]);
        }
    }
    for(ll i = l-1;i < min(r-1,(lb+1)*c);i++)
    {
if(lazy[lb] != 1000000)
        {
            ara[i] = lazy[lb];
        }
        res = min(res,ara[i]);
    }
    for(ll i = max((rb-1)*c,l-1);i <= (r-1);i++)
    {
        if(lazy[rb] != 1000000)
        {
            ara[i] = lazy[rb];
        }
        res = min(res,ara[i]);
    }
    return res;
}




int main()
{
    ll i,j,m,q,x,y,z;
    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter the numbers in the array: ";
    for(i = 0;i < n;i++)
    {
        cin >> ara[i];
    }
    c = sqrt(n);
    d = ceil(n/(double)c);
    for(ll i=0;i < d;i++)
    {
        Block[i]=1000000;
        lazy[i]=1000000;
        for(ll j= (i*c); j < (i+1)*c;j++)
        {
            Block[i] = min( Block[i],ara[j]);
        }
    }
    cout << "Enter number of queries: ";
    cin >> q;

    for(i = 0;i < q;i++)
    {
        cout << "1 for query\n";
        cout << "2 for update\n";
        cin >> m;
        if(m == 1)
        {
            cin >> x >> y;
            cout << "minimum between " << x << " and " << y << " : " << query(x,y) << endl;
        }
        else
        {
            cin >> x >> y >> z;
            update(x,y,z);
        }
    }
    return 0;
}
