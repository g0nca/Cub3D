Guião para Parsing do cub3D
1. Validação Inicial do Ficheiro
1.1 Verificação do Caminho

Verificar se recebeste exatamente 1 argumento (além do nome do programa)
Verificar se o argumento não é NULL ou string vazia
Verificar se o caminho não excede PATH_MAX (geralmente 4096)

1.2 Verificação da Extensão .cub

Verificar se o nome termina em ".cub"
ATENÇÃO: Não aceitar apenas ".cub" como nome (mínimo "a.cub")
ATENÇÃO: Verificar casos como "map.cub.txt" ou "map.cubb" (não devem passar)
ATENÇÃO: Verificar "map.cub/" (diretório com esse nome)
Verificar se tem pelo menos 5 caracteres (x.cub)

1.3 Verificação de Permissões e Existência

Verificar se o ficheiro existe (access com F_OK)
Verificar se tens permissões de leitura (access com R_OK)
Verificar se não é um diretório (stat + S_ISDIR)
Verificar se o ficheiro não está vazio (stat + st_size > 0)

2. Leitura do Ficheiro
2.1 Abertura e Leitura

Abrir o ficheiro com open()
Ler linha a linha com get_next_line
Guardar todas as linhas numa estrutura (array de strings ou lista)
Fechar o file descriptor

2.2 Tratamento de Linhas

Aceitar linhas vazias (apenas whitespace)
Preservar espaços dentro do mapa
Remover '\n' do final de cada linha
Verificar se não há caracteres estranhos (não ASCII ou não imprimíveis)

3. Parsing dos Elementos de Configuração
3.1 Texturas (NO, SO, WE, EA)

Verificar se cada elemento aparece exatamente uma vez
Podem aparecer em qualquer ordem
Podem ter espaços/tabs antes e depois do identificador
Formato: NO ./path/to/texture.xpm ou NO    ./path.xpm
ATENÇÃO: Verificar se o caminho da textura existe
ATENÇÃO: Verificar permissões de leitura das texturas
ATENÇÃO: Verificar extensão .xpm
ATENÇÃO: Verificar se não é um diretório
ATENÇÃO: Rejeitar múltiplos caminhos na mesma linha

3.2 Cores do Chão e Teto (F, C)

Verificar se cada elemento aparece exatamente uma vez
Formato: F 220,100,0 ou F 220, 100, 0 (espaços opcionais)
ATENÇÃO: Cada valor RGB deve estar entre 0 e 255
ATENÇÃO: Devem ser exatamente 3 valores separados por vírgulas
ATENÇÃO: Não aceitar valores negativos
ATENÇÃO: Não aceitar valores decimais (só inteiros)
ATENÇÃO: Não aceitar espaços a mais ou vírgulas duplicadas
ATENÇÃO: Formato: 255,255,255 não 255, 255, 255, (vírgula extra)

3.3 Ordem e Posicionamento

Todos os 6 elementos (NO, SO, WE, EA, F, C) devem aparecer antes do mapa
Podem ter linhas vazias entre eles
Não podem estar misturados com o mapa
ATENÇÃO: Elementos duplicados devem ser rejeitados

4. Parsing do Mapa
4.1 Identificação do Mapa

O mapa começa na primeira linha que contém caracteres '0', '1', ou posição do jogador
Todas as linhas após o início do mapa fazem parte do mapa
ATENÇÃO: Não podem existir linhas vazias no meio do mapa
ATENÇÃO: Não podem existir elementos de config depois do mapa começar

4.2 Caracteres Válidos

0 - espaço vazio (caminhável)
1 - parede
  - espaço (zona fora do mapa)
N, S, E, W - posição e orientação inicial do jogador
ATENÇÃO: Qualquer outro caractere é inválido

4.3 Validação do Jogador

Deve existir exatamente uma posição inicial do jogador
ATENÇÃO: Não pode haver 0 jogadores
ATENÇÃO: Não pode haver mais de 1 jogador
A posição do jogador deve estar num espaço válido (não numa parede)

4.4 Validação das Paredes (Mapa Fechado)

O mapa deve estar completamente cercado por paredes '1' ou espaços ' '
Todos os espaços '0' e posição do jogador devem estar rodeados por paredes
ATENÇÃO: Verificar bordas (primeira/última linha, primeira/última coluna)
ATENÇÃO: Verificar espaços ' ' no meio do mapa - não podem estar adjacentes a '0' ou jogador
ATENÇÃO: Usar flood fill ou algoritmo similar para verificar fechamento

4.5 Formato do Mapa

O mapa pode ter linhas de tamanhos diferentes (não retangular)
Linhas mais curtas são preenchidas com espaços ' ' conceitualmente
ATENÇÃO: Verificar que espaços vazios não criam "buracos" no mapa
Mapa deve ter pelo menos 3 linhas e 3 colunas de área jogável

5. Verificações Extra de Segurança
5.1 Limites do Mapa

Verificar tamanho máximo razoável (evitar mapas gigantes)
Verificar que não há overflow em cálculos de índices
Verificar que não há inteiros negativos onde não deviam existir

5.2 Memory Leaks

Garantir que libertas toda a memória alocada em caso de erro
Fechar todos os file descriptors abertos
Libertar estruturas parcialmente preenchidas

5.3 Mensagens de Erro

Cada tipo de erro deve ter uma mensagem clara
Formato: "Error\n" seguido de descrição do erro
Usar write() para stderr (fd 2)

6. Estrutura de Dados Sugerida
6.1 Guardar Configuração

Caminhos das 4 texturas (strings)
Cores RGB do chão (3 ints)
Cores RGB do teto (3 ints)

6.2 Guardar Mapa

Array 2D ou lista de strings
Largura e altura do mapa
Posição inicial do jogador (x, y)
Orientação inicial do jogador (N, S, E, W)

6.3 Flags de Validação

Booleanos para verificar se cada elemento foi encontrado
Contador de jogadores encontrados

7. Ordem de Operações Recomendada

Validar argumentos do programa
Validar extensão .cub
Validar permissões e existência do ficheiro
Ler ficheiro completo para memória
Parsear elementos de configuração (NO, SO, WE, EA, F, C)
Validar que todos os elementos estão presentes
Identificar onde começa o mapa
Parsear o mapa linha a linha
Validar caracteres do mapa
Validar jogador (existência e quantidade)
Validar paredes (mapa fechado)
Validar texturas (ficheiros existem e são acessíveis)
Retornar estrutura preenchida ou erro