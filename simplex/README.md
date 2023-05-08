# SIMPLEX

Esta é uma implementação do algoritmo Simplex Duas Fases, realizada em Python. O Simplex é um algoritmo comumente utilizado para a resolução
de problemas de programação linear, sendo ele, um dos mais tradicionais nessa área.


## 1. Instruções de entrada:

A entrada deve ser fornecida com o seguinte formato:

Ex:
        MAX x1 + x2
        1*x1 + 3*x2 >= 5
        1/2*x1 + 1/3*x2 <= 3
        x1 >= 0
        x2 >= 0

A primeira linha representa a função objetivo, sendo que a primeira palavra deve ser MAX, caso o problema seja de
maximização ou MIN, caso o problema seja de minimização. As demais palavras devem se referir às variáveis, de modo
que todas devem seguir o seguinte formato "Num*xi", sendo que 
        
        Num -> representa o coeficiente que multiplica a variável, podendo ele ser omitido, caso o coeficiente seja 1.
        O coeficiente deve sempre ser seguido do símbolo '*', que significa o final do coeficiente e o operador de multiplicação.
        Logo, sempre que o coeficiente for diferente de 1 ou -1, o símbolo '*' deve aparecer entre o coeficiente e a variável, sem espaços entre
        eles.

        xi -> representa a variável de índice i, sendo que sempre deve ser especificado o valor de i e que x
        deve ser uma string de comprimento 1.

As demais linhas representam as restrições do LPP, de modo que cada linha represente uma restrição. Elas seguem o 
mesmo formato para a declaração das variáveis. As restrições podem ser formuladas com os sinais ">=", "<=" e "==", que representam,
respectivamente, maior igual, menor igual e igual.

## 2. Execução do programa

O programa deve ser executado com a seguinte linha de comando:

``` python3 simplex.py -i <arquivo_de_entrada> -o <arquivo_de_saida>```


O arquivo de entrada deve ser um arquivo .txt que contenha a especificação do LPP, como definido anteriormente.


## 3. Saída:

A saída para o exemplo passado anteriormente é a seguinte: 

        Status: otimo
        Objetivo:  9.000000000000004
        Solucao:
        [0. 9.]
        Certificado:
        [1.5 1.  0.  3.  0.  0. ]

O status determina se o problema tem solução ótima, se ele é inviável ou se é ilimitado.
O objetivo determina, caso o problema tenha solução ótima, o valor da função objetivo
A solução, caso haja solução ótima, determina o valor das variáveis para alcançar tal solução
O certificado é uma garantia de que o algoritmo foi resolvido corretamente. Ele aparece independentemente
do status retornado.

