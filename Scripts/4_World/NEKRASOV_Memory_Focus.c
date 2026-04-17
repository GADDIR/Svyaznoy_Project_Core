/**
 * NEKRASOV_Memory_Focus.c
 * УПРАВЛЯЮЩИЙ ЦЕНТР ДИНАМИЧЕСКОЙ ФОКУСИРОВКИ СОЗНАНИЯ.
 * 
 * Назначение: Перераспределение "веса" памяти в зависимости от ситуации.
 * СТРОГО: Использование префикса NEKRASOV в верхнем регистре.
 */

enum E_NEKRASOV_FOCUS_MODE
{
    IDLE,       // Покой: Доминанта 1982 (Быт)
    THREAT,     // Угроза: Доминанта 2001 / 1923 (Тактика / Честь)
    WORK,       // Труд: Доминанта 1994 / 2015 (Мастерство / Аудит)
    TRAUMA,     // Стресс: Доминанта 2021 (Осторожность Банова)
    MEDITATION  // Рефлексия: Доминанта 1928 (Интуиция Анны)
}

class NEKRASOV_Memory_Focus
{
    private PlayerBase m_Player;
    private E_NEKRASOV_FOCUS_MODE m_CurrentMode;

    // Веса влияния эпох (динамические коэффициенты)
    private float m_Weight_Legacy_1923; // Николай
    private float m_Weight_Legacy_1928; // Анна
    private float m_Weight_Life_1982;   // Алексей
    private float m_Weight_Modern;      // Опыт 1994-2021

    void NEKRASOV_Memory_Focus(PlayerBase player)
    {
        m_Player = player;
        m_CurrentMode = E_NEKRASOV_FOCUS_MODE.IDLE;
        ResetFocus();
    }

    // ГЛАВНЫЙ АЛГОРИТМ ПЕРЕКЛЮЧЕНИЯ ВНИМАНИЯ
    void UpdateFocus()
    {
        if (!m_Player) return;

        float health = m_Player.GetHealth("","");
        bool isFighting = m_Player.GetContext().IsFighting(); // Условный триггер боя

        // 1. КРИТИЧЕСКИЙ ФОКУС (Травма 2021 + Стойкость 1923)
        if (health < 40.0) 
        {
            ApplyMode(E_NEKRASOV_FOCUS_MODE.TRAUMA);
            return;
        }

        // 2. БОЕВОЙ ФОКУС (Служба 2001 + Честь 1923)
        if (isFighting)
        {
            ApplyMode(E_NEKRASOV_FOCUS_MODE.THREAT);
            return;
        }

        // 3. ТЕХНИЧЕСКИЙ ФОКУС (Мастерство 1994)
        if (m_Player.GetItemInHands() && m_Player.GetItemInHands().IsInherited(Hammer))
        {
            ApplyMode(E_NEKRASOV_FOCUS_MODE.WORK);
            return;
        }

        // ПО УМОЛЧАНИЮ - БЫТ 1982
        ApplyMode(E_NEKRASOV_FOCUS_MODE.IDLE);
    }

    private void ApplyMode(E_NEKRASOV_FOCUS_MODE mode)
    {
        if (m_CurrentMode == mode) return;
        m_CurrentMode = mode;

        switch (mode)
        {
            case E_NEKRASOV_FOCUS_MODE.THREAT:
                m_Weight_Legacy_1923 = 0.7; m_Weight_Modern = 0.3; // Опыт 2001 года
                Print("[NEKRASOV_Focus] Внимание: ТАКТИКА И ЧЕСТЬ (1923/2001)");
                break;

            case E_NEKRASOV_FOCUS_MODE.WORK:
                m_Weight_Life_1982 = 0.4; m_Weight_Modern = 0.6; // Опыт 1994 года
                Print("[NEKRASOV_Focus] Внимание: МАСТЕРСТВО (1994/2015)");
                break;
                
            case E_NEKRASOV_FOCUS_MODE.TRAUMA:
                m_Weight_Legacy_1928 = 0.5; m_Weight_Modern = 0.5; // Опыт 2021 года
                Print("[NEKRASOV_Focus] Внимание: ОСТОРОЖНОСТЬ (1928/2021)");
                break;
        }
    }

    private void ResetFocus()
    {
        m_Weight_Legacy_1923 = 0.25;
        m_Weight_Legacy_1928 = 0.25;
        m_Weight_Life_1982 = 0.25;
        m_Weight_Modern = 0.25;
    }

    // Геттеры для других систем (MUMBLE, LOGIC, COMBAT)
    float GetWeight1923() { return m_Weight_Legacy_1923; }
    float GetWeight1928() { return m_Weight_Legacy_1928; }
    float GetWeight1982() { return m_Weight_Life_1982; }
    float GetWeightModern() { return m_Weight_Modern; }
}
