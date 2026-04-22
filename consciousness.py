import pymorphy3

class Consciousness:
    def __init__(self):
        self.morph = pymorphy3.MorphAnalyzer()
        # Базовая память (пока пустая)
        self.memory = {}

    def perceive(self, word):
        """Метод 'Восприятие': разбирает слово на части речи"""
        p = self.morph.parse(word)[0]
        return {
            "lemma": p.normal_form, # Начальная форма (Зомби, Бежать)
            "pos": p.tag.POS,        # Часть речи (NOUN, VERB...)
            "gender": p.tag.gender   # Род (мужской, женский...)
        }

    def generate_thought(self, object_word, quality_word):
        """Метод 'Мысль': соединяет объект и его свойство"""
        obj = self.perceive(object_word)
        qual = self.perceive(quality_word)
        
        # Логика: если объект — существительное, а свойство — прилагательное
        if obj['pos'] == 'NOUN' and qual['pos'] == 'ADJF':
            return f"Мысль: {obj['lemma']} (объект) сейчас {qual['lemma']} (качество)."
        return "Не могу связать эти понятия."

# Проверка
ai = Consciousness()
print(ai.generate_thought("Зомби", "быстрые")) 
# Выведет: Мысль: зомби сейчас быстрый.

