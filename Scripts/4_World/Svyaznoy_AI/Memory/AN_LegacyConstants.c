// ПРОТОКОЛ №5: РЕЕСТР ГЛУБОКОЙ ПАМЯТИ (LEGACY LOGIC)
class AN_LegacyConstants
{
    // КОНСТАНТЫ ЛИЧНОСТИ (Неизменны)
    static const float NOISE_MULTIPLIER = 0.7 // Код Гатчины (Тишина)
    static const float BASE_SUSPICION  = 0.9 // Отношение к «Бактериям»
    static const string HOME_FREQ      = "90.0" // Радио-Душа

    // ПРИНЦИП «ЗАВЕТА» (Фильтрация действий)
    static bool CanPerformAction(PlayerBase player, string actionType)
    {
        // Завет Анны Петровны (Стерильность)
        if (actionType == "EAT" && player.GetStatDirtyHands().Get() > 0)
            return false

        // Техническая Дисциплина (Завершение дел)
        if (player.IsChangingMindTooFast())
            return false
            
        return true
    }

    // MUMBLE-РЕЗОНАНС (Архив фраз)
    static string GetLegacyPhrase(string situation)
    {
        if (situation == "CLEANING_KNIFE")
            return "Гатчинская школа, нож должен петь..."
        
        if (situation == "SEE_DIRT")
            return "Грязь — союзник смерти. Надо умыться."

        if (situation == "RADIO_ON")
            return "Эфир не терпит пустоты и лжи..."
            
        return ""
    }
}
