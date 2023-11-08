getnum = map(int, input().split())
print(sum(map(lambda x : x**2, getnum)) % 10)