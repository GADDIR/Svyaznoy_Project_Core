/* 
    MASTER LOGIC: MAVERICK_BRAIN [FINAL_LIFE_SYNC]
    INDEX: PRT-100.8 - 100.12 + DIRECTIVE 0.1
    STATUS: FULL INTEGRATION
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

        // --- [ПРЕДПИСАНИЕ 0.1]: ЖИЗНЬ > ВЕЩИ ---
        if (m_Player.GetStress() > 0.8 || mode == 3) // mode 3 = MODE_REFLEX
        {
            if (m_CurrentCampStatus != ECampStatus.ABANDONED) {
                m_CurrentCampStatus = ECampStatus.ABANDONED;
                Print("[100.9-L] ABANDONED: Жизнь важнее имущества. Уход из точки: " + m_Player.GetPosition().ToString());
            }
            return; 
        }

        // --- [100.12-MED]: МЕДИЦИНСКИЙ ПРИОРИТЕТ ---
        if (m_Player.IsBleeding() || m_Player.GetHealth("", "") < 30)
        {
            m_CurrentCampType = ECampType.MEDICAL;
            ExecuteMedicalLogic();
            return;
        }

        // --- БЫТОВОЙ ЦИКЛ И ЛАГЕРЬ ---
        if (m_Player.IsCooking() || mode == 0) // mode 0 = STATIC
        {
            ProcessCampLogic(timeslice);
        }
    }

    void ExecuteMedicalLogic()
    {
        m_CurrentGoal = "LIFE_SAVING";
        // Override светомаскировки разрешен (100.12-MED)
        Print("[100.12-MED] MEDICAL OVERRIDE: Огонь разрешен для спасения жизни.");
    }

    void ProcessCampLogic(float timeslice)
    {
        // 100.11-M: Технический регламент (Ремонт во время готовки)
        if (m_Player.IsCooking()) {
            m_CurrentGoal = "MAINTENANCE_AND_COOKING";
            ExecuteEquipmentMaintenance();
        }

        // 100.10-F: Светомаскировка (запрет ночного огня без MED_OVERRIDE)
        if ((GetGame().GetTime() > 0.8 || GetGame().GetTime() < 0.2) && m_CurrentGoal != "LIFE_SAVING")
        {
            if (!m_Player.IsInBuilding()) return; // Блокировка огня
        }
    }

    void ExecuteEquipmentMaintenance()
    {
        // 100.11-M: Чистка оружия, заточка ножей, ремонт обуви
    }

    float GetNearestThreatDist() { return 1000.0; }
}
