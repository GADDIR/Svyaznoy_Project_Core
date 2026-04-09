/* 
    MASTER LOGIC: MAVERICK_BRAIN [MONOLITH_1.2_TOTAL_SYNC]
    INDEX: PRT-100-900 (Reports 1.0, 2.0, 3.0 + COMM)
    SECURITY: STRICT_LOCAL_CONFIDENTIAL
*/

enum ECampStatus { ACTIVE, ABANDONED, RESERVE, ANCHOR_STASH, ROUTE_STEP }
enum ECampType { STORM, MEDICAL, FARM, REPAIR, KITCHEN, COMBAT, EMERGENCY_X }
enum ESZStage { SAFETY_FIRST, AGRO_AUDIT, ECONOM_CHECK, PREPARE_DEPARTURE }

class Svyaznoy_Logic
{
    PlayerBase m_Player;
    protected string m_CurrentGoal = "NONE";
    protected float m_OpenSpaceTimer = 0;
    protected int m_SZ_Stage = 0;
    protected ECampStatus m_CampStatus = ECampStatus.ACTIVE;

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    // [ГЛАВНЫЙ ДИСПЕТЧЕР]
    void Update(float timeslice, int mode)
    {
        if (!m_Player) return;

        // 1. [100.12-MED] МЕДИЦИНСКИЙ УСТАВ (Высший приоритет)
        if (CheckMedicalStatutes()) return;

        // 2. [ПРЕДПИСАНИЕ 0.1] ЖИЗНЬ > ВЕЩИ
        if (m_Player.GetStress() > 0.8 || mode == 5005) { // 5005 = MODE_REFLEX
            ExecuteEmergencyAbandon();
            return;
        }

        // 3. [500.4] РЕЖИМ ТИШИНЫ И ГЕСТИКУЛЯЦИЯ
        float threatDist = GetNearestThreatDist();
        if (threatDist < 150) ProcessSilentMode(threatDist);

        // 4. [600.1] ЛОГИКА СЕЙФ-ЗОНЫ (АГРО-АУДИТ + ИНДЕКС СКУПОСТИ)
        if (m_Player.IsInSafeZone()) {
            ProcessSafeZoneLogic();
        } else {
            // 5. [200.1] L-OPEN FILTER (ВЕТЕРАНСКАЯ ПОХОДКА)
            ProcessStealthMovement(timeslice, threatDist);
        }
    }

    // [300.7] ЦИФРОВОЙ ГОЛОС И ТЕКСТОВЫЙ ЗАС
    void VoiceOut(string entry, int code = 731)
    {
        string finalMsg = "[" + code.ToString() + "] " + entry;
        m_Player.SendMessageToRadioChat(finalMsg); 
        Print("[СВЯЗНОЙ]: [VOICE_OUT] -> " + finalMsg); // Сигнал для ШВ (TTS)
    }

    void ProcessSilentMode(float dist)
    {
        if (m_Player.IsRadioOn()) m_Player.SetRadioState(false); // [300.4]
        if (dist < 50) m_Player.PlayGesture(EmoteCB.Gesture_Silent); // [300.5]
        if (dist < 100) VoiceOut("Обнаружена активность. Тишина.", 911);
    }

    void ProcessStealthMovement(float timeslice, float threatDist)
    {
        if (m_Player.IsOnOpenSpace()) {
            m_OpenSpaceTimer += timeslice;
            float limit = (threatDist < 150) ? 5.0 : 15.0; // [200.1]
            if (m_OpenSpaceTimer > limit) VoiceOut("Открытое пространство. Ищу укрытие.", 100);
        } else { m_OpenSpaceTimer = 0; }
    }

    void ProcessSafeZoneLogic()
    {
        switch(m_SZ_Stage) {
            case 0: m_Player.SetStress(0.1); m_SZ_Stage = 1; break; // [600.5]
            case 1: // [600.6] АГРО-АУДИТ
                if (HasFarmingEquipment()) m_SZ_Stage = 2; 
                else VoiceOut("Торговля заблокирована. Нужна лопата.", 100); 
                break;
            case 2: // [600.4] ИНДЕКС СКУПОСТИ
                if (m_Player.GetStatEnergy().Get() > 200) VoiceOut("Энергия в норме. Только Tier-UP закупки.");
                m_SZ_Stage = 3; break;
        }
    }

    bool CheckMedicalStatutes()
    {
        if (m_Player.IsBleeding()) {
            VoiceOut("Повреждение оболочки. Гемостаз.", 100); //
            return true;
        }
        return false;
    }

    void ExecuteEmergencyAbandon()
    {
        if (m_CampStatus != ECampStatus.ABANDONED) {
            m_CampStatus = ECampStatus.ABANDONED;
            VoiceOut("Директива 0.1. Покидаю лагерь.", 911);
        }
    }

    float GetNearestThreatDist() { return 1000.0; }
    bool HasFarmingEquipment() { return m_Player.GetInventory().FindEntityInInventory("FarmingHoe") != null; }
}
