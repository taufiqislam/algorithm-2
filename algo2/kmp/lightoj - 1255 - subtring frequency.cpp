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

class KMP 
{
private:
    string pattern;
    vector<int> lps;
    void buildLPS() 
    {
        int len = 0;
        lps[0] = 0;
        int i = 1;
        while (i < pattern.size()) 
        {
            if (pattern[i] == pattern[len]) 
            {
                len++;
                lps[i] = len;
                i++;
            } 
            else 
            {
                if (len != 0) 
                {
                    len = lps[len-1];
                } 
                else 
                {
                    lps[i] = 0;
                    i++;
                }
            }
        }

    }
public:
    KMP(string pattern) : pattern(pattern) {
        lps.resize(pattern.size(), 0);
        buildLPS();
    }
    vector<int> search(string text) 
    {
        vector<int> matches;
        int i = 0;
        int j = 0;
        while (i < text.size()) 
        {
            if (text[i] == pattern[j]) 
            {
                i++;
                j++;
            }
            if (j == pattern.size()) 
            {
                matches.push_back(i - j);
                j = lps[j-1];
            } 
            else if (i < text.size() && text[i] != pattern[j]) 
            {
                if (j != 0) 
                {
                    j = lps[j-1];
                } 
                else 
                {
                    i++;
                }
            }
        }
        return matches;
    }
};

int main()
{
    fastIO();
    ll t = 1,it;
    cin >> t;
    for(it = 1;it <= t;it++)
    {
        ll n,q,i,j,k,s = 0,x,y,c = 0,d;
        string str,stt;
        cin >> str;
        cin >> stt;
        vector<int> ans;
        KMP lp(stt);
        ans = lp.search(str);
        d = ans.size();
        cout << "Case " << it << ": " << d << N;
    }
    return 0;
}
