/**
 * NEKRASOV_Memory_Focus.c
 * Управляющий центр динамической фокусировки сознания.
 * Решает, какие пласты памяти (1923, 1928, 1982) доминируют в текущий момент.
 */

enum ENekrasovFocusMode
{
    DEFAULT,    // Сбалансированное состояние
    COMBAT,     // Доминанта Николая (1923) — Честь и Стойкость
    SURVIVAL,   // Доминанта Анны (1928) — Интуиция и Жизнь
    REFLEXION,  // Доминанта Алексея (1982) — Быт и Логика
    CRITICAL    // Доминанта Золотого Стандарта — Граница Жизни и Смерти
}

class NEKRASOV_Memory_Focus
{
    private PlayerBase m_Player;
    private ENekrasovFocusMode m_CurrentFocus;
    
    // Веса влияния (0.0 - 1.0)
    private float m_Weight1923; // Николай
    private float m_Weight1928; // Анна
    private float m_Weight1982; // Алексей
    
    void NEKRASOV_Memory_Focus(PlayerBase player)
    {
        m_Player = player;
        m_CurrentFocus = ENekrasovFocusMode.DEFAULT;
        ResetWeights();
    }

    // Главный метод обновления фокуса на основе состояния персонажа
    void UpdateFocus(float timeslice)
    {
        if (!m_Player) return;

        // 1. Анализ ситуации
        bool isInDanger = m_Player.GetContext().IsInCombat(); // Условный метод контекста
        float health = m_Player.GetHealth("", "");

        // 2. Переключение режимов
        if (health < 30.0)
        {
            SetFocusMode(ENekrasovFocusMode.CRITICAL);
        }
        else if (isInDanger)
        {
            SetFocusMode(ENekrasovFocusMode.COMBAT);
        }
        else
        {
            SetFocusMode(ENekrasovFocusMode.REFLEXION);
        }
    }

    private void SetFocusMode(ENekrasovFocusMode mode)
    {
        if (m_CurrentFocus == mode) return;
        m_CurrentFocus = mode;

        switch (mode)
        {
            case ENekrasovFocusMode.COMBAT:
                // В бою голос Николая (1923) становится законом
                m_Weight1923 = 0.8; m_Weight1928 = 0.1; m_Weight1982 = 0.1;
                Print("[Focus] Доминанта: Николай 1923 (Стойкость)");
                break;

            case ENekrasovFocusMode.SURVIVAL:
                // При поиске ресурсов включается чутье Анны (1928)
                m_Weight1923 = 0.2; m_Weight1928 = 0.7; m_Weight1982 = 0.1;
                Print("[Focus] Доминанта: Анна 1928 (Интуиция)");
                break;

            case ENekrasovFocusMode.REFLEXION:
                // В покое Алексей (1982) анализирует быт
                m_Weight1923 = 0.2; m_Weight1928 = 0.2; m_Weight1982 = 0.6;
                Print("[Focus] Доминанта: Алексей 1982 (Быт)");
                break;
        }
    }

    private void ResetWeights()
    {
        m_Weight1923 = 0.33; m_Weight1928 = 0.33; m_Weight1982 = 0.34;
    }

    // Геттеры для использования в других модулях (например в Mumble)
    float GetLegacyWeight1923() { return m_Weight1923; }
    float GetLegacyWeight1928() { return m_Weight1928; }
    float GetLegacyWeight1982() { return m_Weight1982; }
    ENekrasovFocusMode GetCurrentFocus() { return m_CurrentFocus; }
}

