#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>
#define BUFFER 64

typedef struct songs {
    char *name;
    char *artist;
    char *album;
    int year;
    struct songs *next;
} SongsList;

SongsList *principal = NULL;

// Cria uma lista vazia apontando para NULL
SongsList *initData(char *name, char *artist, char *album, int year) {
    SongsList *newList;
    newList = (SongsList *)malloc(sizeof(SongsList));

    newList->name = (char *)malloc(strlen(name)+1);
    strncpy(newList->name, name, strlen(name)+1);

    newList->artist = (char *)malloc(strlen(artist)+1);
    strncpy(newList->artist, artist, strlen(artist)+1);

    newList->album = (char *)malloc(strlen(album)+1);
    strncpy(newList->album, album, strlen(album)+1);

    newList->year = year;
    newList->next = NULL;

    return newList;
}

// Insere os dados na lista e atualiza os ponteiros
SongsList *insertData(SongsList *data, char *name, char *artist, char *album, int year) {
    SongsList *newList;
    newList = (SongsList *)malloc(sizeof(SongsList));

    newList->name = (char *)malloc(strlen(name)+1);
    strncpy(newList->name, name, strlen(name)+1);

    newList->artist = (char *)malloc(strlen(artist)+1);
    strncpy(newList->artist, artist, strlen(artist)+1);

    newList->album = (char *)malloc(strlen(album)+1);
    strncpy(newList->album, album, strlen(album)+1);

    newList->year = year;
    newList->next = data;

    return newList;
}

// Insere uma música
void insertSong(void) {
    setlocale(LC_ALL, "Portuguese");
    char *name;
    char *artist;
    char *album;
    int year;

    name = (char *)malloc(BUFFER);
    artist = (char *)malloc(BUFFER);
    album = (char *)malloc(BUFFER);

    fprintf(stdout, " == Informe os dados da música ==\n");
    getchar();
    fprintf(stdout, "\nDigite o nome da música: ");
    gets(name);
    fprintf(stdout, "Digite o nome da banda/artista: ");
    gets(artist);
    fprintf(stdout, "Digite o nome do albúm: ");
    gets(album);
    fprintf(stdout, "Digite o ano de lançamento: ");
    scanf("%d", &year);

    if(principal == NULL) {
        principal = initData(name, artist, album, year);
    } else {
        principal = insertData(principal, name, artist, album, year);
    }

}

// Insere no arquivo de texto
void saveSongs(SongsList *data) {
    fprintf(stdout, " == Informe os dados da música ==\n");
    FILE *registerSongs;
    registerSongs = fopen("playlist.txt", "w");

    fprintf(registerSongs, "Minha playlist\n");

    for(; data != NULL; data = data->next) {
        fprintf(registerSongs, "\nNome da música: %s\n", data->name);
        fprintf(registerSongs, "Nome do artista: %s\n", data->artist);
        fprintf(registerSongs, "Nome do albúm: %s\n", data->album);
        fprintf(registerSongs, "Ano de lançamento: %d\n", data->year);
    } 

    fprintf(stdout, "\n\n O arquivo da playlist foi gerado com sucesso!\n");
    fclose(registerSongs);
    getchar();
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    int option;
    INICIO:
    system("clear");

    printf(" === Criando uma playlist ===\n\n");
    printf("[1] Para inserir uma música\n");
    printf("[2] Para salvar suas músicas\n");
    printf("[3] Para sair\n");
    printf("\nDigite a sua opção: ");
    scanf("%d", &option);

    switch(option) {
        case 1:
            system("clear");
            insertSong();
            goto INICIO;

        case 2:
            system("clear");
            saveSongs(principal);
            goto INICIO;

        case 3:
            system("clear");
            return 0;

        default:
            system("clear");
            printf("\n\n Opção inválida!!");
            goto INICIO;
    }
}
