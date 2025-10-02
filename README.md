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
**Description**: Implemente em C a estimativa estocástica de π. Paralelize com #pragma omp parallel for e explique o resultado incorreto. Corrija a condição de corrida utilizando o #pragma omp critical e reestruturando com #pragma omp parallel seguido de #pragma omp for e aplicando as cláusulas private, firstprivate, lastprivate e shared. Teste diferentes combinações e explique como cada cláusula afeta o comportamento do programa. Comente também como a cláusula default(none) pode ajudar a tornar o escopo mais claro em programas complexos.

## Task 7
### Processamento Paralelo de Lista Encadeada com OpenMP Task
**Description**: Implemente um programa em C que cria uma lista encadeada com nós, cada um, contendo o nome de um arquivo fictício. Dentro de uma região paralela, percorra a lista e crie uma tarefa com #pragma omp task para processar cada nó. Cada tarefa deve imprimir o nome do arquivo e o identificador da thread que a executou. Após executar o programa, reflita: todos os nós foram processados? Algum foi processado mais de uma vez ou ignorado? O comportamento muda entre execuções? Como garantir que cada nó seja processado uma única vez e por apenas uma tarefa?

## Task 8
### Coerência de Cache e Falso Compartilhamento
**Description**: Implemente estimativa estocástica de π usando rand() para gerar os pontos. Cada thread deve usar uma variável privada para contar os acertos e acumular o total em uma variável global com #pragma omp critical. Depois, implemente uma segunda versão em que cada thread escreve seus acertos em uma posição distinta de um vetor compartilhado. A acumulação deve ser feita em um laço serial após a região paralela. Compare o tempo de execução das duas versões. Em seguida, substitua rand() por rand_r() em ambas e compare novamente. Explique o comportamento dos quatro programas com base na coerência de cache e nos efeitos do falso compartilhamento.

## Task 9
### Regiões críticas nomeadas e Locks explícitos
**Description**: Escreva um programa que cria tarefas para realizar N inserções em duas listas encadeadas, cada uma associada a uma thread. Cada tarefa deve escolher aleatoriamente em qual lista inserir um número. Garanta a integridade das listas evitando condição de corrida e, sempre que possível, use regiões críticas nomeadas para que a inserção em uma lista não bloqueie a outra. Em seguida, generalize o programa para um número de listas definido pelo usuário. Explique por que, nesse caso, regiões críticas nomeadas não são suficientes e por que o uso de locks explícitos se torna necessário.

## Task 10
### Mecanismos de Sincronização com OpenMP
**Description**: Implemente novamente o estimador da tarefa 8 que usa um contador compartilhado e o rand_r substituindo o #pragma omp critical pelo #pragma omp atomic. Compare essas duas implementações com suas versões que usam contadores privados. Agora, compare essas com uma 5ª versão que utiliza apenas a cláusula reduction ao invés das diretivas de sincronização. Reflita sobre a aplicabilidade de desses mecanismos em termos de desempenho e produtividade e proponha um roteiro para quando utilizar qual mecanismo de sincronização, incluindo critical nomeadas e locks explícitos.

## Task 11
### Particionamento de dados e Balanceamento de carga
**Description**: Escreva um código que simule o movimento de um fluido ao longo do tempo usando a equação de Navier-Stokes, considerando apenas os efeitos da viscosidade. Desconsidere a pressão e quaisquer forças externas. Utilize diferenças finitas para discretizar o espaço e simule a evolução da velocidade do fluido no tempo. Inicialize o fluido parado ou com velocidade constante e verifique se o campo permanece estável. Em seguida, crie uma pequena perturbação e observe se ela se difunde suavemente. Após validar o código, paralelize-o com OpenMP e explore o impacto das cláusulas schedule e collapse no desempenho da execução paralela.

## Task 12
### Avaliação de escalabilidade
**Description**: Avalie a escalabilidade do seu código de Navier-Stokes utilizando algum nó de computação do NPAD. Procure identificar gargalos de escalabilidade e reporte o seu progresso em versões sucessivas da evolução do código otimizado. Comente sobre a escalabilidade, a escalabilidade fraca e a escalabilidade fortes das versões.

## Task 13
### Avaliação da Escalabilidade com Afinidade de Threads
**Description**: Avalie como a escalabilidade do seu código de Navier-Stokes muda ao utilizar os diversos tipos de afinidades de threads suportados pelo sistema operacional e pelo OpenMP no mesmo nó de computação do NPAD que utilizou para a tarefa 12.

## Task 14
### Programação em memória distribuída
**Description**: Implemente um programa MPI com exatamente dois processos. O processo 0 deve enviar uma mensagem ao processo 1, que imediatamente responde com a mesma mensagem. Meça o tempo total de execução de múltiplas trocas consecutivas dessa mensagem, utilizando MPI_Wtime. Registre os tempos para diferentes tamanhos, desde mensagens pequenas (como 8 bytes) até mensagens maiores (como 1 MB ou mais). Analise graficamente o tempo em função do tamanho da mensagem e identifique os regimes onde a latência domina e onde a largura de banda se torna o fator principal.

## Task 15
### Sobreposição de computação e comunicação
**Description**: Implemente uma simulação da difusão de calor em uma barra 1D, dividida entre dois ou mais processos MPI. Cada processo deve simular um trecho da barra com células extras para troca de bordas com vizinhos. Implemente três versões: uma com MPI_Send/ MPI_Recv, outra com MPI_Isend/ MPI_Irecv e MPI_Wait, e uma terceira usando MPI_Test para atualizar os pontos internos enquanto aguarda a comunicação. Compare os tempos de execução e discuta os ganhos com sobreposição de comunicação e computação.

## Task 16
### Implementação de Produto Matriz-Vetor Usando MPI
**Description**: Implemente um programa MPI que calcule o produto y=A⋅x, onde A é uma matriz M×N e x é um vetor de tamanho N. Divida a matriz A por linhas entre os processos com MPI_Scatter, e distribua o vetor x inteiro com MPI_Bcast. Cada processo deve calcular os elementos de y correspondentes às suas linhas e enviá-los de volta ao processo 0 com MPI_Gather. Compare os tempos com diferentes tamanhos de matriz e número de processos.

## Task 18
### Comparando soma de vetores entre CPU e GPU em OpenMP
**Description**: Faça os exercícios de adição de vetores, vadd.c, dos slides 27 e 48 do [tutorial de programação de GPUs com OpenMP](https://github.com/UoB-HPC/openmp-tutorial) em um dos nós com GPU do NPAD. Compare os tempos de execução somente na CPU e com o uso da GPU. Reporte seu progresso apresentando os problemas encontrados e as soluções apresentadas.

## Task 19
### Simulando transferência de calor em GPU com OpenMP
**Description**: Faça o exercício de transferência de calor (heat.c, slide 64) do [tutorial de programação de GPUs com OpenMP](https://github.com/UoB-HPC/openmp-tutorial). Explore as diretivas de paralelização e movimentação de dados para copiar dados entre host e dispositivo. Experimente com diferentes tamanhos de problema perfilando o programa com o nsys.
