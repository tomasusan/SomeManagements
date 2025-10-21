import random
import sys


def generate_random_numbers(filename: str, count: int, min_value: int = 1, max_value: int = 1_000_000):
    """����ָ��������������������浽�ļ�"""
    with open(filename, 'w') as f:
        for _ in range(count):
            number = random.randint(min_value, max_value)
            f.write(f"{number}\n")

if __name__ == "__main__":
    # �������в�����ȡ����
    if len(sys.argv) > 1:
        try:
            total_number = int(sys.argv[1])
        except ValueError:
            print("��������������������ʹ��Ĭ������ 50000")
            total_number = 50000
    else:
        total_number = 50000
    generate_random_numbers("..\\Sort\\random_numbers.txt", total_number)
    print("����������������ļ� random_numbers.txt")
