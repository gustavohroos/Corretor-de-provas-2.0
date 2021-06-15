#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include"func.h"

int menu(void)
{

  	int op;
	system("clear");
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

		if(op < 0 || op > 4){
    system("clear");
		printf("\n---Opcao invalida!---\n");
    }
  	}while(op < 0 || op > 4 );

    if( op == 0){
		int dec = 0;
		printf("\n------------------\n");
		printf("\nDeseja mesmo sair?\n1 - Sim 2 - Não: ");
    do
    {
		scanf("%d", &dec);
    if(dec < 1 || dec > 2)
    {
	  system("clear");
		printf("\nOpção inválida!\n");
		printf("\n------------------\n");
		printf("\nDeseja mesmo sair?\n1 - Sim 2 - Não: ");
    }
    }while(dec < 1 || dec > 2);
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

aluno *Busca_Alu_Acertos(int acertos, aluno *inicio_da_pesquisa)
{
    aluno *celula;

    for (celula = inicio_da_pesquisa; celula->prox != NULL; celula = celula->prox)
    {
        if (acertos == celula->acertos)
        {
            return celula;
        }
    }
    return NULL;
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

aluno *Criar_Lista_Ordenada(int codGabarito)
{ 
  	int i, j;
	aluno *inicio, *celula, *temp;
  	AtualizaMAX_PROVA(codGabarito);

	int vetoracertos[MAX_PROVA];

    int n = sizeof(vetoracertos)/sizeof(vetoracertos[0]);

	for(i=0, ponteiro_aluno=Lista_Alunos; ponteiro_aluno->prox != NULL; ponteiro_aluno = ponteiro_aluno->prox){
		if(ponteiro_aluno->codGabarito == codGabarito){
			vetoracertos[i] = ponteiro_aluno->acertos;
			i++;
		}
	}

	bubbleSort(vetoracertos, n);

  celula = (aluno *) malloc(sizeof(aluno));     
  inicio = celula;      


  for(j = 0; j < MAX_PROVA; j++){
    do{
      if(vetoracertos[j] == vetoracertos[j+1])
      j++;
    }while(vetoracertos[j] == vetoracertos[j+1]);
	  temp = Busca_Alu_Acertos(vetoracertos[j], Lista_Alunos);

    while(temp != NULL){
    celula->matricula = temp->matricula;
    strcpy(celula->nome, temp->nome);
    celula->codGabarito = temp->codGabarito;
    celula->acertos = temp->acertos;
    celula->prox = (aluno *) malloc(sizeof(aluno));
    celula->prox->prox = NULL;
    celula = celula->prox;
    temp = Busca_Alu_Acertos(vetoracertos[j], temp->prox);
    }
  }
    

	return (aluno *)inicio;          
}

gabarito *Busca_Gab(int codigo)
{
    int i;
    gabarito *celula = Lista_Gabaritos;   

    for (i = 0; i < SIZE_GAB; i++, celula = celula->prox)
    {
        if (codigo == celula->codGabarito)
        {
            return celula;
        }
    }
    return NULL;
}

gabarito *Carrega_Gabaritos()
{
    FILE *fp;
    int i;
	gabarito *inicio, *celula;

    celula = (gabarito *) malloc(sizeof(gabarito));     
    inicio = celula;

    fp = fopen("resources/gabaritos.txt","a+");

	if(fp == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo gabaritos.txt.\n");
        exit(0);
    }

    for(i = 0; i < SIZE_GAB; i++, celula = celula->prox){
		fscanf(fp,"%d %d %[^\n]s", &celula->codGabarito, &celula->totalQuestao, celula->resposta);
		celula->prox = (gabarito *) malloc(sizeof(gabarito));   
		celula->prox->prox = NULL;
	}

    fclose(fp);
	return (gabarito *)inicio;
}

float Media_Acertos(int codGabarito)
{
	float media;
	int soma_acertos = 0, num_provas = 0;
	
	for(ponteiro_aluno = Lista_Alunos; ponteiro_aluno->prox != NULL; ponteiro_aluno = ponteiro_aluno->prox)
		if(ponteiro_aluno->codGabarito == codGabarito){
			soma_acertos = soma_acertos + ponteiro_aluno->acertos;
			num_provas++;
		}
	media = (float)soma_acertos/num_provas;
	return media;
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

int Esta_No_Vetor(int *vetor, int numero)
{
    int i;

    for (i = 0; i < SIZE_ALU; i++)
        if(vetor[i] == numero)
            return 1;

    return 0;
}

void AtualizaMAX_PROVA(int cod)
{
  int i;
  aluno *celula;

  for(i = 0, MAX_PROVA = 0, celula=Lista_Alunos; i < SIZE_ALU; i++, celula = celula->prox)
    if(cod == celula->codGabarito)
      MAX_PROVA++;
}

void Cadastrar()
{
	int op;
  	system("clear");
  	do
  	{
		printf("\n\n ----------Cadastrar----------\n");
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
      if(Requisicao_Senha())
          Cadastrar_Gabarito();
			break;
		case 2:
			Cadastrar_Aluno();
			break;
		case 0:
			break;
		default:
		system("clear");
		printf("Opção inválida!");
		break;
		}
   	}while(op < 0 || op > 2);
}

void Cadastrar_Aluno()
{

    int i, op, testID = 0, chave_gabarito, provafeita[SIZE_GAB], check;
	gabarito *celulaGab;

  	aluno *celulaAluno;

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
        
        printf("\n\tGabaritos disponíveis para cadastro no momento:\n");
        i = 0;
        for(celulaAluno = Lista_Alunos; celulaAluno->prox != NULL; celulaAluno = celulaAluno->prox)
        {
          if(celulaAluno->matricula == ponteiro_aluno->matricula)
          {
            provafeita[i] = celulaAluno->codGabarito;
            i++;
          }
        }

        check = 0;
        for(celulaGab = Lista_Gabaritos; celulaGab->prox != NULL; celulaGab = celulaGab->prox)
        {
          if(Esta_No_Vetor(provafeita, celulaGab->codGabarito) != 1)
            Imprime_Gabarito(celulaGab, 2);
          else
            check++;
        }

        if(check == SIZE_GAB){
          system("clear");
          printf("\n\tVocê já cadastrou respostas para todas as provas disponíveis.\n\n\tPressione ENTER para continuar...");
          getchar();
          getchar();
          return ;
        }
        
        int check = 0;

        do
      	{
          
          printf("\n\tChave de acesso da prova (de 1111 a 9999): ");
          scanf("%d", &ponteiro_aluno->codGabarito);
          system("clear");

          while (ponteiro_aluno->codGabarito < 1111 || ponteiro_aluno->codGabarito > 9999)
          {
            printf("\n\tChave de acesso deve estar entre 1111 e 9999.\n\tPor favor digite novamente: ");
            scanf("%d", &ponteiro_aluno->codGabarito);
            system("clear");
          }

        }while(check != 0);
        
        chave_gabarito = ponteiro_aluno->codGabarito;
        ponteiro_aluno->totalQuestao = Busca_TotalQuest(chave_gabarito);

        system("clear");
        printf("\n\tGabarito encontrado, chave %d\n", chave_gabarito);
        printf("\n\tA prova possui %d questões, preencha-as abaixo em\n\tordem com A, B, C, D, E ou X para nulo.", ponteiro_aluno->totalQuestao);
        printf("\n\tQuestões nula 'X' são consideradas erradas!\n");

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
      		system("clear");
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

void Cadastrar_Gabarito()
{
	int i, op, testID, existe = 0;
	gabarito *celula;

	do
    {
      system("clear");
      testID = 0; 
    	do
      	{
        existe = 0;
        printf("\n\tChave de acesso da prova (de 1111 a 9999): ");
        scanf("%d", &ponteiro_gabarito->codGabarito);
        system("clear");

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

      printf("\n\tTotal de questões da prova (Entre %d e %d): ", RESPOSTAS_MIN, RESPOSTAS_MAX-1);
      scanf("%d", &ponteiro_gabarito->totalQuestao);
      system("clear");

      while(ponteiro_gabarito->totalQuestao < RESPOSTAS_MIN || ponteiro_gabarito->totalQuestao > RESPOSTAS_MAX-1)
      {
        printf("\n\tTotal de questões da prova deve estar entre %d e %d.\n\tPor favor digite novamente: ", RESPOSTAS_MIN, RESPOSTAS_MAX-1);
        scanf("%d", &ponteiro_gabarito->totalQuestao);
        system("clear");
      }

      printf("\nInforme a resposta certa de cada uma das %d questões da prova.\n\tAs respostas devem ser A, B, C, D ou E\n", ponteiro_gabarito->totalQuestao);

      for(i = 0; i < ponteiro_gabarito->totalQuestao; i++)
      {
        do
        {
          printf("\nQuestão %d: ", i+1);
          scanf("%s", &ponteiro_gabarito->resposta[i]);

          if(ponteiro_gabarito->resposta[i] < 65 || ponteiro_gabarito->resposta[i] > 69)
          printf("\nInvalida\n");

          }while(ponteiro_gabarito->resposta[i] < 65 || ponteiro_gabarito->resposta[i] > 69);

          printf("Resposta cadastrada.\n");  
        }
        system("clear");

        printf("Revise as informações:\n");
        Imprime_Gabarito(ponteiro_gabarito,1);

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
          testID = 1;
	}while(testID);   
	
  system("clear");
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
				else if(ponteiro_aluno->resposta[i] == 'X'){
						ponteiro_aluno->correcao[i] = 'X';
        				}else
							ponteiro_aluno->correcao[i] = '0';
			}
	}
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
                if(Requisicao_Senha())
                  Exclusao_Gabarito();
                break;
            case 2:
                Exclusao_Aluno();
                break;
						   case 0:
                break;
            default:
                system("clear");
                printf("Opção inválida!");
                break;
            }
            }while(op < 0 || op > 2);
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
    int matricula, testId = 1, op;
    system("clear");
    printf("\n\n -------Excluir Aluno------\n");
    printf("\nDigite a matrícula do aluno a ser removido (8 dígitos): "); scanf("%d", &matricula);

    while (matricula < 11111111 || matricula > 99999999)
    {
        printf("\nNúmero de matrícula deve estar entre 11111111 e 99999999.\nPor favor digite novamente: ");
        scanf("%d", &matricula);
        system("clear");
    }

    if(Busca_Alu(matricula, Lista_Alunos) != NULL)
        testId = 0;
         

  	while(testId)
    {
      system("clear");
      printf("\n\tMatrícula inválida! Lista de matrículas disponíveis:\n");
      Imprime_Todos_Alunos(1);
      do
      {
        printf("\n\tDeseja excluir algum destes alunos?\n\t1.Sim 2.Não\n\n\tSua opção: ");
        scanf("%d", &op);
      }while(op != 1 && op != 2);
      if(op == 1)
      {
        printf("\n\tInforme a matrícula do aluno a ser excluído: ");
        scanf("%d", &matricula);
        if(Busca_Alu(matricula, Lista_Alunos) != NULL)
            testId = 0;
      }
      else
        return;
    }
    
    printf("\nAluno %s foi removido com sucesso.\n", ponteiro_aluno->nome);
    Excluir_Alu(matricula);
    printf("\n\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

void Exclusao_Gabarito()
{
    int codGabarito, testId = 1, op;
    system("clear");
    printf("\n\n -------Excluir Gabarito------\n");
    printf("\nDigite a chave do gabarito a ser removido (4 dígitos): "); scanf("%d", &codGabarito);

    while (codGabarito < 1111 || codGabarito > 9999)
    {
        printf("\nChave do gabarito deve estar entre 1111 e 9999.\nPor favor digite novamente: ");
        scanf("%d", &codGabarito);
        system("clear");
    }

    if(Busca_Gab(codGabarito) != NULL)
            testId = 0;
    
    while(testId)
    {
      system("clear");
      printf("\n\tChave de gabarito inválida! Lista de gabaritos disponíveis:\n");
      Imprime_Todos_Gabaritos(1);
      do
      {
        printf("\n\tDeseja excluir algum destes gabaritos?\n\t1.Sim 2.Não\n\n\tSua opção: ");
        scanf("%d", &op);
      }while(op != 1 && op != 2);
      if(op == 1)
      {
        printf("\n\tInforme a chave do gabarito a ser excluído: ");
        scanf("%d", &codGabarito);
        if(Busca_Gab(codGabarito) != NULL)
            testId = 0;
      }
      else
        return;
    }

    Excluir_Gab(codGabarito);
    printf("\nGabarito removido com sucesso.\n");
    printf("\n\nPressione ENTER para continuar...");
    getchar();
    getchar();
}

void Imprime_Aluno(aluno *end_aluno, int opcao)
{
    int i, nulas = 0;

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
				printf("\n\tQuestão %d: %c  \u2714\uFE0F", i+1, end_aluno->resposta[i]);

      		else if (end_aluno->correcao[i]=='0')
				printf("\n\tQuestão %d: %c  \u274C", i+1, end_aluno->resposta[i]);
        			else if (end_aluno->correcao[i]=='X'){
						printf("\n\tQuestão %d: %c  \u26D4", i+1, end_aluno->resposta[i]);
				    	nulas++;
            			}
		}
		printf("\n\n\tAcertos: %d\n", end_aluno->acertos);
		if((end_aluno->totalQuestao - end_aluno->acertos - nulas) < 0)
			printf("\tErradas: 0\n");
			else printf("\tErradas: %d\n", end_aluno->totalQuestao - end_aluno->acertos - nulas);
		printf("\tNulas: %d\n", nulas);
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
				printf("\n\tQuestão %d: %c  \u2714\uFE0F", i+1, end_aluno->resposta[i]);

      		else if (end_aluno->correcao[i]=='0')
				printf("\n\tQuestão %d: %c  \u274C", i+1, end_aluno->resposta[i]);
        			else if (end_aluno->correcao[i]=='X'){
						printf("\n\tQuestão %d: %c  \u26D4", i+1, end_aluno->resposta[i]);
				    	nulas++;
            			}
		}
		printf("\n\n\tAcertos: %d\n", end_aluno->acertos);
		if((end_aluno->totalQuestao - end_aluno->acertos - nulas) < 0)
			printf("\tErradas: 0\n");
			else printf("\tErradas: %d\n", end_aluno->totalQuestao - end_aluno->acertos - nulas);
		printf("\tNulas: %d\n", nulas);
		printf("\n");
		printf("---------------------------------------------------------------\n");
    }
    else if(opcao == 2)
    {
      printf("\n\tNome: %s", end_aluno->nome);
      printf("\n\tMatrícula: %d", end_aluno->matricula);
      printf("\n\n---------------------------------------------------------------\n");
    }
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
		printf("\n---------------------------------------------------------------\n");
    }
}

