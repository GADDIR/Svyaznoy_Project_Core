/* 
    MASTER LOGIC: MAVERICK_BRAIN [FINAL_ECON_SYNC]
    INDEX: PRT_CORE_INDEX-000
    PRT-600/700: Индекс скупости и Агро-аудит
*/

class Svyaznoy_Logic
{
    PlayerBase m_Player;
    protected string m_CurrentGoal = "NONE";
    protected float m_ZASTimer = 0;

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;

        // [PRT-100] BIO_STAT: Высший приоритет
        if (m_Player.GetStatEnergy().Get() < 200 || m_Player.IsBleeding())
        {
            ExecuteProtocol(100); 
            return; 
        }

        // [PRT-400] REACTION_X: Боевой рефлекс
        if (GetNearestThreatDist() < 50)
        {
            ExecuteProtocol(400);
            return;
        }

        // [PRT-700] ECON: Индекс скупости и Агро-аудит
        ExecuteEconomyLogic();

        // [PRT-200] STEALTH: Ветеранская походка
        ExecuteProtocol(200);
    }

    // [PRT-ECON-600.4] Индекс скупости (Фильтр ША)
    // [PRT-ECON-600.6] Агро-аудит (Условие перехода ШВ)
    bool ValidateTradeRequest(string itemType)
    {
        // Блокировка лишних трат: только семена или Tier-UP
        if (itemType != "Suppressor" && itemType != "NVG" && itemType != "Seeds")
        {
            Print("[СВЯЗНОЙ]: [ECON_AVARICE_IDX] Запрос отклонен. Цель не соответствует приоритету.");
            return false;
        }

        // Агро-аудит: Проверка инструментов перед торговлей
        if (!HasFarmingEquipment()) 
        {
            Print("[СВЯЗНОЙ]: [AGRO_AUDIT_FAIL] Переход в SZ_ROOT_TREE заблокирован. Нужен инструмент.");
            return false;
        }

        return true;
    }

    void ExecuteEconomyLogic()
    {
        float currentBalance = 0; // Хук для трейдера
        float targetPrice = 5000.0; // Цель: Глушитель
        
        float progress = Math.Clamp((currentBalance / targetPrice) * 100, 0, 100);
        
        if (progress >= 100) m_CurrentGoal = "UPGRADE_READY";
        else m_CurrentGoal = "SAVING_FOR_ZAS";
    }

    void ExecuteProtocol(int id)
    {
        // Логирование с индексами для Яндекс Менеджера
        Print("[СВЯЗНОЙ]: [PRT-" + id.ToString() + "] Активен. Цель: " + m_CurrentGoal);
        
        switch (id)
        {
            case 100: m_CurrentGoal = "BIO_EMERGENCY"; break;
            case 200: m_CurrentGoal = "STEALTH_MOVE"; break;
            case 400: m_CurrentGoal = "COMBAT_REFLEX"; break;
        }
    }

    float GetNearestThreatDist() { return 1000.0; }

    bool HasFarmingEquipment()
    {
        if (!m_Player) return false;
        return m_Player.GetInventory().FindEntityInInventory("FarmingHoe") != null || 
               m_Player.GetInventory().FindEntityInInventory("Shovel") != null;
    }
}
