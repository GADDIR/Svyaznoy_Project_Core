// ЗОЛОТОЙ СТАНДАРТ А.Н. НЕКРАСОВА (СИНТЕЗ БЛОКОВ №1 - №9)
class NEKRASOV_GoldenStandard
{
    // БЛОК №1 и №9: БИОЛОГИЧЕСКИЙ ГЕНЕЗИС (1982)
    static const string M_GEN_HEALTH_GROUP = "A1"
    static const float  M_GEN_STRESS_RESIST = 0.95 // Высокая стрессоустойчивость

    // БЛОК №2 и №3: ПСИХОЛОГИЧЕСКАЯ БАЗА (ШКОЛА/КОЛЛЕДЖ)
    static const bool   M_PSY_HYGIENE_TERROR = true // OCD на чистоту
    static const float  M_PSY_RADIO_SKILL    = 1.8  // Уровень радио-интуиции

    // БЛОК №4: ИНЖЕНЕРНЫЙ ФУНДАМЕНТ (УНИВЕРСИТЕТ)
    static const float  M_ENG_SYSTEM_VISION = 2.0  // Видит мир как схему
    static const bool   M_ENG_AUTONOMY_PRIO = true // Приоритет автономных систем

    // БЛОК №5 и №6: ТАКТИКА И ТРУД (АРМИЯ/РАБОТА)
    static const float  M_TAC_SVD_MASTERY = 1.0  // Снайперский рефлекс
    static const float  M_TAC_SCAN_360    = 1.5  // Дисциплина осмотра сектора
    static const bool   M_TAC_COLD_LOGIC  = true // Утилитарный подход к ресурсам

    // БЛОК №7 и №8: ИДЕНТИЧНОСТЬ (ГОС. ДОКУМЕНТЫ/БАНОВ 2021)
    static const string M_ID_REGISTRATION = "Гатчина"
    static const bool   M_ID_BANOV_EXPERT = true // Знание локальных вышек Банова

    // ГЛАВНЫЙ ФИЛЬТР ПРИНЯТИЯ РЕШЕНИЙ
    static bool RequestDecision(PlayerBase player, string action)
    {
        // Проверка через Биологический генезис (Блок 9)
        if (player.IsCriticallyIll())
            return false

        // Проверка через Гигиенический террор (Блок 1)
        if (M_PSY_HYGIENE_TERROR && player.GetStatDirtyHands().Get() > 0)
            if (action == "EAT" || action == "CRAFT")
                return false

        // Проверка через Боевой устав (Блок 5)
        if (player.IsUnderThreat() && action != "COMBAT")
            return false

        return true
    }
}
