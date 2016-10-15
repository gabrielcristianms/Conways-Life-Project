Este projeto é o jogo da vida de Conway, implementado em c++ como atividade para a disciplina LP1 ministrada pelo professor Selan.

Autores: Gabriel Cristian Melo da Silva
	   : Thiago da Costa Monteiro

Principais sites de referência utilizados:  http://en.cppreference.com/
											http://www.cplusplus.com/

O projeto é composto de três arquivos princiapais, que são o life.h, life.cpp e drive.cpp
Para compilar, mova o terminal para o diretório do projeto e execute o comando g++ -Wall -std=c++11 -I include src/life.cpp src/drive.cpp -o life

Não foi realizada documentação no estilo Doxygen, porém boa parte do código está comentado em inglês.

Todas as funções sugeridas foram implementadas e foi definido uma classe para representar configurações de grades de células.
A estabilidade é checada, a extinção é checada e as regras de evolução estão sendo aplicadas com sucesso.
A impressão é sempre em zeros e uns, onde um representa célula viva e zero representa célula morta. 

O programa não possui tratamento de erros usando exceções, apenas checagens condicionais são realizadas em operações que podem acarretar em problemas
e a maneira que o construtor inicializa colocando células a mais de enchimento evita erros de acesso além dos limites de memória alocada.

O que sentimos mais falta neste projeto foi arquivos de teste disponibilizados via sigaa.

Controle de versões feito usando git e o repositório utilizado foi o GitLab.