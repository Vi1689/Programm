#include <stdio.h>

// Определение констант и параметров модели
double initial_time = 0.0, total_time = 90.0, time_step = 1, alpha_external = 0.999, 
alpha_internal = 0.999, kappa_val = 0.042, rho_val = 0.952, beta_val = 0.999, mu_val = 0.0188, initial_exposed = 99.00, initial_recovered = 24.00;

// Функция для вычисления правых частей дифференциальных уравнений
void calculate_derivatives(double time, double susceptible, double exposed, double infected, double recovered, double deceased, double total_population,
                           double *dSusceptible, double *dExposed, double *dInfected, double *dRecovered, double *dDeceased)
{
    *dSusceptible = -((alpha_internal * susceptible * infected / total_population) + (alpha_external * susceptible * exposed / total_population));                    // Вычисление dS/dt
    *dExposed = ((alpha_internal * susceptible * infected / total_population) + (alpha_external * susceptible * exposed / total_population)) - (kappa_val + rho_val) * exposed; // Вычисление dE/dt
    *dInfected = kappa_val * exposed - beta_val * infected - mu_val * infected;                                       // Вычисление dI/dt
    *dRecovered = beta_val * infected + rho_val * exposed - mu_val * infected;                                         // Вычисление dR/dt
    *dDeceased = mu_val * infected;                                                              // Вычисление dD/dt
}

// Функция для вывода результатов
void output_results(double time, double susceptible, double exposed, double infected, double recovered, double deceased, double total_population, FILE *output_file)
{
    fprintf(output_file, "%.2f %.2f %.2f %.2f %.2f %.2f %.2f\n", time, susceptible, exposed, infected, recovered, deceased, total_population);
}

int main()
{
    // Открытие файла для записи результатов
    FILE *file_output = fopen("/home/vitalii/Bi4_Mat/kursach/test.txt", "w");
    if (file_output == NULL)
    {
        printf("Ошибка открытия файла.\n");
        return 1;
    }

    // Инициализация начальных значений переменных модели
    double time = initial_time;
    double susceptible = 2798170.0 - initial_exposed - initial_recovered; // Начальное значение подверженных инфекции
    double exposed = initial_exposed;                  // Начальное значение экспоненциально инфицированных
    double infected = 0.0;                 // Начальное значение инфицированных
    double recovered = initial_recovered;                  // Начальное значение выздоровевших
    double deceased = 0.0;                 // Начальное значение умерших
    double total_population = susceptible + exposed + infected + recovered + deceased;   // Общее количество людей в системе

    // Цикл интегрирования дифференциальных уравнений
    for (time = 1; time <= total_time; time += time_step)
    {
        total_population = susceptible + exposed + infected + recovered + deceased; // Обновление общего количества людей

        // Вычисление правых частей уравнений на текущем шаге
        double dSusceptible1, dExposed1, dInfected1, dRecovered1, dDeceased1;
        calculate_derivatives(time, susceptible, exposed, infected, recovered, deceased, total_population, &dSusceptible1, &dExposed1, &dInfected1, &dRecovered1, &dDeceased1);

        // Прогнозирование значений на следующем шаге
        double susceptible_next = susceptible + time_step * dSusceptible1;
        double exposed_next = exposed + time_step * dExposed1;
        double infected_next = infected + time_step * dInfected1;
        double recovered_next = recovered + time_step * dRecovered1;
        double deceased_next = deceased + time_step * dDeceased1;

        // Коррекция на половинном шаге
        double dSusceptible2, dExposed2, dInfected2, dRecovered2, dDeceased2;
        calculate_derivatives(time + time_step, susceptible_next, exposed_next, infected_next, recovered_next, deceased_next, total_population, &dSusceptible2, &dExposed2, &dInfected2, &dRecovered2, &dDeceased2);

        // Усредненная коррекция значений на следующем шаге
        susceptible += time_step * (dSusceptible1 + dSusceptible2) / 2;
        exposed += time_step * (dExposed1 + dExposed2) / 2;
        infected += time_step * (dInfected1 + dInfected2) / 2;
        recovered += time_step * (dRecovered1 + dRecovered2) / 2;
        deceased += time_step * (dDeceased1 + dDeceased2) / 2;

        // Вывод результатов в файл
        output_results(time, susceptible, exposed, infected, recovered, deceased, total_population, file_output);
    }

    fclose(file_output); // Закрытие файла

    return 0;
}
