class Nekrasov_Brain_Core
{
    // Ссылки на подсистемы
    private ref Nekrasov_Identity      m_Identity;      // Добавлена ;
    private ref Nekrasov_Memory_Buffer m_Memory;        // Добавлена ;
    private ref Nekrasov_Moral_Engine  m_Moral;         // Добавлена ;
    
    // Состояние системы (State Machine)
    private string m_ActiveState = "OBSERVATION";       // Добавлена ;

    void Nekrasov_Brain_Core(PlayerBase player)
    {
        // Инициализация Личности и Памяти
        m_Identity = new Nekrasov_Identity(player);     // Добавлена ;
        m_Memory   = new Nekrasov_Memory_Buffer(player); // Добавлена ;
        m_Moral    = new Nekrasov_Moral_Engine();       // Добавлена ;
        
        Nekrasov_Mumble_Logic.Say(player, "Система запущена. Сектор 900 под наблюдением."); // Добавлена ;
    }

    void OnUpdate(float timeslice, PlayerBase player)
    {
        m_Memory.OnTick(timeslice, player);             // Добавлена ;

        string decision = m_Moral.DecideOutcome(player, null); // Добавлена ;

        if (decision == "ELIMINATE")
            m_ActiveState = "COMBAT";                   // Добавлена ;
            
        if (decision == "IGNORE" && m_ActiveState != "HOUSEHOLD")
            m_ActiveState = "OBSERVATION";              // Добавлена ;

        if (m_ActiveState == "COMBAT")
            Nekrasov_Combat_Tactics.OnCombatUpdate(player, null, 0); // Добавлена ;
    }

    bool CanIAction(PlayerBase player, string actionName)
    {
        if (!Nekrasov_Food_Taboo.IsActionAllowed(player, null))
            return false;                               // Добавлена ;
            
        return true;                                    // Добавлена ;
    }
}
