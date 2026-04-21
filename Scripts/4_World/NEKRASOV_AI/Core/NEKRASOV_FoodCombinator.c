class NEKRASOV_FoodCombinator
{
    protected PlayerBase m_Maverick;
    
    // Лимиты желудка (ванильные значения DayZ)
    static const float STOMACH_MAX = 5000; 

    void NEKRASOV_FoodCombinator(PlayerBase player)
    {
        m_Maverick = player;
    }

    void EvaluateMetabolism(NEKRASOV_WorldState state)
    {
        if (!m_Maverick) return;

        float energy  = m_Maverick.GetStatEnergy().Get();
        float water   = m_Maverick.GetStatWater().Get();
        float health  = m_Maverick.GetHealth("GlobalHealth", "Health");
        float stomach = m_Maverick.GetStatStomachVolume(); // Объем желудка
        
        // --- 1. ПРОВЕРКА ПЕРЕЕДАНИЯ ---
        // "Могу ли я еще впихнуть?" - Если лимит превышен, блокируем потребление.
        if (stomach >= STOMACH_MAX)
        {
            state.SetState("is_stuffed", true);
            state.SetState("can_eat", false); 
            return;
        }

        // --- 2. БИОЛОГИЧЕСКИЙ КРЕДИТ (Голодное истощение) ---
        // Если еда или вода на нуле, здоровье начинает "платить" за жизнь.
        if (energy <= 0 || water <= 0)
        {
            float starvationDamage = 0.05; // Тихий урон здоровью
            m_Maverick.AddHealth("", "Health", -starvationDamage);
        }

        // --- 3. ПРОТОКОЛ САМООБЛАДАНИЯ (Критическая зона) ---
        // Когда все красное, Некрасов ищет "неожиданную еду" (яблоки, грибы, колонки)
        if (energy < 200.0 || water < 200.0 || health < 20.0)
        {
            // Переходим в режим "тихого выживания"
            state.SetState("self_control_active", true);
            state.SetState("search_natural_food", true); // Ищем яблони/грибы
            
            // Если здоровье критическое, ИИ игнорирует "вкус", ищет только калории
            if (health < 15.0) {
                state.SetState("desperate_search", true);
            }
        }

        // --- 4. ПРИОРИТЕТЫ ПО ИНДИКАТОРАМ ---
        if (water < 200.0)
        {
            state.SetState("priority_water", true); // Жажда убивает быстрее
        }

        if (energy < 200.0)
        {
            state.SetState("priority_food", true);
        }
    }
}

