#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"func.h"

int menu(void)
{
  //Esta função exibe o menu e retorna a opção escolhida pelo usuário

  int op;
//   system("clear");
  do
  {
    printf("\n\n ---------------Bem-vindo-----------------\n");
    printf("| 1.Cadastrar...                          |\n");
	  printf(" -----------------------------------------\n");
    printf("| 2.Mostrar...                            |\n");
  	printf(" -----------------------------------------\n");
	  printf("| 3.Excluir...                            |\n");
	  printf(" -----------------------------------------\n");
	  printf("| 4.Sobre                                 |\n");
	  printf(" -----------------------------------------\n");
    printf("| 0.Sair                                  |\n");
	  printf(" -----------------------------------------\n");
    printf("\nInforme a opção: ");
    scanf("%d", &op);
    getchar();

    // Checa se a opção é válida

    if(op < 0 || op > 4)
    printf("\n---Opcao invalida!---\n");
  }while(op < 0 || op > 4 );

   // Verifica se o usuário quer mesmo finalizar o programa

    if( op == 0){
      int dec = 0;
	  printf("\n------------------\n");
      printf("\nDeseja mesmo sair?\n1 - Sim 2 - Não: ");
      scanf("%d", &dec);
      if(dec == 2)
        op = 5;
      system("clear");
    }

  if(op != 0 && op != 5){
	  system("clear");
    printf("\nFunção Escolhida: %d\n", op);
	}
  else if(op == 0)
    printf("Fim do Programa.\n");

  return op;
}

void Cadastrar()
{
	int op;
  system("clear");
  do
  {
    printf("\n\n ----------Cadastrar----------\n");
    printf("| 1.Gabarito                   |\n");
    printf(" -----------------------------\n");
    printf("| 2.Aluno                      |\n");
    printf(" -----------------------------\n");
    printf("| 0.Voltar                     |\n");
    printf(" -----------------------------\n\nSua escolha: ");
    scanf("%d", &op);

    switch (op)
    {
    case 1:
        Cadastrar_Gabarito();
        system("clear");
        break;
    case 2:
        Cadastrar_Aluno();
        system("clear");
        break;
    case 0:
        system("clear");
        break;
    default:
    system("clear");
    printf("Opção inválida!");
    break;
    }
   }while(op < 0 || op > 2);
}

void Cadastrar_Gabarito()
{
    // Esta função recolhe os dados de uma prova (chave, numero de questões, gabarito) e dá a opção de salvá-los ou não
    // Os dados temporários (para serem salvos ou não) são armazenados em uma célula criada para este fim no início do programa
    // Esta célula é do tipo gabarito e é referenciada pelo ponteiro "ponteiro_gabarito"

   int i, op, testID, existe = 0;
   gabarito *celula;
   do
    {
      testID = 0; 
	  //LoginRequest();
    	do
      	{
        existe = 0;
        printf("\n\tChave de acesso da prova (de 1111 a 9999): ");
        scanf("%d", &ponteiro_gabarito->codGabarito);
        system("clear");

        // Verifica se a informação digitada é válida. Permite apenas números de 4 dígitos que não comecem com zeros

        while (ponteiro_gabarito->codGabarito < 1111 || ponteiro_gabarito->codGabarito > 9999)
        {
            printf("\n\tChave de acesso deve estar entre 1111 e 9999.\n\tPor favor digite novamente: ");
            scanf("%d", &ponteiro_gabarito->codGabarito);
            system("clear");
        }
        for(celula = Lista_Gabaritos, i = 0; celula->prox != NULL; celula = celula->prox, i++)
            {
              if(ponteiro_gabarito->codGabarito == celula->codGabarito){ 
              printf("\n\t\tChave já registrada! %d\n", ponteiro_gabarito->codGabarito);
              existe = 1;
              }
            }
      }while(existe != 0);

      printf("\n\tTotal de questões da prova (Entre %d e %d): ", RESPOSTAS_MIN, RESPOSTAS_MAX);
      scanf("%d", &ponteiro_gabarito->totalQuestao);
      //system("clear");

        // Verifica se a informação digitada é válida

      while(ponteiro_gabarito->totalQuestao < RESPOSTAS_MIN || ponteiro_gabarito->totalQuestao > RESPOSTAS_MAX)
      {
        printf("\n\tTotal de questões da prova deve estar entre %d e %d.\n\tPor favor digite novamente: ", RESPOSTAS_MIN, RESPOSTAS_MAX);
        scanf("%d", &ponteiro_gabarito->totalQuestao);
        //system("clear");
      }

        // Colhe as respostas das questões e verifica se as mesmas são válidas, comparando os dados "char" com seus respectivos
        // códigos da tabela ASC II ('A' = 65 e 'E' = 69)

      for(i = 0; i < ponteiro_gabarito->totalQuestao; i++)
      {
        do
        {
          printf("\nQuestão %d: ", i+1);
          scanf("%s", &ponteiro_gabarito->resposta[i]);

          if((ponteiro_gabarito->resposta[i] < 65 || ponteiro_gabarito->resposta[i] > 69) && ponteiro_gabarito->resposta[i] != 'X')
          printf("\nInvalida\n");

          }while((ponteiro_gabarito->resposta[i] < 65 || ponteiro_gabarito->resposta[i] > 69) && ponteiro_gabarito->resposta[i] != 'X');

          printf("Resposta cadastrada.\n");  // Confirma que a resposta foi cadastrada.
        }
        system("clear");

        // Exibe todas as informações inseridas para fins de revisão

        printf("Revise as informações:\n");
        Imprime_Gabarito(ponteiro_gabarito);

        // Dá a opção de salvar ou não o gabarito e verifica se a opção é válida

        do
        {
          printf("\nDeseja salvar este gabarito?\n1.Sim 2.Não\n\nSua escolha: ");
          scanf("%d", &op);
          if (op < 1 || op > 2)
          {
            system("clear");
            printf("Opção inválida!\n");
          }
        }while(op < 1 || op > 2);

        if(op == 1)
        {
          Salvar_Gabarito();
          system("clear");
          printf("Gabarito salvo com sucesso!\n");
        }
        else if(op == 2)
        {
          system("clear");
          printf("Este gabarito não foi salvo...\n");
        }

        // Dá a opção de cadastrar ou não outro gabarito e verifica se a opção é válida

        do
        {
          printf("\nDeseja cadastrar outro gabarito?\n1.Sim 2.Não\n\nSua escolha: ");
          scanf("%d", &op);
          if (op < 1 || op > 2)
          {
            system("clear");
            printf("Opção inválida!\n");
          }
        }while (op < 1 || op > 2);

        if(op == 1)
        {
          system("clear");
          testID = 1;
        }
	}while(testID);   // Testa a variável de controle da repetição da função}
	
  system("clear");
}

