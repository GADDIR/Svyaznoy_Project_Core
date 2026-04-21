class NEKRASOV_Brain 
{
    protected PlayerBase m_Maverick;
    protected ref NEKRASOV_MainCombinator m_MainCombinator; // Первый (Еда, Сон, Безопасность)
    protected ref NEKRASOV_EmergencyCombinator m_Emergency; // Аварийный (Заглушка)

    void NEKRASOV_Brain(PlayerBase player) 
    {
        m_Maverick = player;
        m_MainCombinator = new NEKRASOV_MainCombinator(m_Maverick);
        m_Emergency = new NEKRASOV_EmergencyCombinator(m_Maverick);
    }

    void DecideNextGoal() 
    {
        if (!m_Maverick || !m_Maverick.IsAlive()) return;

        // 1. Проверка аварийной ситуации (пустая заглушка)
        if (m_Emergency.Evaluate()) return; 

        // 2. Работа основного комбинатора
        m_MainCombinator.Evaluate();
    }
}
