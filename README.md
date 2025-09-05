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

## Task 6
### Escopo de variáveis e regiões críticas
Implemente em C a estimativa estocástica de π. Paralelize com #pragma omp parallel for e explique o resultado incorreto. Corrija a condição de corrida utilizando o #pragma omp critical e reestruturando com #pragma omp parallel seguido de #pragma omp for e aplicando as cláusulas private, firstprivate, lastprivate e shared. Teste diferentes combinações e explique como cada cláusula afeta o comportamento do programa. Comente também como a cláusula default(none) pode ajudar a tornar o escopo mais claro em programas complexos.

## Task 7
### Processamento Paralelo de Lista Encadeada com OpenMP Task
Implemente um programa em C que cria uma lista encadeada com nós, cada um, contendo o nome de um arquivo fictício. Dentro de uma região paralela, percorra a lista e crie uma tarefa com #pragma omp task para processar cada nó. Cada tarefa deve imprimir o nome do arquivo e o identificador da thread que a executou. Após executar o programa, reflita: todos os nós foram processados? Algum foi processado mais de uma vez ou ignorado? O comportamento muda entre execuções? Como garantir que cada nó seja processado uma única vez e por apenas uma tarefa?

## Task 8
### Coerência de Cache e Falso Compartilhamento
Implemente estimativa estocástica de π usando rand() para gerar os pontos. Cada thread deve usar uma variável privada para contar os acertos e acumular o total em uma variável global com #pragma omp critical. Depois, implemente uma segunda versão em que cada thread escreve seus acertos em uma posição distinta de um vetor compartilhado. A acumulação deve ser feita em um laço serial após a região paralela. Compare o tempo de execução das duas versões. Em seguida, substitua rand() por rand_r() em ambas e compare novamente. Explique o comportamento dos quatro programas com base na coerência de cache e nos efeitos do falso compartilhamento.

## Task 9
### Regiões críticas nomeadas e Locks explícitos
Escreva um programa que cria tarefas para realizar N inserções em duas listas encadeadas, cada uma associada a uma thread. Cada tarefa deve escolher aleatoriamente em qual lista inserir um número. Garanta a integridade das listas evitando condição de corrida e, sempre que possível, use regiões críticas nomeadas para que a inserção em uma lista não bloqueie a outra. Em seguida, generalize o programa para um número de listas definido pelo usuário. Explique por que, nesse caso, regiões críticas nomeadas não são suficientes e por que o uso de locks explícitos se torna necessário.