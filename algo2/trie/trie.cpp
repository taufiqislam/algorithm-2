#include<bits/stdc++.h>
#define ll long long
#define N '\n'
using namespace std;

struct node
{
    ll endmark;
    node* next[26+1];
    node()
    {
        endmark = 0;
        for(int i = 0;i < 26;i++)
        {
            next[i] = NULL;
        }
    }
};

void tinsert(string str,node* root)
{
    node* curr = root;
    ll i,len,id;
    len = str.length();
    for( i = 0;i < len;i++)
    {
        id = str[i] - 'a';
        if(curr->next[id] == NULL)
        {
            curr->next[id] = new node();
        }
        curr = curr->next[id];
    }
    curr->endmark = 1;
}

ll tsearch(string str,node* root)
{
    node* curr = root;
    ll i,len,id;
    len = str.length();
    for( i = 0;i < len;i++)
    {
        id = str[i] - 'a';
        if(curr->next[id] == NULL)
        {
            return 0;
        }
        curr = curr->next[id];
    }
    for(i = 0;i < 26;i++)
    {
        if(curr->next[i] != NULL)
        {
            return 1;
        }
    }
    return 0;
}

void del(node* cur)
{
    for(ll i = 0;i < 26;i++)
    {
        if(cur->next[i])
        {
            del(cur->next[i]);
        }
    }
    delete(cur);
}

int main()
{
    ll t = 1,it;
    for(it = 1;it <= t;it++)
    {
        ll n,m,i,j,k,c,d,x,y,f = 0,s = 0;
        cout << "Enter the number of words: ";
        cin >> n;
        node* root = new node();
        string str[n];
        cout << "Enter the words:\n";
        for(i = 0;i < n;i++)
        {
            cin >> str[i];
            tinsert(str[i],root);
        }
        cout << "Enter the number of words you wish to look for: ";
        cin >> m;
        string stt;
        cout << "Enter the words you wish to look for:\n";
        for(i = 0;i < m;i++)
        {
            cin >> stt;
            f = tsearch(stt,root);
            if(f == 0)
            {
                cout << "Found!\n";
            }
            else
            {
                cout << "Not found!\n";
            }
        }
        del(root);
    }
}

