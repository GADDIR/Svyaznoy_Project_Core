class Nekrasov_Mind
{
    // Ссылка на NPC, которым управляет этот "мозг"
    protected DayZPlayer m_Entity;
    
    // Текущие семантические данные (сознание)
    protected string m_Subject;   // Существительное (Цель)
    protected string m_Action;    // Глагол (Действие)
    protected string m_Modifier;  // Наречие (Стиль выполнения)

    void Nekrasov_Mind(DayZPlayer owner)
    {
        m_Self = owner;
    }

    // Главная функция формирования мысли
    void FormThought(string noun, string verb, string adverb = "")
    {
        m_Subject  = noun;
        m_Action   = verb;
        m_Modifier = adverb;

        // Как только мысль сформирована, ИИ начинает её анализировать
        AnalyzeIntention();
    }

    // Анализ намерения (Превращение слов в логику)
    protected void AnalyzeIntention()
    {
        if (!m_Self) return;

        Print("[NEKRASOV_AI] Моя мысль: " + m_Action + " " + m_Subject + " [" + m_Modifier + "]");

        // 1. Обработка Наречия (Как именно делать?)
        float intensity = 1.0;
        if (m_Modifier == "быстро") intensity = 2.0;
        if (m_Modifier == "тихо")   intensity = 0.5;

        // 2. Обработка Глагола (Что делать?)
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
        }
    }

    // --- Исполнительные методы (Взаимодействие с движком) ---

    protected void ExecuteMovement(float speed)
    {
        // Здесь подключается навигация DayZ
        Print("[NEKRASOV_AI] Исполняю действие: Движение. Множитель скорости: " + speed);
        // Код для перемещения NPC по вейпоинтам
    }

    protected void ExecuteStop()
    {
        Print("[NEKRASOV_AI] Исполняю действие: Полная остановка");
        // Очистка путей навигации
    }

    protected void ExecuteAttack(float aggressiveness)
    {
        Print("[NEKRASOV_AI] Исполняю действие: Атака. Агрессия: " + aggressiveness);
        // Логика поиска цели и стрельбы
    }
}
