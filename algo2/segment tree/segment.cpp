#include<bits/stdc++.h>
using namespace std;

struct node
{
    int mn;
    int lazyflag, lazyval;
};

int arr[10000];
node seg[4*15];



void build(int idx, int x, int y )
{
    seg[idx].lazyflag = 0;
    if(x==y)
    {
        seg[idx].mn = arr[x-1];
        return ;
    }

    int mid = (x + y)/2;
    int lft = 2*idx;
    int rgt = 2*idx + 1;

    build(lft, x, mid);
    build(rgt, mid+1,y);

    seg[idx].mn = min(seg[lft].mn, seg[rgt].mn );

}
int query(int idx, int st, int ed, int x, int y)
{
    if(seg[idx].lazyflag == 1)
    {
        seg[idx].mn = seg[idx].lazyval;
        if(st != ed)
        {
            seg[2*idx].lazyflag = 1;
            seg[2*idx].lazyval = seg[idx].lazyval;
            seg[2*idx+1].lazyflag = 1;
            seg[2*idx+1].lazyval = seg[idx].lazyval;
        }
        seg[idx].lazyflag = 0;
    }
    if(st==x && ed==y)
    {
        return seg[idx].mn;
    }
    int mid = (st + ed)/2;
    int lft = 2*idx;
    int rgt = 2*idx + 1;


    if(y<=mid)
    {
        return query(lft,st,mid,x,y);
    }
    else if(x>mid)
    {
        return query(rgt,mid+1,ed,x,y);
    }
    {
        int a = query(lft,st,mid,x,mid);
        int b = query(rgt,mid+1,ed,mid+1,y);
        return min(a,b);
    }
}

void update(int idx, int st, int ed, int x, int y,int k)
{
    if(seg[idx].lazyflag == 1)
{
        seg[idx].mn = seg[idx].lazyval;
        if(st != ed)
        {
            seg[2*idx].lazyflag = 1;
            seg[2*idx].lazyval = seg[idx].lazyval;
            seg[2*idx+1].lazyflag = 1;
            seg[2*idx+1].lazyval = seg[idx].lazyval;

        }
        seg[idx].lazyflag = 0;
    }
    if(st==x && ed==y)
    {
        seg[idx].mn = k;
        if(st != ed)
        {
            seg[2*idx].lazyflag = 1;
            seg[2*idx].lazyval = k;
            seg[2*idx+1].lazyflag = 1;
            seg[2*idx+1].lazyval = k;
        }
        return;
    }
    int mid = (st + ed)/2;
    int lft = 2*idx;
    int rgt = 2*idx + 1;
    if(y<=mid)
    {
        update(lft,st,mid,x,y,k);
    }
    else if(x>mid)
    {
        update(rgt,mid+1,ed,x,y,k);
    }
    else
    {
        update(lft,st,mid,x,mid,k);
        update(rgt,mid+1,ed,mid+1,y,k);
    }
    seg[idx].mn = min(seg[2*idx].mn,seg[2*idx+1].mn);
}


int main()
{
    int n,i,j,q,x,y,z,h;
    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter the elements: ";
    for(i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    build(1,1,n);
    cout << "Enter the number of queries: ";
    cin >> q;
    cout << "1. range query for min value\n";
    cout << "2. range update\n";
    for(i = 0; i < q; i++)
    {
        cin >> h;
        if(h == 1)
        {
            cin >> x >> y;
            cout<<"Minimum value between " << x << " and " << y << " is: " <<query(1,1,n,x,y)<<endl;
        }
        else
        {
            cin >> x >> y >> z;
            update(1,1,n,x,y,z);
        }
    }
    return 0;
}   
