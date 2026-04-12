/*
    МОДУЛЬ: Svyaznoy_Base_Defense
    ВЕРСИЯ: 1.2 [FIRE_NETWORK_V2]
    ОПИСАНИЕ: Круговая оборона Приюта. Сеть из 8 огневых точек Expansion.
*/

class Svyaznoy_Base_Defense
{
    // --- 🚨 СОСТОЯНИЯ ГОТОВНОСТИ ---
    static int STATE_PEACE = 0;   // Сейф-зона активна (Режим: Фермер)
    static int STATE_WARNED = 1;  // Защита OFF (Режим: Часовой)
    static int STATE_ASSAULT = 2; // Прямая атака (Режим: Огневая точка)

    private int m_CurrentState = 0;

    // --- 📍 ЦЕНТР УПРАВЛЕНИЯ ---
    static vector GetPriyutCenter() { return "308.4 283.2 260.4"; }

    // --- 🏰 ОГНЕВОЙ ПЕРИМЕТР (8 ВЫШЕК EXPANSION) ---
    static void GetFullDefenseGrid(out array<vector> firePoints)
    {
        firePoints.Clear();
        // Сектор СЕВЕР (Вход и дорога)
        firePoints.Insert("308.4 288.2 260.4"); // Пост №1: Главные ворота
        firePoints.Insert("318.0 288.2 260.0"); // Пост №8: Дополнительный контроль севера

        // Сектор ЗАПАД (Лесной массив)
        firePoints.Insert("300.1 288.2 258.4"); // Пост №3: Западная стена
        firePoints.Insert("290.5 288.2 255.0"); // Пост №4: Глубокий лес

        // Сектор ВОСТОК (Склон и подход снизу)
        firePoints.Insert("315.2 288.2 265.1"); // Пост №2: Восточный выступ
        firePoints.Insert("320.0 288.2 270.0"); // Пост №5: Высокий край

        // Сектор ЮГ (Тыл и забор)
        firePoints.Insert("305.0 288.2 250.0"); // Пост №7: Тыловая охрана

        // ЦЕНТРАЛЬНЫЙ УЗЕЛ
        firePoints.Insert("310.0 295.0 262.0"); // Пост №6: Главная вышка (Связь и Снайпер)
    }

    // --- ⚙️ УПРАВЛЕНИЕ РЕЖИМАМИ ---
    void SetBaseState(int newState)
    {
        m_CurrentState = newState;
        
        switch (m_CurrentState)
        {
            case STATE_PEACE:
                Print("[СВЯЗНОЙ] Статус: БЕЗОПАСНО. Возврат к регламенту 'Статика'.");
                break;
            case STATE_WARNED:
                Print("[СВЯЗНОЙ] Внимание: СЗ отключена. Занимаю скрытную позицию.");
                break;
            case STATE_ASSAULT:
                Print("[СВЯЗНОЙ] ОСАДА! Анализ секторов обстрела...");
                ChooseBestFirePoint();
                break;
        }
    }

    // --- 🏹 ТАКТИКА ВЫБОРА ТОЧКИ ---
    void ChooseBestFirePoint()
    {
        array<vector> points = new array<vector>;
        GetFullDefenseGrid(points);
        
        // Логика АН: Алексей выбирает вышку, которая ближе всего 
        // к предполагаемой угрозе, обеспечивая обзор через ПСО-1.
        vector targetPoint = points.Get(5); // По умолчанию - центральная вышка (Пост №6)
        
        Print("[СВЯЗНОЙ] Выбрана оптимальная огневая позиция: " + targetPoint.ToString());
        // Здесь вызывается метод перемещения к точке
    }
}
