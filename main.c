/*
//Sistema de correção de gabaritos.
//Autores: Allan Schuh, Gustavo Roos, Gustavo Souza e João Victor.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"func.h"

int main()
{
  int op;
  setlocale(LC_ALL, "");

  Primeira_Execucao();
  Size();
  ponteiro_gabarito = (gabarito *)malloc(SIZE_GAB * sizeof(gabarito));
  ponteiro_aluno = (aluno *)malloc(SIZE_ALU * sizeof(aluno));
  Lista_Gabaritos = Carrega_Gabaritos();
  Lista_Alunos = Carrega_Alunos();

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
