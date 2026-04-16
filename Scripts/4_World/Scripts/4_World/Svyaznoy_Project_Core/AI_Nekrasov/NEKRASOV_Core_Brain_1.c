// ЦЕНТРАЛЬНОЕ ЯДРО ИИ "СВЯЗНОЙ" (CORE BRAIN)
// Интеграция Блоков №1 - №9 и Золотого Стандарта

class NEKRASOV_Core_Brain_1
{
    // Ссылки на подсистемы памяти
    private ref NEKRASOV_MemoryController    m_Memory
    private ref NEKRASOV_SocialBrain          m_Social
    private ref NEKRASOV_ResourceLoyalty      m_Loyalty
    private ref NEKRASOV_PersistentMemory     m_Persistent
    
    // Владелец мозга
    private PlayerBase m_NEKRASOV

    void NEKRASOV_Core_Brain_1(PlayerBase player)
    {
        m_NEKRASOV = player
        
        // Инициализация всех слоев
        m_Memory     = new NEKRASOV_MemoryController(player)
        m_Social     = new NEKRASOV_SocialBrain()
        m_Loyalty    = new NEKRASOV_ResourceLoyalty()
        m_Persistent = new NEKRASOV_PersistentMemory()
        
        // Применение Генезиса 1982 при рождении
        NEKRASOV_Genesis_1982.ApplyChildhoodTraits(player)
    }

    // ГЛАВНЫЙ ЦИКЛ МЫШЛЕНИЯ
    void OnUpdate(float timeslice)
    {
        // 1. Опрос сенсоров (Экстренная память)
        m_Memory.OnUpdate(timeslice, m_NEKRASOV)

        // 2. Проверка инстинктов (Протокол №1 из Блока 5)
        NEKRASOV_MilitaryService_2001.ExecuteTacticalOverride(m_NEKRASOV)

        // 3. Автономный аудит (Блок 6)
        NEKRASOV_WorkExperience_2015.PerformInventoryAudit(m_NEKRASOV)
    }

    // ПРИНЯТИЕ РЕШЕНИЙ (Фильтр через Золотой Стандарт)
    bool CanIAction(string actionType)
    {
        // Сверяемся с "Конституцией" Некрасова
        if (!NEKRASOV_GoldenStandard.ValidateAction(m_NEKRASOV, actionType))
            return false
        
        // Проверка гигиены из Блока 1 (1982)
        if (!NEKRASOV_Genesis_1982.CheckFoodPurity(m_NEKRASOV.GetStatDirtyHands().Get() > 0))
            return false

        return true
    }

    // РЕАКЦИЯ НА ИГРОКА (Социальный скоринг + Прагматизм)
    void OnPlayerDetected(PlayerBase other)
    {
        m_Social.EvaluateTarget(m_NEKRASOV, other)
        
        // Если Бактерия полезная (Блок 9), включаем ресурсную лояльность
        if (m_Social.GetSocialStatus(other.GetIdentity().GetId()) == "NEUTRAL")
            m_Loyalty.UpdateStagnation(other.GetIdentity().GetId(), 0)
    }
}
