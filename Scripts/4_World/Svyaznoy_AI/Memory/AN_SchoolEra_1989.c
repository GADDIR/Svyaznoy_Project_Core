// БЛОК №2: ПЕРИОД СИСТЕМНОГО ОБУЧЕНИЯ (ШКОЛА, 1989 г.)
class AN_SchoolEra_1989
{
    // 1. АКАДЕМИЧЕСКИЙ ПРОФИЛЬ
    static float GetSubjectMastery(string subject)
    {
        if (subject == "PHYSICS" || subject == "MATH")
            return 0.95 // Приоритетные дисциплины
        
        if (subject == "LITERATURE")
            return 0.2 // Игнорируемые гуманитарные науки
            
        return 0.5
    }

    // 2. МЕДИЦИНСКИЙ СТАТУС (ЗРЕНИЕ ДЛЯ ПСО-1)
    static float GetVisionAcuity()
    {
        // Динамика по школьной медкарте: Зрение 1.0 (Стабильное)
        return 1.0 
    }

    // 3. ТЕХНИЧЕСКОЕ САМООПРЕДЕЛЕНИЕ (SCHOOL_RADIO_LOG)
    static void ApplyRadioSkills(PlayerBase player)
    {
        // Фиксация первых сеансов связи. Зарождение "Связного"
        player.SetRadioTuningSpeed(2.0) // Ускоренная настройка частоты
        player.SetSignalDetectionRange(1.2) // Бонус к поиску слабых сигналов
    }

    // 4. СОЦИАЛЬНАЯ ИНТЕГРАЦИЯ
    static string GetSchoolCharacteristic()
    {
        // Подтверждение затворничества из официальных документов
        return "Склонен к техническому творчеству. В общественной жизни пассивен."
    }

    // ЛОГИКА ДИСЦИПЛИНЫ
    static bool IsTaskPersistent()
    {
        // Динамика от поступления до выпуска: Рост усидчивости
        return true 
    }
}
