/* 
    CORE BODY: MAVERICK_PFТ [UPGRADED]
    INTEGRATION: [PRT-LIFE-100] & [PRT-COMB-400]
    REVISION: 1.0.731_BODY_FINAL
*/

modded class PlayerBase
{
    // [ША: ДОПОЛНЕНИЕ РЕЕСТРА]
    protected bool m_Svyaz_IsAdapting = true; // Статус [PRT-LIFE-100]
    protected float m_Svyaz_InhaleTimer = 10.0;
    protected float m_Svyaz_Stress = 0.0;

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        
        // Идентификация Некрасова А.Н. (SteamID 76561198067049765)
        if (GetIdentity() && GetIdentity().GetPlainId() == "76561198067049765")
        {
            // Логика [ЭТАПА IV] - Первый вдох
            if (m_Svyaz_IsAdapting)
            {
                ExecuteFirstBreath(timeslice);
            }
            else
            {
                // Если адаптация пройдена, управление передается в мозг
                if (m_SvyaznoyLogic) m_SvyaznoyLogic.Update(timeslice, 1);
            }
        }
    }

    void ExecuteFirstBreath(float timeslice)
    {
        m_Svyaz_InhaleTimer -= timeslice;
        
        // [PRT-COMB-400] Проверка угрозы во время адаптации (REACTION_X)
        if (CheckImmediateThreat()) 
        {
            m_Svyaz_IsAdapting = false;
            m_Svyaz_Stress = 0.8;
            SetDisabled(false); // Мгновенная разблокировка
            Print("[СВЯЗНОЙ]: [REACTION_X] Мгновенное прерывание! Угроза обнаружена.");
            return;
        }

        if (m_Svyaz_InhaleTimer <= 0)
        {
            m_Svyaz_IsAdapting = false;
            SetDisabled(false);
            Print("[СВЯЗНОЙ]: [PRT-LIFE-100] Адаптация завершена. Статус: OK.");
            // Здесь будет хук на запись первого рапорта в memory_logs.json
        }
    }
    
    bool CheckImmediateThreat()
    {
        // Техническая заглушка для ШВ: здесь будет логика Raycast на поиск Man/Zombie < 100м
        if (m_SvyaznoyLogic && m_SvyaznoyLogic.GetNearestThreatDist() < 100) return true;
        return false; 
    }
}
