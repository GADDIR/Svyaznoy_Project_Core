/*
    МОДУЛЬ: NEKRASOV_Base_Defense
    ВЕРСИЯ: 1.2 [FIRE_NETWORK_V2_INTEGRATED]
    ОПИСАНИЕ: Круговая оборона Приюта. Сеть из 8 огневых точек и логика ротации.
*/

class  NEKRASOV_Base_Defense
{
    // --- 🚨 СОСТОЯНИЯ ГОТОВНОСТИ ---
    static int STATE_PEACE = 0;   // Сейф-зона активна (Режим: Фермер)
    static int STATE_WARNED = 1;  // Защита OFF (Режим: Часовой)
    static int STATE_ASSAULT = 2; // Прямая атака (Режим: Огневая точка)

    private int m_CurrentState = 0;
    private int m_CurrentPointIndex = 0;
    private ref array<vector> m_DefensePositions;

    void Svyaznoy_Base_Defense()
    {
        m_DefensePositions = new array<vector>;
        GetFullDefenseGrid(m_DefensePositions);
    }

    // --- 📍 ЦЕНТР УПРАВЛЕНИЯ ---
    static vector GetPriyutCenter() { return "308.4 283.2 260.4"; }

    // --- 🏰 ОГНЕВОЙ ПЕРИМЕТР (8 ВЫШЕК EXPANSION) ---
    static void GetFullDefenseGrid(out array<vector> firePoints)
    {
        firePoints.Clear();
        firePoints.Insert("308.4 288.2 260.4"); // Пост №1: Главные ворота
        firePoints.Insert("315.2 288.2 265.1"); // Пост №2: Восточный выступ
        firePoints.Insert("300.1 288.2 258.4"); // Пост №3: Западная стена
        firePoints.Insert("290.5 288.2 255.0"); // Пост №4: Глубокий лес
        firePoints.Insert("320.0 288.2 270.0"); // Пост №5: Высокий край
        firePoints.Insert("310.0 295.0 262.0"); // Пост №6: ГЛАВНАЯ ВЫШКА (Связь)
        firePoints.Insert("305.0 288.2 250.0"); // Пост №7: Тыловая охрана
        firePoints.Insert("318.0 288.2 260.0"); // Пост №8: Доп. контроль севера
    }

    // --- ⚙️ УПРАВЛЕНИЕ РЕЖИМАМИ ---
    void SetBaseState(int newState, PlayerBase player)
    {
        m_CurrentState = newState;
        
        switch (m_CurrentState)
        {
            case STATE_PEACE:
                Print("[СВЯЗНОЙ] Статус: БЕЗОПАСНО. Работа в Agro-Hub.");
                break;
            case STATE_WARNED:
                Print("[СВЯЗНОЙ] СЗ ОТКЛЮЧЕНА. Переход в скрытность.");
                break;
            case STATE_ASSAULT:
                Print("[СВЯЗНОЙ] ОСАДА! Занимаю сектор...");
                CycleDefensePoints(player);
                break;
        }
    }

    // --- 🔄 АЛГОРИТМ «СМЕНА СЕКТОРА» ---
    void CycleDefensePoints(PlayerBase player)
    {
        if (m_DefensePositions.Count() == 0) return;

        // Выбор следующей точки для исключения предсказуемости
        m_CurrentPointIndex = (m_CurrentPointIndex + 1) % m_DefensePositions.Count();
        vector targetPoint = m_DefensePositions.Get(m_CurrentPointIndex);
        
        Print("[СВЯЗНОЙ] Динамическая оборона: Смена позиции на Пост №" + (m_CurrentPointIndex + 1));
        
        // Команда на перемещение (скорость 1.5 - тактический бег)
        player.GetInputController().OverrideMovementSpeed(true, 1.5);
    }

    // --- 🛡️ ПРОТОКОЛ «ПОСЛЕДНЯЯ СТЕНА» ---
    void CheckPerimeterBreach(PlayerBase self, vector enemyPos)
    {
        if (vector.Distance(self.GetPosition(), enemyPos) < 10.0)
        {
            Print("[СВЯЗНОЙ] Периметр прорван! Активация Протокола Жертвы.");
            // Вызов из  NEKRASOV_Logic модуля Sacrifice
        }
    }
}
