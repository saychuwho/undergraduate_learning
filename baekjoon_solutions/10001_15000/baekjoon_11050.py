import math

N, K = map(int, input().split())
print(int(math.factorial(N) / (math.factorial(N-K) * math.factorial(K))))