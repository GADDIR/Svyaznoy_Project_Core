/* 
    MASTER LOGIC: MAVERICK_BRAIN [PRT-LIFE-100.11-M_READY]
    INDEX: PRT_CORE_INDEX-000 | PRT-100.8 - 100.11
    STATUS: INTEGRATING CAMP_MAINTENANCE & AMMO_MGMT
*/

enum ESZStage { SAFETY_FIRST, AGRO_AUDIT, ECONOM_CHECK, PREPARE_DEPARTURE }

class Svyaznoy_Logic
{
    PlayerBase m_Player;
    protected ESZStage m_SZ_Stage = ESZStage.SAFETY_FIRST;
    protected string m_CurrentGoal = "NONE";

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    // [PRT-LIFE-100.11-M] ТЕХНИЧЕСКИЙ РЕГЛАМЕНТ ЛАГЕРЯ
    void ExecuteEquipmentMaintenance()
    {
        if (!m_Player) return;

        // 1. Боекомплект: Распаковка и снаряжение магазинов
        UnpackAmmoBoxes();
        
        // 2. Оружейная мастерская: Глушитель и чистка
        EntityAI weapon = m_Player.GetHumanInventory().GetEntityInHands();
        if (weapon && m_Player.GetInventory().FindEntityInInventory("WeaponCleaningKit"))
        {
            if (weapon.GetHealth01("", "") < 0.8) // Профилактика заклинивания
            {
                m_CurrentGoal = "MAINTENANCE_WEAPON";
                Print("[100.11-M] МАСТЕРСКАЯ: Обслуживание оружия и глушителя.");
            }
        }

        // 3. Инструментальный цех: Заточка ножей
        EntityAI stone = m_Player.GetInventory().FindEntityInInventory("SharpeningStone");
        EntityAI knife = m_Player.GetInventory().FindEntityInInventory("Knife");
        if (stone && knife && knife.GetHealth01("", "") < 0.9)
        {
            m_CurrentGoal = "SHARPENING_KNIFE";
            Print("[100.11-M] ИНСТРУМЕНТАРИЙ: Заточка ножа камнем.");
        }

        // 4. Ремонт обуви (Приоритет мобильности)
        MaintainFootwear();
    }

    void UnpackAmmoBoxes()
    {
        // Логика автоматического вскрытия картонных коробок
    }

    void MaintainFootwear()
    {
        // Логика ремонта ботинок через LeatherSewingKit
    }

    // [PRT-LIFE-100.8/9/10] БЫТОВОЙ ЦИКЛ
    void ProcessCampLogic(float timeslice)
    {
        if (!m_Player) return;

        if (GetGame().GetTime() > 0.8 || GetGame().GetTime() < 0.2) 
        {
            if (!m_Player.IsInBuilding()) {
                Print("[100.10-F] КРИТИЧЕСКИЙ РИСК: Ночь, открытое пространство. Костер запрещен.");
                return;
            }
        }

        if (m_Player.IsCooking())
        {
            m_CurrentGoal = "COOKING_SAFE_PROVISION";
            // Активация регламента 100.11-M во время готовки
            ExecuteEquipmentMaintenance(); 
        }
    }

    // ... (остальные методы без изменений) ...

    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;
        if (m_Player.IsInSafeZone()) ProcessSafeZoneLogic(timeslice);
        ProcessCampLogic(timeslice);

        EntityAI target = m_Player.GetTargetEntity();
        if (target) EvaluateFoodSource(target);
    }
    
    // (Методы EvaluateFoodSource, ProcessSafeZoneLogic, HasFarmingEquipment, HasSeeds остаются прежними)
}
