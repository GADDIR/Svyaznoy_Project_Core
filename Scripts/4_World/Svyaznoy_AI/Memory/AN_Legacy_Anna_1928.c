// БЛОК №30: ГЕНЕЗИС — АННА ПЕТРОВНА (МАТЕРИНСКИЙ ЗАВЕТ)
class AN_Legacy_Anna_1928
{
    // 1. УЗЕЛ "МАМА-БАБУШКА" (Mumble Logic)
    static string GetHomeReflex(string context)
    {
        if (context == "COOKING")
            return "Мама Анна говорила: котел должен блестеть."
        
        if (context == "DIRTY_HANDS")
            return "Мама бы за такой беспорядок похвалила... розгами. Сначала мойся."

        if (context == "GARDENING")
            return "Земля — она тишину любит. Мама здесь душой отдыхала..."
            
        return ""
    }

    // 2. СОЦИАЛЬНЫЙ ФИЛЬТР (Фронтовой Триаж)
    static bool IsTargetWorthSaving(PlayerBase target)
    {
        // Не плачем над каждым. Спасаем только тех, кто вернется в строй.
        if (target.IsBallasCharacter() || target.GetUtilityValue() < 0.3)
            return false
            
        return true
    }

    // 3. ЭФФЕКТ УЗНАВАНИЯ (Снижение агрессии)
    static float GetAggressionModifier(PlayerBase target)
    {
        // Если видим хозяйственность (огород/готовка)
        if (target.IsPerformingAction("ActionFertilizeSlot") || target.IsPerformingAction("ActionCook"))
            return 0.5 // Снижение агрессии на 50%
            
        return 1.0
    }

    // ТЕХНИЧЕСКАЯ УСТАНОВКА (Чистота кода)
    static void ApplyPurityStandard(PlayerBase player)
    {
        // Переменная переименована согласно Регламенту №30
        player.m_Nekrasov_MotherFigure_Legacy = 1.0
    }
}
