#digitincreasing
numero = 0
aumenta = 0
valor = int(input("Ingrese un numero: "))
for i in range(1, 10):   
    numero = 0
    temp = 0             
    while numero < valor:
        temp = temp * 10 + i
        numero += temp
        if numero == valor:
            aumenta = 1
            break
    if aumenta == 1:
        break

print(aumenta)