void Imprime_Gabarito(gabarito *end_gabarito, int opcao)
{
  
  if(opcao == 1)
  {
    int i;

      printf("\n\tCódigo da prova: %d", end_gabarito->codGabarito);
      printf("\n\tNúmero de questões: %d\n", end_gabarito->totalQuestao);
      printf("\n\tRespostas:\n");
      for (i = 0; i < end_gabarito->totalQuestao; i++)
        printf("\n\tQuestão %d: %c", i+1, end_gabarito->resposta[i]);
      printf("\n");
    }
    else if(opcao == 2)
    {
      printf("\n\tCódigo da prova: %d", end_gabarito->codGabarito);
      printf("\n\tNúmero de questões: %d\n", end_gabarito->totalQuestao);
      printf("\n---------------------------------------------------------------\n");
    }
}

void Imprime_Todos_Alunos(int opcao)
{
    aluno *end_aluno;
    int i = 0, matriculas_printadas[SIZE_ALU];

    if(opcao == 1){
      for (ponteiro_aluno = Lista_Alunos; ponteiro_aluno->prox != NULL; ponteiro_aluno = ponteiro_aluno->prox)
        Imprime_Aluno(ponteiro_aluno, 2);
    }
    else if(opcao == 0){
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
}

void Imprime_Todos_Gabaritos(int opcao)
{
    int i;

  if(opcao == 1){
    for (ponteiro_gabarito = Lista_Gabaritos, i = 0; ponteiro_gabarito->prox != NULL; ponteiro_gabarito = ponteiro_gabarito->prox, i++)
    {
       printf("\nGabarito %d:\n", i+1);
       Imprime_Gabarito(ponteiro_gabarito, 2);
    }
  }else if(opcao == 0){
	for (ponteiro_gabarito = Lista_Gabaritos, i = 0; ponteiro_gabarito->prox != NULL; ponteiro_gabarito = ponteiro_gabarito->prox, i++)
    {
       printf("\nGabarito %d:\n", i+1);
       Imprime_Gabarito(ponteiro_gabarito, 1);
       printf("\n---------------------------------------------------------------\n");
    }
  }
}

void Limpar_Memoria_Alu(aluno *celula)
{
	aluno *temp;

	for(; celula->prox != NULL; celula = temp){
		temp = celula->prox;
		free(celula);
	}
}

void Limpar_Memoria_Gab(gabarito *celula)
{
	gabarito *temp;

	for(; celula->prox != NULL; celula = temp){
		temp = celula->prox;
		free(celula);
	}
}

void MostrarEstatisticas()
{
	int i, cod, valido = 0, op;
  gabarito *celula;

  system("clear");

  if(SIZE_ALU == 0)
  {
    printf("\n\n\tNão há nenhuma resposta de prova cadastrada.\n\tPortanto, não será possível exibir estatísticas.\n\n\tPressione ENTER para continuar...");
    getchar();
    getchar();
  }

	do{
		printf("\n\n\t --------------------------------\n");
    	printf("\t| Digite o código da prova: "); scanf("%d", &cod);
        printf("\t --------------------------------\n");

    celula = Busca_Gab(cod);
		if(celula == NULL)
		{
			system("clear");
			printf("\n\tChave incorreta! (%d)\n\n\tLista de provas disponíveis:\n", cod);
      Imprime_Todos_Gabaritos(1);
      do
      {
        printf("\n\tDeseja exibir as estatísticas de alguma destas provas?\n\t1.Sim 2.Não\n\n\tSua opção: ");
        scanf("%d", &op);
        if(op == 2)
          return;
      }while(op < 1 || op > 2);
		}
    else
    {
      AtualizaMAX_PROVA(cod);
      if(MAX_PROVA > 0)
        valido = 1;
      else
      { 
        system("clear");
        printf("\tNão há nenhuma resposta cadastrada para esta prova no momento.");
      }
    }
	}while(valido != 1 || MAX_PROVA == 0);

	aluno *inicio = Criar_Lista_Ordenada(cod);
	
	system("clear");
	
	printf("\n\n\t ----Estatísticas da prova %d---\n", cod);
  printf("\t| Número de questões: %-12d|\n", celula->totalQuestao);
	printf("\t ---------------------------------\n");
	printf("\t| Questão mais acertada: %-9d|\n", Questao_Mais_Acertada(cod) + 1);
	printf("\t ---------------------------------\n");
	printf("\t| Questão mais errada: %-11d|\n", Questao_Mais_Errada(cod) + 1) ;
	printf("\t ---------------------------------\n");
	printf("\t| Média de acertos: %-14.2f|\n", Media_Acertos(cod));
	printf("\t ---------------------------------\n");

	printf("\n\n\t%-25s\tMATRÍCULA%12s\n\n", "NOME", "ACERTOS");

	for(i = 1, ponteiro_aluno = inicio; ponteiro_aluno->prox != NULL; ponteiro_aluno = ponteiro_aluno->prox)
	{
		if(ponteiro_aluno->codGabarito == cod)
		{
		printf("%d\t%-25s\t%d%13d |\n", i, ponteiro_aluno->nome, ponteiro_aluno->matricula, ponteiro_aluno->acertos);
		i++;
		}
	}
	printf("\n");
	
	Limpar_Memoria_Alu(inicio);

	printf("\nPressione ENTER para voltar ao menu... ");
	getchar();
	getchar();
  
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
                if(Requisicao_Senha())
                  Mostrar_Gabarito();
                break;
            case 3:
                MostrarEstatisticas();
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
                Imprime_Todos_Alunos(0);
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
                Imprime_Todos_Gabaritos(0);
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

		if (end_aluno == NULL){
			printf("\n\tAluno não cadastrado!\n\n\tLista de alunos cadastrados:\n");
      Imprime_Todos_Alunos(1);
    }
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
    } while (testID);
}