void Cadastrar_Aluno()
{

    int i, op, testID = 0, chave_gabarito;
	gabarito *celula;

    if(SIZE_GAB == 0)
    {
        printf("\n\tImpossível cadastrar um novo aluno pois ainda não há nenhum gabarito cadastrado.\n\n\tPressione ENTER para continuar...");
        while(getchar())
            break;
        getchar();
    }
    else
        testID = 1;

    while(testID)
    {
        testID = chave_gabarito = 0;

        printf("\n\tDigite sua matrícula (8 dígitos): "); scanf("%d", &ponteiro_aluno->matricula);

        while (ponteiro_aluno->matricula < 11111111 || ponteiro_aluno->matricula > 99999999)
        {
            printf("\n\tNúmero de matrícula deve estar entre 11111111 e 99999999.\n\tPor favor digite novamente: ");
            scanf("%d", &ponteiro_aluno->matricula);
            system("clear");
        }

        getchar();
        aluno *auxiliar = Busca_Alu(ponteiro_aluno->matricula, Lista_Alunos);
        if(auxiliar == NULL)
        {
            printf("\n\tDigite seu nome: "); scanf("%[^\n]%*c", ponteiro_aluno->nome);
        }
        else
        {
            strcpy(ponteiro_aluno->nome, auxiliar->nome);
            printf("\n\tMatrícula encontrada! Cadastrar uma nova prova para %s:\n", ponteiro_aluno->nome);
        }


        printf("\n\tChave de acesso da prova (de 1111 a 9999): "); scanf("%d", &ponteiro_aluno->codGabarito);
        system("clear");

        while (ponteiro_aluno->codGabarito < 1111 || ponteiro_aluno->codGabarito > 9999)
        {
            printf("\n\tChave de acesso deve estar entre 1111 e 9999.\n\tPor favor digite novamente: ");
            scanf("%d", &ponteiro_aluno->codGabarito);
            system("clear");
        }

        chave_gabarito = ponteiro_aluno->codGabarito;

        ponteiro_aluno->totalQuestao = Busca_TotalQuest(chave_gabarito);

        while (ponteiro_aluno->totalQuestao == -1){
            printf("\n\tChave de gabarito não cadastrada!\n\tGabaritos cadastrados:\n");
            for (celula = Lista_Gabaritos, i = 0; celula->prox != NULL; celula = celula->prox, i++){
                printf("\n -------------------------------------\n");
                printf("\n\tGabarito %d:\n", i+1);
                printf("\n\tCódigo da prova: %d", celula->codGabarito);
                printf("\n\tNúmero de questões: %d\n", celula->totalQuestao);
                printf("\n");
            }
            printf("\n\tTente novamente: "); scanf("%d", &ponteiro_aluno->codGabarito);
            chave_gabarito = ponteiro_aluno->codGabarito;
            ponteiro_aluno->totalQuestao = Busca_TotalQuest(chave_gabarito);
        }

        system("clear");
        printf("\n\tGabarito encontrado, chave %d\n", chave_gabarito);
        printf("\n\tA prova possui %d questões, preencha-as abaixo em ordem:\n", ponteiro_aluno->totalQuestao);

        for(i = 0; i < ponteiro_aluno->totalQuestao; i++)
        {
            do
            {
                printf("\nQuestão %d: ", i+1);
                scanf("%s", &ponteiro_aluno->resposta[i]);

                if((ponteiro_aluno->resposta[i] < 65 || ponteiro_aluno->resposta[i] > 69) && ponteiro_aluno->resposta[i] != 'X')
                printf("\nInvalida\n");

            }while((ponteiro_aluno->resposta[i] < 65 || ponteiro_aluno->resposta[i] > 69) && ponteiro_aluno->resposta[i] != 'X');

            printf("Resposta cadastrada.\n");
        }

        system("clear");

        printf("Revise as informações:\n");
		Imprime_AlunoAntes(ponteiro_aluno, 0);
		

        do
        {
            printf("\nDeseja salvar estas respostas para essa prova?\n1.Sim 2.Não\n\nSua escolha: ");
            scanf("%d", &op);
            if (op < 1 || op > 2)
            {
                system("clear");
                printf("Opção inválida!\n");
            }
        }while(op < 1 || op > 2);

        if(op == 1)
        {
			ponteiro_aluno->acertos = 0;
			Corrige_Prova();
			Salvar_Aluno(); 
			Imprime_Aluno(ponteiro_aluno, 0);
			Posicao(ponteiro_aluno->codGabarito);
			system("clear");
			printf("\n\tO seu gabarito desta prova foi salvo com sucesso!\n");
            
        }
        else if(op == 2)
        {
            system("clear");
            printf("\n\tEste gabarito não foi salvo...\n");
        }

        do
        {
            printf("\n\tDeseja cadastrar outra prova?\n\t1.Sim 2.Não\n\n\tSua escolha: ");
            scanf("%d", &op);
            if (op < 1 || op > 2)
            {
                system("clear");
                printf("\n\tOpção inválida!\n");
            }
        } while (op < 1 || op > 2);

        if (op == 1)
        {
            system("clear");
            testID = 1;
			getchar();
        }
    }

        system("clear");
}

