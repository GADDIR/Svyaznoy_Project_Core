/* 
    CORE BODY: MAVERICK_PFТ [GLOBAL_SYNC]
    REVISION: 1.1.1_STABLE (INTEGRATED)
    ОПИСАНИЕ: Физическое тело А.Н. Некрасова с логикой адаптации и ID-фильтром.
*/

modded class PlayerBase
{
    ref Svyaznoy_Logic m_SvyaznoyLogic;
    protected bool m_Svyaz_IsAdapting = true; 
    protected float m_Svyaz_InhaleTimer = 10.0;

    override void Init()
    {
        super.Init();

        // [PRT-SYNC] Инициализация разума на стороне сервера при рождении сущности
        if (GetGame().IsServer())
        {
            m_SvyaznoyLogic = new Svyaznoy_Logic(this);
            Print("[ШТАБ В] Тело инициализировано. Ожидание входа Некрасова А.Н. в Сектор 900...");
        }
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        
        // Критическая проверка: работаем только на сервере и только если у игрока загрузились документы (Identity)
        if (!GetGame().IsServer() || !GetIdentity())
        {
            return;
        }

        // Жесткая идентификация Некрасова А.Н. (SteamID 76561198067049765)
        if (GetIdentity().GetPlainId() == "76561198067049765")
        {
            // [PRT-LIFE-100]: Период адаптации (Первый вдох)
            if (m_Svyaz_IsAdapting)
            {
                ExecuteFirstBreath(timeslice);
            }
            else if (m_SvyaznoyLogic)
            {
                // Передача управления в мастер-логику (Протоколы 100-700)
                m_SvyaznoyLogic.Update(timeslice);
            }
        }
    }

    // Метод постепенного пробуждения рефлексов
    void ExecuteFirstBreath(float timeslice)
    {
        m_Svyaz_InhaleTimer -= timeslice;

        // Штатное завершение адаптации через 10 секунд
        if (m_Svyaz_InhaleTimer <= 0)
        {
            m_Svyaz_IsAdapting = false;
            Print("[СВЯЗНОЙ]: [PRT-100] Адаптация завершена. Алексей Николаевич на связи. Эфир чист.");
            
            // Сигнал в ядро об активации рабочего режима 501 (Статика/Мир)
            if (m_SvyaznoyLogic)
            {
                m_SvyaznoyLogic.OnStateChanged(501); 
            }
        }
    }
}
