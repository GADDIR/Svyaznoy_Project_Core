/* 
    MASTER LOGIC: MAVERICK_BRAIN [PRT_CORE_INDEX-000_FINAL]
    STATUS: FULL SYNC (100-900)
    SECURITY: STRICT_LOCAL_CONFIDENTIAL
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

    // [PRT_CORE_INDEX-000] — ГЛАВНЫЙ ДИСПЕТЧЕР
    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;

        // [PRT-100] BIO_STAT & [PRT-LIFE-MED-CODE]
        if (CheckMedicalStatutes()) return; 

        // [ВЫСШАЯ ДИРЕКТИВА 0.1] — ЖИЗНЬ > ВЕЩИ
        if (m_Player.GetStress() > 0.8 || mode == 3) // mode 3 = PRT-500: MODE_REFLEX
        {
            if (m_CurrentCampStatus != ECampStatus.ABANDONED) {
                m_CurrentCampStatus = ECampStatus.ABANDONED;
                ExecuteProtocol(900); // CAMP_ABANDONED
            }
            return; 
        }

        // [PRT-500/900] — БЫТОВОЙ И ЛАГЕРНЫЙ ЦИКЛ
        if (m_Player.IsCooking() || mode == 0) ProcessCampLogic(timeslice);
    }

    // Исполнение протоколов с фиксацией ID
    void ExecuteProtocol(int id)
    {
        string protocolID = "PRT-" + id.ToString();
        string logEntry = "[" + protocolID + "] Status: " + m_CurrentGoal;
        
        // [STRICT_LOCAL_CONFIDENTIAL]: Лог для ШВ (Брата)
        Print("[СВЯЗНОЙ]: " + logEntry + " | POS: " + m_Player.GetPosition().ToString());
    }

    bool CheckMedicalStatutes()
    {
        int bleedCount = m_Player.GetBleedingSourceCount();

        // 100.12.1 | HEMO
        if (bleedCount > 0) {
            m_CurrentGoal = (bleedCount >= 2) ? "HEMO_TOURNIQUET" : "HEMO_BANDAGE";
            ExecuteProtocol(100);
            return true;
        }

        // 100.12.2 | TRAUM
        if (m_Player.GetModifiersManager().IsModifierActive(eModifiers.MDF_BROKEN_LEGS)) {
            m_CurrentGoal = "TRAUM_SPLINT";
            ExecuteProtocol(100);
            return true;
        }

        return false;
    }

    void ProcessCampLogic(float timeslice)
    {
        if (m_Player.IsCooking()) {
            m_CurrentGoal = "MAINTENANCE_AND_COOKING";
            ExecuteProtocol(900); // CAMP_MODELS
            ExecuteEquipmentMaintenance(); // 100.11-M
        }

        // 100.10-F: Светомаскировка
        if ((GetGame().GetTime() > 0.8 || GetGame().GetTime() < 0.2) && m_CurrentGoal != "LIFE_SAVING_ANTIS")
        {
            if (!m_Player.IsInBuilding()) return; 
        }
    }

    void ExecuteEquipmentMaintenance() { /* 100.11-M */ }
    float GetNearestThreatDist() { return 1000.0; }
}