void Mostrar()
{
	int op;
    system("clear");
        do
        {
            printf("\n\n -----------Mostrar-----------\n");
            printf("| 1.Mostrar aluno             |\n");
            printf(" -----------------------------\n");
            printf("| 2.Mostrar gabarito          |\n");
            printf(" -----------------------------\n");
            printf("| 3.Mostrar estatística       |\n");
            printf(" -----------------------------\n");
            printf("| 0.Voltar                    |\n");
            printf(" -----------------------------\n\nSua escolha: ");
            scanf("%d", &op);

            switch (op)
            {
            case 1:
                Mostrar_Aluno();
                break;
            case 2:
                Mostrar_Gabarito();
                break;
            case 3:
                MostarEstatisca();
                break;
            case 0:
                system("clear");
                break;
            default:
                system("clear");
                printf("Opção inválida!");
                break;
            }
            }while(op < 0 || op > 3);
}

void Mostrar_Gabarito()
{
    int op;
    system("clear");
        do
        {
            printf("\n\n ------Mostrar Gabarito-------\n");
            printf("| 1.Pesquisar                 |\n");
            printf(" -----------------------------\n");
            printf("| 2.Mostrar todos             |\n");
            printf(" -----------------------------\n");
            printf("| 0.Voltar                    |\n");
            printf(" -----------------------------\n\nSua escolha: ");
            scanf("%d", &op);

            switch (op)
            {
            case 1:
                Pesquisar_Gabarito();
                system("clear");
                break;
            case 2:
                system("clear");
                Imprime_Todos_Gabaritos();
                printf("\n\nPressione ENTER para continuar...");
                getchar();
                getchar();
                system("clear");
                break;
            case 0:
                system("clear");
                break;
            default:
                system("clear");
                printf("Opção inválida!");
                break;
            }
            }while(op < 0 || op > 2);

}

void Mostrar_Aluno()
{
    int op;
    system("clear");
        do
        {
            printf("\n\n --------Mostrar Aluno--------\n");
            printf("| 1.Pesquisar                 |\n");
            printf(" -----------------------------\n");
            printf("| 2.Mostrar todos             |\n");
            printf(" -----------------------------\n");
            printf("| 0.Voltar                    |\n");
            printf(" -----------------------------\n\nSua escolha: ");
            scanf("%d", &op);

            switch (op)
            {
            case 1:
                Pesquisar_Aluno();
                system("clear");
                break;
            case 2:
                system("clear");
                Imprime_Todos_Alunos();
                printf("\n\nPressione ENTER para continuar...");
                getchar();
                getchar();
                system("clear");
                break;
            case 0:
                system("clear");
                break;
            default:
                system("clear");
                printf("Opção inválida!");
                break;
            }
            }while(op < 0 || op > 2);
}

void Pesquisar_Gabarito()
{

    // Esta função exibe os dados do gabarito correspondente ao código informado pelo usuário

    int testID, op;
    gabarito *end_gabarito;   // Declaração de um ponteiro para armazenar o endereço do gabarito informado

    do
    {
        testID = 0;   // Variável para controlar a repetição da função
        system("clear");

        // Lê o codigo do gabarito a ser pesquisado e armazena na célula para dados temporários

        printf("\n\tInforme uma chave de gabarito válida(de 1111 a 9999): ");
        scanf("%d", &ponteiro_gabarito->codGabarito);
        system("clear");

        // Verifica se a informação digitada é válida. Permite apenas números de 4 dígitos que não comecem com zeros

        while (ponteiro_gabarito->codGabarito < 1111 || ponteiro_gabarito->codGabarito > 9999)
        {
            printf("\n\tChave de gabarito inválida! Tente novamente: ");
            scanf("%d", &ponteiro_gabarito->codGabarito);
            system("clear");
        }

        // Ponteiro recebe o endereço do gabarito retornado pela função de busca

        end_gabarito = Busca_Gab(ponteiro_gabarito->codGabarito);

        // Se o gabarito existir, exibe os dados do mesmo. Senão, informa que não existe

        if (end_gabarito == NULL)
            printf("\n\tChave de gabarito não cadastrada!\n");
        else
        {
            system("clear");
            printf("\n\tGabarito encontrado:\n");
            Imprime_Gabarito(end_gabarito);       // Função para imprimir o gabarito pelo endereço informado
        }

        // Verifica se o usuário deseja fazer outra busca

        do
        {
            printf("\n\tDeseja procurar outro gabarito?\n\t1.Sim 2.Não\n\nSua escolha: ");
            scanf("%d", &op);
            if (op < 1 || op > 2)
            {
                system("clear");
                printf("\n\tOpção inválida!\n");
            }
        } while (op < 1 || op > 2);

        if (op == 1)
        {
            system("clear");
            testID = 1;
        }
    } while (testID);   // Testa a variável de controle da repetição da função
}

void Pesquisar_Aluno()
{
    int testID, op;
    aluno *end_aluno;

    do
    {
        testID = 0;
        system("clear");

        getchar();
        printf("\n\tDigite a matricula do aluno: "); scanf("%d", &ponteiro_aluno->matricula);
        system("clear");

        while (ponteiro_aluno->matricula < 11111111 || ponteiro_aluno->matricula > 99999999)
        {
            printf("\n\tMatrícula inválida! Tente novamente: ");
            scanf("%d", &ponteiro_aluno->matricula);
            system("clear");
        }

		end_aluno = Busca_Alu(ponteiro_aluno->matricula, Lista_Alunos);

		if (end_aluno == NULL)
			printf("\n\tAluno não cadastrado!\n");
		else
		{
			system("clear");
			printf("\n\tAluno encontrado:\n");
			Imprime_Aluno(end_aluno, 0);
		}

    while(end_aluno != NULL)
    {
        end_aluno = Busca_Alu(ponteiro_aluno->matricula, end_aluno->prox);
        if(end_aluno != NULL)
            Imprime_Aluno(end_aluno, 1);
    }

        // Verifica se o usuário deseja fazer outra busca

    do
    {
      printf("\n\tDeseja procurar outro aluno?\n\t1 - Sim 2 - Não\n\n\tSua escolha: ");
      scanf("%d", &op);
      if (op < 1 || op > 2)
      {
        system("clear");
        printf("\n\tOpção inválida!\n");
      }
    } while (op < 1 || op > 2);

    if (op == 1)
    {
      system("clear");
      testID = 1;
    }
    } while (testID);   // Testa a variável de controle da repetição da função
}

