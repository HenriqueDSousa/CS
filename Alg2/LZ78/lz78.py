import numpy as np
import sys

class TrieNode:

    def __init__(self):
        self.children = {}
        self.index = 0
    
    def insert(self,char, index):
        child = TrieNode()
        self.children[char] = child
        child.index  = index


def tuple_to_bin(tupla, index_width= 24, char_size= 16):

    code = ""
    
    if len(tupla[1]) > 0:

        num = str(bin(tupla[0])[2:]).zfill(index_width)
        char = bin(ord(tupla[1]))[2:].zfill(char_size)
        code = num + char
        

    return code

def encoded_file(output_file, array):

    # escrevendo string de bits em binario
    buffer = bytearray()

    i = 0
    while i < len(array):
        buffer.append( int(array[i:i+8], 2) )
        i += 8

    output_file.write(buffer)


def lz78_encode(text):

    # inicializa trie com no raiz que representa o simbolo de vazio
    root = TrieNode()

    code = []
    node = root
    index = 0
    largest_index = index
    char_size = 0

    for c in text:
        
        if c in node.children: # se c ja estiver no no, caminhe para o proximo no

            node = node.children[c]

        else:
            # o prefixo é a concatenacao do prefixo ja existente com c
            code.append((node.index, c))
            char_size = max(char_size, len(format(ord(c), '08b')))
            index += 1

            if index > largest_index:
                largest_index = index
                 
            # inserindo na trie novo prefixo
            node.insert(c, index)
            node = root

    if node.index != 0:
        code.append((node.index, ""))


    index_width = largest_index.bit_length()
    index_width = index_width + 7
    index_width -= (index_width % 8)

    #padding para fit nos bytes
    char_size = char_size + 7
    char_size -= (char_size % 8)

    return code, index_width, char_size

def lz78_decode(code):

    # inicializando dicionario vazio
    dictionary = {0: ""}
    
    text = ""
    for index, c in code:

        #se char for vazio o prefixo tambem é vazio
        if c == "":
            prefix = "" 
        else:

            # o prefixo é a concatenacao do prefixo indicado pelo index com o char c
            prefix = dictionary[index] + c  
        
        # adicionando novo prefixo ao dicionario
        dictionary[len(dictionary)] = prefix 
        text += prefix
    
    return text

# def binary_to_tuple(byte_array, index_width, char_width= 16):
    
#     index = int(bit_string[:index_width], 2)

#     char = chr(int(bit_string[index_width: index_width + char_width], 2))


#     return (index, char)

# ----------------------------------------------- CODIFICACAO -------------------------------------------------------------

if "-c" in sys.argv:

    if sys.argv.index('-c') + 1 < len(sys.argv):
        filename = sys.argv[2]
    else:
        print("Arquivo nao definido")
        sys.exit(1)

    input_file = open(filename, "r")
    text = input_file.read()
                                    
    code, index_width, char_size= lz78_encode(text)

    #numero minimo de bits para codificar os indices
    
    
    # codificando para bits
    bin_code = ""

    #Cabecalho: quantos bits sao necessarios para cada index e cada char
    bin_code += bin(index_width)[2:].zfill(8)
    bin_code += bin(char_size)[2:].zfill(8)
    
    for t in code:
        bin_code += tuple_to_bin(t , index_width, char_size)
        


    if "-o" in sys.argv:
        
        if sys.argv.index('-o') + 1 < len(sys.argv):
            
            aux = sys.argv.index('-o')
            filename = sys.argv[aux+1]
    
    filename = filename.split(sep=".")[0]

    out_file = open(filename + ".z78", "wb")    
    
    encoded_file(out_file, bin_code)

    input_file.close()
    out_file.close()

# ------------------------------------------ DECODIFICACAO -------------------------------------

elif "-x" in sys.argv:
    
    if sys.argv.index("-x") + 1 < len(sys.argv):

        filename = sys.argv[sys.argv.index("-x") + 1]
    
    else:
        print("Arquivo de entrada não especificado")
        sys.exit(1)
    
    input_file = open(filename, "rb")
    
    index_width = ord((input_file.read(1)).decode('latin-1'))
    char_size = ord((input_file.read(1)).decode('latin-1'))

    #excluindo o cabecalho

    # codigo para o algoritmo de decodificacao
    code = []

    while True:
        
        byte = input_file.read(1)

        #EOF
        if not byte:
            break
        
        # decode index
        byte = ord(byte.decode('latin-1'))
        index = byte 
        for i in range(index_width // 8 - 1):

            byte = input_file.read(1)
            byte = ord(byte.decode('latin-1'))
            index = (index << 8) + byte

        byte = input_file.read(1)

        # decode character
        byte = ord(byte.decode('latin-1'))
        char = byte

        for i in range(char_size // 8 - 1):
            byte = input_file.read(1)
            byte = ord(byte.decode('latin-1'))
            # convert character from binary to integer
            char = (char << 8) + byte

        # convert integer into a unicode character
        char = chr(char) 
        tupla = (index, char)

        code.append(tupla)     

    
    
    text = (lz78_decode(code))

    if "-o" in sys.argv:
        
        if sys.argv.index('-o') + 1 < len(sys.argv):
            
            aux = sys.argv.index('-o')
            filename = sys.argv[aux+1]

    filename = filename.split(".")[0]

    out_file = open(filename + ".txt", "w")
    out_file.write(text)

    input_file.close()
    out_file.close()


    