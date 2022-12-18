import unittest
import subprocess

EPS = 1e-8


def run_calculator_program(expression):
    result = subprocess.run(["./Exe", expression],
                            stdout=subprocess.PIPE, check=True)
    return float(result.stdout)


class TestCalculator(unittest.TestCase):
    def test_integral_add(self):
        result = run_calculator_program("1+2")
        self.assertTrue(abs(result - 3.0) < EPS)

    def test_integral_substract(self):
        result = run_calculator_program("1-2")
        self.assertTrue(abs(result - (-1.0)) < EPS)

    def test_integral_multiply(self):
        result = run_calculator_program("256*1024")
        self.assertTrue(abs(result - 262144.0) < EPS)

    def test_integral_divide(self):
        result = run_calculator_program("32/64")
        self.assertTrue(abs(result - 0.5) < EPS)

    def test_integral_power(self):
        result = run_calculator_program("2^8")
        self.assertTrue(abs(result - 256.0) < EPS)

    def test_integral_complex(self):
        result = run_calculator_program("7+3^4-8*9+10/100+2*3/4^5")
        self.assertTrue(abs(result - 16.105859375) < EPS)

    def test_integral_failure(self):
        with self.assertRaises(subprocess.CalledProcessError):
            run_calculator_program("1a1")
        with self.assertRaises(subprocess.CalledProcessError):
            run_calculator_program("1--1")
        with self.assertRaises(subprocess.CalledProcessError):
            run_calculator_program("a")
        with self.assertRaises(subprocess.CalledProcessError):
            run_calculator_program("123/-1")


if __name__ == "__main__":
    unittest.main()
