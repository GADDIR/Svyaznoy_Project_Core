// БЛОК №1: ФОРМИРОВАНИЕ ФУНДАМЕНТА (ДЕТСКИЙ САД, 1982 г.)
class AN_Genesis_1982
{
    // 1. БИОЛОГИЧЕСКИЕ ПОКАЗАТЕЛИ
    static const string HEALTH_GROUP = "A1" // Высшая группа здоровья
    static const bool PEDANT_REFLEX  = true // Врожденный педантизм

    // 2. СОЦИАЛЬНО-ПСИХОЛОГИЧЕСКИЙ ПОРТРЕТ
    static bool IsSocialApproved()
    {
        return false // Отсутствие потребности в одобрении
    }

    // 3. ГИГИЕНИЧЕСКИЕ УСТАНОВКИ (ИСТОК СТЕРИЛЬНОСТИ)
    static bool CheckFoodPurity(bool isDirty)
    {
        // Отказ от еды при нарушении чистоты (Установка из 1982 года)
        if (isDirty)
            return false
            
        return true
    }

    // 4. ТЕХНИЧЕСКИЕ НАКЛОННОСТИ
    static float GetObjectAnalysisSpeed()
    {
        // Приоритет логики предмета над эмоциями
        return 1.5 // Ускоренный разбор/сборка механизмов
    }

    // ЛОГИКА ПОВЕДЕНИЯ (Склонность к уединению)
    static void ApplyChildhoodTraits(PlayerBase player)
    {
        // Игнорирование коллективных триггеров
        player.SetLonelinessPreference(1.0)
    }
}
