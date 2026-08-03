"""
Mostra a letra atual e a palavra formada na tela (terminal).
"""
import os


def limpar_tela():
    os.system("cls" if os.name == "nt" else "clear")


def mostrar(letra, palavra):
    limpar_tela()
    print("=" * 40)
    print("   LUVA TRADUTORA DE LIBRAS")
    print("=" * 40)
    print(f"\n  Letra atual: {letra.strip() if letra.strip() else '-'}")
    print(f"  Palavra:     {palavra}")
    print("\n" + "=" * 40)
