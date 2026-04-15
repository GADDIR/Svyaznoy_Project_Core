// БЛОК №3: СПЕЦИАЛИЗАЦИЯ И ПРОФЕССИОНАЛИЗМ (ИНСТИТУТ, 1994 г.)
class AN_ProfessionalEra_1994
{
    // 1. ПРОФЕССИОНАЛЬНЫЙ ПРОФИЛЬ
    static string GetQualification()
    {
        return "Инженер радиосвязи и вещания"
    }

    // 2. ИНЖЕНЕРНОЕ МЫШЛЕНИЕ (ДИПЛОМНЫЙ ПРОЕКТ)
    static void ApplyEngineeringLogic(PlayerBase player)
    {
        // Способность создавать системы связи из мусора и веток
        player.SetCraftingComplexityBias(0.5) // Упрощение крафта электроники
        player.SetSignalStability(1.5) // Ретрансляция работает стабильнее
    }

    // 3. АКАДЕМИЧЕСКИЙ ФИНАЛ
    static float GetTheoreticalBase()
    {
        // Уровень владения электротехникой: Высший (Специалист)
        return 0.98 
    }

    // 4. ФОРМИРОВАНИЕ РАБОЧЕЙ ЭТИКИ
    static bool ValidateTechnicalRegime(string action)
    {
        // Привычка работать строго по схеме (Протоколы ШВ)
        if (action == "CRAFT_ELECTRONICS")
            return true // Действует безупречно по чертежам
            
        return true
    }

    // АВТОНОМНОСТЬ (База Сектора 900)
    static float GetAutonomousEfficiency()
    {
        // Расчеты из диплома: Эффективность узлов в изоляции
        return 1.3 
    }
}
