// ПРОТОКОЛ №7 и №8: СОЦИАЛЬНЫЙ СКОРИНГ И ПРАГМАТИЧНЫЙ РАСЧЕТ
class AN_SocialBrain
{
    private ref map<string, float> m_SocialScoring
    private float m_Nekrasov_UtilityFactor // Коэффициент выгоды (Cold Logic)
    private float m_PersonalAffinity      // Личная симпатия (Random Seed)

    void AN_SocialBrain()
    {
        m_SocialScoring = new map<string, float>
    }

    // ГЛАВНЫЙ АНАЛИЗАТОР (Кто передо мной и что с него взять?)
    void EvaluateTarget(PlayerBase player, PlayerBase target)
    {
        string id = target.GetIdentity().GetId()
        float currentScore = GetScore(id)
        
        // --- БЛОК ДОВЕРИЯ (Протокол №7) ---
        if (target.GetInHands() == null)
            currentScore += 5.0 // Респект за пустые руки

        if (IsMilitary(target))
            currentScore -= 15.0 // Военные — это всегда угроза
        
        // --- БЛОК ХОЛОДНОГО РАСЧЕТА (Протокол №8) ---
        float risk = CalculateRisk(target)
        float profit = CalculateLootValue(target)
        
        m_Nekrasov_UtilityFactor = profit / risk

        // ПРЕВЕНТИВНЫЙ УДАР: Если пользы мало, а риск высок
        if (m_Nekrasov_UtilityFactor < 0.2 && target.IsWithinRange(50.0))
            ExecuteAction("PREEMPTIVE_STRIKE")

        m_SocialScoring.Set(id, currentScore)
    }

    // МЕХАНИКА ПРЕДАТЕЛЬСТВА (Обкрадывание спящих)
    void ProcessSleeper(PlayerBase sleeper)
    {
        if (sleeper.IsSleeping() || sleeper.IsUnconscious())
        {
            // Утилитарный подход: забираем ресурсы
            ExecuteAction("STEAL_ALL_VALUABLES")
            
            // "Ранение в живот. Не жилец." — добиваем, если мешает
            if (m_Nekrasov_UtilityFactor < 0.4)
                ExecuteAction("ELIMINATE_BURDEN")
        }
    }

    // ХОЛОДНЫЙ АНАЛИЗ ДЛЯ MUMBLE
    string GetColdMumble(string event)
    {
        if (event == "PLAYER_WOUNDED")
            return "Ранение в живот. Не жилец. Лишняя трата бинтов."
        
        if (event == "LOOT_BODY")
            return "Мертвому вещи ни к чему, а живому — подспорье."
            
        return ""
    }

    private float GetScore(string id)
    {
        if (m_SocialScoring.Contains(id))
            return m_SocialScoring.Get(id)
        return 0.0
    }

    private bool IsMilitary(PlayerBase p)
    {
        // Проверка на камуфляж и бронежилеты
        return p.IsWearingMilitary()
    }

    private float CalculateLootValue(PlayerBase p) { return 10.0; } // Заглушка
    private float CalculateRisk(PlayerBase p) { return 5.0; }      // Заглушка
}
