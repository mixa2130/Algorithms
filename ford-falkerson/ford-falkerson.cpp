/*if your programm works with usual start:0 and end:n-1 
delete head from global,create it in main() and sent in functions end
as an automatic variable (function parametr) instead of head

if you need start:0 and end:1 - change in 123 string bfs(0,end) to bfs(0,1)
*/

#include <iostream>
#include <vector>
#include <queue>

using std::vector;

vector< vector <int> > matrix; //handling capacity(edge existance)   пропускная способность(наличие ребра)
vector<bool> used; //pass peak or not?
vector<int> metka; //set of max on each iteration
vector<int> way; //order of passed peaks

int head; 
const int super_metka=-14567; //peak need to delete, special flag

/*
maybe you will need this function to understand algorithms logic

void check()
{
    cout<<endl;

    for(int j=0;j<5;j++)
            for(int i=0;i<5;i++)
            {
                cout<<matrix[j][i]<<' ';
                if(i+1==5)
                    cout<<endl;
            }
}
*/

void initialization() //initialization on the first step
{
    
    used[0]=true;
    metka[0]=0;
    way[0]=-1;
    for(size_t i=1;i<head;i++)
    {
        used[i]=false;
        metka[i]=0;
        way[i]=-1;
    }

}

int min()
{
    int min=50000;

    for(size_t i=0;i<head;i++)
    {
        if(metka[i] && metka[i]<min && metka[i]!=super_metka){
            min=metka[i];
        }
    }
    return min;
}

int bfs(const int &start,const int &end)  //check the way
{
    using std::queue;


    queue<int> turn_of_peaks_numbers; //turn with peak numbers

    initialization();
    turn_of_peaks_numbers.push(start); //iteration start, first peak
    
    int j=0;
    while(j!=end)
    {
        int turn_tail=turn_of_peaks_numbers.front();
        turn_of_peaks_numbers.pop();
        int max=0;

        for(size_t i=0;i<matrix[turn_tail].size();i++)
        {
            if(matrix[turn_tail][i]!=0 && !used[i] &&
                                        matrix[turn_tail][i]>max)
            {

              max=matrix[turn_tail][i];
              j=i;
            }
        }
   
        if(max==0 && turn_tail==0)
            return 0;

        if(max==0 && turn_tail!=0)
        {//step 4,peak delete
        
            metka[j]=super_metka;
            int smth=way[j];
            way[j]=-1;
            j=smth;
    
            turn_of_peaks_numbers.push(j);

        }
        else
        {
        turn_of_peaks_numbers.push(j);
        used[j]=true;
        metka[j]=max;
        way[j]=turn_tail;
        }

    }
 
    if(j!=0)
        return 1;
    return 0;
}


void max_flow(const int &start,const int &end)
{
    int flow=0;

    while(bfs(0,end)) //while the way exists
    {
      int fp=min(); //minimum path flow on iteration
      flow+=fp;

      for(int i=0;i<end+1;i++)
      {
        if(way[i]!=-1)
        {
            matrix[way[i]][i]-=fp;
            matrix[i][way[i]]+=fp;
        }
      }
      
    }

    std::cout<<"max flow="<<flow<<std::endl;
}


int main()
{
    freopen ("test.txt", "r", stdin); //please donot kick me((

    std::cin>>head;
    used.reserve(head+1);
    metka.reserve(head+1);
    way.reserve(head+1);

    for(size_t i=0;i<head;i++)
    {
        vector<int> temp;
        for(size_t j=0;j<head;j++)
        {
            int trash;
            std::cin>>trash;
            temp.push_back(trash);
        }
        matrix.push_back(temp);
    } 
	
    fclose(stdin);
    max_flow(0,head-1);
}
