#include<bits/stdc++.h>
#define ll int
#define N '\n'
using namespace std;


ll sub[100005],ent[100005],tim,anc[100005],par[100005],lev[100005];
ll weight[100005];
vector<ll> adj[100005];
ll seg[4 * 100005];
ll Nsize;


void update(int idx, int val, int i = 1, int l = 1, int r = Nsize) {
	if (l == r) {
		seg[i] = val;
		return;
	}
	int m = (l + r) / 2;
	if (idx <= m) update(idx, val, i * 2, l, m);
	else update(idx, val, i * 2 + 1, m + 1, r);
	seg[i] = seg[i * 2] + seg[i * 2 + 1];
}


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
        return query(2*ind,low,mid,l,r) + query(2*ind+1,mid+1,high,l,r);
    }
}








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
    ent[n]= ++tim;
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
ll hQry(ll u,ll v,ll n)
{
    ll s = 0;
    while(anc[u] != anc[v])
    {
        if(lev[anc[u]] < lev[anc[v]])
        {
            swap(u,v);
        }
        s += query(1,1,n,ent[anc[u]],ent[u]);
        u=par[anc[u]];
    }
    if(lev[u] < lev[v])swap(u,v);
    if(anc[u]==anc[v])
    {
        s += query(1,1,n,ent[v],ent[u]);

    }
    return s;
}

int main()
{
    ll t = 1,it;
    for(it = 1;it <= t;it++)
    {
        ll n,q,i,j,k,s = 0,x,y,c = 0,d,e;
        tim = 0;
        cout << "Enter the number of nodes: ";
        cin >> n;
        Nsize = n;
        ll ara[n+5] = {};
        cout << "Enter the weight of the nodes:\n";
        for(i = 1;i <= n;i++)
        {
            cin >> weight[i];
        }
        for(i = 0;i <= n;i++)
        {
            adj[i].clear();
            sub[i] = 0;
            anc[i] = 0;
            ent[i] = 0;
            par[i] = 0;
            lev[i] = 0;
        }
        cout << "Enter the edges:\n";
        for(i = 0;i < n-1;i++)
        {
            cin >> c >> d;
            c++;
            d++;
            adj[c].push_back(d);
            adj[d].push_back(c);
        }
        dfs(1,-1,0);
        anc[1]=1;
        hld(1,-1);
        cout << "Enter the number of queries:\n";
        cin >> q;
        cout << "Enter the queries(1 for update, 0 for query:\n";
        for(i = 0;i < q;i++)
        {
            cin >> c;
            if(c == 1)
            {
                cin >> d >> e;
                d++;
                update(ent[d],e);
            }
            else
            {
                cin >> d >> e;
                d++;
                e++;
                cout << "Sum: " << hQry(d,e,n) << N;
            }
        }
    }
    return 0;
}