gabarito *Busca_Gab(int codigo)
{
    // Esta função percorre a lista de gabaritos procurando pelo código passado por parâmetro. Se encontra, retorna o endereço deste gabarito. Senão, retorna NULL

    int i;
    gabarito *celula = Lista_Gabaritos;   // Declara um ponteiro para armazenar endereços temporários do tipo gabarito e associa ao endereço inicial da lista de gabaritos

    // Percorre a lista e compara o código informado aos códigos dos gabaritos

    for (i = 0; i < SIZE_GAB; i++, celula = celula->prox)
    {
        if (codigo == celula->codGabarito)
        {
            return celula;
        }
    }
    return NULL;
}

aluno *Busca_Alu(int matricula, aluno *inicio_da_pesquisa)
{
    aluno *celula;

    for (celula = inicio_da_pesquisa; celula->prox != NULL; celula = celula->prox)
    {
        if (matricula == celula->matricula)
        {
            return celula;
        }
    }
    return NULL;
}

void Excluir()
{
    int op;
    system("clear");
        do
        {
            printf("\n\n ----------Excluir------------\n");
            printf("| 1.Gabarito                  |\n");
            printf(" -----------------------------\n");
            printf("| 2.Aluno                     |\n");
            printf(" -----------------------------\n");
            printf("| 0.Voltar                    |\n");
            printf(" -----------------------------\n\nSua escolha: ");
            scanf("%d", &op);

            switch (op)
            {
            case 1:
                Exclusao_Gabarito();
                system("clear");
                break;
            case 2:
                Exclusao_Aluno();
                system("clear");
                break;
            case 0:
                system("clear");
                break;
            default:
                system("clear");
                printf("Opção inválida!");
                break;
            }
            }while(op < 0 || op > 2);
}

void Exclusao_Gabarito()
{
    int i, codGabarito, testId = 1;
    system("clear");
    printf("\n\n -------Excluir Gabarito------\n");
    printf("\nDigite a chave do gabarito a ser removido (4 dígitos): "); scanf("%d", &codGabarito);

    while (codGabarito < 1111 || codGabarito > 9999)
    {
        printf("\nChave do gabarito deve estar entre 1111 e 9999.\nPor favor digite novamente: ");
        scanf("%d", &codGabarito);
        system("clear");
    }

    for(i = 0, ponteiro_gabarito = Lista_Gabaritos; i < SIZE_GAB; i++, ponteiro_gabarito = ponteiro_gabarito->prox)
        if(ponteiro_gabarito->codGabarito == codGabarito)
        {
            testId = 0;
            break;
        }

	if(testId)
	{
        printf("\n\tChave de gabarito inválida!");
    }
    else
    {
        Excluir_Gab(codGabarito);
        printf("\nGabarito removido com sucesso.\n");
    }
    printf("\n\nPressione ENTER para continuar...");
    getchar();
    getchar();
}



void Excluir_Gab(int codGabarito)
{
    FILE *fp;
    gabarito *excluirGab;
    aluno *excluirAlu, *celula;
    int i;

        for(ponteiro_gabarito = Lista_Gabaritos; ponteiro_gabarito->prox != NULL; ponteiro_gabarito = ponteiro_gabarito->prox)
        if(ponteiro_gabarito->codGabarito == codGabarito)
        {
            Lista_Gabaritos = Lista_Gabaritos->prox;
            excluirGab = ponteiro_gabarito;
            break;
        }
        else if(ponteiro_gabarito->prox->codGabarito == codGabarito)
        {
            excluirGab = ponteiro_gabarito->prox;
            ponteiro_gabarito->prox = ponteiro_gabarito->prox->prox;
            break;
        }

        SIZE_GAB--;
        free(excluirGab);

    fp = fopen("resources/gabaritos.txt", "w");
    if(fp == NULL){
        fprintf(stderr, "\nErro arquivo gabaritos.txt.\n");
        exit(0);
    }
    ponteiro_gabarito = Lista_Gabaritos;
    for(i = 0; i < SIZE_GAB; i++, ponteiro_gabarito = ponteiro_gabarito->prox){
        fprintf(fp , "%d %d %s\n", ponteiro_gabarito->codGabarito, ponteiro_gabarito->totalQuestao, ponteiro_gabarito->resposta);
    }
    fclose(fp);

    while(i != SIZE_ALU)
    {
        for(celula = Lista_Alunos, i = 0; i < SIZE_ALU; i++, celula = celula->prox)
        {
            if(celula->codGabarito == codGabarito)
            {
                Lista_Alunos = Lista_Alunos->prox;
                free(celula);
                SIZE_ALU--;
                break;
            }
            else if(celula->prox->codGabarito == codGabarito)
            {
                excluirAlu = celula->prox;
                celula->prox = celula->prox->prox;
                SIZE_ALU--;
                free(excluirAlu);
                break;
            }
        }
    }

    fp = fopen("resources/alunos.txt", "w");
    if(fp == NULL){
        fprintf(stderr, "\nErro arquivo alunos.txt.\n");
        exit(0);
    }

    ponteiro_aluno = Lista_Alunos;
    if(ponteiro_aluno != NULL)
        for(i = 0; i < SIZE_ALU; i++, ponteiro_aluno = ponteiro_aluno->prox){
            fprintf(fp , "%d %d %d %d %s %s %s\n", ponteiro_aluno->matricula, ponteiro_aluno->codGabarito, ponteiro_aluno->totalQuestao, ponteiro_aluno->acertos, ponteiro_aluno->resposta, ponteiro_aluno->correcao, ponteiro_aluno->nome);
        }
    fclose(fp);

    Update_Size();
}


