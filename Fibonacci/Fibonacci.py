class MatrixFibonacci:
    start_matrix = [[1, 1],
                    [1, 0]]

    @staticmethod
    def __matrix_multiplication(m1, m2=start_matrix):

        a11 = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0]
        a12 = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1]
        a21 = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0]
        a22 = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1]
        r = [[a11, a12], [a21, a22]]
        return r

    def get_number(self, n):
        if n <= 0:
            return -1
        elif n <= 2:
            return n-1

        result_matrix = self.__matrix_multiplication(self.start_matrix)
        res = 2
        while res != n-1:
            if res * 2 > n - 1:
                result_matrix = self.__matrix_multiplication(result_matrix)
                res += 1
            elif res * 2 <= n - 1:
                result_matrix = self.__matrix_multiplication(result_matrix, result_matrix)
                res *= 2
        return result_matrix[0][1]


if __name__ == '__main__':
    fib = MatrixFibonacci()

    while True:
        n = int(input())
        print(fib.get_number(n))
