// БЛОК №35: АДВЕНТИЗМ И ПИЩЕВОЙ КОДЕКС (УСТАВ ЧИСТОГО СИГНАЛА)
class NEKRASOV_Food_Taboo
{
    // МЕТОД ПРОВЕРКИ ПИЩИ
    static bool IsPure(EntityAI item)
    {
        string cls = item.ClassName()
        
        // Запрет на свинину (Механика Taboo Logic)
        if (cls == "Food_MeatPig" || cls == "Food_FatPig" || cls == "Food_BaconCan")
            return false
        
        // Трезвость (Алкоголь — только для ран)
        if (item.IsInherited(ItemBase) && cls.Contains("Vodka"))
            return false
            
        return true
    }

    // МОРАЛЬНЫЙ СУББОТНИЙ ПОКОЙ (Sabbath)
    static float GetActivityMultiplier()
    {
        // Проверка дня недели через системное время сервера
        int year, month, day, dayOfWeek
        GetYearMonthDay(year, month, day)
        dayOfWeek = GetDayOfWeek(year, month, day) // 6 = Суббота

        if (dayOfWeek == 6)
            return 0.3 // Снижение интенсивности работ на 70%
            
        return 1.0
    }

    // РЕАКЦИЯ В MUMBLE
    static string GetTabooMumble(EntityAI item)
    {
        if (item.ClassName().Contains("Pig"))
            return "Дед Николай свинины в дом не вносил, и я не стану. Отойди, нечистое."
        
        if (item.ClassName().Contains("Vodka"))
            return "Ясность ума — оружие связиста. А это — яд."
            
        return ""
    }
}