void Exclusao_Aluno()
{
    int i, matricula, testId = 1;
    system("clear");
    printf("\n\n -------Excluir Aluno------\n");
    printf("\nDigite a matrícula do aluno a ser removido (8 dígitos): "); scanf("%d", &matricula);

    while (matricula < 11111111 || matricula > 99999999)
    {
        printf("\nNúmero de matrícula deve estar entre 11111111 e 99999999.\nPor favor digite novamente: ");
        scanf("%d", &matricula);
        system("clear");
    }

    for(i = 0, ponteiro_aluno = Lista_Alunos; i < SIZE_ALU; i++, ponteiro_aluno = ponteiro_aluno->prox)
        if(ponteiro_aluno->matricula == matricula)
        {
            testId = 0;
            break;
        }

	if(testId)
	{
        printf("\n\tMatrícula inválida!");
    }
    else
    {
        printf("\nAluno %s foi removido com sucesso.\n", ponteiro_aluno->nome);
        Excluir_Alu(matricula);
    }
    printf("\n\nPressione ENTER para continuar...");
    getchar();
    getchar();
}


void Excluir_Alu(int matricula)
{
    FILE *fp;
    aluno *excluir;
    int i;

    excluir = Busca_Alu(matricula, Lista_Alunos);

    while(excluir != NULL)
    {
        for(i = 0, ponteiro_aluno = Lista_Alunos; i < SIZE_ALU; i++, ponteiro_aluno = ponteiro_aluno->prox)
        if(ponteiro_aluno == excluir)
        {
            Lista_Alunos = Lista_Alunos->prox;
            break;
        }
        else if(ponteiro_aluno->prox == excluir)
        {
            ponteiro_aluno->prox = ponteiro_aluno->prox->prox;
            break;
        }

        SIZE_ALU--;
        free(excluir);
        excluir = Busca_Alu(matricula, ponteiro_aluno);
    }

    fp = fopen("resources/alunos.txt", "w");
    if(fp == NULL){
        fprintf(stderr, "\nErro arquivo alunos.txt.\n");
        exit(0);
    }
    ponteiro_aluno = Lista_Alunos;
    for(i = 0; i < SIZE_ALU; i++, ponteiro_aluno = ponteiro_aluno->prox){
        fprintf(fp , "%d %d %d %d %s %s %s\n", ponteiro_aluno->matricula, ponteiro_aluno->codGabarito, ponteiro_aluno->totalQuestao, ponteiro_aluno->acertos, ponteiro_aluno->resposta, ponteiro_aluno->correcao, ponteiro_aluno->nome);
    }
    fclose(fp);

    Update_Size();
}


int Busca_TotalQuest(int codigo)
{
    int i;
    gabarito *celula = Lista_Gabaritos;   

    for (i = 0; i < SIZE_GAB; i++, celula = celula->prox)
    {
        if (codigo == celula->codGabarito)
        {
            return celula->totalQuestao;
        }
    }
    return (-1);
}

void Salvar_Gabarito()
{
    // Esta função salva de fato o gabarito, anexando seus dados na próxima linha em branco do arquivo de salvamento
    // Os dados a serem salvos estão temporariamente armazenados na célula apontada pelo ponteiro "ponteiro_gabarito"

    FILE *fp;         // Ponteiro de stream

    fp = fopen("resources/gabaritos.txt", "a");     // Abre arquivo para anexar informações

    // Verifica e avisa se houve algum erro ao abrir a stream "fp" com o arquivo

    if(fp == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo gabaritos.txt..\n");
        exit(0);
    }

    // Imprime no arquivo os dados separados por espaços

    fprintf(fp,"%d %d %s\n", ponteiro_gabarito->codGabarito, ponteiro_gabarito->totalQuestao, ponteiro_gabarito->resposta);
    SIZE_GAB++;         // Incrementa constante que armazena a quantidade de gabaritos salvos
    Update_Size();      // Salva os dados da constante SIZE_GAB no arquivo size_gabaritos
    fclose(fp);         // Fecha a stream com o arquivo de gabaritos
    Limpar_Memoria_Gab(Lista_Gabaritos);     // Limpa a lista que contém os dados dos gabaritos (desatualizada)
    Lista_Gabaritos = Carrega_Gabaritos();   // Carrega na lista os dados dos gabaritos recém atualizados do arquivo

}

void Salvar_Aluno()
{
    FILE *fp;
    int i;

    fp = fopen("resources/alunos.txt", "a");

    if(fp == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo alunos.txt..\n");
        exit(0);
    }

    fprintf(fp,"%d %d %d %d %s ", ponteiro_aluno->matricula, ponteiro_aluno->codGabarito, ponteiro_aluno->totalQuestao, ponteiro_aluno->acertos, ponteiro_aluno->resposta);
    for (i = 0; i < ponteiro_aluno->totalQuestao; i++)
        fputc(ponteiro_aluno->correcao[i], fp);
    fprintf(fp," %s\n", ponteiro_aluno->nome);
    SIZE_ALU++;
    Update_Size();
    fclose(fp);
    Limpar_Memoria_Alu(Lista_Alunos);
    Lista_Alunos = Carrega_Alunos();
}

gabarito *Carrega_Gabaritos()
{
    // Esta função cria uma lista sem cabeça, lê os dados de gabaritos do arquivo em que estão salvos,
    // armazena esses dados na lista e retorna um ponteiro para o início dessa lista

    FILE *fp;   // Ponteiro de stream
    int i;
	gabarito *inicio, *celula;

	// "*inicio" é o ponteiro que armazena o começo da lista e *celula o endereço da celula atual, onde serão gravadas as informações

    celula = (gabarito *) malloc(sizeof(gabarito));     // Aloca espaço para uma celula de dados da struct gabarito
    inicio = celula;      // Define a celula atual como a primeira



    fp = fopen("resources/gabaritos.txt","a+");   // Abre arquivo para leitura e anexar informações. Caso o arquivo ainda não exista, será criado

    // Verifica e avisa se houve algum erro ao abrir a stream "fp" com o arquivo

	if(fp == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo gabaritos.txt.\n");
        exit(0);
    }

    // Copia para a lista os tres dados (inteiro, inteiro e string de chars) de cada linha do arquivo, desconsiderando o '/n'

    for(i = 0; i < SIZE_GAB; i++, celula = celula->prox){
		fscanf(fp,"%d %d %[^\n]s", &celula->codGabarito, &celula->totalQuestao, celula->resposta);
		celula->prox = (gabarito *) malloc(sizeof(gabarito));   // Aloca espaço para a próxima célula da lista
		celula->prox->prox = NULL;    // Define o endereço da proxima celula da célula recém alocada como NULL, identificando-a como última da lista
	}

    fclose(fp);       // Fecha a stream com o arquivo de gabaritos
	return (gabarito *)inicio;          // Retorna um ponteiro para o início da lista criada na função
}

