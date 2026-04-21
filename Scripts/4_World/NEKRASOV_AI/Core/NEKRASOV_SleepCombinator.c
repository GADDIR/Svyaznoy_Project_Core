/**
 * NEKRASOV_SleepCombinator
 * Реализует логику "Честного Сна" и "Биологического обмена" (Здоровье за Сон).
 */
class NEKRASOV_SleepCombinator
{
    protected PlayerBase m_Maverick;
    protected float m_BaseRecovery = 1.0; // Базовая скорость восстановления Zz

    void NEKRASOV_SleepCombinator(PlayerBase player)
    {
        m_Maverick = player;
    }

    void ProcessSleepPhysics(float deltaT)
    {
        if (!m_Maverick) return;

        // --- ПРИОРИТЕТ 0: КРОВЬ (Bleeding) ---
        // Если течет кровь — сон невозможен физически. Просыпаемся немедленно.
        if (m_Maverick.GetBleedingManager() && m_Maverick.GetBleedingManager().GetBleedingSourcesCount() > 0)
        {
            WakeUp(); 
            return;
        }

        float energy = m_Maverick.GetStatEnergy().Get();
        float water  = m_Maverick.GetStatWater().Get();

        // --- ПРИОРИТЕТ 1: ЗДОРОВЬЕ (Health) В ОБМЕН НА СОН ---
        // Если желудок пуст (Energy/Water <= 0), мы не просыпаемся,
        // а начинаем "жечь" Здоровье. Это цена контроля над Zz.
        if (energy <= 0 || water <= 0)
        {
            // Наносим урон именно ЗДОРОВЬЮ, имитируя истощение организма во сне
            float starvationDamage = 0.05 * deltaT; 
            m_Maverick.AddHealth("", "Health", -starvationDamage);
        }

        // --- ПРИОРИТЕТ 2: ВОССТАНОВЛЕНИЕ (Zz) ---
        // Обсчитываем эффективность (Ночь, Тепло, Сухость)
        float efficiency = GetSleepEfficiency(); 
        m_Maverick.AddStatSleep(m_BaseRecovery * efficiency * deltaT);
        
        // --- ПРИОРИТЕТ 3: ПРЕДЕЛ ВЫЖИВАНИЯ ---
        // Если Здоровье упало до 10% — организм выбрасывает нас из сна судоргой
        if (m_Maverick.GetHealth("", "Health") < 10.0)
        {
            WakeUp(); 
        }
    }

    protected float GetSleepEfficiency()
    {
        // Здесь логика Ночь/Тепло/Сухость, которую мы обсудили ранее
        return 1.0; // Заглушка
    }

    protected void WakeUp()
    {
        m_Maverick.GetNEKRASOV_Brain().SetActiveMode(NEKRASOV_EModes.IDLE);
        // Тут можно добавить анимацию тяжелого подъема
    }
}
