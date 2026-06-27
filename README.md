 Tsunade-Sama: Sistema Virtual de Robô Babá e Professora Infantil

<p align="right">
  <b>Disciplina: Estruturas de Dados</b><br>
  <b>Linguagem: C</b><br>
  <b>Autor: Grupo 10</b><br>
</p>

1. Conceito Fundamental de Funcionamento
A **Tsunade-Sama** opera sob um modelo de tomada de decisão autônoma avançada, assemelhando-se a uma arquitetura de Inteligência Artificial Real. O robô **nunca executa diretamente uma tarefa**. Em vez disso, diante de qualquer estímulo do ambiente ou do usuário (como a entrada da criança no sistema), o motor cognitivo gera uma lista dinâmica de possíveis ações (ex: cumprimentar, perguntar como a criança está, continuar a aula anterior, contar uma história ou mostrar uma missão). 

A seleção da ação ótima a ser executada em cada cenário é delegada a uma estrutura de **Heap Máxima**, que ordena as possibilidades de acordo com o peso de relevância e o estado contextual atual.

 Funcionalidades Atuais do Sistema (Status do Desenvolvimento)
* **Aprendizado Autônomo:** O sistema expande sua base de conhecimento de forma ativa através da interação com o ambiente, estruturando novos conceitos sem a necessidade de reinserção de código.
* **Memória de Longo Prazo (Persistência):** Utilizando mecanismos de persistência de dados, o robô lembra de toda a conversa e informações compartilhadas pelo usuário mesmo após o programa ser completamente encerrado e reiniciado. Se questionada sobre algo dito há muito tempo, ela recuperará a informação e a explicará.
* **Empatia e Monitoramento Emocional:** O sistema monitora de forma contínua o estado emocional da criança, adaptando seu comportamento, tom de resposta e prioridade de atividades para garantir o bem-estar psicológico e físico.

 2. Arquitetura de Estruturas de Dados Customizadas
O projeto foi modularizado utilizando as seguintes estruturas de dados complexas, todas implementadas do zero pelo grupo:

<table border="1" cellpadding="8" cellspacing="0" style="border-collapse: collapse; width: 100%; font-family: Arial, sans-serif; line-height: 1.25;">
  <thead>
    <tr style="background-color: #f2f2f2; font-weight: bold; text-align: left;">
      <th style="padding: 10px; width: 25%;">Estrutura</th>
      <th style="padding: 10px; width: 75%;">Utilização Técnica no Domínio do Robô</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <td style="font-weight: bold; padding: 10px;">Heap Máxima</td>
      <td style="padding: 10px;"><b>Escolha da melhor ação:</b> Responsável por processar a lista de possibilidades geradas e extrair instantaneamente ($O(1)$) o evento de maior prioridade a ser executado pelo robô.</td>
    </tr>
    <tr style="background-color: #f9f9f9;">
      <td style="font-weight: bold; padding: 10px;">BST (Binary Search Tree)</td>
      <td style="padding: 10px;"><b>Alertas de emergência:</b> Gerenciamento estrito de filas de prioridade para situações críticas (fogo, quedas, perigo ambiental), garantindo tratamento imediato de anomalias.</td>
    </tr>
    <tr>
      <td style="font-weight: bold; padding: 10px;">Árvore AVL</td>
      <td style="padding: 10px;"><b>Histórico escolar:</b> Armazenamento indexado temporalmente e balanceado dos logs de atividades e evolução do aprendizado da criança, mantendo operações em complexidade logarítmica ($O(\log n)$).</td>
    </tr>
    <tr style="background-color: #f9f9f9;">
      <td style="font-weight: bold; padding: 10px;">Hash Table</td>
      <td style="padding: 10px;"><b>Perfil da criança:</b> Cache e dicionário para armazenamento de dados sensíveis e fixos do perfil (nome, idade, restrições médicas/alergias e permissões) com busca em tempo constante médio $O(1)$.</td>
    </tr>
    <tr>
      <td style="font-weight: bold; padding: 10px;">Árvore Trie</td>
      <td style="padding: 10px;"><b>Comandos e intenções:</b> Árvore de prefixos utilizada no módulo de linguagem para mapear o vocabulário infantil, realizar autocomplete e interpretar a intenção semântica de comandos de voz via terminal.</td>
    </tr>
    <tr style="background-color: #f9f9f9;">
      <td style="font-weight: bold; padding: 10px;">Grafo (Estrutura 1)</td>
      <td style="padding: 10px;"><b>Máquina de Emoções:</b> Modelagem probabilística não-linear dos estados afetivos do robô e da criança, onde os nós são sentimentos e as arestas representam gatilhos e transições de humor.</td>
    </tr>
    <tr>
      <td style="font-weight: bold; padding: 10px;">Grafo (Estrutura 2)</td>
      <td style="padding: 10px;"><b>Rede de Conhecimento:</b> Representação de conceitos interligados que formam a ontologia e a base de fatos que o robô utiliza para ensinar e reter novos aprendizados coletados de forma autônoma.</td>
    </tr>
    <tr style="background-color: #f9f9f9;">
      <td style="font-weight: bold; padding: 10px;">Lista Duplamente Encadeada</td>
      <td style="padding: 10px;"><b>Memória episódica:</b> Linha do tempo sequencial e persistente que registra os eventos passados em ordem crônica, permitindo navegação bidirecional rápida pelas memórias do sistema.</td>
    </tr>
    <tr>
      <td style="font-weight: bold; padding: 10px;">Fila (Queue)</td>
      <td style="padding: 10px;"><b>Conversa recente:</b> Buffer circular/fila clássica encarregada de manter o histórico imediato do diálogo atual (as últimas linhas trocadas no terminal) para manter a coerência imediata do contexto.</td>
    </tr>
  </tbody>
</table>

<br>

 3. Integrantes do Grupo 10
* **[Paulo da Rosa]** - (20243965) -  Responsável pelo Repositório
* **[Cláudio Sousa]** - (20241264)
* **[André Muinga]** - (20240422)
