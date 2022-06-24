#include<iostream>
using namespace std;
int a[10][10],n=9;
struct vertex
{
	int tag;
	int via;
	int dist;
}v[10];
void intialise(int f,int check[10])
{
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			if(f==1)
			a[i][j]=0;
			v[i].tag=0;
			v[i].via=-1;
			v[i].dist=1000;
			check[i]=0;
		}
	}
}
void Add(int i,int j,int k)
{
	a[i][j]=k;a[j][i]=k;
}
int distance(int b[10],int k)
{
	int sum=0;
	for(int i=0;i<k-1;i++)
	{
		sum=sum+a[b[i]][b[i+1]];
	}
	return sum;
}
void printallpaths(int s,int e,int b[10],int l,int check[10])
{
	if(s==e)
	{
		for(int i=0;i<l;i++)
		{
			if(i==l-1) cout<<b[i];
			else cout<<b[i]<<"->";
		}
		int d=distance(b,l);
		cout<<"  with "<<d<<" kms ";
		cout<<endl;
	}
	else
	{
		for(int i=1;i<=n;i++)
		{
			if(a[s][i]!=0&&check[i]!=1)
			{
				b[l++]=i;check[i]=1;
				printallpaths(i,e,b,l,check);check[i]=0;l--;
			}
		}
	}
}
int find()
{
	int temp=1001,temp1=0;
	for(int i=1;i<=n;i++)
	{
		if(v[i].tag!=1&&v[i].dist<temp)
		{
			temp=v[i].dist;
			temp1=i;
		}
	}
	return temp1;
}
void shortest_path(int s)
{
	if(s!=0)
	{
	v[s].tag=1;
	for(int i=1;i<=n;i++)
	{
		if(a[s][i]!=0&&v[i].tag!=1)
		{
			if(v[i].dist>a[s][i]+v[s].dist)
			{
				v[i].via=s;
				v[i].dist=a[s][i]+v[s].dist;
			}
		}
	}
	shortest_path(find());
	}
}
int main()
{
	int choice,check[10],s,e;
	intialise(1,check);
	Add(1,5,1);Add(1,3,4);Add(1,8,3);Add(1,9,2);Add(3,7,6);
	Add(3,8,2);Add(3,5,5);Add(9,4,3);Add(9,5,3);Add(9,7,1);
	Add(4,7,4);Add(4,6,2);Add(5,2,5);Add(8,2,2);Add(2,6,6); Add(2,7,2);Add(2,4,5);
	do
	{
		intialise(0,check);
		cout<<"1-printing all paths from source to destination\n2-shortest distance from source to destination\n";
		cout<<"3-shortest path from source to destination via a point\n4-exit";
		cout<<"\nenter your choice :";
		cin>>choice;
		switch(choice)
		{
			case 1 :
				{
					cout<<"enter the source :";
					cin>>s;
					cout<<"enter the destination :";
					cin>>e;int c[10];
					c[0]=s;
					cout<<"paths are :\n";
					printallpaths(s,e,c,1,check);break;
				}
			case 2 :
				{
					cout<<"enter the source :";
					cin>>s;
					cout<<"enter the destination :";
					cin>>e;
					v[s].dist=0;
					shortest_path(s);
					int c[10],d=1;
					c[0]=e;
					while(e!=s)
					{
						c[d++]=v[e].via;
						e=v[e].via;
					}
					cout<<"shortest path is :";
					for(int i=d-1;i>=0;i--)
					{
						cout<<c[i];if(i!=0)cout<<"->";
					}
					int di=distance(c,d);
					cout<<"   with "<<di<<" kms "<<endl;
					break;
				}
			case 3 :
				{
					int t;
					cout<<"enter the source :";
					cin>>s;
					cout<<"enter the destination :";
					cin>>e;
					cout<<"enter via :";
					cin>>t;
					int c[20],d=1;
					c[0]=e;
					v[t].dist=0;
					shortest_path(t);
					while(e!=t)
					{
						c[d++]=v[e].via;
						e=v[e].via;
					}
					intialise(0,check);
					v[s].dist=0;
					shortest_path(s);
					while(t!=s)
					{
						c[d++]=v[t].via;
						t=v[t].via;
					}
					cout<<"shortest path is :";
					for(int i=d-1;i>=0;i--)
					{
						cout<<c[i];if(i!=0)cout<<"->";
					}
					int di=distance(c,d);cout<<"   with "<<di<<" kms "<<endl;
					break;
				}
			case 4 :
				{
					break;
				}
			default :
				{
					cout<<"enter correct value";
					break;
				}
		}
		cout<<endl<<endl;
	}while(choice!=4);
}
