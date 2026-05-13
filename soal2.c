// Nama : Daffa Rafandy Tariganb
// NIM : 13224068
// Soal 2 Praktikum PMP Modul 5 - Foundation of Algorithm

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    int visited;
    struct Node *atas;
    struct Node *bawah;
    struct Node *kiri;
    struct Node *kanan;
} Node;

int R, C;
Node ***grid = NULL;

void buatgrid() {
    grid = malloc(R * sizeof(Node **));
    for (int i = 0; i < R; i++) {
        grid[i] = malloc(C * sizeof(Node *));
    }
}

void bacagrid() {
    for (int i = 0; i < R; i++) {
        char row[C + 1];
        scanf("%s", row);
        for (int j = 0; j < C; j++) {
            grid[i][j] = malloc(sizeof(Node));
            grid[i][j]-> value = row[j] - '0';
            grid[i][j]-> visited = 0;
            grid[i][j]-> atas = grid[i][j]-> bawah = grid[i][j]-> kiri = grid[i][j]-> kanan = NULL;
        }
    }
}
void ceksekeliling() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (i > 0) grid[i][j]-> atas = grid[i - 1][j];
            if (i < R - 1) grid[i][j] -> bawah = grid[i + 1][j];
            if (j > 0) grid[i][j] -> kiri = grid[i][j - 1];
            if (j < C - 1) grid[i][j]-> kanan = grid[i][j + 1];
        }
    }
}
int dfs(Node *node) {
    if (!node || node->visited || node->value == 0) return 0;
    node->visited = 1;
    int size = 1;
    size += dfs(node->atas);
    size += dfs(node->bawah);
    size += dfs(node->kiri);
    size += dfs(node->kanan);
    return size;
}

void hitung_pulau_dan_ukurannya(int *islands, int *largest) {
    *islands = 0;
    *largest = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (!grid[i][j]->visited && grid[i][j]->value == 1) {
                (*islands)++;
                int size = dfs(grid[i][j]);
                if (size > *largest) *largest = size;
            }
        }
    }
}
void hapusgrid() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            free(grid[i][j]);
        }
        free(grid[i]);
    }
    free(grid);
}

int main() {
    scanf("%d %d", &R, &C);
    buatgrid();
    bacagrid();
    ceksekeliling();

    int islands, largest;
    hitung_pulau_dan_ukurannya(&islands, &largest);

    printf("ISLANDS %d\n", islands);
    printf("LARGEST %d\n", largest);

    hapusgrid();
    return 0;
}
