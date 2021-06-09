#include<stdio.h>
#include<stdlib.h>
#include <locale.h>
#include "func.c"




int main()
{

setlocale(LC_ALL, "");   // Função para reparar erros de codificação de caracteres no Windows

int op;

Size();   // atualiza o valor as constantes SIZE_GAB e SIZE_ALU com o valor armazenado nos arquivos size_gabaritos e size_alunos

// Aloca espaço na memória para a célula responsável por armazenar dados do tipo gabarito de forma temporária
ponteiro_gabarito = (gabarito *)malloc(SIZE_GAB * sizeof(gabarito));

// Aloca espaço na memória para a célula responsável por armazenar dados do tipo aluno de forma temporária
ponteiro_aluno = (aluno *)malloc(SIZE_ALU * sizeof(aluno));

Lista_Gabaritos = Carrega_Gabaritos(); // Carrega na Lista_Gabaritos os dados dos gabaritos salvos em arquivo. Cria o arquivo caso nao exista

Lista_Alunos = Carrega_Alunos();
// Laço de repetição infinito para exibição do menu

for(;;)
{
    op = menu();

    switch (op)
    {
    case 1:
        Cadastrar_Gabarito();
        break;
    case 2:
        Cadastrar_Aluno();
        break;
    case 3:
        Mostrar_Gabarito();
        break;
    case 4:

        break;
    case 5:
        Excluir();
        break;
    case 6:

        break;
    case 0:
        exit(0);
    break;
    }
}


return 0;

}
