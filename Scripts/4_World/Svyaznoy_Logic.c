/* 
    MASTER LOGIC: MAVERICK_BRAIN [PRT-LIFE-100.X_READY]
    INDEX: PRT_CORE_INDEX-000 | PRT-100.X
    STATUS: INTEGRATING FOOD_MATRIX & LOOT_FILTER
*/

enum ESZStage { SAFETY_FIRST, AGRO_AUDIT, ECONOM_CHECK, PREPARE_DEPARTURE }

class Svyaznoy_Logic
{
    PlayerBase m_Player;
    protected ESZStage m_SZ_Stage = ESZStage.SAFETY_FIRST;
    protected string m_CurrentGoal = "NONE";

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    // [PRT-LIFE-100.X] МАТРИЦА СПОСОБОВ ДОБЫЧИ ПИТАНИЯ
    void EvaluateFoodSource(EntityAI target)
    {
        if (!target) return;

        // 100.2-H | Фильтр охоты (Предотвращение отравлений)
        if (target.IsKindOf("Animal_Wolf") || target.IsKindOf("Animal_Bear"))
        {
            Print("[100.2-H] ВНИМАНИЕ: Мясо хищника. Сбор только ЖИРА.");
            m_CurrentGoal = "HUNT_FAT_ONLY";
            return; 
        }

        // 100.3-G | Собирательство (LootFilter)
        if (target.IsFood() && target.IsSubstituent()) // Упрощенная проверка на Rotten
        {
            Print("[100.3-G] ОБЪЕКТ ИГНОРИРУЕТСЯ: Обнаружена гниль.");
            return;
        }
    }

    // 100.5-Z | Зомби-хантинг (Логика последней надежды)
    bool CanEngageZombies(int count)
    {
        bool hasSuppressor = false; // Хук для проверки глушителя
        if (count > 3 || !hasSuppressor || m_Player.GetStatEnergy().Get() > 500)
        {
            Print("[100.5-Z] РИСК > ВЫГОДА. Протокол блокировки режима.");
            return false;
        }
        return true;
    }

    // [600.4] ТЕСТ-ДРАЙВ И ОБНОВЛЕННАЯ ТОРГОВЛЯ
    bool ShouldBuyItem(string itemName, float energyPercent)
    {
        // 100.6-T: Торговля разрешена только при критическом голоде (< 10%)
        if (IsFoodItem(itemName) && energyPercent > 0.10) 
        {
            Print("[600.4][ECON_AVARICE_IDX] Transaction Blocked. Reason: Priority 100.1-F (Auto-Farm).");
            return false; 
        }
        return true;
    }

    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;
        
        float energyLevel = m_Player.GetStatEnergy().Get() / 1000.0;

        if (m_Player.IsInSafeZone()) ProcessSafeZoneLogic(timeslice);
        
        // Постоянный мониторинг источника перед взаимодействием
        EntityAI target = m_Player.GetTargetEntity();
        if (target) EvaluateFoodSource(target);
    }

    void ProcessSafeZoneLogic(float timeslice)
    {
        switch(m_SZ_Stage)
        {
            case ESZStage.SAFETY_FIRST: m_Player.SetStress(0.1); m_SZ_Stage = ESZStage.AGRO_AUDIT; break;
            case ESZStage.AGRO_AUDIT:
                if (HasFarmingEquipment() && HasSeeds()) m_SZ_Stage = ESZStage.ECONOM_CHECK;
                else m_CurrentGoal = "BUY_AGRO_TOOLS"; 
                break;
            case ESZStage.ECONOM_CHECK: m_SZ_Stage = ESZStage.PREPARE_DEPARTURE; break;
        }
    }

    bool IsFoodItem(string name) { return (name == "Food_Can" || name == "BakedBeans"); }
    bool HasFarmingEquipment() { return m_Player.GetInventory().FindEntityInInventory("FarmingHoe") != null || m_Player.GetInventory().FindEntityInInventory("Shovel") != null; }
    bool HasSeeds() { return m_Player.GetInventory().FindEntityInInventory("ZucchiniSeeds") != null; }
}