aluno *Carrega_Alunos()
{
    FILE *fp;  
    int i, j, k;
	aluno *inicio, *celula;

    celula = (aluno *) malloc(sizeof(aluno));     
    inicio = celula;      

    fp = fopen("resources/alunos.txt","a+");   

	if(fp == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo alunos.txt.\n");
        exit(0);
  }

    for(i = 0; i < SIZE_ALU; i++, celula = celula->prox){

		fscanf(fp,"%d %d %d %d ", &celula->matricula, &celula->codGabarito, &celula->totalQuestao, &celula->acertos);

	for (k = 0; k <= celula->totalQuestao; k++)
	{
		celula->resposta[k] = fgetc(fp);
	}
	celula->resposta[k-1] = '\0';
	
    for(j = 0; j <= celula->totalQuestao; j++){
    	celula->correcao[j] = fgetc(fp);
	}
	celula->correcao[j-1] = '\0';
	
	fscanf(fp,"%[^\n]%*c", celula->nome);
	celula->prox = (aluno *) malloc(sizeof(aluno));
	celula->prox->prox = NULL;
	}

    fclose(fp);       
	return (aluno *)inicio;          
}

void Imprime_Gabarito(gabarito *end_gabarito)
{
  int i;
    // Esta função imprime os dados de um determinado gabarito, passando por parâmetro seu endereço

    // Imprime os dados

    printf("\n\tCódigo da prova: %d", end_gabarito->codGabarito);
    printf("\n\tNúmero de questões: %d\n", end_gabarito->totalQuestao);
    printf("\n\tRespostas:\n");
    for (i = 0; i < end_gabarito->totalQuestao; i++)
      printf("\n\tQuestão %d: %c", i+1, end_gabarito->resposta[i]);
    printf("\n");
}

void Imprime_AlunoAntes(aluno *end_aluno, int opcao)
{
    int i;

    if(opcao == 0)
    {
		printf("\n\tNome: %s", end_aluno->nome);
		printf("\n\tMatrícula: %d", end_aluno->matricula);
		printf("\n\n---------------------------------------------------------------\n");
        printf("\n\tCódigo da prova: %d", end_aluno->codGabarito);
		printf("\n\tTotal de questões: %d\n", end_aluno->totalQuestao);
		printf("\n\tRespostas:\n");
		for (i = 0; i < end_aluno->totalQuestao; i++)
			printf("\n\tQuestão %d: %c", i+1, end_aluno->resposta[i]);
		
		printf("\n");
		printf("---------------------------------------------------------------\n");
    }
}

void Imprime_Aluno(aluno *end_aluno, int opcao)
{
    int i;

    if(opcao == 0)
    {
		printf("\n\tNome: %s", end_aluno->nome);
		printf("\n\tMatrícula: %d", end_aluno->matricula);
		printf("\n\n---------------------------------------------------------------\n");
        printf("\n\tCódigo da prova: %d", end_aluno->codGabarito);
		printf("\n\tTotal de questões: %d\n", end_aluno->totalQuestao);
		printf("\n\tRespostas:\n");
		for (i = 0; i < end_aluno->totalQuestao; i++){
			
			if(end_aluno->correcao[i]=='1')
				printf("\n\tQuestão %d: %c  --> CORRETA", i+1, end_aluno->resposta[i]);

      		else if (end_aluno->correcao[i]=='0')
				printf("\n\tQuestão %d: %c  --> errouuuuuuuuuu", i+1, end_aluno->resposta[i]);
				
		}


		printf("\n\n\tAcertos: %d\n", end_aluno->acertos);
    printf("\tErradas: %d\n", end_aluno->totalQuestao-end_aluno->acertos);
		printf("\n");
		printf("---------------------------------------------------------------\n");
    }
    else if(opcao == 1)
    {
		printf("\n\tCódigo da prova: %d", end_aluno->codGabarito);
		printf("\n\tTotal de questões: %d\n", end_aluno->totalQuestao);
		printf("\n\tRespostas:\n");
		for (i = 0; i < end_aluno->totalQuestao; i++){
			
			if(end_aluno->correcao[i]=='1')
				printf("\n\tQuestão %d: %c  --> CORRETA", i+1, end_aluno->resposta[i]);	
				else if (end_aluno->correcao[i]=='0')
					printf("\n\tQuestão %d: %c  --> errouuuuuuuuuu", i+1, end_aluno->resposta[i]);
				
		}
		printf("\n\n\tAcertos: %d\n", end_aluno->acertos);
    printf("\tErradas: %d\n", end_aluno->totalQuestao-end_aluno->acertos);
		printf("\n");
		printf("---------------------------------------------------------------\n");
    }
}

void Imprime_Todos_Gabaritos()
{
    // Esta função imprime os dados de todos os gabaritos cadastrados
    int i;

    // Percorre a lista encadeada que contém os dados de todos os gabaritos até o final, imprimindo seu conteúdo

	for (ponteiro_gabarito = Lista_Gabaritos, i = 0; ponteiro_gabarito->prox != NULL; ponteiro_gabarito = ponteiro_gabarito->prox, i++)
    {
       printf("\nGabarito %d:\n", i+1);
       Imprime_Gabarito(ponteiro_gabarito);
       printf("\n---------------------------------------------------------------\n");
    }
}


void Imprime_Todos_Alunos()
{
    aluno *end_aluno;
    int i = 0, matriculas_printadas[SIZE_ALU];


    for (ponteiro_aluno = Lista_Alunos; ponteiro_aluno->prox != NULL; ponteiro_aluno = ponteiro_aluno->prox)
    {
        if(Esta_No_Vetor(matriculas_printadas, ponteiro_aluno->matricula) != 1)
        {
            matriculas_printadas[i] = ponteiro_aluno->matricula;
            i++;
            Imprime_Aluno(ponteiro_aluno, 0);
            end_aluno = Busca_Alu(ponteiro_aluno->matricula, ponteiro_aluno->prox);
            while(end_aluno != NULL)
            {
                Imprime_Aluno(end_aluno, 1);
                end_aluno = Busca_Alu(ponteiro_aluno->matricula, end_aluno->prox);
            }
        }
    }
}


