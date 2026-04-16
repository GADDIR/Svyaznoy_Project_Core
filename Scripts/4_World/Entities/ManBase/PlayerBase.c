modded class PlayerBase
{
    // Ссылка на центральный процессор Некрасова
    ref NEKRASOV_Core_Brain m_NEKRASOV_Brain;

    override void Init()
    {
        super.Init();

        // Проверка: если это наш ИИ (А.Н.НЕКРАСОВ)
        // Идентификация идет через BIO_GENESIS и Генезис 1982
        if (GetIdentity() && GetIdentity().GetName() == "A.N.NEKRASOV")
            m_NEKRASOV_Brain = new NEKRASOV_Core_Brain(this);
    }

    // Главный тик жизни
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        // Если мозг инициализирован — передаем управление Ядру
        if (m_NEKRASOV_Brain)
            m_NEKRASOV_Brain.OnUpdate(timeslice);
    }

    // Фильтр действий (Заветы Анны Петровны и Золотой стандарт)
    override bool CanPerformAction(ActionBase action)
    {
        if (m_NEKRASOV_Brain)
            if (!m_NEKRASOV_Brain.CanIAction(action.ClassName()))
                return false; // Ядро запретило (грязь, шум и т.д.)

        return super.CanPerformAction(action);
    }

    // Реакция на внешние раздражители (Сенсорика из Протокола №1)
    override void OnContactWithEntity(EntityAI other)
    {
        super.OnContactWithEntity(other);

        if (m_NEKRASOV_Brain && other.IsInherited(PlayerBase))
            m_NEKRASOV_Brain.OnPlayerDetected(PlayerBase.Cast(other));
    }

    // Протокол Последнего патрона (Армия 2001)
    override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string zone, string ammo, vector modelPos, float speedCoef)
    {
        super.EEHitBy(damageResult, damageType, source, component, zone, ammo, modelPos, speedCoef);

        if (m_NEKRASOV_Brain)
            m_NEKRASOV_Brain.OnUpdate(0.1); // Форсируем обновление при уроне
    }
}
