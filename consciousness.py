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
        # Берем первый, самый вероятный разбор слова
        p = self.morph.parse(word)[0]
        return {"lemma": p.normal_form, "pos": p.tag.POS}

    def think(self, object_word, quality_word):
        obj = self.perceive(object_word)
        qual = self.perceive(quality_word)

        if obj['pos'] == 'NOUN' and qual['pos'] == 'ADJF':
            lemma_obj = obj['lemma']
            lemma_qual = qual['lemma']
            
            # Сохраняем в память связку Объект + Качество
            self.memory[lemma_obj] = lemma_qual
            self.save_memory()

            # Базовые настройки (Глагол + Наречие)
            action = "Идти"
            how = "обычно"

            # Логика принятия решений на основе "Золотых глаголов"
            if lemma_qual in ['опасный', 'злой', 'страшный', 'вооруженный']:
                action = "Прятаться"
                how = "надежно"
            elif lemma_qual in ['быстрый', 'агрессивный']:
                action = "Атаковать"
                how = "внезапно"
            elif lemma_qual in ['вкусный', 'полезный', 'нужный']:
                action = "Взять"
                how = "аккуратно"
            elif lemma_qual in ['раненый', 'больной']:
                action = "Лечить"
                how = "срочно"
            elif lemma_qual in ['неизвестный', 'странный']:
                action = "Изучать"
                how = "внимательно"

            return f"МЫСЛЬ: {lemma_obj} — {lemma_qual}. РЕШЕНИЕ: {action} ({how})."
        
        return "Недостаточно данных для формирования мысли."

# Тест работы сознания:
ai = Consciousness()
print(ai.think("Зомби", "страшные"))
print(ai.think("Аптечка", "полезная"))
