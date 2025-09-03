# Parallel programming
## Task 1
### Localidade temporal e espacial de cache.
**Description**: Implemente duas versões da multiplicação de matriz por vetor (MxV) em C: uma com acesso à matriz por linhas (laço interno variando coluna) e outra por colunas (laço interno variando linha). Meça o tempo de execução de cada versão com uma função apropriada e execute testes com diferentes tamanhos de matriz. Identifique a partir de que tamanho os tempos passam a divergir significativamente e explique por que isso ocorre, relacionando suas observações com o uso da memória cache e o padrão de acesso à memória.

## Task 2
### Paralelismo ao nível de instrução
**Description**: Implemente três laços em C para investigar os efeitos do paralelismo ao nível de instrução (ILP).

- Inicialize um vetor com um cálculo simples;
- Some seus elementos de forma acumulativa, criando dependência entre as iterações;
- Quebre essa dependência utilizando múltiplas variáveis.

Compare o tempo de execução das versões compiladas com diferentes níveis de otimização (O0, O2, O3) e analise como o estilo do código e as dependências influenciam o desempenho. 

## Task 3
### Aproximação matemática de pi
**Description**: Implemente um programa em C que calcule uma aproximação de π usando uma série matemática, variando o número de iterações e medindo o tempo de execução. Compare os valores obtidos com o valor real de π e analise como a acurácia melhora com mais processamento. Reflita sobre como esse comportamento se repete em aplicações reais que demandam resultados cada vez mais precisos, como simulações físicas e inteligência artificial.

## Task 4
### Aplicações limitadas por memória ou CPU
**Description**: Implemente dois programas paralelos em C com OpenMP: um limitado por memória, com somas simples em vetores, e outro limitado por CPU, com cálculos matemáticos intensivos. Paralelize com #pragma omp parallel for e meça o tempo de execução variando o número de threads. Analise quando o desempenho melhora, estabiliza ou piora, e reflita sobre como o multithreading de hardware pode ajudar em programas memory-bound, mas atrapalhar em programas compute-bound pela competição por recursos.

## Task 5
### Comparação entre programação sequencial e paralela
**Description**: Implemente um programa em C que conte quantos números primos existem entre 2 e um valor máximo n. depois, paralelize o laço principal usando a diretiva #pragma omp parallel for sem alterar a lógica original. compare o tempo de execução e os resultados das versões sequencial e paralela. observe possíveis diferenças no resultado e no desempenho, e reflita sobre os desafios iniciais da programação paralela, como correção e distribuição de carga.