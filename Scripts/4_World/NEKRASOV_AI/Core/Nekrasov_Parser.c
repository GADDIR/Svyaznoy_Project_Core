class Nekrasov_Parser
{
    // Метод для разбора строки
    // Пример: "Некрасов иди быстро в дом"
    static void ParseCommand(string message, Nekrasov_Mind mind)
    {
        message.ToLower(); // Приводим к нижнему регистру для удобства
        
        // Проверяем, к нам ли обращаются
        if (!message.Contains("некрасов")) return;

        TStringArray words = new TStringArray;
        message.Split(" ", words); // Разбиваем фразу на отдельные слова

        string foundVerb = "";
        string foundAdverb = "";
        string foundNoun = "цель"; // По умолчанию

        // Простейший перебор слов (Лингвистический сито)
        foreach (string word : words)
        {
            // Ищем глагол
            if (word == "иди" || word == "беги" || word == "стой" || word == "атакуй")
                foundVerb = word;

            // Ищем наречие
            if (word == "быстро" || word == "тихо" || word == "медленно")
                foundAdverb = word;

            // Ищем существительное (если это не имя и не глагол/наречие)
            // В реальном моде тут будет список объектов или ключевых точек
            if (word == "дом" || word == "дерево" || word == "враг")
                foundNoun = word;
        }

        // Если нашли хотя бы глагол — отправляем в мозг
        if (foundVerb != "")
        {
            mind.FormThought(foundNoun, foundVerb, foundAdverb);
        }
    }
}

