import numpy as np


def insert_number_at_index(lst, num, index):
    """
    Insere um numero em um especifico index na lista, com 0s para posicoes nao inseridas anteriormente.
    
    Args:
        lst (list): Lista
        num (int ou float): numero a ser inserido
        index (int): Index a inserir o numero
        
    Returns:
        list: lista com a nova insercao
    """
    #padding
    if index >= len(lst):
        lst.extend([0] * (index - len(lst) + 1))

    # insere
    lst[index] = num

    return lst



def obj_func_parser(input):

    """
    Parser para a funcao objetivo
    
    Args:
        input(str): string com a função objetivo
        
    Returns:
        list: funcao objetivo em formato matricial 
        max: booleano para verificar se é tratado o caso de min ou max -> 1 = max e 0 = min              
    """
    input = input.split(sep="\n")[0]
    
    max = 1
    if (input.split()[0] == "MIN"):
        max = 0

    c = []
    function = input.split()[1:]

    vars_dict = {} #dicionario com as variaveis e seus indexes
    vars_count = 0 # qtd de variaveis ja inputadas
    next_negative = False
    coef = 1
    i = 0
    while i < len(function):
        
        if function[i] == "+":
            i+=1
        
        elif function[i] == "-":
            next_negative = True
            i+=1

        elif function[i] == "−":
            next_negative = True
            i+=1

        #caso de word ser coeficiente/numero
        if function[i].isdigit() == True:

        
            if(next_negative == False):
                coef = float(function[i])

            else:
                #caso seja negativo
                coef = float(function[i])*(-1)
                next_negative = False

            i+=1

        #caso seja uma variavel ou parenteses
        elif function[i].isdigit() == False:
            
            #fracao
            if function[i] == '(':
                coef = (int(function[i+1])/ int(function[i+3]))
                if next_negative == True:
                    coef = coef*(-1)
                    next_negative = False

                i += 5
                

            elif function[i] == '*':
                i += 1
                continue

            else:

                if function[i] in vars_dict:
                    
                    insert_number_at_index(c, float(coef), vars_dict[function[i]])
                
                else:

                    vars_dict[function[i]] = vars_count
                    insert_number_at_index(c, float(coef), vars_dict[function[i]])

                    vars_count += 1
                    coef = 1
            
            i+= 1
    
    return c, max, vars_dict



def add_constraint(input:str, vars_dict):

    new_A = []
    new_b = 0
    b_sign = ""
    next_negative = False

    #qtd de variaveis
    vars_count = len(vars_dict)



    function = input.split()

    i = 0
    coef = 1
    while i < len(function):
        
        if function[i] == ">=":
            b_sign = ">="
            i+=1

        elif function[i] == "<=":
            b_sign = "<="
            i+=1

        elif function[i] == "==":
            b_sign = "=="
            i+=1
        
        if function[i] == "+":
            i+=1
        
        if function[i] == "-":
            next_negative = True
            i+=1
        
        if function[i] == "−":
            next_negative = True
            i+=1
        
        #caso de word ser coeficiente/numero
        if function[i].isdigit() == True:


            if(next_negative == False):
                coef = int(function[i])

            else:
                #caso seja negativo
                coef = int(function[i])*(-1)
                next_negative = False

            i+=1
        
        #caso seja uma variavel ou parenteses
        elif function[i].isdigit() == False:
            
            #fracao
            if function[i] == '(':
                coef = (int(function[i+1])/ int(function[i+3]))
                if next_negative == True:
                    coef = coef*(-1)
                    next_negative = False
                i += 5
                

            elif function[i] == '*':
                i += 1
                continue

            else:

                if function[i] in vars_dict:
                    
    
                    insert_number_at_index(new_A, float(coef), vars_dict[function[i]])
                
                else:

                    vars_dict[function[i]] = vars_count
                    insert_number_at_index(new_A, float(coef), vars_dict[function[i]])

                    vars_count += 1
                    coef = 1
            
            i+= 1

        new_b =  float(function[-1])
    
    return new_A, new_b, b_sign, vars_dict

def get_constraints(input:str, vars_dict):

    A = []
    b = []
    b_signs = []

    for line in input.split(sep="\n")[1:]:
        new_A, new_b, b_sign, vars_dict = add_constraint(line, vars_dict)
        A.append(new_A)
        b.append(new_b)
        b_signs.append(b_sign)

    max_len = len(vars_dict)
    for sublist in A:
        
        if len(sublist) > max_len:
            max_len = len(sublist) 

    matrix = []
    # Padding para tornar todas listas com o mesmo tamanho
    for sublist in A :
        padded_sublist = sublist + [0] * (max_len - len(sublist))
        matrix.append(padded_sublist)

    A = np.array(matrix)
    
    return A, b, b_signs, vars_dict

