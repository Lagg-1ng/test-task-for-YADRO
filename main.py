import numpy as np


class FastFourierTransform:
    def fft(self, a, invert=False):
        n = len(a)
        if n <= 1:
            return a

        # Split the array into even and odd parts
        a_even = self.fft(a[::2], invert)
        a_odd = self.fft(a[1::2], invert)

        # Compute the twiddle factors
        angle = 2 * np.pi / n * (1 if invert else -1)
        w = np.exp(angle * 1j)

        # Combine the results using the twiddle factors
        mid = n // 2
        for i in range(mid):
            even_part = a_even[i]
            odd_part = w ** i * a_odd[i]
            a[i] = even_part + odd_part
            a[i + mid] = even_part - odd_part

        if invert:
            a /= 2

        return a

    def ifft(self, a):
        return self.fft(a, invert=True)


# Пример использования
if __name__ == "__main__":
    fft = FastFourierTransform()

    # Генерация случайных комплексных входных данных
    input_data = np.random.random(16) + 1j * np.random.random(16)

    # Прямое FFT
    forward_fft_result = fft.fft(input_data.copy())

    # Обратное FFT
    inverse_fft_result = fft.ifft(forward_fft_result.copy())

    # Вывод результатов
    print("Input data:\n", input_data)
    print("Forward FFT result:\n", forward_fft_result)
    print("Inverse FFT result:\n", inverse_fft_result)
