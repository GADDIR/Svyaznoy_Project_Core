modded class PlayerBase
{
    protected ref Svyaznoy_Logic m_SvyaznoyLogic;
    protected bool m_IsFirstBreathComplete = false;
    protected float m_FirstBreathTimer = 10.0;
    protected int m_CurrentMode = 1; // По умолчанию MODE_TRANSIT

    override void Init()
    {
        super.Init();
        // Проверка: мы работаем только с телом Некрасова (ID 76561198067049765)
        if (GetSvyaznoyIdentity() && GetSvyaznoyIdentity().IsSvyaznoy(this)) 
        {
            m_SvyaznoyLogic = new Svyaznoy_Logic(this);
            SetDisabled(true); // Запуск Этапа IV: Блокировка управления на 10 сек
        }
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        if (!m_SvyaznoyLogic) return;

        // ЛОГИКА ЭТАПА IV: ПЕРВЫЙ ВДОХ
        if (!m_IsFirstBreathComplete)
        {
            m_FirstBreathTimer -= timeslice;
            // Директива 4: Если враг ближе 100м — просыпаемся мгновенно
            if (m_SvyaznoyLogic.GetNearestThreatDist() < 100 || m_FirstBreathTimer <= 0) 
            {
                m_IsFirstBreathComplete = true;
                SetDisabled(false);
                m_SvyaznoyLogic.SetRadioState(true); // Выход в эфир
            }
            return;
        }

        // ПЕРЕКЛЮЧАТЕЛЬ РЕЖИМОВ (PRT-CODE-500)
        float threat = m_SvyaznoyLogic.GetNearestThreatDist();
        if (threat < 50) m_CurrentMode = 3;      // MODE_REFLEX
        else if (threat < 150) m_CurrentMode = 2; // MODE_SILENCE
        else m_CurrentMode = 1;                  // MODE_TRANSIT

        m_SvyaznoyLogic.Update(timeslice, m_CurrentMode);
    }

    override void OnEnterSafeZone() // PRT-SAFE-600
    {
        super.OnEnterSafeZone();
        if (m_SvyaznoyLogic) m_SvyaznoyLogic.ActivateSafeZoneProtocol();
    }
}
