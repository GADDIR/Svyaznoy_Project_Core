// ПРОТОКОЛ №3: РЕЕСТР ВРЕМЕННОЙ ПАМЯТИ (ДО РЕСТАРТА)
class AN_OperationalMemory
{
    // Огороды, Инвентарь, Биология
    private ref map<int, float> m_GardenStates // ID грядки -> Время созревания
    private int   m_AmmoCount                  // Текущий БК
    private float m_HungerTrend                // Динамика сытости
    private int   m_LootForQuinn               // Товар на продажу (тыквы/мясо)

    void AN_OperationalMemory()
    {
        m_GardenStates = new map<int, float>
        m_AmmoCount = 0
        m_LootForQuinn = 0
    }

    // ИНВЕНТАРНАЯ СВОДКА (Раз в 60 секунд)
    void InventoryAudit(PlayerBase player)
    {
        m_AmmoCount = player.GetTotalAmmoCount()
        
        // Если БК < 10 — смена режима на Стелс (Decision)
        if (m_AmmoCount < 10)
            player.SetBehaviorMode("STEALTH_RETREAT")
    }

    // ХОЗЯЙСТВЕННЫЙ АУДИТ
    void CheckGardens(int gardenID, float growthStage)
    {
        m_GardenStates.Set(gardenID, growthStage)
        
        // Если созрело (growthStage >= 1.0) — Приоритет «Сбор»
        if (growthStage >= 1.0)
            player.AddTaskToQueue("HARVEST", gardenID)
    }

    // БИОЛОГИЧЕСКИЙ СТАТУС (Предчувствие голода)
    void UpdateBioTrend(float currentEnergy, float lastEnergy)
    {
        m_HungerTrend = currentEnergy - lastEnergy
        
        // Если тренд отрицательный — поиск еды заранее
        if (m_HungerTrend < -5.0)
            player.SayMumble("Живот подводит, надо бы перекусить скоро...")
    }

    // ТРИГГЕР «РЕСТАРТ»: Обнуление происходит автоматически при уничтожении объекта класса
}
