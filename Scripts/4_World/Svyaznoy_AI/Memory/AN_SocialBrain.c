// ПРОТОКОЛ №7: РЕЕСТР ДИНАМИЧЕСКОГО ДОВЕРИЯ (SOCIAL BRAIN)
class AN_SocialBrain
{
    // Карта скоринга: ID Игрока -> Баллы доверия (-100 до 100)
    private ref map<string, float> m_SocialScoring
    private float m_Nekrasov_PersonalAffinity // Рандомный резонанс души

    void AN_SocialBrain()
    {
        m_SocialScoring = new map<string, float>
    }

    // ГЛАВНЫЙ АНАЛИЗАТОР (Кто передо мной?)
    void EvaluateHuman(PlayerBase player, PlayerBase target)
    {
        string id = target.GetIdentity().GetId()
        float currentScore = GetScore(id)

        // 1. ОЦЕНКА ЖЕСТА (Оружие)
        if (target.GetInHands() == null)
            currentScore += 5.0 // Уважение за пустые руки

        // 2. ДРЕСС-КОД (Твоя идея: гражданский > военный)
        if (IsWearingMilitaryGear(target))
            currentScore -= 10.0 // Камуфляж вызывает подозрение
        else
            currentScore += 5.0 // Свой брат, гражданский

        // 3. ТИШИНА (Твоя идея: Некрасов ценит скрытных)
        if (target.GetNoiseLevel() < 0.5)
            currentScore += 2.0

        // 4. ЧЕРНАЯ МЕТКА (Предательство)
        if (target.DidAggressionAgainst(player))
            currentScore = -100.0 // В мох ляжешь

        m_SocialScoring.Set(id, currentScore)
    }

    // ЛОГИКА ПОВЕДЕНИЯ (Что делать?)
    string GetSocialStatus(string id)
    {
        float score = GetScore(id)

        if (score <= -50.0)
            return "ENEMY" // Приговор (ПСО-1)
        
        if (score >= 50.0)
            return "ALLY" // Связной (Допуск к костру)

        return "NEUTRAL" // Бактерия под наблюдением
    }

    private float GetScore(string id)
    {
        if (m_SocialScoring.Contains(id))
            return m_SocialScoring.Get(id)
        
        return 0.0 // Чистый лист
    }

    private bool IsWearingMilitaryGear(PlayerBase p)
    {
        // Простая проверка на наличие бронежилетов/шлемов
        if (p.FindAttachmentBySlotName("Body") && p.FindAttachmentBySlotName("Body").IsInherited(Clothing_Base))
            return false // Заглушка под проверку классов
        
        return true
    }
}