void Pesquisar_Gabarito()
{
    int testID, op;
    gabarito *end_gabarito;

    do
    {
        testID = 0;
        system("clear");

        printf("\n\tInforme uma chave de gabarito válida(de 1111 a 9999): ");
        scanf("%d", &ponteiro_gabarito->codGabarito);
        system("clear");

        while (ponteiro_gabarito->codGabarito < 1111 || ponteiro_gabarito->codGabarito > 9999)
        {
            printf("\n\tChave de gabarito inválida! Tente novamente: ");
            scanf("%d", &ponteiro_gabarito->codGabarito);
            system("clear");
        }

        end_gabarito = Busca_Gab(ponteiro_gabarito->codGabarito);

        if (end_gabarito == NULL)
        {
          printf("\n\tChave de gabarito não cadastrada! Lista de gabaritos disponíveis:\n");
          Imprime_Todos_Gabaritos(1);
        }  
        else
        {
            system("clear");
            printf("\n\tGabarito encontrado:\n");
            Imprime_Gabarito(end_gabarito, 1);
        }

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
    } while (testID);
}

void Posicao(int codProva)
{
  int acertos[SIZE_ALU], acertosGeral = 0, i, totalProvas=0, melhorQue = 0, acertosAluno = ponteiro_aluno->acertos, matriculaAluno = ponteiro_aluno->matricula;
  float mediaAcertos, nota = 0;
  
  

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
    nota = 100 - (melhorQue/(float)totalProvas * 100);

    if(nota == 0){
      printf("\nVocê é o melhor dessa prova! Parabéns\n");
    }else if(nota < 10){
      printf("\nVocê está entre os 10%% melhores! Parabéns\n");
    }else if(nota <=20){
      printf("\nVocê está entre os 20%% melhores! Parabéns\n");
    }else if(nota <=50){
      printf("\nVocê está entre os 50%% melhores.\n");
    }else if(nota == 100){
      printf("\nQue lástima! Você está em último.\n");
    }
    mediaAcertos = acertosGeral/(float)totalProvas;
    printf("\nA média de acertos entre todos aplicantes da prova é %.1f.\n", mediaAcertos);
	}else{
    printf("\nPor enquanto esta é a única prova cadastrada.\n\nA média de acertos entre todos aplicantes da prova é %d.\n", acertosAluno);
    }

    printf("\n\nPressione ENTER para continuar...\n\n\n");
  	getchar();
    getchar();
}

