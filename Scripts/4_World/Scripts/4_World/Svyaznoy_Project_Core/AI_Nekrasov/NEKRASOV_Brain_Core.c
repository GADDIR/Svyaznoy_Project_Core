// Исправленная логика вызовов для синхронизации с твоими данными
void OnUpdate(float timeslice, PlayerBase player)
{
    m_Memory.OnTick(timeslice, player);
    // Модуль Морали теперь получает данные о игроке напрямую
    string decision = m_Moral.DecideOutcome(player, null); 
    if (decision == "ELIMINATE")
        m_ActiveState = "COMBAT";
            
    if (decision == "IGNORE" && m_ActiveState != "HOUSEHOLD")
        m_ActiveState = "OBSERVATION";
    if (m_ActiveState == "COMBAT")
        Nekrasov_Combat_Tactics.OnCombatUpdate(player, null, 0);
}
