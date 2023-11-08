prime_number = []
test_num = [i for i in range(2, 10001)]

for i in range(len(test_num)):
    if test_num[i] == 0:
        continue
    tmp = test_num[i]
    prime_number.append(tmp)
    for j in range(i+1, len(test_num)):
        if test_num[j] != 0 and test_num[j] % tmp == 0:
            test_num[j] = 0


input_num = input().split()

A = int(input_num[0])
B = int(input_num[1])

A_origin = A
B_origin = B

A_prime_fact = []
B_prime_fact = []
res_prime = 1

p_idx = 0
while(A>1):
    prime = prime_number[p_idx]
    tmp = 1
    while(True):
        if(A % prime != 0):
            A_prime_fact.append(tmp)
            break
        A = A // prime
        tmp *= prime
    p_idx += 1

p_idx = 0
while(B>1):
    prime = prime_number[p_idx]
    tmp = 1
    while(True):
        if(B % prime != 0):
            B_prime_fact.append(tmp)
            break
        B = B // prime
        tmp *= prime
    p_idx += 1


test_length = 0
if len(A_prime_fact) > len(B_prime_fact):
    test_length = len(B_prime_fact)
else:
    test_length = len(A_prime_fact)

for i in range(test_length):
    res_prime *= min(A_prime_fact[i], B_prime_fact[i])

print(res_prime)
print((A_origin*B_origin) // res_prime)