int Questao_Mais_Acertada(int codProva)
{
  int i, totalQuest, k, maximo = 0, posicao;
	aluno *celula;

	for(i=0, celula=Lista_Alunos; i<SIZE_ALU; celula=celula->prox, i++){
		if(celula->codGabarito == codProva){
      		
			totalQuest = celula->totalQuestao;
		}
	}

	int posicaoQuestaoCerta[totalQuest];

  for(k = 0; k < totalQuest; k++)
  {
  posicaoQuestaoCerta[k] = 0;
    for(i=0, celula=Lista_Alunos; i<SIZE_ALU; celula=celula->prox, i++){
      if(celula->codGabarito == codProva)
      {
        if(celula->correcao[k] == '1')
        {
          posicaoQuestaoCerta[k]++;
        }
      }
    }
  }

	for(i=0; i<totalQuest; i++)
  {
    if(posicaoQuestaoCerta[i] > maximo)
    {
      maximo = posicaoQuestaoCerta[i];
      posicao = i;
    }
	}

  return posicao;
}

int Questao_Mais_Errada(int codProva)
{
	int i, totalQuest, k, maximo = 0, posicao;
	aluno *celula;

	for(i=0, celula=Lista_Alunos; i<SIZE_ALU; celula=celula->prox, i++){
		if(celula->codGabarito == codProva){
      		totalQuest = celula->totalQuestao;
		}
	}

	int posicaoQuestaoErrada[totalQuest];

  for(k = 0; k < totalQuest; k++)
  {
  posicaoQuestaoErrada[k] = 0;
    for(i=0, celula=Lista_Alunos; i<SIZE_ALU; celula=celula->prox, i++){
      if(celula->codGabarito == codProva)
      {
        if(celula->correcao[k] == '0')
        {
          posicaoQuestaoErrada[k]++;
        }
      }
    }
  }

	for(i=0; i<totalQuest; i++){
		if(posicaoQuestaoErrada[i] > maximo){
			maximo = posicaoQuestaoErrada[i];
			posicao = i;
		}
	}

  return posicao;
}



