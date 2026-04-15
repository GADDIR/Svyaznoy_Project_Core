// AI_PERSONALITYCORE.C — ЦЕНТРАЛЬНЫЙ УЗЕЛ ПРИНЯТИЯ РЕШЕНИЙ
// Объединение 5 уровней памяти и 12 блоков биографии

class AI_PersonalityCore
{
    // Ссылки на ключевые системы
    private ref Nekrasov_Memory_Manager m_Memory
    private ref Nekrasov_Moral_Engine   m_Moral
    private ref Nekrasov_Trust_System   m_Trust
    
    // Текущее состояние личности (State Machine)
    private string m_CurrentState = "OBSERVATION" // Наблюдение по умолчанию

    void AI_PersonalityCore(PlayerBase player)
    {
        m_Memory = new Nekrasov_Memory_Manager(player)
        m_Moral  = new Nekrasov_Moral_Engine()
        m_Trust  = new Nekrasov_Trust_System()
        
        // Запуск Генезиса при рождении
        ApplyGenesisStats(player)
    }

    // ГЛАВНЫЙ ЦИКЛ МЫШЛЕНИЯ (Вызывается каждый тик)
    void OnLogicTick(float timeslice, PlayerBase player)
    {
        // 1. Опрос Памяти: Что я вижу и что я помню?
        m_Memory.Update(timeslice)

        // 2. Опрос Морального Движка: Как я к этому отношусь?
        string decision = m_Moral.EvaluateSituation(player, m_Memory)

        // 3. Смена состояний (State Machine)
        if (decision == "DANGER")
            SwitchToState("COMBAT")
        
        if (decision == "SAFE" && m_CurrentState != "AGRO")
            SwitchToState("HOUSEHOLD") // Возврат к грядкам и ремонту
            
        ExecuteStateLogic(timeslice, player)
    }

    private void SwitchToState(string newState)
    {
        if (m_CurrentState == newState)
            return
            
        m_CurrentState = newState
        // Лог в LIFE_LOG_NEKRASOV.json через Ша
    }

    private void ExecuteStateLogic(float timeslice, PlayerBase player)
    {
        // Приоритет №1: Гигиена Анны Петровны
        if (player.GetStatDirtyHands().Get() > 0)
            player.ForceAction("WASH_HANDS")

        // Реализация состояний
        if (m_CurrentState == "COMBAT")
            Svyaznoy_Tactical_Z.Execute(player)
            
        if (m_CurrentState == "HOUSEHOLD")
            Svyaznoy_Agro_Memory.Execute(player)
    }

    private void ApplyGenesisStats(PlayerBase player)
    {
        // Блок IX: Био-генезис (Темперамент)
        player.SetStressResistance(0.95)
    }
}
