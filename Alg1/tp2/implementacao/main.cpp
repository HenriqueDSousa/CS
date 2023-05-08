#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "rock.hpp"

using namespace std;

int main() {
  
  int num_shows, num_amigos;


  while (cin>>num_amigos>>num_shows)
  { 
    if (num_amigos==0 && num_shows == 0) break;
    
    float arr[num_shows]; 
    shows(arr, num_shows, num_amigos);
    
    int res_right = -999999;
    int res_left = -999999;
    float res_sum = INT16_MIN;
    float result = maxSubArray(arr, 0, num_shows-1, &res_left, &res_right, &res_sum);
    
    cout<<res_left+1<<" "<<res_right+1<<endl;
    result += 1;
  }

  
  


  return 0;
}