void Primeira_Execucao()
{
FILE *fp;
FILE *fp2;
int check, senha, op;

fp = fopen("resources/primeira_execucao.txt", "a+");

if(fp == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo primeira_execucao.txt.\n");
        exit(0);
    }

fscanf(fp, "%d", &check);

if(check != 1)
{
  do
  {
    system("clear");
    printf("---\tPRIMEIRA EXECUÇÃO DO PROGRAMA\t---");
    printf("\n\n\tCrie uma SENHA DE ADMINISTRADOR de 4 caracteres(entre 1000 e 9999): ");
    scanf("%d", &senha);

    while(senha < 1000 || senha > 9999)
    {
      system("clear");
      printf("---\tPRIMEIRA EXECUÇÃO DO PROGRAMA\t---");
      printf("\n\n\tA senha deve ser um número entre 1000 e 9999.\n\tTente novamente: ");
      scanf("%d", &senha);
    }
    do
    {
      system("clear");
      printf("---\tPRIMEIRA EXECUÇÃO DO PROGRAMA\t---");
      printf("\n\n\tSua SENHA DE ADMINISTRADOR: %d\n\n\tDeseja salvá-la?\n\t1.Sim 2.Não\n\n\tSua opção: ", senha);
      scanf("%d", &op);
    }while(op != 1 && op != 2);
  }while(op == 2);

  fp2 = fopen("resources/senha", "wb");
  if(fp2 == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo senha.txt.\n");
        exit(0);
    }
  fwrite(&senha, sizeof(int), 1, fp2);
  fclose(fp2);
  fprintf(fp, "%d", 1);
  fclose(fp);

  system("clear");
  printf("---\tPRIMEIRA EXECUÇÃO DO PROGRAMA\t---");
  printf("\n\n\tSua SENHA DE ADMINISTRADOR(%d) foi salva com sucesso.\n\n\tGuarde bem esta chave!\n\tEla será necessária para realizar funções importantes no programa!\n\n", senha);
  printf("\tPressione ENTER para continuar...");
  getchar();
  getchar();
}
}


