def char_to_digit(c: str) -> int:
    if "0" <= c <= "9":
        return ord(c) - ord("0")
    if "a" <= c <= "z":
        return 10 + ord(c) - ord("a")
    return 36 + ord(c) - ord("A")


def parse(x: str) -> list[int]:
    num = []
    for c in x:
        num.append(char_to_digit(c))

    return num


def min_base(x: list[int]) -> int:
    return max(2, max(x) + 1)


def eval(x: list[int], b: int) -> int:
    S = 0
    base = 1
    for i in range(len(x) - 1, -1, -1):
        e = x[i]
        S += e * base
        base *= b
    return S


N = int(input())


def solve(A, B) -> str:
    A = parse(A)
    B = parse(B)
    A0 = min_base(A)
    B0 = min_base(B)
    A_bases = {eval(A, base): base for base in range(A0, 7501)}

    for b in range(B0, 7501):
        x = eval(B, b)
        if x in A_bases.keys():
            return f"{x} {A_bases[x]} {b}"

    return "CANNOT MAKE EQUAL"


def solve2(A, B) -> str:
    A = parse(A)
    B = parse(B)
    A0 = min_base(A)
    B0 = min_base(B)
    A_bases = [eval(A, base) for base in range(A0, 7501)]
    B_bases = [eval(B, base) for base in range(B0, 7501)]

    i = j = 0

    while i < len(A_bases) and j < len(B_bases):
        if A_bases[i] == B_bases[j]:
            return f"{A_bases[i]} {A0 + i} {B0 + j}"

        if A_bases[i] < B_bases[j]:
            i += 1
        else:
            j += 1

    return "CANNOT MAKE EQUAL"


import time

avg_solve1 = 0.0
avg_solve2 = 0.0
for _ in range(N):
    A, B = input().split()
    start = time.time()
    solve(A, B)
    end = time.time()
    avg_solve1 += end - start
    start = time.time()
    solve2(A, B)
    end = time.time()
    avg_solve2 += end - start

avg_solve1 /= N
avg_solve2 /= N

print(f"Avg Time (Hashmap): {avg_solve1}\n Avg Time (Two-Ptr): {avg_solve2}")
print(f"Winner: {'Hashmap' if avg_solve - 2 < avg_solve2 else 'Two-Ptr'}")
