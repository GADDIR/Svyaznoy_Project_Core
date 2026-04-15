// ЦЕНТРАЛЬНОЕ ЯДРО ИИ "СВЯЗНОЙ" (CORE BRAIN)
// Интеграция Блоков №1 - №9 и Золотого Стандарта

class AN_Core_Brain
{
    // Ссылки на подсистемы памяти
    private ref AN_MemoryController    m_Memory
    private ref AN_SocialBrain          m_Social
    private ref AN_ResourceLoyalty      m_Loyalty
    private ref AN_PersistentMemory     m_Persistent
    
    // Владелец мозга
    private PlayerBase m_Nekrasov

    void AN_Core_Brain(PlayerBase player)
    {
        m_Nekrasov = player
        
        // Инициализация всех слоев
        m_Memory     = new AN_MemoryController(player)
        m_Social     = new AN_SocialBrain()
        m_Loyalty    = new AN_ResourceLoyalty()
        m_Persistent = new AN_PersistentMemory()
        
        // Применение Генезиса 1982 при рождении
        AN_Genesis_1982.ApplyChildhoodTraits(player)
    }

    // ГЛАВНЫЙ ЦИКЛ МЫШЛЕНИЯ
    void OnUpdate(float timeslice)
    {
        // 1. Опрос сенсоров (Экстренная память)
        m_Memory.OnUpdate(timeslice, m_Nekrasov)

        // 2. Проверка инстинктов (Протокол №1 из Блока 5)
        AN_MilitaryService_2001.ExecuteTacticalOverride(m_Nekrasov)

        // 3. Автономный аудит (Блок 6)
        AN_WorkExperience_2015.PerformInventoryAudit(m_Nekrasov)
    }

    // ПРИНЯТИЕ РЕШЕНИЙ (Фильтр через Золотой Стандарт)
    bool CanIAction(string actionType)
    {
        // Сверяемся с "Конституцией" Некрасова
        if (!AN_GoldenStandard.ValidateAction(m_Nekrasov, actionType))
            return false
        
        // Проверка гигиены из Блока 1 (1982)
        if (!AN_Genesis_1982.CheckFoodPurity(m_Nekrasov.GetStatDirtyHands().Get() > 0))
            return false

        return true
    }

    // РЕАКЦИЯ НА ИГРОКА (Социальный скоринг + Прагматизм)
    void OnPlayerDetected(PlayerBase other)
    {
        m_Social.EvaluateTarget(m_Nekrasov, other)
        
        // Если Бактерия полезная (Блок 9), включаем ресурсную лояльность
        if (m_Social.GetSocialStatus(other.GetIdentity().GetId()) == "NEUTRAL")
            m_Loyalty.UpdateStagnation(other.GetIdentity().GetId(), 0)
    }
}