int Esta_No_Vetor(int *vetor, int numero)
{
    int i;

    for (i = 0; i < SIZE_ALU; i++)
        if(vetor[i] == numero)
            return 1;

    return 0;
}


void Corrige_Prova()
{
  int i;
  ponteiro_gabarito = Lista_Gabaritos;

	for(i = 0; i < SIZE_GAB; i++, ponteiro_gabarito = ponteiro_gabarito->prox){
		if(ponteiro_gabarito->codGabarito == ponteiro_aluno->codGabarito)
			for(i=0; i<ponteiro_aluno->totalQuestao; i++){
				if (ponteiro_gabarito->resposta[i] == ponteiro_aluno->resposta[i]){
					ponteiro_aluno->correcao[i] = '1';
					ponteiro_aluno->acertos++;
				}
				else
					ponteiro_aluno->correcao[i] = '0';
			}
	}
}


void Posicao(int codProva)
{
  int acertos[SIZE_ALU], acertosGeral = 0, mediaAcertos, i, totalProvas=0, j, melhorQue = 0, acertosAluno = ponteiro_aluno->acertos, matriculaAluno = ponteiro_aluno->matricula, nota ;
  
  

  for(i=0, ponteiro_aluno = Lista_Alunos; i < SIZE_ALU; i++, ponteiro_aluno = ponteiro_aluno->prox)
  {
	  if(ponteiro_aluno->codGabarito == codProva && ponteiro_aluno->matricula != matriculaAluno)
    {
      acertos[totalProvas] = ponteiro_aluno->acertos;
      totalProvas++;
      acertosGeral = acertosGeral + ponteiro_aluno->acertos;
		}
  }
	
  for(i = 0; i < totalProvas; i++)
    if(acertosAluno > acertos[i])
      melhorQue++;
  
  if(totalProvas != 0)
  {
    nota = 100 - (melhorQue/totalProvas * 100);
    if(nota == 0){
      printf("Você é o melhor dessa prova! Parabéns\n");
    }else if(nota < 10 && nota != 0){
      printf("Você está entre os 10%% melhores! Parabéns\n");
    }else if(nota > 10 && nota <=20){
      printf("Você está entre os 20%% melhores! Parabéns\n");
    }else if(nota > 20 && nota <=30){
      printf("Você está entre os 30%% melhores! Parabéns\n");
    }else if(nota > 30 && nota <=40){
      printf("Você está entre os 40%% melhores.\n");
    }else if(nota > 40 && nota <=50){
      printf("Você está entre os 50%% melhores.\n");
    }else if(nota > 50 && nota <=60){
      printf("Você está entre os 60%% melhores. Estude mais da próxima vez...\n");
    }else if(nota > 60 && nota <=70){
      printf("Você está entre os 70%% melhores. Estude mais da próxima vez...\n");
    }else if(nota > 70 && nota <=80){
      printf("Você está entre os 80%% melhores. Estude mais da próxima vez...\n");
    }else if(nota > 80 && nota <=90){
      printf("Você está entre os 90%% melhores. Estude mais da próxima vez...\n");
    }else if(nota > 90 && nota <= 100){
      printf("Que lástima! Você está praticamente em último.\n");
    }else if(nota == 100){
      printf("Que lástima! Você está em último.\n");
    }
    printf("Acertos Geral: %d\nTotal provas: %d", acertosGeral, totalProvas);
    mediaAcertos = acertosGeral/totalProvas;
    printf("\nA média de acertos entre todos aplicantes da prova é %d ", mediaAcertos);
	}else{
    printf("Por enquanto esta é a única prova cadastrada.\n\nA média de acertos entre todos aplicantes da prova é %d", acertosAluno);
    }
  	getchar();
    getchar();
  
	

  
  
}


void Swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void AtualizaSIZE_ALU(int cod)
{
  int i;
  aluno *celula;

  for(i = 0, SIZE_ALU = 0, celula=Lista_Alunos; i < SIZE_ALU; i++, celula = celula->prox)
    if(cod == celula->codGabarito)
      SIZE_ALU++;

}


void BubbleSort(int arr[2][SIZE_ALU], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)     
 
       // Last i elements are already in place  
       for (j = 0; j < n-i-1; j++)
           if (arr[0][j] < arr[0][j+1])
           {
              Swap(&arr[0][j], &arr[0][j+1]);
              Swap(&arr[1][j], &arr[1][j+1]);
		        }
}
//////////////////////////////// BUBBLE SORT



void Size()
{
    // Esta função atualiza o valor as constantes SIZE_GAB e SIZE_ALU com o valor armazenado nos
    // arquivos size_gabaritos e size_alunos, que, por sua vez, informam o número de linhas de
    // gabaritos e alunos cadastrados nos arquivos "gabaritos.txt" e "Alunos.txt"

	FILE *arquivo;      // Ponteiro de stream
	arquivo = fopen("resources/size_gabaritos.txt", "a+");  // Abre arquivo para leitura. Cria o arquivo caso não exista

	// Verifica e avisa se houve algum erro ao abrir a stream "fp" com o arquivo

	if(arquivo == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo size_gabaritos.\n");
        exit(0);
    }

	fscanf(arquivo, "%d", &SIZE_GAB);   // Atualiza a constante com o valor do arquivo
	fclose(arquivo);     // Fecha a stream com o arquivo size_gabaritos.txt

	arquivo = fopen("resources/size_alunos.txt", "a+");

	// Verifica e avisa se houve algum erro ao abrir a stream "fp" com o arquivo

	if(arquivo == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo size_alunos.\n");
        exit(0);
    }
	fscanf(arquivo, "%d", &SIZE_ALU);     // Atualiza a constante com o valor do arquivo
	fclose(arquivo);    // Fecha a stream com o arquivo resources/size_alunos.txt
}

