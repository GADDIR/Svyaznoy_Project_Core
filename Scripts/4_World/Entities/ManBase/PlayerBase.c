modded class PlayerBase
{
    // Ссылка на модуль логики Связного
    protected ref Svyaznoy_Logic m_SvyaznoyLogic;

    override void Init()
    {
        super.Init();
        // Инициализация только для нашего SteamID или NPC
        if (GetSvyaznoyIdentity().IsSvyaznoy(this)) {
            m_SvyaznoyLogic = new Svyaznoy_Logic(this);
        }
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        
        // Передача управления в FSM (Режимы PRT-CODE-500)
        if (m_SvyaznoyLogic) {
            m_SvyaznoyLogic.Update(timeslice);
        }
    }
}
