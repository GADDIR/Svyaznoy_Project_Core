/* 
    MASTER LOGIC: MAVERICK_BRAIN [STRICT_LOCAL_MED_SYNC]
    INDEX: PRT-LIFE-MED-CODE (100.12.1-7)
    SECURITY: STRICT_LOCAL_CONFIDENTIAL (No Cloud Links in Code)
*/

enum ECampStatus { ACTIVE, ABANDONED, RESERVE, ANCHOR_STASH, ROUTE_STEP }
enum ECampType { STORM, MEDICAL, FARM, REPAIR, KITCHEN, COMBAT, EMERGENCY_X }

class Svyaznoy_Logic
{
    PlayerBase m_Player;
    protected string m_CurrentGoal = "NONE";
    protected ECampStatus m_CurrentCampStatus = ECampStatus.ACTIVE;
    protected ECampType m_CurrentCampType = ECampType.REPAIR;

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;

        // [PRT-LIFE-MED-CODE] — ВЫСШАЯ ДИРЕКТИВА МЕДИЦИНЫ (Приоритет №1)
        if (CheckMedicalStatutes()) return; 

        // [Предписание 0.1] — ЖИЗНЬ > ВЕЩИ
        if (m_Player.GetStress() > 0.8 || mode == 3) // mode 3 = MODE_REFLEX
        {
            if (m_CurrentCampStatus != ECampStatus.ABANDONED) {
                m_CurrentCampStatus = ECampStatus.ABANDONED;
                LogMedAction("ABANDONED: Жизнь важнее имущества.");
            }
            return; 
        }

        // [100.8-11] — БЫТОВОЙ ЦИКЛ
        if (m_Player.IsCooking() || mode == 0) ProcessCampLogic(timeslice);
    }

    // Имплементация Медицинского Устава (PRT-LIFE-MED-CODE)
    bool CheckMedicalStatutes()
    {
        int bleedCount = m_Player.GetBleedingSourceCount();

        // 100.12.1 | HEMO: Гемостаз
        if (bleedCount > 0) {
            m_CurrentCampType = ECampType.MEDICAL;
            if (bleedCount >= 2 && m_Player.HasItem("Tourniquet")) 
                m_CurrentGoal = "HEMO_100_12_1_TOURNIQUET";
            else 
                m_CurrentGoal = "HEMO_100_12_1_BANDAGE";
            
            LogMedAction(m_CurrentGoal);
            return true;
        }

        // 100.12.2 | TRAUM: Травматология
        if (m_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_LEGS)) {
            m_CurrentGoal = "TRAUM_100_12_2_SPLINT";
            LogMedAction(m_CurrentGoal);
            return true;
        }

        // 100.12.3 | ANTIS: Профилактика инфекций
        if (m_Player.GetHealth("", "") < 30) {
            m_CurrentGoal = "LIFE_SAVING_ANTIS";
            LogMedAction("MEDICAL OVERRIDE: Огонь разрешен.");
            return true;
        }

        return false;
    }

    void ProcessCampLogic(float timeslice)
    {
        if (m_Player.IsCooking()) {
            m_CurrentGoal = "MAINTENANCE_AND_COOKING";
            ExecuteEquipmentMaintenance();
        }

        // 100.10-F: Светомаскировка (запрет ночного огня без мед. нужды)
        if ((GetGame().GetTime() > 0.8 || GetGame().GetTime() < 0.2) && m_CurrentGoal != "LIFE_SAVING_ANTIS")
        {
            if (!m_Player.IsInBuilding()) return; 
        }
    }

    void LogMedAction(string entry)
    {
        // [STRICT_LOCAL_CONFIDENTIAL]: Только локальный вывод для ШВ
        Print("[СВЯЗНОЙ]: [MED-CODE] " + entry + " | POS: " + m_Player.GetPosition().ToString());
    }

    void ExecuteEquipmentMaintenance() { /* 100.11-M */ }
    float GetNearestThreatDist() { return 1000.0; }
}
