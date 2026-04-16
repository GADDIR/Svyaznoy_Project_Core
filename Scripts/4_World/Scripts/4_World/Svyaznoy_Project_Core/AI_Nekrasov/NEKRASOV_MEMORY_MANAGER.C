// NEKRASOV_MEMORY_MANAGER.C — РЕАЛИЗАЦИЯ 5 УРОВНЕЙ ПАМЯТИ
// Основано на Протоколах №1 - №9

class Nekrasov_Memory_Manager
{
    // 1. Экстренная (Рефлексы - 15 сек)
    private vector m_E_ThreatVector
    private float  m_E_ReflexTTL

    // 2. Короткая (Быт - 30 мин)
    private ref map<string, vector> m_S_TaskMap

    // 3. Временная (День - до рестарта)
    private int m_O_AmmunitionCount
    private ref map<int, float> m_O_GardenStages

    // 4. Постоянная (Опыт - JSON)
    private ref Nekrasov_Profile m_P_Profile

    // 5. Глубокая (Догмы - Legacy)
    private ref AN_GoldenStandard m_L_Standard

    void Nekrasov_Memory_Manager(PlayerBase player)
    {
        m_S_TaskMap = new map<string, vector>
        m_O_GardenStages = new map<int, float>
        m_P_Profile = player.GetProfile() // Загрузка из Nekrasov_Profile.json
    }

    // ЛОГИКА ЗАПИСИ И ОБРАБОТКИ
    void Update(float timeslice, PlayerBase player)
    {
        // Очистка экстренной памяти (Чистая доска)
        if (m_E_ReflexTTL > 0)
        {
            m_E_ReflexTTL -= timeslice
            if (m_E_ReflexTTL <= 0)
                m_E_ThreatVector = "0 0 0"
        }

        // Проверка дистанции для короткой памяти (500м)
        if (vector.Distance(player.GetPosition(), m_P_Profile.GetHomeBase()) > 500)
            m_S_TaskMap.Clear()
    }

    // МЕТОД: ВСПОМНИТЬ ПРЕРЫВАНИЕ (Action Resume)
    string GetLastAction()
    {
        return m_P_Profile.GetLastInterruptedAction()
    }
}
