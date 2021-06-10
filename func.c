#include"func.h"


int menu(void)
{
    //Esta função exibe o menu e retorna a opção escolhida pelo usuário

    int op;
    system("clear");
    do
    {
    printf("\n\n ---------------Bem-vindo-----------------\n");
    printf("| 1.Cadastrar Gabarito                    |\n");
	printf(" -----------------------------------------\n");
    printf("| 2.Cadastrar Aluno                       |\n");
	printf(" -----------------------------------------\n");
    printf("| 3.Mostrar Gabarito                      |\n");
	printf(" -----------------------------------------\n");
    printf("| 4.Pesquisar Aluno                       |\n");
	printf(" -----------------------------------------\n");
	printf("| 5.Excluir                               |\n");
	printf(" -----------------------------------------\n");
    printf("| 6.Mostrar Ranking                       |\n");
	printf(" -----------------------------------------\n");
    printf("| 0.Sair                                  |\n");
	printf(" -----------------------------------------\n");
    printf("\nInforme a opção: ");
    scanf("%d", &op);
    getchar();

    system("clear");

    // Verifica se o usuário quer mesmo finalizar o programa

    if( op == 0){
      int dec = 0;
      printf("Deseja mesmo sair?\n 1. Sim 2. Não: ");
      scanf("%d", &dec);
      if(dec == 2)
      op = 7;
      system("clear");
    }

    // Checa se a opção é válida

    if(op < 0 || op > 7)
    printf("\n---Opcao invalida!---\n");

  }while(op < 0 || op > 6 );

    if(op != 0)
    printf("\nFunção Escolhida: %d\n", op);
    else
    printf("Fim do Programa.\n");

  return op;
}


void Cadastrar_Gabarito()
{
    // Esta função recolhe os dados de uma prova (chave, numero de questões, gabarito) e dá a opção de salvá-los ou não
    // Os dados temporários (para serem salvos ou não) são armazenados em uma célula criada para este fim no início do programa
    // Esta célula é do tipo gabarito e é referenciada pelo ponteiro "ponteiro_gabarito"

   int i, op, testID;

    do
    {
        testID = 0;    // Variável para controlar a repetição da função
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

        printf("\n\tTotal de questões da prova (Entre %d e %d): ", RESPOSTAS_MIN, RESPOSTAS_MAX);
        scanf("%d", &ponteiro_gabarito->totalQuestao);
        system("clear");

        // Verifica se a informação digitada é válida

        while(ponteiro_gabarito->totalQuestao < RESPOSTAS_MIN || ponteiro_gabarito->totalQuestao > RESPOSTAS_MAX)
        {
            printf("\n\tTotal de questões da prova deve estar entre %d e %d.\n\tPor favor digite novamente: ", RESPOSTAS_MIN, RESPOSTAS_MAX);
            scanf("%d", &ponteiro_gabarito->totalQuestao);
            system("clear");
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
        } while (op < 1 || op > 2);

        if (op == 1)
        {
            system("clear");
            testID = 1;
        }
        }while(testID);   // Testa a variável de controle da repetição da função

        system("clear");
}

