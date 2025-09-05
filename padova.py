    #padova
n = int(input("Ingrese el valor de n: "))

P0, P1, P2 = 1, 1, 1

if n == 0:
        print("P(0) =", P0)
elif n == 1:
        print("P(1) =", P1)
elif n == 2:
        print("P(2) =", P2)
else:
    for i in range(3, n+1):
            P = P0 + P1
            P0, P1, P2 = P1, P2, P
        
    print(f"P({n}) =", P)
