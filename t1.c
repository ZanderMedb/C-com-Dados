#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_nome 100
#define max_fone 18
#define max_curso 25
#define max_notas 10
#define max_Final 20

typedef struct {
    char nome[max_nome];
    char telefone[max_fone];
    char curso[max_curso];
    float notas[max_notas];
    int Nnotas;
    float media;
    char Final[max_Final];
} Aluno;

void CalculaM(Aluno *aluno) {
    float soma = 0;
    for (int i = 0; i < aluno->Nnotas; i++) {
        soma += aluno->notas[i];
    }
    aluno->media = soma / aluno->Nnotas;
}

void situcao_aluno(Aluno *aluno) {
    if (aluno->media >= 7.0) {
        strcpy(aluno->Final, "APROVADO");
    } else {
        strcpy(aluno->Final, "REPROVADO");
    }
}

int main() {
    FILE *fp = fopen("DadosEntrada.csv", "r");
    FILE *p = fopen("SituacaoFinal.csv", "w");

     if (fp == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    if (p == NULL) {
        printf("Erro ao abrir o arquivo de saída.\n");
        return 1;
    }

    char buffer[1024];
    fgets(buffer, sizeof(buffer), fp); 

    Aluno alunos[max_nome];
    int qntAlunos = 0;

    while (fscanf(fp, "%49[^,],%14[^,],%49[^,],%f,%f\n", alunos[qntAlunos].nome, alunos[qntAlunos].telefone, alunos[qntAlunos].curso) != EOF) {
        alunos[qntAlunos].Nnotas = 0;
        float nota;
        while (fscanf(fp, "%f,", &nota) == 1) {
            alunos[qntAlunos].notas[alunos[qntAlunos].Nnotas++] = nota;
        }
        CalculaM(&alunos[qntAlunos]);
        situcao_aluno(&alunos[qntAlunos]);
        qntAlunos++;
    }

    for (int i = 0; i < qntAlunos; i++) {
        fprintf(p, "%s, %.2f, %s\n", alunos[i].nome, alunos[i].media, alunos[i].Final);
    }

    fclose(fp);
    fclose(p);

    printf("SituacaoFinal.csv gerado com sucesso.\n");

    return 0;
}

