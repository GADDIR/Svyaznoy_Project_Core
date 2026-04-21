class NEKRASOV_FoodCombinator
{
    protected PlayerBase m_Maverick;
    
    // Лимиты желудка (ванильные значения DayZ)
    static const float STOMACH_MAX = 5000; // Условный порог переполнения

    void NEKRASOV_FoodCombinator(PlayerBase player)
    {
        m_Maverick = player;
    }

    void EvaluateMetabolism(NEKRASOV_WorldState state)
    {
        float energy  = m_Maverick.GetStatEnergy().Get();
        float water   = m_Maverick.GetStatWater().Get();
        float stomach = m_Maverick.GetStatStamina().Get(); // В DayZ объем желудка проверяется через m_Stomach
        
        // --- 1. ПРОВЕРКА ПЕРЕЕДАНИЯ ---
        // Если желудок полон (иконка "желудок" на HUD)
        if (m_Maverick.GetStatStomachVolume() >= STOMACH_MAX)
        {
            state.SetState("is_stuffed", true);
            state.SetState("can_eat", false); // ВЕТО: Больше не едим
            return;
        }

        // --- 2. ПРОВЕРКА ЖАЖДЫ ---
        if (water < 200.0)
        {
            state.SetState("priority_water", true);
        }

        // --- 3. ПРОВЕРКА СЫТОСТИ ---
        if (energy < 200.0)
        {
            state.SetState("priority_food", true);
        }
    }
}

