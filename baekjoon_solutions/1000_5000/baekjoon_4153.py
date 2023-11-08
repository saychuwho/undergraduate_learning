while(True):
    get_num = input().split()
    get_num = [int(i) for i in get_num]
    
    if get_num[0] == 0:
        break

    get_num.sort()
    if(get_num[2]**2 == get_num[0]**2 + get_num[1]**2):
        print("right")
    else:
        print("wrong")
