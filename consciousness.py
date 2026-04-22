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
            lemma_obj = obj['lemma']
            lemma_qual = qual['lemma']
            self.memory[lemma_obj] = lemma_qual
            self.save_memory()

            # Базовые переменные мысли
            action = "Идти"
            how = "обычно"
            not_particle = "" 

            # Оценка собственного состояния (Местоимение + Прилагательное)
            is_weak = self.health < 40
            state_desc = "слабый" if is_weak else "сильный"

            # Логика принятия решений
            if lemma_qual in ['опасный', 'злой', 'страшный']:
                if is_weak:
                    not_particle = "НЕ "
                    action = "Атаковать" # В итоге будет "НЕ Атаковать"
                    how = "рискованно"
                else:
                    action = "Атаковать"
                    how = "решительно"
            
            elif lemma_qual in ['вкусный', 'полезный', 'нужный']:
                action = "Взять"
                how = "немедленно"

            # Смена тактики при слабости
            if is_weak and action == "Атаковать":
                final_decision = f"{not_particle}{action} ({how}), лучше Прятаться."
            else:
                final_decision = f"{not_particle}{action} ({how})"

            return f"МЫСЛЬ: Я {state_desc}. {lemma_obj} {lemma_qual}. РЕШЕНИЕ: {final_decision}."
        
        return "В мыслях пустота..."

# Тест:
ai = Consciousness()
# Пример 1: ИИ здоров
print(ai.think("Волк", "злой"))
# Пример 2: ИИ ранен
ai.health = 25
print(ai.think("Зомби", "страшные"))
