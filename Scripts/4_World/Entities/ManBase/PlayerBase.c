/* 
    CORE BODY: MAVERICK_PFТ [GLOBAL_SYNC]
    INDEX: PRT_CORE_INDEX-000
    REVISION: 1.0.731_FINAL
*/

modded class PlayerBase
{
    protected bool m_Svyaz_IsAdapting = true; 
    protected float m_Svyaz_InhaleTimer = 10.0;

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        
        // Идентификация Некрасова А.Н. (SteamID 76561198067049765)
        if (GetIdentity() && GetIdentity().GetPlainId() == "76561198067049765")
        {
            // [PRT-LIFE-100]: Логика адаптации (Первый вдох)
            if (m_Svyaz_IsAdapting)
            {
                ExecuteFirstBreath(timeslice);
            }
            else if (m_SvyaznoyLogic)
            {
                // Постоянный мониторинг через мастер-логику (100-700)
                m_SvyaznoyLogic.Update(timeslice, 1);
            }
        }
    }

    void ExecuteFirstBreath(float timeslice)
    {
        m_Svyaz_InhaleTimer -= timeslice;

        // [PRT-COMB-400]: Экстренное прерывание при угрозе (REACTION_X)
        if (m_SvyaznoyLogic && m_SvyaznoyLogic.GetNearestThreatDist() < 100) 
        {
            m_Svyaz_IsAdapting = false;
            SetDisabled(false);
            m_SvyaznoyLogic.ExecuteProtocol(400); // Мгновенный выход в бой
            Print("[СВЯЗНОЙ]: [PRT-400] Экстренное пробуждение! Угроза обнаружена.");
            return;
        }

        // Штатное завершение адаптации
        if (m_Svyaz_InhaleTimer <= 0)
        {
            m_Svyaz_IsAdapting = false;
            SetDisabled(false);
            Print("[СВЯЗНОЙ]: [PRT-100] Адаптация завершена. Документы на месте.");
            
            // Первый рапорт в память
            if (m_SvyaznoyLogic) m_SvyaznoyLogic.ExecuteProtocol(100);
        }
    }
}
