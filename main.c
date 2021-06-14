/*
//Sistema de correção de gabaritos.
//Autores: Allan Schuh, Gustavo Roos, Gustavo Souza e João Victor.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"func.c"

int main()
{
  int op;
  int a;// TIRAR
  setlocale(LC_ALL, "");   // Função para reparar erros de codificação de caracteres no Windows




  // atualiza o valor as constantes SIZE_GAB e SIZE_ALU com o valor armazenado nos arquivos size_gabaritos e size_alunos
  Size();
  // Aloca espaço na memória para a célula responsável por armazenar dados do tipo gabarito de forma temporária
  ponteiro_gabarito = (gabarito *)malloc(SIZE_GAB * sizeof(gabarito));
  ponteiro_aluno = (aluno *)malloc(SIZE_ALU * sizeof(aluno));
  //ponteiro_login = (login *)malloc(SIZE_ALU * sizeof(login));
  // Carrega na Lista_Gabaritos os dados dos gabaritos salvos em arquivo. Cria o arquivo caso nao exista
  Lista_Gabaritos = Carrega_Gabaritos();
  Lista_Alunos = Carrega_Alunos();

//   LoginSimplesMuitoSimplesMesmo();
//   FirstRun();

  for(;;)
  {
      op = menu();

      switch (op)
      {
      case 1:
          Cadastrar();
          break;
      case 2:
          Mostrar();
          break;
      case 3:
          Excluir();
          break;
      case 4:
          Sobre();
          break;
      case 0:
          exit(0);
      break;
      }
  }


  return 0;
}
