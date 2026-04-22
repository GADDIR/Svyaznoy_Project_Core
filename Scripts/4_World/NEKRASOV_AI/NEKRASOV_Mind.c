class NEKRASOV_Mind
{
    // Архив памяти (те самые данные из биографии)
    ref array<string> m_BiographyArchive;
    
    void NEKRASOV_Mind()
    {
        m_BiographyArchive = new array<string>;
        LoadLifeExperience();
    }

    // Здесь мы "прошиваем" его жизнь в память игры
    void LoadLifeExperience()
    {
        // Сюда мы вставим ваш текст про садик, армию и т.д.
        m_BiographyArchive.Insert("Армия: Служба научила дисциплине и обращению с оружием.");
        m_BiographyArchive.Insert("Институт: Получены знания о химии и медицине.");
        m_BiographyArchive.Insert("Банов: Экстремальное выживание, страх и холод.");
    }

    // Функция "внутреннего голоса" на русском языке
    string GetThought(string context)
    {
        // Логика поиска смысла по ключевым словам в архиве
        foreach (string record : m_BiographyArchive)
        {
            if (record.Contains(context))
                return "Я помню: " + record;
        }
        return "В моей памяти нет этого, но я чувствую...";
    }
}
