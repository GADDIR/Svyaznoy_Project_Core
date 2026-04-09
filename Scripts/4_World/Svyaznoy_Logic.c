/* 
    MASTER LOGIC: MAVERICK_BRAIN [SZ_ROOT_FULL_SYNC]
    INDEX: PRT-600.1 / 600.4 / 600.6 / NVG_COMPAT
    STATUS: FINAL_REVISION (10.04.2026)
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
    protected bool m_SZ_ReadyToLeave = false;
    protected string m_CurrentGoal = "NONE";

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    // [600.1] Протокол SZ_ROOT_TREE (Алгоритм Сейф-зоны)
    void Svyaznoy_SZ_Process(float timeslice)
    {
        if (!m_Player) return;

        switch(m_SZ_Stage)
        {
            case ESZStage.SAFETY_FIRST: // 600.5
                m_Player.SetStress(0.1);
                // В будущем: if (ScanExits())
                m_SZ_Stage = ESZStage.AGRO_AUDIT;
                break;

            case ESZStage.AGRO_AUDIT: // 600.6 (ПРИОРИТЕТ №0)
                if (HasFarmingEquipment() && (HasSeeds() || m_Player.HasItem("Pumpkin"))) 
                    m_SZ_Stage = ESZStage.ECONOM_CHECK;
                else 
                    m_CurrentGoal = "BUY_AGRO_TOOLS"; 
                break;

            case ESZStage.ECONOM_CHECK: // 600.4 (ИНДЕКС СКУПОСТИ)
                ExecuteAvariceFilter();
                m_SZ_Stage = ESZStage.PREPARE_DEPARTURE;
                break;

            case ESZStage.PREPARE_DEPARTURE: // 600.7
                if (GetFoodCount() >= 3) m_SZ_ReadyToLeave = true;
                break;
        }
    }

    // [600.4] Индекс скупости и [SZ_NVG_COMPATIBILITY]
    void ExecuteAvariceFilter()
    {
        // Блокировка трат, если Energy > 15% (200 ед)
        if (m_Player.GetStatEnergy().Get() > 200) 
        {
            m_CurrentGoal = "TECH_UPGRADE_ONLY"; // Только Глушитель или ПНВ
            CheckOpticsCompatibility();
        }
    }

    void CheckOpticsCompatibility()
    {
        // Проверка прицела на совместимость с ПНВ (600.4)
        EntityAI optics = m_Player.GetWeaponOptics(); 
        if (optics && !optics.IsKindOf("NV_Capable_Base"))
        {
            Print("[СВЯЗНОЙ]: [600.4] Purchase: NVG_Goggles | Compatibility: NO_SCOPE_WARNING");
        }
    }

    // --- СИСТЕМНЫЕ МЕТОДЫ ---
    void Update(float timeslice, int mode)
    {
        if (m_Player.IsInSafeZone()) Svyaznoy_SZ_Process(timeslice);
        // Остальная логика Update...
    }

    bool HasFarmingEquipment() { return m_Player.GetInventory().FindEntityInInventory("FarmingHoe") != null || m_Player.GetInventory().FindEntityInInventory("Shovel") != null; }
    bool HasSeeds() { return m_Player.GetInventory().FindEntityInInventory("ZucchiniSeeds") != null; }
    int GetFoodCount() { return 0; } // Заглушка для PRT-600.7
}
