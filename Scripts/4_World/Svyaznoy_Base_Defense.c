/*
    МОДУЛЬ: Svyaznoy_Base_Defense
    ОПИСАНИЕ: Логика охраны Приюта и использования огневых точек (вышек).
*/

class Svyaznoy_Base_Defense
{
    // Состояния готовности
    static int STATE_PEACE = 0;   // СЗ активна - режим "Фермер"
    static int STATE_WARNED = 1;  // СЗ отключена - режим "Часовой"
    static int STATE_ASSAULT = 2; // Бой - режим "Огневая точка"

    private int m_CurrentState = 0;

    // Координаты базы (Центр Приюта)
    static vector GetPriyutCenter() { return "308.4 283.2 260.4"; }

    // Огневые точки (Охотничьи вышки из Эдитора)
    // Вставь сюда точные координаты своих вышек, если они отличаются
    static vector GetFirePoint_1() { return "310.5 288.0 265.0"; } 
    static vector GetFirePoint_2() { return "300.0 288.0 258.0"; }

    // Метод переключения режима (вызывать при изменении статуса Сейф-зоны)
    void SetBaseState(int newState)
    {
        m_CurrentState = newState;
        
        if (m_CurrentState == STATE_WARNED) {
            Print("[СВЯЗНОЙ] Внимание: СЗ отключена. Ухожу с открытого неба.");
        }
        if (m_CurrentState == STATE_ASSAULT) {
            Print("[СВЯЗНОЙ] Осада! Занимаю огневую точку.");
            GoToFirePoint();
        }
    }

    // Логика занятия вышки
    void GoToFirePoint()
    {
        // АН выбирает ближайшую вышку как огневую позицию
        vector targetPoint = GetFirePoint_1(); 
        // Здесь будет команда на перемещение (Pathfinding)
        Print("[СВЯЗНОЙ] Двигаюсь к позиции: " + targetPoint.ToString());
    }
}
