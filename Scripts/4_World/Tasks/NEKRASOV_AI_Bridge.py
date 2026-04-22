import openai # Или любая другая библиотека нейросети
import json

# Твоя инструкция для нейросети (System Prompt)
SYSTEM_PROMPT = """
Ты — ИИ-контроллер бота 'Игорь' в игре DayZ. 
Твоя задача: переводить фразы игрока в JSON-команды.
Доступные задачи:
1. HARVEST (параметр: GardenPlot) - если просят съесть или собрать огород.
2. FOLLOW (параметр: Admin) - если просят идти за игроком.

Формат ответа: {"action": "НАЗВАНИЕ", "args": "АРГУМЕНТ"}
"""

def process_admin_command(text):
    # Отправляем запрос нейросети
    response = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        messages=[
            {"role": "system", "content": SYSTEM_PROMPT},
            {"role": "user", "content": text}
        ]
    )
    
    # Получаем JSON от ИИ
    ai_decision = json.loads(response.choices[0].message.content)
    return ai_decision

# Пример:
# Ввод: "Игорь, обнеси этот огород"
# Вывод: {"action": "HARVEST", "args": "GardenPlot"}

