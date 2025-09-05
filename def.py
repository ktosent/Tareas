#contar vocales
def contar_vocales(cadena):
    vocales = "aeiouAEIOU"
    contador = 0
    for char in cadena:
        if char in vocales:
            contador += 1
    return contador
cadena = input("Ingrese una cadena de texto: ")
print("Número de vocales en la cadena:", contar_vocales(cadena))