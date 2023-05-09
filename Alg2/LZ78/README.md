# LZ78

Esta é um implementação do algoritmo LZ78, em Python. Este algoritmo é baseado na substituição de prefixos que já aconteceram no texto de entrada por referências aos prefixos que já ocorreram anteriormente. Nesta implementação foi utilizado uma Trie como estrutura de dados auxiliar ao algoritmo, de modo que as consultas, durante a compressão, pudessem ser feitas mais eficientemente. No geral, esse algoritmo é implementado com dicionários, de modo que são geradas tuplas de números e caracteres, cada uma representando um prefixo que já aconteceu no texto.
Para salvar o arquivo compresso, foi verificado o número e o char que mais gastavam bits para serem codificados, de modo que o cabeçalho do arquivo compresso é quantos bits é necessário para codificar os números e os caracteres, utilizando o algoritmo de descompressão.

## Instruções de inicialização

Para utilizar o algoritmo de compressão, deve-se executar a seguinte linha de comando:

``` python3 lz78.py -c <arquivo_de_entrada> -o <arquivo_de_saida>```

Caso não seja especificado o nome do arquivo de saída, ele terá o mesmo prefixo do arquivo de entrada, porem com terminação '.z78'.

Para utilizar o algoritmo de descompressão, deve-se executar a seguinte linha de comando:

``` python3 lz78.py -x <arquivo_de_entrada> -o <arquivo_de_saida>```

Caso não seja especificado o nome do arquivo de saída, ele terá o mesmo prefixo do arquivo de entrada, porem com terminação '.txt'.
Nesse caso, o arquivo de entrada deve ser um arquivo '.z78'.

# Resultados:

Foram realizados testes em 10 diferentes textos, de modo que a taxa de compressão foi calculada pelo tamanho original do texto dividido pelo tamanho do texto comprimido. Isso mostra a relação de quantos bytes do texto original o texto compresso guarda em 1 byte. Os resultados foram os seguintes:

    1.  Assim falou Zarathustra - Friedrich Nietzsche
        Original size: 476786 bytes
        Compressed size: 404402 bytes
        Compression ratio: 1.17

    2.  Leviatã - Thomas Hobbes
        Original size: 413366 bytes
        Compressed size: 348302 bytes
        Compression ratio: 1.18

    3.  Os irmãos Karamazov - Fiódor Dostoiévski
        Original size: 2014789 bytes
        Compressed size: 1412597 bytes
        Compression ratio: 1.42

    4.  Metamorfose - Franz Kafka
        Original size: 139182 bytes
        Compressed size: 105486 bytes
        Compression ratio: 1.31

    5.  My Life - Richard Wagner
        Original size: 1277141 bytes
        Compressed size: 957857 bytes
        Compression ratio: 1.33

    6.  Quincas Borba - Machado de Assis
        Original size: 485688 bytes
        Compressed size: 414092 bytes
        Compression ratio: 1.17

    7.  Notas do Subterrâneo - Fiódor Dostoiévski 
        Original size: 262705 bytes
        Compressed size: 191090 bytes
        Compression ratio: 1.37

    8.  O Grande Gatsby - F. Scott Fitzgerald
        Original size: 299891 bytes
        Compressed size: 213082 bytes
        Compression ratio: 1.40

    9.  A República - Platão
        Original size: 1228326 bytes
        Compressed size: 893057 bytes
        Compression ratio: 1.37

    10. Odisseia - Homero
        Original size: 708411 bytes
        Compressed size: 562442 bytes
        Compression ratio: 1.25

Todos os arquivos utilizados para o teste estão na pasta 'inputs'. Esses testes foram gerados ao executar o arquivo 'script.sh', que foi criado, exclusivamente, para realizar tais testes.
No fim, o programa tem um taxa de compressão média de, aproximadamente, 1.3. Isso significa que, em média, cada 1.3 bytes do texto original pode ser codificado em 1 byte, no texto compresso.
Vale ressaltar que essas taxas dependem do texto passado na entrada.

## Compatibilidade da entrada

Esta implementação aceita textos com codificação 'utf-8' e 'latin1'.


