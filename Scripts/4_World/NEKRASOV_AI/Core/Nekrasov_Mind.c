class Nekrasov_Mind {
    protected EntityAI m_Owner; // Тот, в чьей голове этот ИИ
    protected ref Nekrasov_Vocabulary m_Vocab;
    
    void Nekrasov_Mind(EntityAI owner) {
        m_Owner = owner;
        m_Vocab = new Nekrasov_Vocabulary();
    }

    // Главная функция "Осознания"
    void Interpret(string subject, string verb, string adverb) {
        Print("NEKRASOV_AI: Обработка мысли -> " + subject + " " + verb + " " + adverb);
        
        // Превращаем грамматику в физику DayZ
        float speed = m_Vocab.GetSpeedFromAdverb(adverb);
        int actionID = m_Vocab.GetActionID(verb);
        
        ExecuteAction(actionID, speed);
    }

    protected void ExecuteAction(int action, float speed) {
        // Здесь будет код управления анимациями и навигацией
    }
}

