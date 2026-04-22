class Nekrasov_Mind
{
    // Ссылка на тело (NPC или Игрок)
    protected DayZPlayer m_Entity;
    
    // Семантическое "сознание"
    protected string m_Subject;   // Существительное (Кто/Что)
    protected string m_Action;    // Глагол (Действие)
    protected string m_Modifier;  // Наречие (Как)

    // Конструктор (Исправлено имя переменной с m_Self на m_Entity)
    void Nekrasov_Mind(DayZPlayer owner)
    {
        m_Entity = owner;
    }

    // Внешний интерфейс для Парсера
    void FormThought(string noun, string verb, string adverb = "")
    {
        m_Subject  = noun;
        m_Action   = verb;
        m_Modifier = adverb;

        AnalyzeIntention();
    }

    protected void AnalyzeIntention()
    {
        if (!m_Entity) return;

        // Вывод "мыслей" в лог сервера (script.log)
        Print("[NEKRASOV_AI] Сознание: " + m_Action + " " + m_Subject + " (" + m_Modifier + ")");

        // 1. Модификатор действия (Наречие)
        float intensity = 1.0;
        if (m_Modifier == "быстро") intensity = 2.0;
        if (m_Modifier == "тихо")   intensity = 0.5;

        // 2. Выбор действия (Глагол)
        switch (m_Action)
        {
            case "иди":
            case "беги":
                ExecuteMovement(intensity);
                break;
                
            case "стой":
                ExecuteStop();
                break;

            case "атакуй":
                ExecuteAttack(intensity);
                break;
                
            default:
                Print("[NEKRASOV_AI] Ошибка: Я не знаю глагола '" + m_Action + "'");
                break;
        }
    }

    // --- Реализация физических действий движком DayZ ---

    protected void ExecuteMovement(float speed)
    {
        // Здесь мы будем использовать AI-контроллер (например, из Expansion или Vanilla AI)
        Print("[NEKRASOV_AI] Физика: Движение к '" + m_Subject + "' Скорость: " + speed);
    }

    protected void ExecuteStop()
    {
        Print("[NEKRASOV_AI] Физика: Остановка всех систем");
    }

    protected void ExecuteAttack(float aggressiveness)
    {
        Print("[NEKRASOV_AI] Физика: Боевой режим против '" + m_Subject + "'");
    }
}
