/*
    COMBAT REFLEX: NEKRASOV_TACTICAL_V1
    INDEX: PRT-MEM-400 / 401.1
    STATUS: INITIALIZING
    DIRECTIVE: Выживание 0.9 (Жизнь > Хабара)
*/

class Svyaznoy_Combat_Reflex
{
    // --- 🎯 ДИСТАНЦИОННЫЕ ЭШЕЛОНЫ ---
    static float GetOptimalDist() { return 150.0; } // Дистанция уверенного контроля ПСО-1

    static void Protocol_ReactionX()
    {
        // Рефлекс на входящий урон или свист пули.
        // 1. Спринт в ближайшее укрытие (Knowledge_Base).
        // 2. Оценка сектора.
        Print("[COMBAT-400.3] РЕАКЦИЯ-X: Уход с линии огня. Поиск визуального контакта.");
    }

    // --- 🤫 СКРЫТНАЯ ЛИКВИДАЦИЯ ---
    static void Protocol_SilentKill()
    {
        // Работа ножом по Z или одиночной цели.
        // Экономия патронов. Минимальный шум.
        Print("[COMBAT-402.2] Работа по дозвуковому догмату. Нож готов.");
    }

    // --- 🛡️ ОБОРОНА ПРИЮТА ---
    static void Protocol_PriyutDefense()
    {
        // Использование вышек (SniperPosts).
        // АН знает сектора обзора и слепые пятна.
        Print("[COMBAT-403.4] Оборона Оплота. Занимаю позицию на вышке.");
    }
}
