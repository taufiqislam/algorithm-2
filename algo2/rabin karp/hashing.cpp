#include<bits/stdc++.h>
#define ll long long
using namespace std;

vector<int>RabinKarp(string const& s, string const& t)
{
    const int p = 37;
    const int m = 1e9 + 7;
    int ls = (int)s.size(), lt = (int)t.size();
    vector<long long> p_pow(max(ls, lt));
    p_pow[0] = 1;

    for (int i = 1; i < (int)p_pow.size(); i++)
    {
        p_pow[i] = (p_pow[i-1] * p) % m;
    }

    vector<long long>h(lt + 1, 0);
    for (int i = 0; i < lt; i++)
    {
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m;
    }

    long long h_s = 0;
    for (int i = 0; i < ls; i++)
    {
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m;
    }

    vector<int>occurences;
    for (int i = 0; i + ls - 1 < lt; i++)
    {
        long long cur_h = (h[i+ls] + m - h[i]) % m;
        if (cur_h == h_s * p_pow[i] % m)
        {
            occurences.emplace_back(i);
        }
    }
    return occurences;
}

int main()
{
    ll t = 1,it;
    for(it = 1;it <= t;it++)
    {
        ll n,q,i,j,k,s = 0,x,y,c = 0,d;
        string str,stt;
        cout << "Enter text: ";
        cin >> str;
        cout << "Enter pattern: ";
        cin >> stt;
        vector<int> ans;
        ans = RabinKarp(stt,str);
        d = ans.size();
        cout << "Occurrence count: " << d << endl;
        for(i = 0;i < d;i++)
        {
            cout << ans[i]+1 << " ";
        }
        cout << endl;
    }
    return 0;
}


