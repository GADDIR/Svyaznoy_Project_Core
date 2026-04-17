modded class PlayerBase // Вшиваем разум прямо в тело Некрасова
{
    private ref NEKRASOV_Core_Brain_1 m_Mind;

    override void Init()
    {
        super.Init();
        // Инициализируем разум при рождении персонажа
        m_Mind = new NEKRASOV_Core_Brain_1(this);
    }
}

class NEKRASOV_Core_Brain_1
{
    private ref NEKRASOV_MemoryController    m_Memory;
    private ref NEKRASOV_SocialBrain          m_Social;
    private ref NEKRASOV_ResourceLoyalty      m_Loyalty;
    private ref NEKRASOV_PersistentMemory     m_Persistent;
    private PlayerBase m_NEKRASOV;

    void NEKRASOV_Core_Brain_1(PlayerBase player)
    {
        m_NEKRASOV = player;
        
        // Инициализация подсистем (Твои блоки 1-9)
        m_Memory     = new NEKRASOV_MemoryController(player);
        m_Social     = new NEKRASOV_SocialBrain();
        m_Loyalty    = new NEKRASOV_ResourceLoyalty();
        m_Persistent = new NEKRASOV_PersistentMemory();
        
        // Генезис 1982
        NEKRASOV_Genesis_1982.ApplyChildhoodTraits(player);
    }

    void OnUpdate(float timeslice)
    {
        if (!m_NEKRASOV) return;

        m_Memory.OnUpdate(timeslice, m_NEKRASOV);
        NEKRASOV_MilitaryService_2001.ExecuteTacticalOverride(m_NEKRASOV);
        NEKRASOV_WorkExperience_2015.PerformInventoryAudit(m_NEKRASOV);
    }

    // Твоя проверка через Золотой Стандарт
    bool CanIAction(string actionType)
    {
        if (!NEKRASOV_GoldenStandard.ValidateAction(m_NEKRASOV, actionType))
            return false;
        
        // Проверка чистоты рук (Блок 1)
        if (!NEKRASOV_Genesis_1982.CheckFoodPurity(m_NEKRASOV.GetStatDirtyHands().Get() > 0))
            return false;

        return true;
    }
}
