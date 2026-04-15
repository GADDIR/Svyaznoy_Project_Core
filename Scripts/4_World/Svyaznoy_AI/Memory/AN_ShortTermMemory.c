// МОДУЛЬ КОРОТКОЙ ПАМЯТИ А.Н. НЕКРАСОВА (SESSION CACHE)
class AN_ShortTermMemory
{
    // Объект хранения: название -> позиция
    private ref map<string, vector> m_ItemsPositions;
    // Таймеры хранения: название -> оставшееся время (сек)
    private ref map<string, float>  m_ItemsTimers;
    
    private float m_PurgeDistance = 500.0; // Дистанция "забывания" из реестра

    void AN_ShortTermMemory()
    {
        m_ItemsPositions = new map<string, vector>;
        m_ItemsTimers = new map<string, float>;
    }

    // ЗАПОМНИТЬ: Фиксация объекта (топор, Z за углом, рюкзак)
    void Pin(string name, vector pos, float duration = 1800.0)
    {
        m_ItemsPositions.Set(name, pos);
        m_ItemsTimers.Set(name, duration);
    }

    // ОБНОВЛЕНИЕ: Тик памяти (вызывается из PlayerBase или MainController)
    void Tick(float timeslice, vector currentPos)
    {
        // 1. Проверка дистанции: ушел далеко — забыл всё
        if (vector.Distance(currentPos, GetLastAnchor(currentPos)) > m_PurgeDistance)
            ClearAll();

        // 2. Проверка времени: суп остыл, косуля убежала
        for (int i = 0; i < m_ItemsTimers.Count(); i++)
        {
            string key = m_ItemsTimers.GetKey(i);
            float timeLeft = m_ItemsTimers.Get(key) - timeslice;

            if (timeLeft <= 0)
                Unpin(key);
            else
                m_ItemsTimers.Set(key, timeLeft);
        }
    }

    // Проверка: помнит ли Некрасов, где объект?
    vector GetPosition(string name)
    {
        if (m_ItemsPositions.Contains(name))
            return m_ItemsPositions.Get(name);
        
        return "0 0 0";
    }

    private void Unpin(string name)
    {
        m_ItemsPositions.Remove(name);
        m_ItemsTimers.Remove(name);
    }

    private void ClearAll()
    {
        m_ItemsPositions.Clear();
        m_ItemsTimers.Clear();
    }

    private vector GetLastAnchor(vector p) { return p; } // Заглушка под логику якоря
}
