import sys


T = int(sys.stdin.readline())

save = {}

def fibonacci(n):
    counter_0 = 0
    counter_1 = 0

    if n in save:
        return save[n]

    if n == 0:
        counter_0 += 1
        save[n] = (counter_0, counter_1)
        return save[n]
    
    elif n == 1:
        counter_1 += 1
        save[n] = (counter_0, counter_1)
        return save[n]
    else:
        save_1 = fibonacci(n-1)
        save_2 = fibonacci(n-2)
        counter_0 += save_1[0] + save_2[0]
        counter_1 += save_1[1] + save_2[1]
        save[n] = (counter_0, counter_1)
        return save[n]

for _ in range(T):
    num = int(sys.stdin.readline())
    fibonacci(num)
    print("{} {}".format(save[num][0], save[num][1]))

