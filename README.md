# trabalho_sistemas_operacionais

O objetivo principal é gerenciar o acesso concorrente a um recurso compartilhado (um buffer de memória) entre múltiplas threads.

    Produtores: Threads que geram dados e os inserem no buffer.

    Consumidores: Threads que retiram dados do buffer para processá-los.

O desafio resolvido é garantir que produtores não escrevam em um buffer cheio e consumidores não leiam de um buffer vazio, evitando também condições de corrida (race conditions) onde duas threads tentam alterar o buffer simultaneamente.
