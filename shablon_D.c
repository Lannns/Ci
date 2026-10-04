Шаблон D. Процент (задача 9)
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    if (fin == NULL || fout == NULL) return 1;

    char keys[1000][100];
    int total[1000];   // всего
    int bad[1000];     // невыполненных
    int n = 0;

    char line[256], f1[100], f2[100], f3[100], f4[100], key[100];

    while (fgets(line, 256, fin) != NULL) {
        // пример: заказчик, название, производитель, дата(или пусто)
        int got = sscanf(line, "%s %s %s %s", f1, f2, f3, f4);
        if (got < 3) continue;

        strcpy(key, f3);   // ключ = производитель

        int found = -1;
        for (int i = 0; i < n; i++)
            if (strcmp(keys[i], key) == 0) found = i;

        if (found == -1) {
            strcpy(keys[n], key);
            total[n] = 1;
            bad[n] = 0;
            found = n;
            n++;
        } else {
            total[found]++;
        }

        // если дата НЕ прочиталась (got == 3) — ремонт не выполнен
        if (got == 3) bad[found]++;
    }

    // сортировка по ключу
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (strcmp(keys[j], keys[j + 1]) > 0) {
                char tmp[100]; strcpy(tmp, keys[j]);
                strcpy(keys[j], keys[j + 1]); strcpy(keys[j + 1], tmp);
                int t = total[j]; total[j] = total[j + 1]; total[j + 1] = t;
                t = bad[j]; bad[j] = bad[j + 1]; bad[j + 1] = t;
            }

    fprintf(fout, "Производитель Процент\n");
    for (int i = 0; i < n; i++) {
        int percent = bad[i] * 100 / total[i];
        fprintf(fout, "%s %d%%\n", keys[i], percent);
    }

    fclose(fin); fclose(fout);
    return 0;
}
Что менять:
sscanf и got < 3 / got == 3 — под структуру файла.
Ключ (key = f3).
Заголовок.
