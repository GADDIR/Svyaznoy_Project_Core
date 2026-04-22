class Nekrasov_Mind
{
    // Владелец "мозга" (NPC или игрок)
    protected DayZPlayer m_Self;
    
    // Текущее состояние "сознания"
    protected string m_CurrentSubject;   // Существительное (Кто/Что)
    protected string m_CurrentIntent;    // Глагол (Что делать)
    protected string m_CurrentModifier;  // Наречие (Как)

    void Nekrasov_Mind(DayZPlayer owner)
    {
        m_Self = owner;
    }

    // Метод "Внедрения мысли"
    // Сюда парсер будет передавать разобранную русскую фразу
    void Think(string noun, string verb, string adverb = "")
    {
        m_CurrentSubject = noun;
        m_CurrentIntent = verb;
        m_CurrentModifier = adverb;

        ProcessThought();
    }

    // Логический процессор (превращает слова в действия движка)
    protected void ProcessThought()
    {
        if (!m_Self) return;

        Print("[NEKRASOV_AI] Анализ мысли: " + m_CurrentSubject + " | " + m_CurrentIntent + " | " + m_CurrentModifier);

        // 1. Определяем скорость (Наречие)
        float speed = 1.0; // По умолчанию (шаг)
        if (m_CurrentModifier == "быстро") speed = 2.0; // Спринт
        if (m_CurrentModifier == "тихо")   speed = 0.5; // Красться

        // 2. Определяем действие (Глагол)
        switch (m_CurrentIntent)
        {
            case "иди":
                MoveToTarget(speed);
                break;
                
            case "стой":
                StopMovement();
                break;

            case "атакуй":
                EngageTarget();
                break;
        }
    }

    // Вспомогательные методы управления телом (Enforce Script)
    protected void MoveToTarget(float speed)
    {
        // Здесь будет вызов навигационного движка (Navigation/Pathfinding)
        Print("[NEKRASOV_AI] Исполняю: Движение со скоростью " + speed);
    }

    protected void StopMovement()
    {
        // Остановка всех команд перемещения
        Print("[NEKRASOV_AI] Исполняю: Остановка");
    }
}
