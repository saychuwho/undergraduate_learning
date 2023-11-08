while True:
    getnum = input()
    
    if getnum == "0":
        break

    result = "yes"
    mid = len(getnum) // 2
    if len(getnum) % 2 == 0:
        left = getnum[:mid]
        right = getnum[mid:]
    else:
        left = getnum[:mid]
        right = getnum[mid+1:]
    
    for i in range(mid):
        if left[i] != right[len(right)-1-i]:
            result = "no"
    
    print(result)