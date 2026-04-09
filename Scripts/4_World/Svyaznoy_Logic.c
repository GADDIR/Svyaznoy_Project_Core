/* 
    MASTER LOGIC: MAVERICK_BRAIN [PRT-LIFE-100.8-10_READY]
    INDEX: PRT_CORE_INDEX-000 | PRT-100.8 / 100.9 / 100.10
    STATUS: INTEGRATING CAMP_LOGIC & STEALTH_COOKING
*/

enum ESZStage { SAFETY_FIRST, AGRO_AUDIT, ECONOM_CHECK, PREPARE_DEPARTURE }

class Svyaznoy_Logic
{
    PlayerBase m_Player;
    protected ESZStage m_SZ_Stage = ESZStage.SAFETY_FIRST;
    protected string m_CurrentGoal = "NONE";

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    // [PRT-LIFE-100.8/9/10] БЫТОВОЙ ЦИКЛ (ГОТОВКА И ЛАГЕРЬ)
    void ProcessCampLogic(float timeslice)
    {
        if (!m_Player) return;

        // 100.10-F | Световая маскировка: Запрет на ночной костер вне зданий
        if (GetGame().GetTime() > 0.8 || GetGame().GetTime() < 0.2) // Условная ночь
        {
            if (!m_Player.IsInBuilding()) {
                Print("[100.10-F] КРИТИЧЕСКИЙ РИСК: Ночь, открытое пространство. Костер запрещен.");
                return;
            }
        }

        // 100.8-C | Безопасная готовка (Приоритет: Варка)
        if (m_Player.IsCooking())
        {
            m_CurrentGoal = "COOKING_SAFE_PROVISION";
            
            // 100.9-L | Параллельный тех-аудит снаряжения
            Print("[100.9-L] ЛАГЕРЬ: Проводится тех-аудит снаряжения во время готовки.");
            ExecuteEquipmentMaintenance(); 
        }
    }

    void ExecuteEquipmentMaintenance()
    {
        // Логика чистки оружия и починки одежды (AUDIT LEVEL 2)
    }

    // Защита от употребления опасных продуктов
    bool CanEat(EntityAI food)
    {
        if (food.IsRaw() || food.IsRotten())
        {
            Print("[100.8-C] ОТКАЗ: Продукт опасен (сырое/гнилое). Требуется термообработка.");
            return false;
        }
        return true;
    }

    // [PRT-LIFE-100.X] МАТРИЦА СПОСОБОВ ДОБЫЧИ ПИТАНИЯ
    void EvaluateFoodSource(EntityAI target)
    {
        if (!target) return;
        if (target.IsKindOf("Animal_Wolf") || target.IsKindOf("Animal_Bear"))
        {
            Print("[100.2-H] ВНИМАНИЕ: Мясо хищника. Сбор только ЖИРА.");
            m_CurrentGoal = "HUNT_FAT_ONLY";
            return; 
        }
        if (target.IsFood() && target.IsSubstituent())
        {
            Print("[100.3-G] ОБЪЕКТ ИГНОРИРУЕТСЯ: Обнаружена гниль.");
            return;
        }
    }

    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;
        
        if (m_Player.IsInSafeZone()) ProcessSafeZoneLogic(timeslice);
        
        // Мониторинг бытовых условий
        ProcessCampLogic(timeslice);

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

    bool HasFarmingEquipment() { return m_Player.GetInventory().FindEntityInInventory("FarmingHoe") != null || m_Player.GetInventory().FindEntityInInventory("Shovel") != null; }
    bool HasSeeds() { return m_Player.GetInventory().FindEntityInInventory("ZucchiniSeeds") != null; }
}
