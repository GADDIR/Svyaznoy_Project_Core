/* 
    MASTER LOGIC: MAVERICK_BRAIN [TEST_DRIVE_READY]
    INDEX: PRT_CORE_INDEX-000 | PRT-600.4
    STATUS: INTEGRATING ECON_AVARICE_IDX
*/

enum ESZStage {
    SAFETY_FIRST,
    AGRO_AUDIT,
    ECONOM_CHECK,
    PREPARE_DEPARTURE
}

class Svyaznoy_Logic
{
    PlayerBase m_Player;
    protected ESZStage m_SZ_Stage = ESZStage.SAFETY_FIRST;
    protected string m_CurrentGoal = "NONE";
    protected float m_OpenSpaceTimer = 0;

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    // [600.4] ТЕСТ-ДРАЙВ: ИНДЕКС СКУПОСТИ
    bool ShouldBuyItem(string itemName, float energyPercent)
    {
        // Если это еда и энергии больше 15% — блокируем транзакцию
        if (IsFoodItem(itemName) && energyPercent > 0.15) 
        {
            Print("[600.4][ECON_AVARICE_IDX] Transaction Blocked: Food purchase denied. Reason: Energy > 15% & Priority: AUTO_FARM_READY.");
            // Синхронизация с Яндекс Менеджером через memory_logs.json
            SyncWithCloud(false); 
            return false; 
        }
        return true;
    }

    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;

        // [PRT-100] Критический био-мониторинг
        float energyLevel = m_Player.GetStatEnergy().Get() / 1000.0; // % от максимума
        
        if (m_Player.IsInSafeZone()) 
        {
            ProcessSafeZoneLogic(timeslice);
            // Инициация тест-драйва при попытке покупки (имитация)
            ShouldBuyItem("Food_Can", energyLevel); 
        }
    }

    void ProcessSafeZoneLogic(float timeslice)
    {
        switch(m_SZ_Stage)
        {
            case ESZStage.SAFETY_FIRST:
                m_Player.SetStress(0.1);
                m_SZ_Stage = ESZStage.AGRO_AUDIT;
                break;

            case ESZStage.AGRO_AUDIT: // 600.6
                if (HasFarmingEquipment() && HasSeeds()) m_SZ_Stage = ESZStage.ECONOM_CHECK;
                else m_CurrentGoal = "BUY_AGRO_TOOLS"; 
                break;

            case ESZStage.ECONOM_CHECK: // 600.4
                m_CurrentGoal = "TECH_UPGRADE_ONLY";
                m_SZ_Stage = ESZStage.PREPARE_DEPARTURE;
                break;
        }
    }

    void ExecuteProtocol(int id)
    {
        Print("[СВЯЗНОЙ]: [PRT-" + id.ToString() + "] Активирован. Цель: " + m_CurrentGoal);
        SyncWithCloud(false);
    }

    void SyncWithCloud(bool isEmergency) {
        // [800.1] Фиксация JSON_DB_STREAM для Яндекс Менеджера
    }

    bool IsFoodItem(string name) {
        return (name == "Food_Can" || name == "BakedBeans");
    }

    bool HasFarmingEquipment() { return m_Player.GetInventory().FindEntityInInventory("FarmingHoe") != null || m_Player.GetInventory().FindEntityInInventory("Shovel") != null; }
    bool HasSeeds() { return m_Player.GetInventory().FindEntityInInventory("ZucchiniSeeds") != null; }
}
