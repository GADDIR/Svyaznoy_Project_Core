// ПРОТОКОЛ №9: РЕЕСТР РЕСУРСНОЙ ЛОЯЛЬНОСТИ (UTILITY INTAKE)
class AN_ResourceLoyalty
{
    // ID Игрока -> Накопленная ценность (Score)
    private ref map<string, float> m_LoyaltyRegistry
    private float m_Nekrasov_ResourceDependence // Уровень зависимости

    void AN_ResourceLoyalty()
    {
        m_LoyaltyRegistry = new map<string, float>
    }

    // ЛОГИКА ПРИЕМА ДАРОВ (Utility Math)
    void RegisterGift(PlayerBase giver, EntityAI item)
    {
        string id = giver.GetIdentity().GetId()
        float currentVal = GetPlayerValue(id)
        float itemWeight = CalculateWeight(item)

        // Защита от "пустого" подкупа (Гниль/Мусор)
        if (item.IsRuined())
            currentVal -= 10.0
        else
            currentVal += itemWeight

        m_LoyaltyRegistry.Set(id, currentVal)

        // Порог "Вечного друга" (500 очков)
        if (currentVal >= 500.0)
            ApplyPermanentStatus(id)
    }

    // ЛОГИКА ОТДАЧИ (Только при угрозе потери поставщика)
    bool CanGiveAid(PlayerBase receiver)
    {
        string id = receiver.GetIdentity().GetId()
        
        // Если ветеран при смерти и он ценен (Value > 400)
        if (receiver.IsCriticallyWounded() && GetPlayerValue(id) > 400.0)
            return true
            
        return false // В остальных случаях Некрасов не делится
    }

    // СИСТЕМА ДЕГРАДАЦИИ (Если кормушка пуста)
    void UpdateStagnation(string id, int daysPassed)
    {
        if (daysPassed > 7)
        {
            float newVal = GetPlayerValue(id) * 0.8
            m_LoyaltyRegistry.Set(id, newVal)
        }
    }

    private float CalculateWeight(EntityAI item)
    {
        if (item.IsInherited(Ammunition_Base)) return 15.0
        if (item.IsInherited(FoodBase)) return 5.0
        if (item.IsInherited(WeaponCleaningKit)) return 20.0
        return 1.0
    }

    private float GetPlayerValue(string id)
    {
        if (m_LoyaltyRegistry.Contains(id))
            return m_LoyaltyRegistry.Get(id)
        return 0.0
    }

    private void ApplyPermanentStatus(string id) { /* Статус Вечного Друга */ }
}
