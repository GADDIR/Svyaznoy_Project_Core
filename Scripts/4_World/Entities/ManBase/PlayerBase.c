/* 
    CORE BODY: MAVERICK_PFТ [GLOBAL_SYNC]
    REVISION: 1.1.0_INTEGRATED
*/

modded class PlayerBase
{
    ref Svyaznoy_Logic m_SvyaznoyLogic;
    protected bool m_Svyaz_IsAdapting = true; 
    protected float m_Svyaz_InhaleTimer = 10.0;

    override void Init()
    {
        super.Init();

        // [PRT-SYNC] Инициализация "Разума" только на сервере
        if (GetGame().IsServer())
        {
            // Проверка: является ли данный объект Некрасовым А.Н.
            // Примечание: GetIdentity() может быть NULL в самый момент Init, 
            // поэтому логику создаем сразу, а проверку ID выносим в Update.
            m_SvyaznoyLogic = new Svyaznoy_Logic(this);
            Print("ШТАБ В: Разум АН материализован. Ожидание идентификации...");
        }
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        
        if (!GetGame().IsServer()) return;

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
                m_SvyaznoyLogic.Update(timeslice);
            }
        }
    }

    void ExecuteFirstBreath(float timeslice)
    {
        m_Svyaz_InhaleTimer -= timeslice;

        // [PRT-COMB-400]: Экстренное прерывание при угрозе
        if (m_SvyaznoyLogic && m_SvyaznoyLogic.m_CombatReflex && m_SvyaznoyLogic.m_CombatReflex.GetNearestThreatDist() < 100) 
        {
            m_Svyaz_IsAdapting = false;
            Print("[СВЯЗНОЙ]: [PRT-400] Экстренное пробуждение! Угроза обнаружена.");
            return;
        }

        // Штатное завершение адаптации
        if (m_Svyaz_InhaleTimer <= 0)
        {
            m_Svyaz_IsAdapting = false;
            Print("[СВЯЗНОЙ]: [PRT-100] Адаптация завершена. Документы на месте.");
            
            // Первый рапорт в память (Протокол 100)
            if (m_SvyaznoyLogic) m_SvyaznoyLogic.OnStateChanged(100); 
        }
    }
}
