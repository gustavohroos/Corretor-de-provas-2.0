#define NOME_MAX 100
#define RESPOSTAS_MAX 51
#define RESPOSTAS_MIN 1
int SIZE_GAB, SIZE_ALU;   

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

gabarito *ponteiro_gabarito;
aluno *ponteiro_aluno;
gabarito *Lista_Gabaritos;
aluno *Lista_Alunos;

aluno *Busca_Alu(int matricula, aluno *inicio_da_pesquisa);
aluno *Carrega_Alunos();
gabarito *Busca_Gab(int codigo);
gabarito *Carrega_Gabaritos();
int Busca_TotalQuest(int codigo);
int Esta_No_Vetor(int *vetor, int numero);
int menu(void);
int Questao_Mais_Acertada(int codProva);
int Questao_Mais_Errada(int codProva);
float Media_Acertos(int codGabarito);
void Cadastrar_Aluno();
void Cadastrar_Gabarito();
void Cadastrar();
void Corrige_Prova();
void Excluir_Alu(int matricula);
void Excluir_Gab(int codGabarito);
void Excluir();
void Exclusao_Aluno();
void Exclusao_Gabarito();
void Imprime_Aluno(aluno *end_aluno, int opcao);
void Imprime_AlunoAntes(aluno *end_aluno, int opcao);
void Imprime_Gabarito(gabarito *end_gabarito, int opcao);
void Imprime_Todos_Alunos();
void Imprime_Todos_Gabaritos();
void Limpar_Memoria_Alu(aluno *celula);
void Limpar_Memoria_Gab(gabarito *celula);
void MostrarEstatitiscas();
void Mostrar_Aluno();
void Mostrar_Gabarito();
void Mostrar();
void Pesquisar_Aluno();
void Pesquisar_Gabarito();
void Posicao(int codProva);
void Salvar_Aluno();
void Salvar_Gabarito();
void Size();
void Sobre();
void Update_Size();