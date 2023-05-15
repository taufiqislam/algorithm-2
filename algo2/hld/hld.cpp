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

ll sub[200005],ent[200005],tim,anc[200005],par[200005],lev[200005];
ll weight[200005];
vector<ll> adj[200005];
ll seg[4 * 200005];

ll lazy[4*200005];

void build(ll ara[],ll ind,ll low,ll high)
{
    if(low == high)
    {
        seg[ind] = ara[low];
        return;
    }
    ll mid = (low + high) / 2;
    build(ara,2*ind,low,mid);
    build(ara,2*ind+1,mid+1,high);
    seg[ind] = seg[2*ind] + seg[2*ind+1];
    return;
}

ll lazyquery(ll ind,ll low,ll high,ll l,ll r)
{
    if(lazy[ind] != 0)
    {
        seg[ind] = (high - low + 1) * lazy[ind];
        if(low != high)
        {
            lazy[2*ind] = lazy[ind];
            lazy[2*ind+1] = lazy[ind];
        }
        lazy[ind] = 0;
    }
    if((r < low) || (l > high))
    {
        return 0;
    }
    if((low >= l) && (high <= r))
    {
        return seg[ind];
    }

    ll mid = (low + high) / 2;
    return lazyquery(2*ind,low,mid,l,r) + lazyquery(2*ind+1,mid+1,high,l,r);
}

void rangeupdate(ll ind,ll low,ll high,ll l,ll r,ll v)
{
    if(lazy[ind] != 0)
    {
        seg[ind] = (high - low + 1) * lazy[ind];
        if(low != high)
        {
            lazy[2*ind] = lazy[ind];
            lazy[2*ind+1] = lazy[ind];
        }
        lazy[ind] = 0;
    }
    if((r < low) || (l > high))
    {
        return;
    }
    if((low >= l) && (high <= r))
    {
        seg[ind] = (high - low + 1) * v;
        if(low != high)
        {
            lazy[2*ind] = v;
            lazy[2*ind+1] = v;
        }
        return;
    }

    ll mid = (low + high) / 2;
    rangeupdate(2*ind,low,mid,l,r,v);
    rangeupdate(2*ind+1,mid+1,high,l,r,v);
    seg[ind] = seg[2*ind] + seg[2*ind+1];
}



void dfs(ll n,ll p,ll l)
{
    sub[n]=1,par[n]=p,lev[n]=l;
    for(auto x:adj[n])
    {
        if(x==p)continue;
        dfs(x,n,l+1);
        sub[n]+=sub[x];
    }
}
void hld(ll n,ll p)
{
    ent[n]= ++tim;//add to the ds
    ll mx=-1,b=-1;
    for(auto x:adj[n])
    {
        if(x==p)continue;
        if(sub[x]>mx)
        {
            mx=sub[x];
            b=x;
        }

    }
    if(b!=-1)
    {
        anc[b]=anc[n];
        hld(b,n);
    }
    for(auto x:adj[n])
    {
        if(x==p||x==b)continue;
        anc[x]=x;
        hld(x,n);
    }
}
ll hQry(ll u,ll v,ll n)//query on path u,v;
{
    ll s = 0;
    while(true)
    {
        if(lev[u] < lev[v])swap(u,v);
        if(anc[u]==anc[v])
        {
            s += lazyquery(1,1,n,ent[v],ent[u]);
            return s;
        }
        if(lev[anc[u]] < lev[anc[v]])
        {
            swap(u,v);
        }
        s += lazyquery(1,1,n,ent[anc[u]],ent[u]);
        u=par[anc[u]];
    }
}

int main()
{

    fastIO();
    ll t = 1,it;
    for(it = 1;it <= t;it++)
    {
        ll n,q,i,j,k,s = 0,x,y,c = 0,d,e;
        cin >> n >> q;
        ll ara[n+5] = {};
        for(i = 1;i <= n;i++)
        {
            cin >> weight[i];
        }
        for(i = 0;i < n-1;i++)
        {
            cin >> c >> d;
            adj[c].pb(d);
            adj[d].pb(c);
        }
        dfs(1,-1,0);
        anc[1]=1;
        hld(1,-1);
        for(i = 1;i <= n;i++)
        {
            //cout << i << " " << ent[i] << N;
            ara[ent[i]] = weight[i];
        }
        build(ara,1,1,n);
        for(i = 0;i < q;i++)
        {
            cin >> c;
            if(c == 1)
            {
                cin >> d >> e;
                rangeupdate(1,1,n,ent[d],ent[d],e);
            }
            else
            {
                cin >> d;
                cout << hQry(1,d,n) << N;
            }
        }
    }
    return 0;
}
