void SyncWithEngine(PlayerBase m_Maverick) {
    // 1. ЕДА И ВОДА (Индикаторы яблока и бутылки)
    float energy = m_Maverick.GetStatEnergy().Get();
    float water  = m_Maverick.GetStatWater().Get();

    // 2. КРОВЬ И ЗДОРОВЬЕ (Индикаторы капли и креста)
    // GetHealth("", "") берет общее ХП, а не конкретной части тела
    float health = m_Maverick.GetHealth("GlobalHealth", "Health");
    int bleedingZones = m_Maverick.GetBleedingManager().GetBleedingSourcesCount();

    // 3. БАКТЕРИИ И ОТРАВЛЕНИЕ (Индикатор бактерии)
    // Проверяем наличие активных модификаторов (Холера, Сальмонелла, Отравление)
    bool isSick = m_Maverick.GetModifiersManager().IsModifierActive(eModifiers.MDF_CHOLERA) || 
                  m_Maverick.GetModifiersManager().IsModifierActive(eModifiers.MDF_POISONING);
    bool hasDirtyHands = m_Maverick.HasBloodyHands();

    // 4. ТЕМПЕРАТУРА (Индикатор термометра)
    float temp = m_Maverick.GetStatTemperature().Get();

    // 5. СОН (Твой кастомный индикатор Zz или Стамина)
    float sleep = m_Maverick.GetStatSleep(); 
}

