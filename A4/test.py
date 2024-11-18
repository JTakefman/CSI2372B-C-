import pdb;

def find_1(L, l, h):
    if (len(L)==1):
        if (L[0]==1):
            return 0
        return -1
    
    if (h-l==1):
        if (L[h]==1):
            return h
        return len(L)+1
    half = ((h-l)//2) + l
    
    if (L[half]==1):
        print("Calling left")
        return min(half, find_1(L, l, half))
    else:
        print("Calling right")
        return find_1(L, half, h)

L=[0, 0, 0, 0]

print("Lowest index of 1 is " + str(find_1(L, 0, len(L))))
