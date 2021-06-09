#include <iostream>
using namespace std;
#include<vector>
#include<cmath>

int distance(int x1, int y1, int x2, int y2)
{
    int dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    return dist;
}

int nearest_c(int cluster[][2],int k, int v1x, int v1y)
{
    int minimum=9999, c_no=0, d;
    for(int i=0; i<k; i++)
    {
        d=distance(cluster[i][0], cluster[i][1], v1x, v1y);
        if(d<minimum)
        {
            minimum=d;
            c_no=i;
        }
    }
    return c_no;
}

int main()
{
    vector <vector<int>> vertex;
    int n,t,i,k,loop_no=0;
    cout<<"enter no of clusters"<<endl;
    cin>>k;
    cout<<"enter points"<<endl;
    cin>>n;
    for(i=0; i<n; i++)
    {
        vector<int> temp;
        for(int j=0; j<3; j++)
        {
            if(j==2)
            {
                temp.push_back(0);
            }
            else
            {
                cin>>t;
                temp.push_back(t);
            }

        }
        vertex.push_back(temp);
        temp.clear();
    }
    cout<<"Input vertex"<<endl;
    for(int i=0; i<n ;i ++)
    {
        for(int j=0; j<3;j++)
        {
            cout<<vertex[i][j]<<"\t";
        }
        cout<<endl;
    }
    int cluster[k][2], cluster_list[n], c1, flag;

    for(i=0;i<k;i++)
    {
          c1=rand()%n;
          cluster[i][0]=vertex[c1][0];
          cluster[i][1]=vertex[c1][1];
    }
    cout<<" randomly selected clusters:"<<endl;
    for(int i=0; i<k ;i ++)
    {
        for(int j=0; j<2;j++)
        {
            cout<<cluster[i][j]<<"\t";
        }
        cout<<endl;
    }

    while(1)
    {
        loop_no+=1;
        cout<<"iter "<<loop_no<<endl;
        flag=0;
        for(i=0; i<n; i++)
        {
            int result = nearest_c(cluster ,k, vertex[i][0], vertex[i][1]);
            vertex[i][2]=result;
            cout<<"cluster "<<result<< " assigned to "<< i <<"   "<<endl;
        }
        cout<<endl;

        int new_cluster[k][2];
        int c_count[k]={0};
        int cluster_sum[k][2];

        for(int j=0; j<k; j++)
        {
            for(int i=0; i<2; i++)
            {
                    cluster_sum[j][i]=0;
            }
        }

        for(int j=0; j<k; j++)
        {
            for(int i=0; i<n; i++)
            {
                if(vertex[i][2]==j)
                {
                    c_count[j]+=1;
                    cluster_sum[j][0]+=vertex[i][0];
                    cluster_sum[j][1]+=vertex[i][1];
                }
            }
        }
        for(int j=0;j<k;j++)
        {
            if(c_count[j]!=0)
            {
                new_cluster[j][0]=cluster_sum[j][0]/c_count[j];
                new_cluster[j][1]=cluster_sum[j][1]/c_count[j];
            }
        }
        cout<<"new selected clusters:"<<endl;
        for(int i=0; i<k ;i ++)
        {
            for(int j=0; j<2;j++)
            {
                cout<<new_cluster[i][j]<<"\t";
            }
            cout<<endl;
        }

        cout<<endl;
        for(i=0; i<n; i++)
        {
            int result = nearest_c(new_cluster , k, vertex[i][0], vertex[i][1]);
            cluster_list[i]=result;
        }

        for(int i=0; i<n;i++)
        {
            if(vertex[i][2]!=cluster_list[i])
            {
                flag=1;
                break;
            }
        }

        if(flag!=1)
        {
            cout<<"done"<<endl;
            break;
        }

        if(loop_no>=10)
         {
            cout<<"loop end"<<endl;
            break;
         }

        cout<<"centroid changed"<<endl;

        for(int i=0;i<k;i++)
        {
            cluster[i][0]=new_cluster[i][0];
            cluster[i][1]=new_cluster[i][1];
        }

    }

    cout<<"final result"<<endl;
    for(int i=0; i<n ;i ++)
    {
        for(int j=0; j<3;j++)
        {
            cout<<vertex[i][j]<<"\t";
        }
        cout<<endl;
    }

    return 0;
}
