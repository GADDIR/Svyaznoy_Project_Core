class Svyaznoy_Agro_Memory
{
    private static float m_LastCheckTime = 0;

    // --- 📊 СТРАТЕГИЯ: АЛЕКСЕЙ НИКОЛАЕВ (ЗОНИРОВАНИЕ) ---
    static string GetCropByPriority(float energy, array<string> inventory)
    {
        if (inventory.Count() == 0) return "";

        // 1. РЕЖИМ: СРОЧНО (Голод < 1000)
        // Помидоры: 2 цикла роста за время 1 тыквы. Быстро едим, быстро продаем.
        if (energy < 1000)
        {
            if (inventory.Contains("TomatoSeeds")) return "Tomato";
        }

        // 2. РЕЖИМ: ТЕРПИМО / ПОЛНОЕ НАСЫЩЕНИЕ (Энергия 1000 - 3000)
        // Кабачки и картошка для долгой сытости и заготовки на засушку.
        if (energy < 3000)
        {
            if (inventory.Contains("ZucchiniSeeds")) return "Zucchini";
            if (inventory.Contains("PotatoSeed"))    return "Potato";
        }

        // 3. КОММЕРЧЕСКИЙ РЕЖИМ (Сытость > 3000)
        // Только Тыква. Максимальный вес и цена у торговца.
        if (inventory.Contains("PumpkinSeeds")) return "Pumpkin";

        return "Tomato"; // Дефолтный "быстрый" режим
    }

    // --- ♻️ РЕЗЕРВ И ЗАГОТОВКА (ЗАХАРДКОЖЕНО) ---
    static string DecideAction(string cropClass, int seedCount)
    {
        // Если семян меньше 10 — Алексей режет овощ на семена (Резерв)
        if (seedCount < 10) return "CRAFT_SEEDS";
        
        // Если овощей много — засушка (для долгого хранения) или продажа
        return "PROCESS_OR_SELL";
    }

    // --- 🌧 ПОГОДНЫЙ МОДУЛЬ (Сохранен из V2) ---
    static bool ShouldWaitRain()
    {
        float overCast = GetGame().GetWeather().GetOvercast().GetActual();
        float rain = GetGame().GetWeather().GetRain().GetActual();
        return (overCast > 0.7 || rain > 0.1);
    }

    // --- 🛡 БЕЗОПАСНОСТЬ (РЕАЛЬНЫЙ ТАЙМЕР) ---
    static void Protocol_SoilPreparation()
    {
        float currentTime = GetGame().GetTime() * 0.001; 
        if (currentTime - m_LastCheckTime > 30.0)
        {
            Print("[СВЯЗНОЙ-АГРО] Алексей Николаев: Осмотр плантаций 360°. Безопасно.");
            m_LastCheckTime = currentTime;
            // Здесь срабатывает триггер на выход из анимации в логике NPC
        }
    }
}
