#include<bits/stdc++.h>
#define ll long long
using namespace std;

ll BIT[200005];
ll n;

ll query(ll idx)
{
    ll s = 0;
    while(idx > 0)
    {
        s += BIT[idx];
        idx -= idx & (-idx);
    }
    return s;
}

void update(ll idx,ll val)
{
    while(idx <= n)
    {
        BIT[idx] += val;
        idx += idx & (-idx);
    }
}

int main()
{
    ll t,it;
    t = 1;
    for(it = 1;it <= t;it++)
    {
        ll q,i,j,k,s = 0,x,y,c = 0,d,e;
        cout << "Enter the number of elements: ";
        cin >> n;
        ll ara[n];
        cout << "Enter the array elements:\n";
        for(i = 0;i < n;i++)
        {
            cin >> ara[i];
        }
        memset(BIT,0,sizeof(BIT));
        for(i = 0;i < n;i++)
        {
            update(i+1,ara[i]);
        }
        cout << "Enter the number of queries: ";
        cin >> q;
        cout << "Enter the queries(1 is update, 2 is query):\n";
        for(i = 0;i < q;i++)
        {
            cin >> c >> d >> e;
            if(c == 1)
            {
                update(d,e);
                ara[d-1] = e;
            }
            else
            {
                cout << "Sum: " << query(e) - query(d-1) << endl;
            }
        }
    }
    return 0;
}

