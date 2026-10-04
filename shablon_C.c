Шаблон C. Фильтр — выбираем строки по условию и сортируем
Задачи: 8, 11, 13, 17, 18, 21
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    if (fin == NULL || fout == NULL) return 1;

    char keys[1000][100];   // по чему сортируем
    char out1[1000][100];   // первое поле вывода
    char out2[1000][100];   // второе поле вывода
    char out3[1000][100];   // третье поле (если нужно)
    int n = 0;

    char line[256], f1[100], f2[100], f3[100], f4[100], f5[100];

    while (fgets(line, 256, fin) != NULL) {
        // === sscanf ПОД ФАЙЛ ===
        // пример: дата, читатель, книга, автор
        if (sscanf(line, "%s %s %s %s", f1, f2, f3, f4) != 4) continue;

        // === ФИЛЬТР — МЕНЯЕШЬ ПОД ЗАДАЧУ ===
        // пример: только книги Пушкина
        if (strcmp(f4, "Пушкин") != 0) continue;

        // === ЧТО СОРТИРУЕМ И ЧТО ВЫВОДИМ ===
        strcpy(keys[n], f2);   // сортируем по читателю
        strcpy(out1[n], f2);   // вывод: читатель
        strcpy(out2[n], f3);   // вывод: книга
        n++;
    }

    // сортировка по keys
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (strcmp(keys[j], keys[j + 1]) > 0) {
                char t[100];
                strcpy(t, keys[j]); strcpy(keys[j], keys[j + 1]); strcpy(keys[j + 1], t);
                strcpy(t, out1[j]); strcpy(out1[j], out1[j + 1]); strcpy(out1[j + 1], t);
                strcpy(t, out2[j]); strcpy(out2[j], out2[j + 1]); strcpy(out2[j + 1], t);
            }

    fprintf(fout, "Читатель Книга\n");
    for (int i = 0; i < n; i++)
        fprintf(fout, "%s %s\n", out1[i], out2[i]);

    fclose(fin); fclose(fout);
    return 0;
}

Что менять:
sscanf — под поля файла.
Строку if (strcmp(...) != 0) continue; — под условие фильтра.
Что в keys[n] (по чему сортируем) и что в out1/out2/out3 (что выводим).
Заголовок и формат fprintf.
