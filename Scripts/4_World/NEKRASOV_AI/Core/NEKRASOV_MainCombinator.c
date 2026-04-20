/**
 * NEKRASOV_MainCombinator
 * Управляет тремя главными ветками: БЕЗОПАСНОСТЬ, ЕДА, СОН.
 * Реализует систему вето: Смерть отменяет всё, Грязь отменяет Еду.
 */
class NEKRASOV_MainCombinator
{
    protected PlayerBase m_Maverick;
    
    void NEKRASOV_MainCombinator(PlayerBase player)
    {
        m_Maverick = player;
    }

    // Главная функция выбора режима
    void Evaluate(NEKRASOV_WorldState worldState)
    {
        // --- ПРИОРИТЕТ 1: БЕЗОПАСНОСТЬ (Ультимативное вето) ---
        // Если нас убивают - плевать на голод и сон.
        if (IsUnderAttack())
        {
            SetGlobalMode(NEKRASOV_EModes.COMBAT);
            return;
        }

        // --- ПРИОРИТЕТ 2: ГИГИЕНА И МЕДИЦИНА (Санитарный барьер) ---
        // Наследие Анны Петровны: грязные руки блокируют еду.
        if (m_Maverick.HasBloodyHands() || IsInfected())
        {
            // Если критически устал - можно упасть в сон грязным (исключение)
            if (IsCriticallyTired())
            {
                SetGlobalMode(NEKRASOV_EModes.SLEEP);
            }
            else
            {
                SetGlobalMode(NEKRASOV_EModes.SECURITY); // Включает "Мытье рук"
            }
            return;
        }

        // --- ПРИОРИТЕТ 3: ЕДА (Метаболизм) ---
        // Если руки чистые и врагов нет - можно подумать о животе.
        if (IsHungry() || IsThirsty())
        {
            SetGlobalMode(NEKRASOV_EModes.FOOD); // Включает Огород / Охоту / Торговлю
            return;
        }

        // --- ПРИОРИТЕТ 4: СОН (Восстановление) ---
        // Если сыт, чист и в безопасности - идем в палатку.
        if (IsTired())
        {
            SetGlobalMode(NEKRASOV_EModes.SLEEP);
            return;
        }

        // --- СВОБОДНОЕ ВРЕМЯ (Развитие) ---
        // Если все нужды закрыты - режим "Связного" (Исследование/Торговля)
        SetGlobalMode(NEKRASOV_EModes.IDLE_DEVELOPMENT);
    }

    // Вспомогательные проверки (интерфейс с Телом)
    protected bool IsUnderAttack() { return m_Maverick.GetNEKRASOV_Sensors().IsThreatDetected(); }
    protected bool IsHungry() { return m_Maverick.GetStatEnergy().Get() < 200; }
    protected bool IsTired() { return m_Maverick.GetStatStamina().Get() < 50; }
    protected bool IsCriticallyTired() { return m_Maverick.GetStatStamina().Get() < 10; }
    protected bool IsInfected() { return m_Maverick.GetModifiersManager().IsModifierActive(eModifiers.MDF_CHOLERA); }

    protected void SetGlobalMode(int mode)
    {
        m_Maverick.GetNEKRASOV_Brain().SetActiveMode(mode);
    }
}

