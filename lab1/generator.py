#!/usr/bin/env python3
"""generator.py – генератор строк вида
+<country>-<city>-<phone>\t<random_string>

Запуск:
    python generator.py 1000 -o data.txt

Аргументы:
    count  – количество строк для генерации (обязательный)
    -o/--output – путь к выходному файлу (по умолчанию output.txt)
"""
import argparse
import random
import string
from typing import List

MAX_RANDOM_STRING_LENGTH = 2048


def generate_line() -> str:
    """Формирует одну строку с телефонным номером и случайной строкой."""
    country_code: str = f"+{random.randint(0, 999)}"  # 1‑3 цифры
    city_code: str = f"{random.randint(0, 99999)}"    # 1-5
    phone_number: str = f"{random.randint(1000000, 9999999)}"  # 7 цифр

    rand_len: int = random.randint(1, MAX_RANDOM_STRING_LENGTH)
    rand_str: str = "".join(random.choices(string.ascii_letters, k=rand_len))

    return f"{country_code}-{city_code}-{phone_number}\t{rand_str}"


def write_lines(count: int, file_path: str) -> None:
    """Записывает `count` строк в файл `file_path`."""
    # Генерируем все строки списком для более быстрой записи
    lines: List[str] = [generate_line() for _ in range(count)]
    with open(file_path, "w", encoding="utf-8") as f:
        f.write("\n".join(lines))


def parse_args():
    parser = argparse.ArgumentParser(
        description="Генерирует строки телефонных записей и сохраняет их в файл.)"
    )
    parser.add_argument(
        "count",
        type=int,
        help="Количество строк для генерации (положительное целое).",
    )
    parser.add_argument(
        "-o",
        "--output",
        default="output.txt",
        help="Имя/путь выходного файла (по умолчанию output.txt).",
    )
    args = parser.parse_args()

    if args.count <= 0:
        parser.error("count должно быть положительным целым числом")

    return args


def main() -> None:
    args = parse_args()
    write_lines(args.count, args.output)


if __name__ == "__main__":
    main()
