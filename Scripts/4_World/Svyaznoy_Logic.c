/* 
    CORE LOGIC: MAVERICK_BRAIN
    STATUS: INTEGRATED [PRT-CODE-500 / PRT-SAFE-600]
*/

class Svyaznoy_Logic
{
    PlayerBase m_Player;

    void Svyaznoy_Logic(PlayerBase player) { m_Player = player; }

    // [PRT-CODE-500] Сканер угроз (ПСЛ)
    float GetNearestThreatDist()
    {
        // Базовая заглушка: в будущем здесь Raycast
        return 1000.0; 
    }

    // [PRT-CODE-500] Управление рацией
    void SetRadioState(bool state)
    {
        if (m_Player) Print("[СВЯЗНОЙ]: Статус ЗАС изменен на: " + state.ToString());
    }

    // [PRT-SAFE-600] Сейф-зона
    void ActivateSafeZoneProtocol()
    {
        if (m_Player) {
            m_Player.SetTargetGoal("TRADE_AGRO");
            Print("[СВЯЗНОЙ]: Протокол СЗ активен. Поиск семян.");
        }
    }

    void Update(float timeslice, int mode)
    {
        // Здесь обрабатываются режимы STATIC, TRANSIT, SILENCE, REFLEX
    }

    // Проверка агро-инвентаря
    bool HasFarmingEquipment()
    {
        return m_Player.GetInventory().FindAttachment(InventorySlots.GetSlotIdFromString("Shoulder")) != null; // Упрощенная проверка
    }
}

