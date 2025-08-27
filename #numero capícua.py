#numero capícua
numero=(input("Digite um número: "))
original=numero
reverso=0
reverso = numero[::-1]
if original==reverso:
    print("el numero es capicua")
else:
    print("el numero no es capicua")