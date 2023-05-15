#include<bits/stdc++.h>
#define ll long long
using namespace std;

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
        KMP lp(stt);
        ans = lp.search(str);
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

