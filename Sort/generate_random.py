import random
import sys


def generate_random_numbers(filename: str, count: int, min_value: int = 1, max_value: int = 1_000_000):
    """生成指定数量的随机整数并保存到文件"""
    with open(filename, 'w') as f:
        for _ in range(count):
            number = random.randint(min_value, max_value)
            f.write(f"{number}\n")

if __name__ == "__main__":
    # 从命令行参数读取数量
    if len(sys.argv) > 1:
        try:
            total_number = int(sys.argv[1])
        except ValueError:
            print("参数错误，请输入整数。使用默认数量 50000")
            total_number = 50000
    else:
        total_number = 50000
    generate_random_numbers("..\\Sort\\random_numbers.txt", total_number)
    print("已生成随机整数到文件 random_numbers.txt")
