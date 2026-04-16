// NEKRASOV_AI_PERSONALITYCORE.C — ЦЕНТРАЛЬНЫЙ ПРОЦЕССОР СОСТОЯНИЙ
// Интеграция: Блоки 1-36. Узел принятия финальных решений.

class AI_PersonalityCore
{
    // Ссылки на подсистемы разума
    private ref Nekrasov_Identity      m_Identity
    private ref Nekrasov_Memory_Buffer m_Memory
    private ref Nekrasov_Moral_Engine   m_Moral
    
    // Текущее состояние (State Machine)
    private string m_ActiveState = "OBSERVATION"

    void AI_PersonalityCore(PlayerBase player)
    {
        // Сборка Личности при спавне
        m_Identity = new Nekrasov_Identity(player)
        m_Memory   = new Nekrasov_Memory_Buffer(player)
        m_Moral    = new Nekrasov_Moral_Engine()
        
        Nekrasov_Mumble_Logic.Say(player, "Система запущена. Сектор 900 под наблюдением.")
    }

    // ГЛАВНЫЙ ЦИКЛ МЫШЛЕНИЯ
    void OnUpdate(float timeslice, PlayerBase player)
    {
        // 1. Опрос Памяти (Что я вижу/помню?)
        m_Memory.OnTick(timeslice, player)

        // 2. Вердикт Морального Движка (Как я отношусь к цели?)
        EntityAI target = player.GetTarget()
        string decision = m_Moral.DecideOutcome(player, PlayerBase.Cast(target))

        // 3. ПЕРЕКЛЮЧЕНИЕ СОСТОЯНИЙ
        if (decision == "ELIMINATE")
            m_ActiveState = "COMBAT"
            
        if (decision == "IGNORE" && m_ActiveState != "HOUSEHOLD")
            m_ActiveState = "OBSERVATION"

        // 4. ИСПОЛНЕНИЕ (Узлы поведения)
        if (m_ActiveState == "COMBAT")
            Nekrasov_Combat_Tactics.OnCombatUpdate(player, target, player.GetTargetDistance())
            
        if (m_ActiveState == "HOUSEHOLD")
            Nekrasov_Lifestyle_Module.OnLifestyleUpdate(player, player.GetLocalTime())
    }

    // ВЕРХОВНЫЙ ФИЛЬТР ДЕЙСТВИЙ (Блок Х)
    bool CanPerformAction(PlayerBase player, string actionName)
    {
        // Если гигиена или табу запрещают — ИИ блокирует действие
        if (!Nekrasov_Food_Taboo.IsActionAllowed(player, player.GetItemInHands()))
            return false
            
        return true
    }
}
