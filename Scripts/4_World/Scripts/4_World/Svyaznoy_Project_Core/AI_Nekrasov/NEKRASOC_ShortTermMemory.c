// ПРОТОКОЛ №2: РЕЕСТР КОРОТКОЙ ПАМЯТИ (SESSION CACHE)
class NEKRASOC_ShortTermMemory
{
    private ref map<string, vector> m_TaskPositions; // Координаты объектов
    private ref map<string, float>  m_TaskTimers;    // TTL (Время жизни)
    private string m_LastInterruptedAction;          // Принцип "Незавершенного дела"

    void NEKRASOV_ShortTermMemory()
    {
        m_TaskPositions = new map<string, vector>
        m_TaskTimers = new map<string, float>
    }

    // Фиксация задачи (Бытовой фокус, Лут, Одежда)
    void PinTask(string taskName, vector pos, float ttl)
    {
        m_TaskPositions.Set(taskName, pos)
        m_TaskTimers.Set(taskName, ttl)
    }

    // ЛОГИКА ОБРАБОТКИ (Вызывается каждый тик)
    void Tick(float timeslice, PlayerBase player)
    {
        vector currentPos = player.GetPosition()

        // ГЕО-ПРИВЯЗКА: Очистка при удалении > 500м
        if (vector.Distance(currentPos, GetAnchor()) > 500)
            ClearSession()

        for (int i = 0; i < m_TaskTimers.Count(); i++)
        {
            string key = m_TaskTimers.GetKey(i)
            float timeLeft = m_TaskTimers.Get(key) - timeslice
            
            // Если срок истек (Мясо сгорело / Косуля ушла)
            if (timeLeft <= 0)
            {
                // Взаимодействие с Mumble (Ворчание)
                player.SayMumble("Эх, память дырявая, проглядел " + key)
                UnpinTask(key)
            }
            else
            {
                m_TaskTimers.Set(key, timeLeft)
            }
        }
    }

    // ACTION RESUME: Что я делал до того, как начали стрелять?
    void SetInterruptedAction(string action)
    {
        m_LastInterruptedAction = action
    }

    string GetResumeAction()
    {
        return m_LastInterruptedAction
    }

    private void UnpinTask(string name)
    {
        m_TaskPositions.Remove(name)
        m_TaskTimers.Remove(name)
    }

    private void ClearSession()
    {
        m_TaskPositions.Clear()
        m_TaskTimers.Clear()
        m_LastInterruptedAction = ""
    }

    private vector GetAnchor() { return "0 0 0"; } // Здесь будет привязка к базе
}
