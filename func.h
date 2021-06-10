#define NOME_MAX 100
#define RESPOSTAS_MAX 50
#define RESPOSTAS_MIN 1

// DECLARAÇÃO STRUCTS


struct prova {
  int codGabarito, totalQuestao;
  char resposta[RESPOSTAS_MAX];
  struct prova *prox;
};

typedef struct prova gabarito;

struct alu {
  int matricula, codGabarito, totalQuestao;
  char nome[NOME_MAX], resposta[RESPOSTAS_MAX];
  struct alu *prox;
};

typedef struct alu aluno;

// Declaração do ponteiro universal que apontará o endereço da célula responsável por armazenar dados do tipo gabarito de forma temporária
gabarito *ponteiro_gabarito;

// Declaração do ponteiro universal que apontará o endereço da célula responsável por armazenar dados do tipo aluno de forma temporária
aluno *ponteiro_aluno;


// VARIÁVEIS GLOBAIS


int SIZE_GAB, SIZE_ALU;   // Armazenam o número de linhas de gabaritos e alunos cadastrados nos arquivos "Gabaritos.txt" e "Alunos.txt"

// Declaração do ponteiro universal que apontará para o início da lista encadeada que armazenará os dados de todos os gabaritos cadastrados
gabarito *Lista_Gabaritos;

// Declaração do ponteiro universal que apontará para o início da lista encadeada que armazenará os dados de todos os alunos cadastrados
aluno *Lista_Alunos;


// DECLARAÇÃO FUNÇÕES


int menu(void);
void Cadastrar_Gabarito();
void Cadastrar_Aluno();
void Salvar_Gabarito();
void Salvar_Aluno();
void Pesquisar_Gabarito();
void Mostrar_Gabarito();
void Excluir();
void Exclui_Gab();
void Exclui_Aluno();
void Imprime_Gabarito(gabarito *end_gabarito);
void Imprime_Aluno(aluno *end_aluno);
void Imprime_Todos_Gabaritos();
gabarito *Carrega_Gabaritos();
aluno *Carrega_Alunos();
gabarito *Busca_Gab(int codigo);
int Busca_TotalQuest(int codigo);
void Size();
void Update_Size();
void Limpar_Memoria_Gab(gabarito *celula);
void Limpar_Memoria_Alu(aluno *celula);



