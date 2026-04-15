// NEKRASOV_BRAIN_CORE.C — ЦЕНТРАЛЬНЫЙ ПРОЦЕССОР СОСТОЯНИЙ
// Интеграция всех 12 блоков. Узел принятия финальных решений.

class Nekrasov_Brain_Core
{
    // Ссылки на подсистемы
    private ref Nekrasov_Identity      m_Identity
    private ref Nekrasov_Memory_Buffer m_Memory
    private ref Nekrasov_Moral_Engine   m_Moral
    
    // Состояние системы (State Machine)
    private string m_ActiveState = "OBSERVATION"

    void Nekrasov_Brain_Core(PlayerBase player)
    {
        // Инициализация Личности и Памяти
        m_Identity = new Nekrasov_Identity(player)
        m_Memory   = new Nekrasov_Memory_Buffer(player)
        m_Moral    = new Nekrasov_Moral_Engine()
        
        Nekrasov_Mumble_Logic.Say(player, "Система запущена. Сектор 900 под наблюдением.")
    }

    // ГЛАВНЫЙ ЦИКЛ (Вызывается каждый тик)
    void OnUpdate(float timeslice, PlayerBase player)
    {
        // 1. Опрос Памяти (Что я вижу?)
        m_Memory.OnTick(timeslice, player)

        // 2. Вердикт Морального Движка (Как я на это реагирую?)
        string decision = m_Moral.DecideOutcome(player, null) // Здесь будет цель

        // 3. УПРАВЛЕНИЕ СОСТОЯНИЯМИ
        if (decision == "ELIMINATE")
            m_ActiveState = "COMBAT"
            
        if (decision == "IGNORE" && m_ActiveState != "HOUSEHOLD")
            m_ActiveState = "OBSERVATION"

        // Исполнение тактики
        if (m_ActiveState == "COMBAT")
            Nekrasov_Combat_Tactics.OnCombatUpdate(player, null, 0)
    }

    // ПРАВО ВЕТО (Блок Х)
    bool CanIAction(PlayerBase player, string actionName)
    {
        // Заветы Анны и Николая превыше игровых команд
        if (!Nekrasov_Food_Taboo.IsActionAllowed(player, null))
            return false
            
        return true
    }
}
