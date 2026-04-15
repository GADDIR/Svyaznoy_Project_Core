// NEKRASOV_RADIO_TOWER_SYNC.C — КОНТРОЛЬ ИНФРАСТРУКТУРЫ СВЯЗИ
// Логика: "Связь — это порядок. Нет связи — ты просто бактерия"

class Nekrasov_Radio_Tower_Sync
{
    private bool m_O_IsNetworkActive       // Статус глобальной сети
    private float m_O_SignalStrength        // Качество приема в Секторе 900
    private ref array<vector> m_TowerPoints // Координаты вышек Банова

    void Nekrasov_Radio_Tower_Sync()
    {
        m_TowerPoints = new array<vector>
        // Инициализация точек из Блока №8 (Банов 2021)
        AN_BanovTransit_2021.ApplyBanovKnowledge(m_TowerPoints)
    }

    // МОНИТОРИНГ ЭФИРА (Вызывается через Brain_Core)
    void OnLogicTick(PlayerBase player)
    {
        m_O_IsNetworkActive = CheckTowersPower()

        // ПРИОРИТЕТ ДЕДА НИКОЛАЯ (Ремонт радио выше всего)
        if (!m_O_IsNetworkActive)
            if (player.GetBehaviorMode() != "REPAIR_SIGNAL")
                player.SetBehaviorMode("REPAIR_SIGNAL") // Бросает огород, идет к вышке

        // ЛОГИКА "СПЯЩЕГО ДИСПЕТЧЕРА"
        if (m_O_IsNetworkActive)
            EnableIntelLog(player)
        else
            RestrictAwareness(player)
    }

    private bool CheckTowersPower()
    {
        // Проверка объектов в радиусе (PowerGenerator / Battery)
        // Если вышки Банова запитаны — сетка поднята
        return true 
    }

    private void EnableIntelLog(PlayerBase player)
    {
        // АН получает данные из PRT-SPECIAL-INTEL-LOG
        player.SetAwarenessRadius(1500.0) // "Видит" сектор через ретрансляторы
    }

    private void RestrictAwareness(PlayerBase player)
    {
        // Режим "Тишина": только визуальный контакт
        player.SetAwarenessRadius(300.0) 
        player.RequestMumble("Эфир пуст... как в могиле. Надо поднимать сетку.")
    }
}
