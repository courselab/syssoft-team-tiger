# SYSeg – Perguntas resolvidas

## p1.c

O porgrama print o endereço da função main. Quando executado várias vezes, esse endreço muda devido ao ASLR.

O ASLR aleatoriza a disposição da memória a cada exeução, por razões de segurança: caso, por algum motivo, um atacante mal intencionado consiga acesso a uma localização especifica da memoria, essa medida torna mais dificil que esse atacante execute código ou acesse informações especificas.

## p2.c 

O programa possui uma falha de design: quando uma string maior que o tamanho do buffer é inserida isso sobrescreve a variavel 'verified', potencialmente alterando o funcionamento do codigo para permitir que um usuario seja incorretamente considerado verificado (para que isso aconteça o código também é compilado desabilitando instruções de segurança).

Para corrigir precisamos usar uma função que valida a entrada. A escolhida foi a mais comum, fgets, que limita a entrada a um tamanho configuravel.

## p3.c


### a) 

Antes da chamada da função temos um push para `%eax` no assembly:
```
 	      80491ae:       50                push   %eax
 	      80491af:       e8 eb ff ff ff    call   804919f <bar>
 	      80491b4:       83 c4 10          add    $0x10,%esp
```

Dessa forma podemos inferir que o valor passado para bar está inicialmente em `%eax`. Esta se trata da convenção de chamada no qual quem chama a função é responsável por garantir que os parametros estão no lugar correto e port limpar a stack após a chamada.


### b) 

Ao final de `bar` temos `80491ce:       8b 45 fc          mov    -0x4(%ebp),%eax`, no qual o valor é inserido em `%eax`. Ou seja, `foo` que precisa desse valor pode buscalo de `%eax`. Essa conveção de comunicação é consistente com a descrita acima.

### c)

Esses pedaços salvam o base pointer da pilha e os restauram após o termino da função. São essenciais para o gerenciamento da stack, o que quer dizer que podem ser omitidos se a função não necessitar de variaveis na stack.

### d) 

Essas instruções alocam espaço na stack para as variaveis locais as funções. Segundo a ABI x86, a pilha deve ser alinhada a 4 bytes antes de chamadas de funções para garantir compatibilidade, mas 16 é preferivel.

## p4.c

### a)

```bash
./p4-v1
./p4-v2
./p4-v3
```

v1 e v3 funcionam, printando `foo`.
v3 falha pois nao consegue achar libp4.so em runtime. Para consertar, basta configurar a variavel de ambiente LD_LIBRARY_PATH com o caminho  do diretorio da biblioteca.

### b) 

v1: 15.020 bytes - Maior de todos., pois incorpora diretamente todos os objetos (.o) necessários na construção do binário.
v2: 14.980 bytes - Médio, pois linka somente o conteudo em uso.
v3: 14.924 bytes - O menor do tres, apenas referencia a biblioteca, sem incorporar ela no codigo.

### c) 

v1:
Os simbolos aparecem com `T`, pois estão presentes no executavel.

v2:
`foo` aprece com `T` mas `bar` não é listado, pois não foi incluido na linkagem.

v3:
`foo` aparece com `U` (undefined) pois vai ser resolvido em runtime. `bar` novamentee não aparece.

Ao todo:
É possível por meio dessa listagem notar quais elementos estão presentes em cada versão do código fonte.

### d) 

Distribuição para outros sistemas:
A linkagem stática facilita a distribuição pois centraliza o executavel em somente um arquivo, evitando a necessidade de tranportar tambem os `.o`.

Atualização de bibliotecas (b):
É mais fácila atualizar bibliotecas dinamicas, pois basta trocar um arquivo, sem precisar recompilar.

Uso compartilhado em um único sistema (c):
Bilbiotecas estáticas repetem código, tornando seu uso de memória pouco eficiente. Bibliotecas dinamicas reusam as mesmas depencencias, reduzindo a duplicação.


## dyn

### a)

Biblioteca copiada na compilação.
Vantagem: Facilita compartilhamento.
Desvantagem: Uso de memória ineficiente, processo de atualização dificil.

* Archive `.a` with object files
* Linked into executable at compile time
* No runtime dependencies
* Larger executable size, less flexible updates

### b) 

Biblioteca com relocação de código em tempo de execução.
Vantagem: Código compartilhado, uso de memória mais efetivo que bibliotecas estáticas.
Desvantagem: Carregamente mais lento devido a realocação.

### c) Dynamic library with position-independent code (PIC)

Biblioteca independente de posição.
Vantagem: Uso eficaz de memória. Facilidade de atualização. Preferivel atualmente.