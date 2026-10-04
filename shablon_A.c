Шаблон A. Считаем количество записей по ключу
Задачи: 1, 3, 6, 7, 12, 14, 20, 22, 25
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    if (fin == NULL || fout == NULL) return 1;

    char keys[1000][100];
    int counts[1000];
    int n = 0;

    char line[256], a[100], b[100], c[100], key[100];
    int v1;

    while (fgets(line, 256, fin) != NULL) {
        // === СЮДА ПОДСТАВЛЯЕШЬ sscanf ПОД ФАЙЛ ===
        // пример для 3 полей: номер, время, станция
        if (sscanf(line, "%s %s %[^\n]", a, b, key) != 3) continue;

        int found = -1;
        for (int i = 0; i < n; i++)
            if (strcmp(keys[i], key) == 0) found = i;

        if (found == -1) {
            strcpy(keys[n], key);
            counts[n] = 1;
            n++;
        } else {
            counts[found]++;
        }
    }

    // сортировка по ключу (алфавит)
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (strcmp(keys[j], keys[j + 1]) > 0) {
                char tmp[100]; strcpy(tmp, keys[j]);
                strcpy(keys[j], keys[j + 1]); strcpy(keys[j + 1], tmp);
                int t = counts[j]; counts[j] = counts[j + 1]; counts[j + 1] = t;
            }

    // === ЗАГОЛОВОК МЕНЯЕШЬ ПОД ЗАДАЧУ ===
    fprintf(fout, "Станция Количество рейсов\n");
    for (int i = 0; i < n; i++)
        fprintf(fout, "%s %d\n", keys[i], counts[i]);

    fclose(fin); fclose(fout);
    return 0;
}

Что менять:
Строку sscanf — под поля файла.
Заголовок в fprintf.
Иногда — сортировку (если «по убыванию»).
