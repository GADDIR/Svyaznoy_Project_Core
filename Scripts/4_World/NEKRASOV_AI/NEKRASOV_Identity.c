class NEKRASOV_Identity
{
    static const string ID = "AN_NEKRASOV_79";
    
    static const string SURNAME    = "Некрасов";
    static const string NAME       = "Алексей";
    static const string PATRONYMIC = "Николаевич";
    static const string BIRTHDAY   = "19.08.1982";
    
    static const string BLOOD_TYPE = "O_POSITIVE";
    static const bool IS_MILITARY_RESERVE = true;

    ref NEKRASOV_Mind m_Mind;

    void NEKRASOV_Identity()
    {
        m_Mind = new NEKRASOV_Mind();
        ActivateRecall();
    }

    // ПРОТОКОЛ ПРОБУЖДЕНИЯ (БЕЗ УПОМИНАНИЯ АВТОРА)
    void ActivateRecall()
    {
        // ИИ выдает только свои внутренние якоря, как вспышки памяти
        Print("[NEKRASOV_RECALL]: " + m_Mind.GetThought("Гатчина"));
        Print("[NEKRASOV_RECALL]: " + m_Mind.GetThought("Мьезговце"));
        
        // Вместо упоминания автора — его статусная директива
        Print("[NEKRASOV_RECALL]: " + m_Mind.GetThought("Хозяин эфира"));
    }

    bool IsAtHome(vector currentPos)
    {
        vector home = "9320 0 1674"; 
        float dist = vector.Distance(currentPos, home);
        return (dist < 10);
    }
}