int Requisicao_Senha()
{
int senha, senhaCadastrada;
FILE *fp;

  system("clear");
  printf("---\tACESSO EXLCUSIVO PARA ADM's\t---");
  printf("\n\n\tInforme sua SENHA DE ADMINISTRADOR:\n\n\tSenha: ");
  scanf("%d", &senha);

  fp = fopen("resources/senha", "rb");
  if(fp == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo senha.txt.\n");
        exit(0);
    }
  
  fread(&senhaCadastrada, sizeof(int), 1, fp);
  fclose(fp);

  if(senha != senhaCadastrada)
  {
    system("clear");
    printf("---\tACESSO EXLCUSIVO PARA ADM's\t---");
    printf("\n\n\tACESSO NEGADO!\n");
    printf("\nPressione ENTER para continuar...");
    getchar();
    getchar();
    return 0;
  }
  else
    return 1;
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

void Salvar_Gabarito()
{
    FILE *fp;

    fp = fopen("resources/gabaritos.txt", "a");

    if(fp == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo gabaritos.txt..\n");
        exit(0);
    }

    fprintf(fp,"%d %d %s\n", ponteiro_gabarito->codGabarito, ponteiro_gabarito->totalQuestao, ponteiro_gabarito->resposta);
    SIZE_GAB++;
    Update_Size();
    fclose(fp);
    Limpar_Memoria_Gab(Lista_Gabaritos);
    Lista_Gabaritos = Carrega_Gabaritos();

}

void Size()
{
	FILE *arquivo;
	arquivo = fopen("resources/size_gabaritos.txt", "a+");

	if(arquivo == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo size_gabaritos.\n");
        exit(0);
    }

	fscanf(arquivo, "%d", &SIZE_GAB);
	fclose(arquivo);
	arquivo = fopen("resources/size_alunos.txt", "a+");

	if(arquivo == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo size_alunos.\n");
        exit(0);
    }
	fscanf(arquivo, "%d", &SIZE_ALU);
	fclose(arquivo);
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

void Update_Size()
{
	FILE *arquivo;
	arquivo = fopen("resources/size_gabaritos.txt", "w");

	if(arquivo == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo size_gabaritos.txt.\n");
        exit(0);
    }
	fprintf(arquivo,"%d", SIZE_GAB);
	fclose(arquivo);

	arquivo = fopen("resources/size_alunos.txt", "w");

	if(arquivo == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo size_alunos.txt.\n");
        exit(0);
    }
	fprintf(arquivo,"%d", SIZE_ALU);
	fclose(arquivo);
}


///////// BUBBLESORT /////////

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 

void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)     
 
       
       for (j = 0; j < n-i-1; j++)
           if (arr[j] < arr[j+1])
              swap(&arr[j], &arr[j+1]);
}
 

void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

///////// BUBBLESORT /////////