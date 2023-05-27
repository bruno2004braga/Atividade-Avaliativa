#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_USERS 1000

typedef struct {
    int id;
    char nome[100];
    char email[100];
    char sexo[20];
    char endereco[100];
    double altura;
    int vacina;
} Usuario;

Usuario usuarios[MAX_USERS];
int numUsuarios = 0;

int gerarIdAleatorio() {
    srand(time(NULL));
    return rand() % 10000 + 1;
}

bool validarEmail(const char *email) {
    return strchr(email, '@') != NULL;
}

bool validarSexo(const char *sexo) {
    return strcmp(sexo, "Feminino") == 0 || strcmp(sexo, "Masculino") == 0 || strcmp(sexo, "Indiferente") == 0;
}

bool validarAltura(double altura) {
    return altura >= 1.0 && altura <= 2.0;
}

void adicionarUsuario() {
    if (numUsuarios >= MAX_USERS) {
        printf("Limite máximo de usuários atingido.\n");
        return;
    }
    
    Usuario novoUsuario;
    
    printf("\nNome completo: ");
    fgets(novoUsuario.nome, sizeof(novoUsuario.nome), stdin);
    novoUsuario.nome[strcspn(novoUsuario.nome, "\n")] = '\0';  

    printf("Email: ");
    fgets(novoUsuario.email, sizeof(novoUsuario.email), stdin);
    novoUsuario.email[strcspn(novoUsuario.email, "\n")] = '\0';  
    
    if (!validarEmail(novoUsuario.email)) {
        printf("Email inválido. O email deve conter o caractere '@'.\n");
        return;
    }
    
    printf("Sexo ( Feminino - Masculino - Indiferente ): ");
    fgets(novoUsuario.sexo, sizeof(novoUsuario.sexo), stdin);
    novoUsuario.sexo[strcspn(novoUsuario.sexo, "\n")] = '\0';  
    
    if (!validarSexo(novoUsuario.sexo)) {
        printf("Sexo inválido. Digite 'Feminino', 'Masculino' ou 'Indiferente'.\n");
        return;
    }
    
    printf("Endereço: ");
    fgets(novoUsuario.endereco, sizeof(novoUsuario.endereco), stdin);
    novoUsuario.endereco[strcspn(novoUsuario.endereco, "\n")] = '\0';  
    
    printf("Altura (1 - 2 metros): ");
    scanf("%lf", &novoUsuario.altura);
    getchar();  
    
    if (!validarAltura(novoUsuario.altura)) {
        printf("Altura inválida. A altura deve estar entre 1 e 2 metros.\n");
        return;
    }
    
    printf("Vacina ( 1 - Sim / 0 - Não): ");
    scanf("%d", &novoUsuario.vacina);
    getchar();  
    
    novoUsuario.id = gerarIdAleatorio();
    
    usuarios[numUsuarios++] = novoUsuario;
    
    printf("Usuário adicionado com sucesso. ID: %d\n", novoUsuario.id);
}

void editarUsuario() {
    int id;
    printf("Digite o ID do usuário a ser editado: ");
    scanf("%d", &id);
    getchar();  
    
    bool usuarioEncontrado = false;
    
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].id == id) {
            Usuario *usuario = &usuarios[i];
            
            printf("Nome completo (%s): ", usuario->nome);
            fgets(usuario->nome, sizeof(usuario->nome), stdin);
            usuario->nome[strcspn(usuario->nome, "\n")] = '\0';
            
            printf("Email (%s): ", usuario->email);
            fgets(usuario->email, sizeof(usuario->email), stdin);
            usuario->email[strcspn(usuario->email, "\n")] = '\0';
            
            if (!validarEmail(usuario->email)) {
                printf("Email inválido. O email deve conter o caractere '@'.\n");
                return;
            }
            
            printf("Sexo (%s): ", usuario->sexo);
            fgets(usuario->sexo, sizeof(usuario->sexo), stdin);
            usuario->sexo[strcspn(usuario->sexo, "\n")] = '\0';
            
            if (!validarSexo(usuario->sexo)) {
                printf("Sexo inválido. Digite 'Feminino', 'Masculino' ou 'Indiferente'.\n");
                return;
            }
            
            printf("Endereço (%s): ", usuario->endereco);
            fgets(usuario->endereco, sizeof(usuario->endereco), stdin);
            usuario->endereco[strcspn(usuario->endereco, "\n")] = '\0';
            
            printf("\nAltura (%.2lf): ", usuario->altura);
            scanf("%lf", &usuario->altura);
            getchar();
            
            if (!validarAltura(usuario->altura)) {
                printf("\nAltura inválida. A altura deve estar entre 1 e 2 metros.\n");
                return;
            }
            
            printf("\nVacina (%d - Sim / 0 - Não): ", usuario->vacina);
            scanf("%d", &usuario->vacina);
            getchar();
            
            printf("\nUsuário editado com sucesso.\n");
            usuarioEncontrado = true;
            break;
        }
    }
    
    if (!usuarioEncontrado) {
        printf("\nUsuário não encontrado.\n");
    }
}