void Cadastrar_Aluno()
{

   int i, op, testID, chave_gabarito, total_quest, acertos_total = 0;
   gabarito *end_gabarito, *celula;
   aluno *end_aluno;


    do
    {
        testID = chave_gabarito = total_quest = 0; 

        printf("\n\tDigite seu nome: "); scanf("%[^\n]%*c", ponteiro_aluno->nome);
        
        printf("\n\tDigite sua matrícula (8 dígitos): "); scanf("%d", &ponteiro_aluno->matricula);

        while (ponteiro_aluno->matricula < 11111111 || ponteiro_aluno->matricula > 99999999)
        {
            printf("\n\tNúmero de matrícula deve estar entre 11111111 e 99999999.\n\tPor favor digite novamente: ");
            scanf("%d", &ponteiro_aluno->matricula);
            system("clear");
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
        Imprime_Aluno(ponteiro_aluno);

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
            Salvar_Aluno();
            system("clear");
            printf("O seu gabarito desta prova foi salvo com sucesso!\n");
            printf("%d", acertos_total);
            acertos_total = CompararRespostas(ponteiro_aluno);
            printf("%d", acertos_total);
            printf("Parabéns, você acertou %d/%d questões nessa prova", acertos_total, total_quest);
        }
        else if(op == 2)
        {
            system("clear");
            printf("Este gabarito não foi salvo...\n");
        }

        do
        {
            printf("\nDeseja cadastrar outra prova?\n1.Sim 2.Não\n\nSua escolha: ");
            scanf("%d", &op);
            if (op < 1 || op > 2)
            {
                system("clear");
                printf("Opção inválida!\n");
            }
        } while (op < 1 || op > 2);

        if (op == 1)
        {
            system("clear");
            testID = 1;
			getchar();
        }
        }while(testID); 

        system("clear");
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
                printf("\n\nPressione qualquer tecla para continuar...");
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
                Exclui_Gab();
                system("clear");
                break;
            case 2:
                Exclui_Aluno();
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
            printf("\n\tDeseja procurar outro gabarito?\n1.Sim 2.Não\n\nSua escolha: ");
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

void Exclui_Gab()
{
    int i, codigo, auxiliar = 0, testId = 1;
    gabarito *temp, *start, *celula; 
    FILE *fp;
    system("clear");
    printf("\n\n -------Excluir Gabarito------\n");
    printf("\nDigite o código de acesso do gabarito a ser removido: "); scanf("%d", &codigo);
    celula = Lista_Gabaritos;
    start = celula;

    for(i = 0, celula = start; i < SIZE_GAB; i++, celula = celula->prox){
        if(celula->codGabarito == codigo){
            testId = 0;
        }
    }
	  if(testId){
	    printf("\n\tCódigo inválido");
    }else{
		celula = start;

		for(i = 0; i < SIZE_GAB; i++, celula = celula->prox){
			if(celula->codGabarito==codigo){
				auxiliar = 1;
				if(i == 0){
					start = celula->prox;
				}else{
					temp->prox = celula->prox;
				}
				free(celula);
				i = SIZE_GAB--;
			}else{
				temp = celula;
			}
		}
        Update_Size();
		fp = fopen("resources/gabaritos.txt", "w");
		if(fp == NULL){ 
			fprintf(stderr, "\nErro arquivo resources/gabaritos.txt.\n"); 
			exit(0);
		}
		celula = start;
		for(i = 0; i < SIZE_GAB; i++, celula = celula->prox){
			fprintf(fp , "%d %d %s\n", celula->codGabarito, celula->totalQuestao, celula->resposta);
		}
		if(auxiliar)
			printf("\nGabarito foi removido com sucesso.\n");
		fclose(fp);

        Limpar_Memoria_Gab(celula);
        Lista_Gabaritos = Carrega_Gabaritos();
        printf("\n\nPressione qualquer tecla para continuar...");
        getchar();
        getchar();
}

}

void Exclui_Aluno()
{
    int i, matricula, auxiliar = 0, testId = 1;
    aluno *temp, *start, *celula;   
    FILE *fp;
    system("clear");
    printf("\n\n -------Excluir Aluno------\n");
    printf("\nDigite a matrícula do aluno a ser removido: "); scanf("%d", &matricula);
    celula = Lista_Alunos;
    start = celula;

    for(i = 0, celula = start; i < SIZE_ALU; i++, celula = celula->prox){
        if(celula->matricula == matricula){
            testId = 0;
        }
    }
	if(testId){
	    printf("\n\tMatrícula inválida");
    }else{
		celula = start;

		for(i = 0; i < SIZE_ALU; i++, celula = celula->prox){
			if(celula->matricula==matricula){
				auxiliar = 1;
				if(i == 0){
					start = celula->prox;
				}else{
					temp->prox = celula->prox;
				}
				free(celula);
				i = SIZE_ALU--;
			}else{
				temp = celula;
			}
		}
        Update_Size();
		fp = fopen("resources/alunos.txt", "w");
		if(fp == NULL){ 
			fprintf(stderr, "\nErro arquivo alunos.txt.\n"); 
			exit(0);
		}
		celula = start;
		for(i = 0; i < SIZE_ALU; i++, celula = celula->prox){
			fprintf(fp , "%d %d %d %s %s\n", celula->matricula, celula->codGabarito, celula->totalQuestao, celula->resposta, celula->nome);
		}
		if(auxiliar)
			printf("\nAluno foi removido com sucesso.\n");
		fclose(fp);
        Limpar_Memoria_Alu(celula);
        Lista_Alunos = Carrega_Alunos();
        printf("\n\nPressione qualquer tecla para continuar...");
        getchar();
        getchar();
    }
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

    fp = fopen("resources/alunos.txt", "a");     

    if(fp == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo alunos.txt..\n");
        exit(0);
    }

    fprintf(fp,"%d %d %d %s %s\n", ponteiro_aluno->matricula,  ponteiro_aluno->codGabarito, ponteiro_aluno->totalQuestao, ponteiro_aluno->resposta,ponteiro_aluno->nome);
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
    int i, j;
	aluno *inicio, *celula;

    celula = (aluno *) malloc(sizeof(aluno));     
    inicio = celula;      

    fp = fopen("resources/alunos.txt","a+");   

	if(fp == NULL){
        fprintf(stderr, "\nErro ao abrir o arquivo alunos.txt.\n");
        exit(0);
    }

    for(i = 0; i < SIZE_ALU; i++, celula = celula->prox){

		fscanf(fp,"%d %d %d ", &celula->matricula, &celula->codGabarito, &celula->totalQuestao);
		for (j = 0; j <= celula->totalQuestao; j++)
		{
		   celula->resposta[j] = fgetc(fp);
		}
		celula->resposta[j-1] = '\0';
		fscanf(fp,"%[^\n]%*c", celula->nome);
		celula->prox = (aluno *) malloc(sizeof(aluno));
		celula->prox->prox = NULL;
	}

    fclose(fp);       
	return (aluno *)inicio;          
}



void Imprime_Gabarito(gabarito *end_gabarito)
{
    // Esta função imprime os dados de um determinado gabarito, passando por parâmetro seu endereço

    int i;

    // Imprime os dados

    printf("\n\tCódigo da prova: %d", end_gabarito->codGabarito);
    printf("\n\tNúmero de questões: %d\n", end_gabarito->totalQuestao);
    printf("\n\tRespostas:\n");
    for (i = 0; i < end_gabarito->totalQuestao; i++)
    {
        printf("\n\tQuestão %d: %c", i+1, end_gabarito->resposta[i]);
    }
    printf("\n");
}

void Imprime_Aluno(aluno *end_aluno)
{
    // Esta função imprime os dados de um determinado gabarito, passando por parâmetro seu endereço

    int i;

    // Imprime os dados

    printf("\n\tNome: %s", end_aluno->nome);
    printf("\n\tMatrícula: %d", end_aluno->matricula);
    printf("\n\tCódigo da prova: %d", end_aluno->codGabarito);
    printf("\n\tTotal de questões: %d\n", end_aluno->totalQuestao);
    printf("\n\tRespostas:\n");
    for (i = 0; i < end_aluno->totalQuestao; i++)
    {
        printf("\n\tQuestão %d: %c", i+1, end_aluno->resposta[i]);
    }
    printf("\n");
}


void Imprime_Todos_Gabaritos()
{
    // Esta função imprime os dados de todos os gabaritos cadastrados

    gabarito *celula;   // Declarando um ponteiro "*celula" do tipo gabarito para armazenar temporariamente os endereços das celulas da lista
    int i, j;

    // Percorre a lista encadeada que contém os dados de todos os gabaritos até o final, imprimindo seu conteúdo

	for (celula = Lista_Gabaritos, i = 0; celula->prox != NULL; celula = celula->prox, i++)
    {
       printf("\nGabarito %d:\n", i+1);
       printf("\n\tCódigo da prova: %d", celula->codGabarito);
       printf("\n\tNúmero de questões: %d\n", celula->totalQuestao);
       printf("\n\tRespostas:\n");
       for (j = 0; j < celula->totalQuestao; j++)
       {
           printf("\n\tQuestão %d: %c", j+1, celula->resposta[j]);
       }
       printf("\n");
    }
}

int CompararRespostas(aluno *celula_aluno){
    
    int i, testId = 1, acertos = 0;
    char respostas[RESPOSTAS_MAX];
    FILE *fp;
    gabarito *celula = Lista_Gabaritos;
    strcpy(respostas, celula_aluno->resposta);

    fopen("resources/gabaritos.txt", "r");
    if(fp == NULL){ 
			fprintf(stderr, "\nErro arquivo gabaritos.txt.\n"); 
			exit(0);
	}

    for(i = 0 ; i < SIZE_GAB; i++, celula = celula->prox){
        if(celula->codGabarito == celula_aluno->codGabarito){
            testId = 0;
        }
    }
	  if(testId){
	    printf("\n\tCódigo inválido");
        }else{
            for(i = 0; i < SIZE_GAB; i++, celula = celula->prox){
                if(celula->codGabarito == celula_aluno->codGabarito){
                    for(i=0; i<celula_aluno->totalQuestao; i++){
                        if (celula->resposta[i] == celula_aluno->resposta[i])
                        {
                            acertos++;
                        }
                    }
                }
            }
        }
    return acertos;
}

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




