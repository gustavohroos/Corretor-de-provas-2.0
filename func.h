#define NOME_MAX 100
#define RESPOSTAS_MAX 50
#define RESPOSTAS_MIN 1
// VARIÁVEIS GLOBAIS
int SIZE_GAB, SIZE_ALU;   // Armazenam o número de linhas de gabaritos e alunos cadastrados nos arquivos "Gabaritos.txt" e "Alunos.txt"

// DECLARAÇÃO STRUCTS

struct acertos{
	int codGabarito, matricula, acertos;
	struct acertos *prox;
};
//https://www.geeksforgeeks.org/c-program-bubble-sort-linked-list/
typedef struct acertos acertos;

struct prova {
  int codGabarito, totalQuestao;
  char resposta[RESPOSTAS_MAX];
  struct prova *prox;
};

typedef struct prova gabarito;

struct alu {
  int matricula, codGabarito, totalQuestao, acertos;
  char nome[NOME_MAX], resposta[RESPOSTAS_MAX], correcao[RESPOSTAS_MAX];
  struct alu *prox;
};

typedef struct alu aluno;

struct login {
  char login[RESPOSTAS_MAX], senha[RESPOSTAS_MAX];
  struct login *prox;
};

typedef struct login login;

// Declaração do ponteiro universal que apontará o endereço da célula responsável por armazenar dados do tipo gabarito de forma temporária
gabarito *ponteiro_gabarito;
// Declaração do ponteiro universal que apontará o endereço da célula responsável por armazenar dados do tipo aluno de forma temporária
aluno *ponteiro_aluno;

login *ponteiro_login;

// Declaração do ponteiro universal que apontará para o início da lista encadeada que armazenará os dados de todos os gabaritos cadastrados
gabarito *Lista_Gabaritos;
// Declaração do ponteiro universal que apontará para o início da lista encadeada que armazenará os dados de todos os alunos cadastrados
aluno *Lista_Alunos;

int menu(void);
void Cadastrar();
void Cadastrar_Gabarito();
void Cadastrar_Aluno();
void Salvar_Gabarito();
void Salvar_Aluno();
void Mostrar();
void Mostrar_Gabarito();
void Mostrar_Aluno();
void Pesquisar_Gabarito();
void Pesquisar_Aluno();
void Excluir();
void Exclusao_Gabarito();
void Exclusao_Aluno();
void Excluir_Alu(int matricula);
void Excluir_Gab(int codGabarito);
void Imprime_Gabarito(gabarito *end_gabarito);
void Imprime_Aluno(aluno *end_aluno, int opcao);
void Imprime_AlunoAntes(aluno *end_aluno, int opcao);
void Imprime_Todos_Gabaritos();
void Imprime_Todos_Alunos();
gabarito *Carrega_Gabaritos();
aluno *Carrega_Alunos();
gabarito *Busca_Gab(int codigo);
aluno *Busca_Alu(int matricula, aluno *inicio_da_pesquisa);
int Busca_TotalQuest(int codigo);
void Corrige_Prova();
void Ranqueamento();
void Size();
void Update_Size();
void Limpar_Memoria_Gab(gabarito *celula);
void Limpar_Memoria_Alu(aluno *celula);
void MostarEstatisca();
void Sobre();
int Esta_No_Vetor(int *vetor, int numero);

void HowMuchTimesRun();
void FirstRun();
void LoginSimplesMuitoSimplesMesmo();
void LoginRequest();

void Swap(int *xp, int *yp);
void Posicao(int codProva);
void BubbleSort(int arr[2][SIZE_ALU], int n);
