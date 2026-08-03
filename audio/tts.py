import pyttsx3


class Falador:
    def __init__(self):
        self.engine = pyttsx3.init()
        self.engine.setProperty("rate", 170)

        # tenta usar uma voz em portugues, se existir no sistema
        for voz in self.engine.getProperty("voices"):
            nome = voz.name.lower() + voz.id.lower()
            if "brazil" in nome or "portuguese" in nome or "pt-br" in nome or "pt_br" in nome:
                self.engine.setProperty("voice", voz.id)
                break

    def falar(self, texto):
        if texto and texto.strip():
            self.engine.say(texto.strip())
            self.engine.runAndWait()
