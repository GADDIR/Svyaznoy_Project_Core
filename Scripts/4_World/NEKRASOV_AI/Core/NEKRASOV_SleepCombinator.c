/**
 * NEKRASOV_SleepCombinator
 * Реализует логику "Честного Сна" Некрасова А.Н.
 */
class NEKRASOV_SleepCombinator
{
    protected PlayerBase m_Maverick;
    
    // Константы порогов
    static const float THRESHOLD_COLLAPSE = 14.0; // Провал сознания
    static const float THRESHOLD_REQUEST  = 25.0; // Запрос к безопасности
    
    void NEKRASOV_SleepCombinator(PlayerBase player)
    {
        m_Maverick = player;
    }

    /**
     * Возвращает коэффициент эффективности сна (0.0 - 1.0)
     */
    float GetSleepEfficiency()
    {
        float efficiency = 1.0;
        
        // 1. УСЛОВИЕ: Время суток (Только ночь дает 100%)
        if (!GetGame().GetNightTime()) 
        {
            efficiency *= 0.3; // Днем сон поверхностный
        }
        
        // 2. УСЛОВИЕ: Тепло (Если синий индикатор - сон почти не идет)
        float temp = m_Maverick.GetStatTemperature().Get();
        if (temp < 35.0) 
        {
            efficiency *= 0.1; 
        }
        
        // 3. УСЛОВИЕ: Сухость (Мокрая одежда "тихо" режет КПД)
        float wet = m_Maverick.GetStatWet().Get();
        if (wet > 0.1)
        {
            efficiency *= 0.5;
        }
        
        return efficiency;
    }

    /**
     * Основная логика обсчета
     */
    void Process(float deltaT)
    {
        float currentSleep = m_Maverick.GetStatSleep();

        // --- ЛОГИКА ПРОВАЛА (14%) ---
        if (currentSleep <= THRESHOLD_COLLAPSE)
        {
            // Отключаем сознание (Шок в 0)
            m_Maverick.SetHealth("", "Shock", 0);
            return;
        }

        // --- ЛОГИКА ВОССТАНОВЛЕНИЯ ---
        if (m_Maverick.IsSleeping() || m_Maverick.IsUnconscious())
        {
            float recovery = 1.5 * GetSleepEfficiency() * deltaT;
            m_Maverick.AddStatSleep(recovery);
            
            // Если спим в мокром - есть шанс проснуться больным (без чата)
            if (m_Maverick.GetStatWet().Get() > 0.5 && Math.RandomFloat01() < 0.001)
            {
                m_Maverick.GetModifiersManager().ActivateModifier(eModifiers.MDF_COLD);
            }
        }
    }
}
