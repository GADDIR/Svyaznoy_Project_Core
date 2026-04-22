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

    def think(self, object_word, quality_word, place_word="лес"):
        obj = self.perceive(object_word)
        qual = self.perceive(quality_word)
        place = self.perceive(place_word)

        if obj['pos'] == 'NOUN' and qual['pos'] == 'ADJF':
            lemma_obj = obj['lemma']
            lemma_qual = qual['lemma']
            self.memory[lemma_obj] = lemma_qual
            self.save_memory()

            # Оценка состояния
            is_weak = self.health < 40
            state_desc = "слабый" if is_weak else "сильный"

            # Логика Глагола и Наречия
            action = "Идти"
            how = "обычно"
            reason = "" # Для союза "потому что"

            if lemma_qual in ['опасный', 'злой', 'страшный']:
                if is_weak:
                    action = "Прятаться"
                    how = "тихо"
                    reason = f"я {state_desc}, а он {lemma_qual}"
                else:
                    action = "Атаковать"
                    how = "решительно"
                    reason = f"я {state_desc}"
            
            elif lemma_qual in ['вкусный', 'полезный']:
                action = "Взять"
                how = "немедленно"
                reason = "это полезно"

            # Работа с Предлогом
            prep = "в" if place['lemma'] in ['лес', 'дом', 'сарай', 'куст'] else "на"
            if place['lemma'] in ['дорога', 'гора', 'крыша']:
                prep = "на"

            # Сборка итоговой мысли (Местоимение + Предлог + Союз)
            return (f"МЫСЛЬ: Вижу {lemma_obj} {prep} {place['lemma']}. "
                    f"РЕШЕНИЕ: Буду {action} {how}, "
                    f"ПОТОМУ ЧТО {reason}.")
        
        return "В мыслях пустота..."

# Тест:
ai = Consciousness()
# Пример: ИИ ранен, видит волка в лесу
ai.health = 30
print(ai.think("Волк", "злой", "лес"))
# Пример: ИИ здоров, видит еду на дороге
ai.health = 100
print(ai.think("Еда", "вкусная", "дорога"))
