class NEKRASOV_Actions {
    protected PlayerBase m_Agent;

    void NEKRASOV_Actions(PlayerBase agent) {
        m_Agent = agent;
    }

    // Метод: Поднять предмет
    void LootItem(EntityAI item) {
        if (m_Agent.CanTakeEntityToInventory(item)) {
            m_Agent.TakeEntityToInventory(item);
            Print("NEKRASOV AI: Маверик подобрал " + item.GetDisplayName());
        }
    }

    // Метод: Использовать предмет (например, съесть)
    void Consume(EntityAI item) {
        // Логика использования еды/воды
    }
}

