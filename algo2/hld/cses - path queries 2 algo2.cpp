#pragma GCC Optimize ("Ofast")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll int
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
ll Nsize;

//ll lazy[5*200005];

void update(int idx, int val, int i = 1, int l = 1, int r = Nsize) {
	if (l == r) {
		seg[i] = val;
		return;
	}
	int m = (l + r) / 2;
	if (idx <= m) update(idx, val, i * 2, l, m);
	else update(idx, val, i * 2 + 1, m + 1, r);
	seg[i] = max(seg[i * 2], seg[i * 2 + 1]);
}

//void build(ll ara[],ll ind,ll low,ll high)
//{
//    if(low == high)
//    {
//        seg[ind] = ara[low];
//        return;
//    }
//    ll mid = (low + high) / 2;
//    build(ara,2*ind,low,mid);
//    build(ara,2*ind+1,mid+1,high);
//    seg[ind] = max(seg[2*ind] , seg[2*ind+1]);
//    return;
//}

ll query(ll ind,ll low,ll high,ll l,ll r)
{
    if((low >= l) && (high <= r))
    {
        return seg[ind];
    }
    else if((high < l) || (low > r))
    {
        return 0;
    }
    else
    {
        ll mid = (low+high) / 2;
        return max(query(2*ind,low,mid,l,r), query(2*ind+1,mid+1,high,l,r));
    }
}


//ll update(ll ind,ll low,ll high,ll l,ll r,ll v)
//{
//    if((low >= l) && (high <= r))
//    {
//        return seg[ind] = v;
//    }
//    else if((high < l) || (low > r))
//    {
//        return seg[ind];
//    }
//    else
//    {
//        ll mid = (low+high) / 2;
//        return seg[ind] = max(update(2*ind,low,mid,l,r,v), update(2*ind+1,mid+1,high,l,r,v));
//    }
//}





void dfs(ll n,ll p,ll l)
{
    sub[n]=1,par[n]=p,lev[n]=l;
    for(ll i = 0;i < adj[n].size();i++)
    {
        ll x = adj[n][i];
        if(x==p)continue;
        dfs(x,n,l+1);
        sub[n]+=sub[x];
    }
}
void hld(ll n,ll p)
{
    ent[n]= ++tim;//add to the ds
    update(ent[n],weight[n]);
    ll mx=-1,b=-1;
    for(ll i = 0;i < adj[n].size();i++)
    {
        ll x = adj[n][i];
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
    for(ll i = 0;i < adj[n].size();i++)
    {
        ll x = adj[n][i];
        if(x==p||x==b)continue;
        anc[x]=x;
        hld(x,n);
    }
}
ll hQry(ll u,ll v,ll n)//query on path u,v;
{
    ll s = 0;
    while(anc[u] != anc[v])
    {
        if(lev[anc[u]] < lev[anc[v]])
        {
            swap(u,v);
        }
        s = max(s,query(1,1,n,ent[anc[u]],ent[u]));
        u=par[anc[u]];
    }
    if(lev[u] < lev[v])swap(u,v);
    if(anc[u]==anc[v])
    {
        s = max(s,query(1,1,n,ent[v],ent[u]));

    }
    return s;
}

int main()
{
    fastIO();
    ll t = 1,it;
    for(it = 1;it <= t;it++)
    {
        ll n,q,i,j,k,s = 0,x,y,c = 0,d,e;
        tim = 0;
        cin >> n >> q;
        Nsize = n;
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
        //build(ara,1,1,n);
        for(i = 0;i < q;i++)
        {
            cin >> c;
            if(c == 1)
            {
                cin >> d >> e;
                update(ent[d],e);
            }
            else
            {
                cin >> d >> e;
                cout << hQry(d,e,n) << " ";
            }
        }
        cout << N;
    }
    return 0;
}

