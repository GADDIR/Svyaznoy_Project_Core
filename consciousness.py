import pymorphy3
import json
import os

class Consciousness:
    def __init__(self):
        self.morph = pymorphy3.MorphAnalyzer()
        self.memory_file = 'memory.json'
        # Загружаем старую память, если она есть
        self.memory = self.load_memory()

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
            
            # Сохраняем в память
            self.memory[lemma_obj] = lemma_qual
            self.save_memory()

            # Простая логика выбора Глагола
            action = "Изучать"
            if lemma_qual in ['опасный', 'злой', 'быстрый', 'страшный']:
                action = "Убегать"
            elif lemma_qual in ['вкусный', 'полезный', 'нужный']:
                action = "Взять"

            return f"МЫСЛЬ: {lemma_obj} — {lemma_qual}. РЕШЕНИЕ: {action}."
        
        return "Недостаточно данных для формирования мысли."

# Тест:
ai = Consciousness()
print(ai.think("Зомби", "страшные"))
