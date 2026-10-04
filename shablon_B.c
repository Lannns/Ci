Шаблон B. Считаем сумму значений по ключу
Задачи: 2, 4, 5, 10, 15, 16, 19, 23, 24, 26
Отличий от A — две строчки: counts[n] = value; и counts[found] += value;
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *fin = fopen("in.txt", "r");
    FILE *fout = fopen("out.txt", "w");
    if (fin == NULL || fout == NULL) return 1;

    char keys[1000][100];
    int counts[1000];
    int n = 0;

    char line[256], a[100], b[100], key[100];
    int value;

    while (fgets(line, 256, fin) != NULL) {
        // === sscanf ПОД ФАЙЛ (value — число, которое суммируем) ===
        // пример: номер, станция, пассажиры
        if (sscanf(line, "%s %s %d", a, key, &value) != 3) continue;

        int found = -1;
        for (int i = 0; i < n; i++)
            if (strcmp(keys[i], key) == 0) found = i;

        if (found == -1) {
            strcpy(keys[n], key);
            counts[n] = value;       // первая запись = само значение
            n++;
        } else {
            counts[found] += value;  // плюсуем
        }
    }

    // сортировка по ключу; если надо по убыванию суммы — см. ниже
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (strcmp(keys[j], keys[j + 1]) > 0) {
            // ЕСЛИ ПО УБЫВАНИЮ СУММЫ — ЗАМЕНИТЬ ВЕРХНЮЮ СТРОКУ НА:
            // if (counts[j] < counts[j + 1]) {
                char tmp[100]; strcpy(tmp, keys[j]);
                strcpy(keys[j], keys[j + 1]); strcpy(keys[j + 1], tmp);
                int t = counts[j]; counts[j] = counts[j + 1]; counts[j + 1] = t;
            }

    fprintf(fout, "Ключ Сумма\n");
    for (int i = 0; i < n; i++)
        fprintf(fout, "%s %d\n", keys[i], counts[i]);

    fclose(fin); fclose(fout);
    return 0;
}

Что менять:
sscanf — под поля файла.
Если значение = произведение двух чисел (задачи 15, 16, 24, 28): в sscanf читаешь два числа, потом value = x * y;.
Сортировка: по ключу (strcmp) или по убыванию суммы (counts[j] < counts[j+1]).
Заголовок.
