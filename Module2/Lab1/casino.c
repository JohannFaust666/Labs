#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <cs50.h>
#include <math.h>

int main(int argc, char *argv[])
{
    // Проверяем, что передано ровно два аргумента
    if (argc != 2)
    {
        printf("В аргументах не указан пользователь.\n");
        return 1;
    }

    // Открываем файл для чтения
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Такого пользователя нет: %s\n", argv[1]);
        return 1;
    }

    // Читаем банк игрока из файла
    int bank;
    if (fscanf(file, "%d", &bank) != 1)
    {
        printf("Не удалось прочитать файл: %s\n", argv[1]);
        return 1;
    }

    // Закрываем файл
    fclose(file);

    // Запрашиваем у пользователя ставку и проверяем, что она корректна
    int bet = 0;

    // Генерируем случайные числа относительно времени
    srand(time(NULL));
    bool keep_playing = true;
    while (keep_playing)
    {
        int minRange, maxRange, numTries = 0;

        // Коэфициент выигрыша (сам придумал)
        float coefficient;

        do
        {
            printf("Ваш баланс: %d\n", bank);
            printf("Введите вашу ставку (от 1 до %d): ", bank);
            scanf("%i", &bet);
            getchar(); // считываем символ переноса строки из входного буфера
        }
        while (bet < 1 || bet > bank);

        // Диапазон
        printf("Минимальное число диапазона: ");
        scanf("%i", &minRange);
        getchar(); // считываем символ переноса строки из входного буфера

        printf("Максимальное число диапазона: ");
        scanf("%i", &maxRange);
        getchar(); // считываем символ переноса строки из входного буфера

        // Количество попыток
        printf("Количество попыток: ");
        scanf("%i", &numTries);
        getchar(); // считываем символ переноса строки из входного буфера

        // Генерируем случайное число
        int randomNumber = minRange + rand() % (maxRange - minRange + 1);

        int lose = 1;

        for (int i = 1; i <= numTries; i++)
        {
            coefficient = 1 /
                          (1 / ((float)(maxRange - minRange + 1) / numTries)) - 1 /
                          (numTries - (1 / ((float)(maxRange - minRange + 1) / numTries)));

            int guess = 0;
            printf("Попытка %i: ", i);
            scanf("%i", &guess);

            if (guess == randomNumber)
            {
                printf("Вы угадали число %d с %i попытки(-ок)!\n", randomNumber, i);
                lose = 0;
                bank += round((float)bet * coefficient); // Вернуть round((float)bet * 0.65) если не понравится
                break;
            }
            else if (guess < randomNumber)
            {
                printf("Нужное число больше!\n");
            }
            else if (guess > randomNumber)
            {
                printf("Нужное число меньше!\n");
            }
        }

        if (lose == 1)
        {
            printf("К сожалению, загаданное число было %d.\n", randomNumber);
            bank -= round((float)bet); // Вернуть round((float)bet * 0.65) если не понравится
        }

        // Проверяем, достаточно ли денег у пользователя для продолжения игры
        if (bank < 1)
        {
            printf("У вас закончились деньги. Игра окончена!\n");
            keep_playing = false;
        }
        else
        {
            // Спрашиваем пользователя, хочет ли он продолжить игру
            char answer;
            do
            {
                printf("Ваш баланс: %d\n", bank);
                printf("Хотите сыграть ещё раз? (y/n) ");
                scanf(" %c", &answer);
            }
            while (answer != 'y' && answer != 'n');

            keep_playing = answer == 'y';
        }
    }

    // Сохраняем банк игрока в файл
    file = fopen(argv[1], "w");
    if (file == NULL)
    {
        printf("Не удалось открыть файл %s\n", argv[1]);
        return 1;
    }

    fprintf(file, "%d\n", bank);
    fclose(file);

    return 0;
}
