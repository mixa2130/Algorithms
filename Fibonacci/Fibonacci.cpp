/*
Fibonacci matrix method and binary exponentiation 
O(log n)
binary exponentiation:
n%2==0 =>a^n=a^(n/2) * a^(n/2)
else   =>a^n=a^(n-1) * a

use script t.sh to test the algorithm
*/

#include <iostream>
#include <vector>

int fibonacci(unsigned long long int &n,const unsigned int &m)
{
    using std::vector;
    vector<unsigned long int> fibonacci_matrix={1,1,1,0};
    vector<unsigned long int> result_matrix={1,0,0,1};

    while(n)
    {
        if(n & 1){
            //uneven. This step makes our n even
            vector<unsigned long int> trash(4);
            std::copy(result_matrix.begin(),result_matrix.end(),trash.begin());
            result_matrix[0]=trash[0]*fibonacci_matrix[0] + 
                                            trash[1]*fibonacci_matrix[2];
            result_matrix[1]=trash[0]*fibonacci_matrix[1] + 
                                            trash[1]*fibonacci_matrix[3]; 
            result_matrix[2]=trash[2]*fibonacci_matrix[0] + 
                                            trash[3]*fibonacci_matrix[2];
            result_matrix[3]=trash[2]*fibonacci_matrix[1] + 
                                            trash[3]*fibonacci_matrix[3];  
        }

        vector<unsigned long int> trash(4);
        std::copy(fibonacci_matrix.begin(),fibonacci_matrix.end(),trash.begin());

        fibonacci_matrix[0]=trash[0]*trash[0] + 
                                            trash[1]*trash[2];
        fibonacci_matrix[1]=trash[0]*trash[1] + 
                                            trash[1]*trash[3]; 
        fibonacci_matrix[2]=trash[2]*trash[0] + 
                                            trash[3]*trash[2];
        fibonacci_matrix[3]=trash[2]*trash[1] + 
                                            trash[3]*trash[3];

        n>>=1;

        if(fibonacci_matrix[0] > m && fibonacci_matrix[1] > m
                                && fibonacci_matrix[2] > m && fibonacci_matrix[3] > m){
            
            for (int i = 0; i < 4; i++)
            {
                fibonacci_matrix[i]%=m;
            }
            
        }
        if(result_matrix[0] > m && result_matrix[1] > m
                                && result_matrix[2] > m && result_matrix[3] > m){
            
            for (int i = 0; i < 4; i++)
            {
                result_matrix[i]%=m;
            }
            
        }
        
    }

    return result_matrix[1]%m;
}

int main()
{
    unsigned long long int n;
    unsigned int m;
    //n-fibonacci degree, m-mod  
    std::cin>>n>>m;

    std::cout<<fibonacci(n,m);
    
}