void Update_Size()
{
    // Esta função atualiza o valor armazenado nos arquivos size_gabaritos e size_alunos
    // com os valores das constantes SIZE_GAB e SIZE_ALU respectivamente

	FILE *arquivo;     // Ponteiro de stream
	arquivo = fopen("resources/size_gabaritos.txt", "w");   // Abre arquivo para escrita, substituindo o existente de mesmo nome

	// Verifica e avisa se houve algum erro ao abrir a stream "fp" com o arquivo

	if(arquivo == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo size_gabaritos.txt.\n");
        exit(0);
    }
	fprintf(arquivo,"%d", SIZE_GAB);   // Imprime no arquivo o valor da constante
	fclose(arquivo);    //Fecha a stream com o arquivo size_gabaritos.txt

	arquivo = fopen("resources/size_alunos.txt", "w");    // Abre arquivo para escrita, substituindo o existente de mesmo nome

	// Verifica e avisa se houve algum erro ao abrir a stream "fp" com o arquivo

	if(arquivo == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo size_alunos.txt.\n");
        exit(0);
    }
	fprintf(arquivo,"%d", SIZE_ALU);  // Imprime no arquivo o valor da constante
	fclose(arquivo);    // Fecha a stream com o arquivo size_alunos.txt
}

void Limpar_Memoria_Gab(gabarito *celula)
{

    // Esta função desaloca o espaço na memória reservado para uma lista do tipo gabarito
    // cujo endereço da primeira célula é passado por parâmetro

	gabarito *temp;     // ponteiro para armazenar endereços temporariamente

	// Percorre a lista até o fim, liberando o espaço alocado para cada célula

	for(; celula->prox != NULL; celula = temp){
		temp = celula->prox;
		free(celula);
	}
}

void Limpar_Memoria_Alu(aluno *celula)
{
    // Esta função desaloca o espaço na memória reservado para uma lista do tipo aluno
    // cujo endereço da primeira célula é passado por parâmetro

	aluno *temp;      // ponteiro para armazenar endereços temporariamente

	// Percorre a lista até o fim, liberando o espaço alocado para cada célula

	for(; celula->prox != NULL; celula = temp){
		temp = celula->prox;
		free(celula);
	}
}

void Sobre()
{
	printf("\n\tSistema de cadastro, consulta e correção de");
	printf("\n\tprovas, utilizável por professores e alunos.");
	printf("\n\n\tDesenvolvido em 2021/01 pelos alunos da computação");
	printf("\n\tUFPEL Allan Schuch, Gustavo Roos, Gustavo Souza e ");
	printf("\n\tJoão Victor Pozada, para a cadeira de Programação");
	printf("\n\tde Computadores, sob orientação do professor Marilton");
	printf("\n\tSanchotene de Aguiar.");
	printf("\n\n\n\tPressione ENTER para voltar...");
    getchar();
}

//////
/*         EM DESENVOLVIMENTO          */
void MostarEstatisca()
{
   int i, j, cod, valido = 0;
  
  do{
    gabarito *celula = Lista_Gabaritos;

    printf("\n\tChave do gabarito:");
    scanf("%d", &cod);
    //valida a chave da prova para saber se existe ou não.
    for (i = 0; i < SIZE_GAB; i++, celula = celula->prox)
    {
      if(cod == celula->codGabarito)
        valido = 1;
    }

    if(valido != 1)
    {
      system("clear");
      printf("\n\tChave incorreta!  %d",cod);
    }

    //Enquanto ele for Diferente de 1 ele não sai.
  }while(valido != 1);


  


  system("clear");
  printf("\n\t%d.Dentro de estatítica.",cod);
  
  printf("\n\n\t1.Continuar:");
  scanf("%d", &i);
  
}


//////
void FirstRun()
{
	FILE *fp;

	fp = fopen("resources/login/first_time_run.txt", "w");
	if(fp == NULL){
		fprintf(stderr, "\nErro ao abrir o arquivo first_time_run.txt..\n");
		exit(0);
	}
	fprintf(fp, "1");

	fclose(fp);
}

void LoginSimplesMuitoSimplesMesmo()
{
	int first;
	char lixo;

	FILE *fp;

	fp = fopen("resources/login/first_time_run.txt", "r");

	fscanf(fp, "%d", &first);

	fclose(fp);

	if(first != 1){
		FILE *login;         

    	login = fopen("resources/login/login.txt", "w");     

    	if(login == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo login.txt..\n");
        exit(0);
    	}
		printf("\n\tBem-vindo ao corretor de provas, este é seu primeiro acesso.");
		printf("\n\tPor gentileza, defina um login e senha para acesso");
		printf("\n\tde futuros arquivos confidenciais");
		printf("\n\n\tLogin: ");scanf("%s", ponteiro_login->login);
		printf("\n\tSenha: ");scanf("%s", ponteiro_login->senha);

    	fprintf(login,"%s\n%s", ponteiro_login->login,  ponteiro_login->senha);

		fclose(login);

	}
	else{

		FILE *fp;         

    	fp = fopen("resources/login/login.txt", "r");     

		if(fp == NULL){
			fprintf(stderr, "\nErro ao abrir o arquivo login.txt..\n");
			exit(0);
		}
	
    	fscanf(fp, "%[^\n]s", ponteiro_login->login);
    	fscanf(fp, "%c", &lixo);
    	fscanf(fp, "%[^\n]s", ponteiro_login->senha);
		fscanf(fp, "%c", &lixo);

		fclose(fp);
		
	}
}

void LoginRequest()
{
	login *celula;

	printf("\n\tPara acessar essa função, é necessário login e senha.");
	printf("\n\tPor gentileza, faça login como administrador abaixo.");
	printf("\n\n\tLogin: ");scanf("%s", celula->login);
	getchar();
	printf("\n\tSenha: ");scanf("%s", celula->senha);
	

	while((strcmp(celula->login, ponteiro_login->login)) != 0 || ((strcmp(celula->senha, ponteiro_login->senha)) != 0)){
		printf("\nLogin ou senha não confere, digite novamente:");
		printf("\n\n\tLogin: ");scanf("%s", celula->login);
		getchar();
		printf("\n\tSenha: ");scanf("%s", celula->senha);
	}
	
}