/*
    COMBAT REFLEX:NEKRASOV_TACTICAL_INTEGRATED
    INDEX: PRT-MEM-400 / 401.1
    DIRECTIVE: Выживание 0.9 (Жизнь > Хабара)
    ОПИСАНИЕ: Слияние алгоритмов "Призрак" и "Контр-снайпер".
*/

class  NEKRASOV_Combat_Reflex
{
    // --- 🎯 ДИСТАНЦИОННЫЕ ЭШЕЛОНЫ ---
    static float GetOptimalDist() { return 150.0; } // Лимит уверенного контроля ПСО-1

    // --- 🎯 АЛГОРИТМ «РЕАКЦИЯ-X» (КОНТР-СНАЙПЕР) ---
    static void OnUnderFire(PlayerBase player)
    {
        Print("[COMBAT-400.3] РЕАКЦИЯ-X: Обстрел! Уход с линии огня. Зигзаг.");
        
        // 1. Мгновенный разрыв дистанции
        player.GetInputController().OverrideMovementSpeed(true, 2.0); // Спринт
        player.GetInputController().OverrideMovementAngle(true, Math.RandomFloat(-0.5, 0.5)); // Хаотичный зигзаг
        
        // 2. Поиск жесткого укрытия (Hard Cover) через Knowledge_Base
    }

    // --- 👤 РЕЖИМ «ТЕНЬ» И ОЦЕНКА (STEALTH) ---
    static bool EvaluateEngagement(PlayerBase player, Object target)
    {
        float dist = vector.Distance(player.GetPosition(), target.GetPosition());

        // Если цель дальше оптимальной дистанции и мы не обнаружены — ОГОНЬ ЗАПРЕЩЕН
        if (dist > GetOptimalDist())
        {
            Print("[COMBAT-401.1] Режим Тень: Дистанция " + dist + "м. Наблюдение без демаскировки.");
            return false; 
        }
        return true;
    }

    // --- 🔪 ПРОТОКОЛ «ТИХАЯ ЛИКВИДАЦИЯ» (SILENT KILL) ---
    static void Protocol_SilentKill(PlayerBase player, EntityAI target)
    {
        // Работа ножом по Z или одиночной цели. Экономия патронов.
        if (target.IsAlive())
        {
            Print("[COMBAT-402.2] Дозвуковой догмат. Выполняю контроль ножом.");
        }
    }

    // --- 🛡️ ОБОРОНА ПРИЮТА (PRIYUT DEFENSE) ---
    static void Protocol_PriyutDefense()
    {
        // Ротация по сетке 8 огневых точек (SniperPosts).
        // АН использует знание слепых пятен периметра.
        Print("[COMBAT-403.4] Оборона Оплота. Занимаю секторную вышку.");
    }
}
