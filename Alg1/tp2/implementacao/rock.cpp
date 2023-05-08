#include "rock.hpp"

using namespace std;

void shows(float* shows,int num_shows, int num_amigos)
{
    //vetor para armazenar os shows

    for (int i = 0; i < num_shows; i++)
    {
      shows[i] = 0;
    }

    float aux;
    //atribuindo notas para cada show
    for (int i = 0; i < num_amigos; i++)
    {
      for (int j = 0; j < num_shows; j++)
      {
        
        cin>>aux;
        shows[j] += aux;

      }
    }

    // for (int i = 0; i < num_shows; i++)
    // {
    //   cout<<shows[i]<<" ";
    // }
    // cout<<endl;

}
float maxCrossing(float* arr, int left, int mid, int right, int *res_left, int* res_right, float* res_sum)
{
    float soma = 0;
    float left_sum = INT16_MIN;

    //index auxiliar para cross sum
    int idx_l = -1;
    int idx_r = -1;
    //calculando a soma dos elementos da esquerda
    //do pivo até a posicao left
    for (int i = mid; i >= left; i--)
    {
        soma += arr[i];

        if (soma > left_sum)
        {  
           idx_l = i;
           left_sum = soma;
        }
    }
    
    //calculando a soma dos elementos da direita
    //do pivo ate right
    soma = 0;
    float right_sum = INT16_MIN;
    for (int i = mid; i <= right; i++)
    {
        soma += arr[i];

        if (soma > right_sum)
        {   
            idx_r = i;
            right_sum = soma;
        }
    }

    float calculated_cross = left_sum + right_sum - arr[mid];
    float max_val = max( max(calculated_cross, left_sum), right_sum);

    //se o maior valor for maior do que a resposta calculada
    if (max_val > (*res_sum))
    {   
        (*res_sum) = max_val;
        (*res_left) = idx_l;
        (*res_right) = idx_r;
    }
    
    //se o maior valor for igual à resposta calculada
    if(max_val  == (*res_sum))
    {   
        /*verificar se o intervalo da cross sum é maior
        do que o intervalo calculado. A intenção é pegar o maior intervalo*/
        
        if(idx_r - idx_l > (*res_right) - (*res_left))
        {
            (*res_left) = idx_l;
            (*res_right) = idx_r;
        }
    }
    

    return max_val;
    
}

float maxSubArray(float *arr, int left, int right, int *res_left, int* res_right, float* res_sum)
{   
    //caso invalido
    if (left > right)
        return INT16_MIN;
    

    //caso base
    if (left == right)
    {   
        //se a posicao for maior que o valor da soma calculada
        if(arr[left] >= *res_sum)
        {
            *res_sum = arr[left];
            *res_left = left;
            *res_right = *res_left;
        }

        return arr[left];
    }
    
    //pivot
    int mid = (right+left)/2;

    return max(max(maxSubArray(arr, left, mid - 1, res_left, res_right, res_sum), maxSubArray(arr, mid + 1, right,res_left, res_right, res_sum)), 
           maxCrossing(arr, left, mid, right,res_left, res_right, res_sum));
}