void excluirUsuario() {
    int id;
    printf("\nDigite o ID do usuário a ser excluído: ");
    scanf("%d", &id);
    getchar();  

    bool usuarioEncontrado = false;
    
    for (int i = 0; i < numUsuarios; i++) {
        if (usuarios[i].id == id) {
            for (int j = i; j < numUsuarios - 1; j++) {
                usuarios[j] = usuarios[j + 1];
            }
            
            numUsuarios--;
            
            printf("\nUsuário excluído com sucesso.\n");
            usuarioEncontrado = true;
            break;
        }
    }
    
    if (!usuarioEncontrado) {
        printf("\nUsuário não encontrado.\n");
    }
}

void buscarUsuarioPorEmail() {
    char email[100];
    printf("\nDigite o email do usuário a ser buscado: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0';
    
    bool usuarioEncontrado = false;
    
    for (int i = 0; i < numUsuarios; i++) {
        if (strcmp(usuarios[i].email, email) == 0) {
            printf("\nUsuário encontrado:\n\n");
            printf("ID: %d\n", usuarios[i].id);
            printf("Nome: %s\n", usuarios[i].nome);
            printf("Email: %s\n", usuarios[i].email);
            printf("Sexo: %s\n", usuarios[i].sexo);
            printf("Endereço: %s\n", usuarios[i].endereco);
            printf("Altura: %.2lf\n", usuarios[i].altura);
            printf("Vacina: %s\n", usuarios[i].vacina ? "Sim" : "Não");
            usuarioEncontrado = true;
            break;
        }
    }
    
    if (!usuarioEncontrado) {
        printf("\nUsuário não encontrado.\n");
    }
}

void imprimirUsuarios() {
    if (numUsuarios == 0) {
        printf("\nNenhum usuário cadastrado.\n");
        return;
    }
    
    printf("\nLista de usuários cadastrados:\n\n");
    
    for (int i = 0; i < numUsuarios; i++) {
        printf("ID: %d\n", usuarios[i].id);
        printf("Nome: %s\n", usuarios[i].nome);
        printf("Email: %s\n", usuarios[i].email);
        printf("Sexo: %s\n", usuarios[i].sexo);
        printf("Endereço: %s\n", usuarios[i].endereco);
        printf("Altura: %.2lf\n", usuarios[i].altura);
        printf("Vacina: %s\n", usuarios[i].vacina ? "Sim" : "Não");
        printf("\n");
    }
}

void fazerBackup() {
    FILE *arquivo = fopen("backup.txt", "w");
    
    if (arquivo == NULL) {
        printf("\nErro ao criar o arquivo de backup.\n");
        return;
    }
    
    for (int i = 0; i < numUsuarios; i++) {
        fprintf(arquivo, "%d;%s;%s;%s;%s;%.2lf;%d\n", usuarios[i].id, usuarios[i].nome, usuarios[i].email, usuarios[i].sexo,
                usuarios[i].endereco, usuarios[i].altura, usuarios[i].vacina);
    }
    
    fclose(arquivo);
    
    printf("\nBackup realizado com sucesso.\n");
}

void fazerRestauracao() {
    FILE *arquivo = fopen("backup.txt", "r");
    
    if (arquivo == NULL) {
        printf("\nArquivo de backup não encontrado.\n");
        return;
    }
    
    numUsuarios = 0;
    
    while (fgets(usuarios[numUsuarios].nome, sizeof(usuarios[numUsuarios].nome), arquivo) != NULL) {
        sscanf(usuarios[numUsuarios].nome, "%d;%[^;];%[^;];%[^;];%[^;];%lf;%d\n", &usuarios[numUsuarios].id,
               usuarios[numUsuarios].nome, usuarios[numUsuarios].email, usuarios[numUsuarios].sexo,
               usuarios[numUsuarios].endereco, &usuarios[numUsuarios].altura, &usuarios[numUsuarios].vacina);
        
        usuarios[numUsuarios].nome[strcspn(usuarios[numUsuarios].nome, "\n")] = '\0';
        usuarios[numUsuarios].email[strcspn(usuarios[numUsuarios].email, "\n")] = '\0';
        usuarios[numUsuarios].sexo[strcspn(usuarios[numUsuarios].sexo, "\n")] = '\0';
        usuarios[numUsuarios].endereco[strcspn(usuarios[numUsuarios].endereco, "\n")] = '\0';
        
        numUsuarios++;
    }
    
    fclose(arquivo);
    
    printf("\nRestauração dos dados realizada com sucesso.\n");
}

int main() {
    char opcao;
    
    do {
        printf("\nEscolha uma opção:\n\n");
        printf("1 - Adicionar usuário\n");
        printf("2 - Editar usuário\n");
        printf("3 - Excluir usuário\n");
        printf("4 - Buscar usuário por email\n");
        printf("5 - Imprimir todos os usuários cadastrados\n");
        printf("6 - Fazer backup dos usuários cadastrados\n");
        printf("7 - Fazer restauração dos dados\n");
        printf("0 - Sair\n");
        printf("\nOpção:\t ");
        scanf("%c", &opcao);
        getchar();  
                
        switch (opcao) {
            case '1':
                adicionarUsuario();
                break;
            case '2':
                editarUsuario();
                break;
            case '3':
                excluirUsuario();
                break;
            case '4':
                buscarUsuarioPorEmail();
                break;
            case '5':
                imprimirUsuarios();
                break;
            case '6':
                fazerBackup();
                break;
            case '7':
                fazerRestauracao();
                break;
            case '0':
                printf("Encerrando o programa.\n");
                break;
            default:
                printf("Opção inválida. Digite novamente.\n");
        }
    } while (opcao != '0');
    
    return 0;
}
