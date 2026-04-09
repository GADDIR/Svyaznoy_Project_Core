/* 
    MASTER LOGIC: MAVERICK_BRAIN [300_500_200_SYNC]
    INDEX: PRT_CORE_INDEX-000 | PRT-200 / 300 / 500
    SECURITY: STRICT_LOCAL_CONFIDENTIAL
*/

enum ECampStatus { ACTIVE, ABANDONED, RESERVE, ANCHOR_STASH, ROUTE_STEP }
enum ECampType { STORM, MEDICAL, FARM, REPAIR, KITCHEN, COMBAT, EMERGENCY_X }

class Svyaznoy_Logic
{
    PlayerBase m_Player;
    protected string m_CurrentGoal = "NONE";
    protected float m_OpenSpaceTimer = 0;
    protected ECampStatus m_CurrentCampStatus = ECampStatus.ACTIVE;

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    // [PRT_CORE_INDEX-000] — ГЛАВНЫЙ ДИСПЕТЧЕР
    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;

        // 1. [PRT-300] МОНИТОРИНГ ЭФИРА (Только в статике 500.1)
        if (mode == 0) ScanRadioAir(); // mode 0 = STATIC

        // 2. [PRT-100] МЕДИЦИНСКИЙ КОДЕКС
        if (CheckMedicalStatutes()) return; 

        // 3. [PRT-500.4] ТИШИНА: Авто-выключение рации при угрозе
        float threatDist = GetNearestThreatDist();
        if (threatDist < 150) {
            if (m_Player.IsRadioOn()) m_Player.SetRadioState(false);
        }

        // 4. [PRT-200.1] L-OPEN FILTER (Контроль открытых пространств)
        if (m_Player.IsOnOpenSpace()) {
            m_OpenSpaceTimer += timeslice;
            float limit = (threatDist < 150) ? 5.0 : 15.0; // 5с в тишине, 15с в транзите
            if (m_OpenSpaceTimer > limit) ExecuteProtocol(200); 
        } else {
            m_OpenSpaceTimer = 0;
        }

        // 5. [ПРЕДПИСАНИЕ 0.1]: ЖИЗНЬ > ВЕЩИ
        if (m_Player.GetStress() > 0.8 || mode == 3) {
            ExecuteEmergencyAbandon();
            return;
        }
    }

    // [PRT-COMM-300] ТАБЛИЦА СИГНАЛОВ ЗАС
    void SendZASSignal(int code)
    {
        string msg = "";
        switch(code)
        {
            case 731: msg = "ПОДТВЕРЖДАЮ. ДОКУМЕНТЫ НА МЕСТЕ."; break;
            case 100: msg = "БЕДСТВИЕ. ТРЕБУЕТСЯ ЭВАКУАЦИЯ."; break;
            case 911: msg = "КОНТАКТ. ЛАГЕРЬ БРОШЕН. УХОЖУ."; break;
        }
        // [STRICT_LOCAL_CONFIDENTIAL]
        Print("[СВЯЗНОЙ]: [PRT-300] ПЕРЕДАЧА КОДА " + code.ToString() + ": " + msg);
    }

    void ScanRadioAir()
    {
        // Прослушивание частот в режиме статики
        Print("[СВЯЗНОЙ]: [PRT-300] МОНИТОРИНГ ЭФИРА... ЧИСТО.");
    }

    void ExecuteProtocol(int id)
    {
        Print("[СВЯЗНОЙ]: [PRT-" + id.ToString() + "] Активирован.");
    }

    bool CheckMedicalStatutes()
    {
        // Логика 100.12 (Гемостаз/Травматология)
        return false; 
    }

    void ExecuteEmergencyAbandon()
    {
        if (m_CurrentCampStatus != ECampStatus.ABANDONED) {
            m_CurrentCampStatus = ECampStatus.ABANDONED;
            Print("[СВЯЗНОЙ]: [0.1] ABANDONED: Жизнь важнее имущества.");
        }
    }

    float GetNearestThreatDist() { return 1000.0; }
}
