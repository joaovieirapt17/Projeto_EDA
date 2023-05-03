# Projeto_EDA

A essência deste projecto prende-se com o desenvolvimento de uma solução de software que permita agilizar a gestão (registo, partilha, utilização) de meios de mobilidade urbana num contexto de smart-city. A implementação da solução deverá considerar estruturas de dados dinâmicas, armazenamento de ficheiros, modularização e apresentar uma estruturação e documentação adequadas. Considerando dois tipos de utilizadores, nomeadamente gestores e clientes registados. 

1ª Fase:
1. Definição de uma estrutura de dados dinâmica (a ser previamente validada com o docente), para a representação dos meios de mobilidade eléctrica, clientes e gestores;
2. Armazenamento/leitura de dados em ficheiro de texto (valores de simulação) e binário (preservar dados);
3. Inserção de novos dados (cliente/gestor/meio de mobilidade eléctrica);
4. Remoção de determinados dados (cliente/gestor/meio de mobilidade eléctrica);
5. Modificação de determinados dados (cliente/gestor/modo de mobilidade eléctrica);
6. Registo do aluguer de um determinado meio de mobilidade eléctrica;
7. Listagem dos meios de mobilidade eléctrica por ordem decrescente de autonomia;
8. Listagem dos meios de mobilidade eléctrica existentes num local com um determinado geocódigo.


2ª Fase: 
1. Definição de uma estrutura de dados dinâmica para representar a localização de um conjunto de clientes e meios de mobilidade eléctrica, utilizando um grafo;
2. Armazenamento/leitura dos dados em ficheiros de texto (valores de simulação) e binários (preservar dados).
Dada a localização de um cliente, listar os meios de mobilidade eléctrica de um determinado tipo existentes num determinado raio;
3. Calcular uma solução (adaptação do problema do caixeiro viajante) da rota com a menor distância a percorrer, utilizando um camião, para recolher todos os meios de mobilidade eléctrica com carga de bateria inferior a 50%. O ponto de partida e de chegada é o mesmo. A capacidade de transporte do camião é limitada e dependente dos tipos de meios de mobilidade transportados, pelo que poderá ser necessário efectuar vários circuitos para completar a recolha destes meios de mobilidade eléctrica.
