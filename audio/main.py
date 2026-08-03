"""
LUVA TRADUTORA DE LIBRAS - Programa principal
================================================
Conecta na ESP32 pela serial, mostra a letra/palavra na tela e fala em voz alta.

- Fala cada LETRA assim que a mao muda de sinal.
- Fala a PALAVRA inteira quando ela e atualizada

Uso:
    python3 main.py /dev/ttyUSB0      -> Linux/Mac
    python3 main.py COM3              -> Windows
"""

import sys

from leitor_serial import LeitorSerial
from tts import Falador
from display import mostrar


def main():
    if len(sys.argv) < 2:
        print("Uso: python3 main.py <porta_serial>")
        print("Exemplo Linux/Mac: python3 main.py /dev/ttyUSB0")
        print("Exemplo Windows:   python3 main.py COM3")
        sys.exit(1)

    porta = sys.argv[1]
    leitor = LeitorSerial(porta)
    falador = Falador()

    letra_atual = ""
    palavra_atual = ""
    ultima_letra_falada = ""
    ultima_palavra_falada = ""

    print("Pronto! Aguardando dados da luva... (Ctrl+C para sair)")

    while True:
        try:
            dado = leitor.ler_dado()
            if dado is None:
                continue

            if dado["tipo"] == "letra":
                letra_atual = dado["valor"]
                mostrar(letra_atual, palavra_atual)

                # fala a letra só quando ela muda (evita repetir toda hora)
                if letra_atual.strip() and letra_atual != ultima_letra_falada:
                    falador.falar(letra_atual)
                    ultima_letra_falada = letra_atual

            elif dado["tipo"] == "palavra":
                nova_palavra = dado["valor"]
                if nova_palavra != palavra_atual:
                    palavra_atual = nova_palavra
                    mostrar(letra_atual, palavra_atual)

                    # fala a palavra inteira quando ela for atualizada
                    if palavra_atual.strip() and palavra_atual != ultima_palavra_falada:
                        falador.falar(palavra_atual)
                        ultima_palavra_falada = palavra_atual

        except KeyboardInterrupt:
            print("\nEncerrando...")
            leitor.fechar()
            break


if __name__ == "__main__":
    main()
