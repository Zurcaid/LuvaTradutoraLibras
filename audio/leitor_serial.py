"""
Extrai a letra e a palavra
"""

import serial


class LeitorSerial:
    def __init__(self, porta, baud=115200):
        print(f"[Leitor] Conectando na ESP32: {porta} ({baud} bps)")
        self.serial = serial.Serial(porta, baud, timeout=2)

    def ler_dado(self):
        """
        Le uma linha da serial.
        Devolve {"tipo": "letra", "valor": "A"} ou {"tipo": "palavra", "valor": "OI"}.
        Devolve None se a linha nao for uma dessas duas.
        """
        linha = self.serial.readline().decode("utf-8", errors="ignore").strip()

        if not linha:
            return None

        if linha.startswith("LETRA:"):
            letra = linha.replace("LETRA:", "").strip()
            return {"tipo": "letra", "valor": letra}

        if linha.startswith("PALAVRA:"):
            palavra = linha.replace("PALAVRA:", "").strip()
            return {"tipo": "palavra", "valor": palavra}

        return None

    def fechar(self):
        self.serial.close()
