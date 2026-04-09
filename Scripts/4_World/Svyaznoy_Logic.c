/* 
    MASTER LOGIC: MAVERICK_BRAIN [PRT-LIFE-100.12-MED_READY]
    INDEX: PRT_CORE_INDEX-000 | PRT-100.11 - 100.12
    STATUS: INTEGRATING MEDICAL_EMERGENCY_OVERRIDE
*/

enum ESZStage { SAFETY_FIRST, AGRO_AUDIT, ECONOM_CHECK, PREPARE_DEPARTURE }

class Svyaznoy_Logic
{
    PlayerBase m_Player;
    protected ESZStage m_SZ_Stage = ESZStage.SAFETY_FIRST;
    protected string m_CurrentGoal = "NONE";

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    // [PRT-LIFE-100.12-MED] ПРОТОКОЛ МЕДИЦИНСКОГО ВМЕШАТЕЛЬСТВА
    void HandleMedicalEmergency(float timeslice)
    {
        if (!m_Player) return;

        float health = m_Player.GetHealth("", "");
        
        // 1. ПРИОРИТЕТ №1: ОСТАНОВКА КРОВИ И ПЕРЕЛОМЫ
        if (m_Player.IsBleeding()) 
        {
            m_CurrentGoal = "MED_STOP_BLEEDING";
            m_Player.ExecuteAction(ActionBandage); 
            return;
        }

        if (m_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_LEGS))
        {
            m_CurrentGoal = "MED_APPLY_SPLINT";
            Print("[100.12-MED] КРИТИЧЕСКИЙ ПЕРЕЛОМ. Движение заблокировано.");
            return; 
        }

        // 2. [MED_EMERGENCY_OVERRIDE]: НАРУШЕНИЕ СКРЫТНОСТИ (ША Одобрено)
        // Если здоровье < 30% или гипотермия — огонь разрешен в любых условиях
        if (health < 30.0 || m_Player.GetStatTemperature().Get() < 34.0) 
        {
            Print("[100.12-MED] Critical Emergency! Fire started for medical reasons. Status: Stabilizing.");
            m_CurrentGoal = "MED_FIRE_SURVIVAL";
            // Игнорируем запрет 100.10-F на ночные костры
            m_Player.SetOverrideStealth(true); 
        }
    }

    // [PRT-LIFE-100.11-M] ТЕХНИЧЕСКИЙ РЕГЛАМЕНТ ЛАГЕРЯ
    void ExecuteEquipmentMaintenance()
    {
        if (!m_Player) return;
        UnpackAmmoBoxes();
        EntityAI weapon = m_Player.GetHumanInventory().GetEntityInHands();
        if (weapon && m_Player.GetInventory().FindEntityInInventory("WeaponCleaningKit"))
        {
            if (weapon.GetHealth01("", "") < 0.8)
            {
                m_CurrentGoal = "MAINTENANCE_WEAPON";
                Print("[100.11-M] МАСТЕРСКАЯ: Обслуживание оружия и глушителя.");
            }
        }
        MaintainFootwear();
    }

    // [PRT-LIFE-100.8/9/10] БЫТОВОЙ ЦИКЛ
    void ProcessCampLogic(float timeslice)
    {
        if (!m_Player) return;

        // Ночной запрет на огонь (если нет мед. необходимости)
        if ((GetGame().GetTime() > 0.8 || GetGame().GetTime() < 0.2) && m_CurrentGoal != "MED_FIRE_SURVIVAL") 
        {
            if (!m_Player.IsInBuilding()) return;
        }

        if (m_Player.IsCooking())
        {
            m_CurrentGoal = "COOKING_SAFE_PROVISION";
            ExecuteEquipmentMaintenance(); 
        }
    }

    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;
        
        HandleMedicalEmergency(timeslice); // Высший приоритет
        if (m_Player.IsInSafeZone()) ProcessSafeZoneLogic(timeslice);
        ProcessCampLogic(timeslice);

        EntityAI target = m_Player.GetTargetEntity();
        if (target) EvaluateFoodSource(target);
    }

    void UnpackAmmoBoxes() {}
    void MaintainFootwear() {}
    void EvaluateFoodSource(EntityAI target) {}
    void ProcessSafeZoneLogic(float timeslice) {}
    bool HasFarmingEquipment() { return false; }
    bool HasSeeds() { return false; }
}
