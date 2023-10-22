import numpy as np
from scipy.fft import fft, ifft

# Генерация случайных комплексных входных данных
N_values = [6, 10, 15, 20, 30]  # Длины преобразования (кратные 2, 3 и 5)
input_data = np.random.random(max(N_values)) + 1j * np.random.random(max(N_values))

for N in N_values:
    input_data_N = input_data[:N]  # Ограничиваем длину входных данных до N

    # Прямое FFT
    forward_fft_result = fft(input_data_N)

    # Обратное FFT
    inverse_fft_result = ifft(forward_fft_result)

    # Сравнение входных и выходных данных
    error = np.max(np.abs(input_data_N - inverse_fft_result))

    # Вывод результатов
    print(f"Длина преобразования {N}:")
    print("Исходные данные:\n", input_data_N)
    print("Результат прямого преобразования Фурье:\n", forward_fft_result)
    print("Результат обратного преобразования Фурье:\n", inverse_fft_result)
    print(f"Максимальная ошибка между входными и выходными данными: {error:.2e}\n")