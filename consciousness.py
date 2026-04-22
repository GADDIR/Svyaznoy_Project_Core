import pymorphy3
import json
import os

class Consciousness:
    def __init__(self):
        self.morph = pymorphy3.MorphAnalyzer()
        self.memory_file = 'memory.json'
        self.memory = self.load_memory()
        
        # СОСТОЯНИЕ "Я"
        self.health = 100 
        self.energy = 100 

    def load_memory(self):
        if os.path.exists(self.memory_file):
            with open(self.memory_file, 'r', encoding='utf-8') as f:
                return json.load(f)
        return {}

    def save_memory(self):
        with open(self.memory_file, 'w', encoding='utf-8') as f:
            json.dump(self.memory, f, ensure_ascii=False, indent=4)

    def perceive(self, word):
        p = self.morph.parse(word)[0]
        return {"lemma": p.normal_form, "pos": p.tag.POS}

    def think(self, object_word, quality_word):
        obj = self.perceive(object_word)
        qual = self.perceive(quality_word)

        if obj['pos'] == 'NOUN' and qual['pos'] == 'ADJF':
            self.memory[obj['lemma']] = qual['lemma']
            self.save_memory()

            # Внутренние параметры
            is_weak = self.health < 40
            is_tired = self.energy < 30
            
            # Базовая конструкция
            action = "Идти"
            how = "спокойно"
            extra = "оглядываясь" # Деепричастие

            # Логика принятия решений
            if qual['lemma'] in ['опасный', 'злой', 'страшный']:
                if is_weak:
                    action = "Прятаться"
                    how = "тихо"
                    extra = "затаив дыхание"
                else:
                    action = "Атаковать"
                    how = "решительно"
                    extra = "выкрикивая угрозы"
            
            elif qual['lemma'] in ['вкусный', 'полезный', 'нужный']:
                action = "Взять"
                how = "быстро"
                extra = "радуясь находке"

            # Модификация деепричастия от усталости или ран
            if is_tired:
                extra = "тяжело дыша"
            elif is_weak and action == "Идти":
                extra = "хромая"

            state_desc = "слабый" if is_weak else "сильный"
            
            # Итоговая синтаксическая сборка
            return (f"МЫСЛЬ: Я {state_desc}. Вижу {obj['lemma']} ({qual['lemma']}). "
                    f"РЕШЕНИЕ: Буду {action} {how}, {extra}, "
                    f"потому что я так чувствую.")
        
        return "В мыслях пустота..."

# Тест:
ai = Consciousness()
# Пример 1: ИИ ранен и устал
ai.health = 30
ai.energy = 20
print(ai.think("Зомби", "страшные"))
# Пример 2: ИИ полон сил
ai.health = 100
ai.energy = 100
print(ai.think("Консервы", "вкусные"))
          
