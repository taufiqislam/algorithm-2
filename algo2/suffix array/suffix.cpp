#include<bits/stdc++.h>
using namespace std;

void suffix(string str,int n,int p[])
{
    int i,j,k;
    int c[n+5] = {};
    vector<pair<char,int> > a(n);
    for(i = 0;i < n;i++)
    {
        a[i] = make_pair(str[i],i);
    }
    sort(a.begin(),a.end());
    for(int i = 0;i < n;i++)
    {
        p[i] = a[i].second;
    }
    c[p[0]] = 0;
    for(int i = 1;i < n;i++)
    {
        if(a[i].first == a[i-1].first)
        {
            c[p[i]] = c[p[i-1]];
        }
        else
        {
            c[p[i]] = c[p[i-1]] + 1;
        }
    }
    for(k = 0;(1<<k) < n;k++)
    {
        vector<pair<pair<int,int>,int > > atemp(n);
        for(int i = 0;i < n;i++)
        {
            atemp[i] = make_pair(make_pair(c[i],c[i+(1<<k) % n]),i);
        }
        sort(atemp.begin(),atemp.end());
        for(int i = 0;i < n;i++)
        {
            p[i] = atemp[i].second;
        }
        c[p[0]] = 0;
        for(int i = 1;i < n;i++)
        {
            if(atemp[i].first == atemp[i-1].first)
            {
                c[p[i]] = c[p[i-1]];
            }
            else
            {
                c[p[i]] = c[p[i-1]] + 1;
            }
        }
    }

}

int main()
{
    string text,pattern;
    cout << "Enter text: ";
    cin >> text;
    cout << "Enter pattern: ";
    cin >> pattern;
    text += "$";
    int n = text.size();
    int p[n+5];
    int i,j,k;
    suffix(text,n,p);
    int l = 1,r = n-1,mid;
    k = 0;
    while(l <= r)
    {
        mid = (l+r) / 2;
        for(i = p[mid],j = 0;i < n && j < pattern.length();i++,j++)
        {
            if(text[i] > pattern[j])
            {
                r = mid-1;
                break;
            }
            else if(text[i] < pattern[j])
            {
                l = mid + 1;
                break;
            }
        }
        if(j >= pattern.length())
        {
            k = 1;
            break;
        }
    }
    if(k == 0)
    {
        cout << "Not Found!\n";
    }
    else
    {
        cout << "Found at: " << p[mid]+1 << endl;
    }
}
