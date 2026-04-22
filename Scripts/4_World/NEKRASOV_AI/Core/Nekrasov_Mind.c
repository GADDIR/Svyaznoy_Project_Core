class NEKRASOV_MaverickController
{
    protected PlayerBase m_Agent;
    
    // Текущая "мысль"
    protected string m_LastVerb;   // Глагол
    protected string m_LastAdverb; // Наречие

    void NEKRASOV_MaverickController(PlayerBase agent)
    {
        m_Agent = agent;
    }

    // Обработка русского языка
    void ProcessText(string text)
    {
        text.ToLower();
        
        // Разделяем строку на слова
        TStringArray words = new TStringArray;
        text.Split(" ", words);

        string v = ""; // Глагол
        string a = ""; // Наречие

        foreach (string word : words)
        {
            // Грамматический фильтр (Глаголы)
            if (word == "иди" || word == "беги" || word == "стой" || word == "атакуй") v = word;
            
            // Грамматический фильтр (Наречия)
            if (word == "быстро" || word == "тихо" || word == "аккуратно") a = word;
        }

        if (v != "") 
        {
            m_LastVerb = v;
            m_LastAdverb = a;
            ApplyLogic();
        }
    }

    protected void ApplyLogic()
    {
        float speed = 1.0;
        if (m_LastAdverb == "быстро") speed = 2.0;
        if (m_LastAdverb == "тихо")   speed = 0.5;

        Print("[NEKRASOV] Осознал команду: " + m_LastVerb + " | Стиль: " + m_LastAdverb);

        // Здесь вызываются реальные методы движения NPC
        switch (m_LastVerb)
        {
            case "иди":
            case "беги":
                // m_Agent.GetInputController().... (Логика движения)
                break;
            case "стой":
                // Остановка
                break;
        }
    }

    void OnUpdate(float timeslice) 
    {
        // Здесь можно дописывать логику движения в реальном времени
    }
}
