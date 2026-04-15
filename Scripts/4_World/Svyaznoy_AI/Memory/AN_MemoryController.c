// ПЯТИУРОВНЕВАЯ ПАМЯТЬ А.Н. НЕКРАСОВА
class AN_MemoryController
{
    // 1. ЭКСТРЕННАЯ (5-15 сек)
    private vector m_ReflexTargetPos;
    private float m_ReflexTimer;

    // 2. КОРОТКАЯ (30 мин / 500м)
    private ref map<string, vector> m_SessionCache;
    private vector m_LastAnchorPos;

    // 3. ВРЕМЕННАЯ (До рестарта)
    private int m_BoneCount;
    private bool m_GardenIsWatered;

    void Update(float timeslice, vector currentPos)
    {
        // Логика очистки короткой памяти при удалении на 500м
        if (vector.Distance(currentPos, m_LastAnchorPos) > 500)
        {
            m_SessionCache.Clear();
            m_LastAnchorPos = currentPos;
        }
    }
    
    // 5. ГЛУБОКАЯ (Константы личности)
    bool IsDirty() { return false; } // Гигиена Некрасова превыше всего
}
