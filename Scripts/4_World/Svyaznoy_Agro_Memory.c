/*
    AGRO MEMORY: NEKRASOV_FARMER_LOGIC_V2_RAIN
    INDEX: PRT-MEM-700 / 700.WEATHER
    STATUS: UPDATED (Rain-Logic Integrated)
    DIRECTIVE: Лопата > Пушка (Экономический базис)
*/

class Svyaznoy_Agro_Memory
{
    // --- 🌧️ ЛОГИКА ЕСТЕСТВЕННОГО ОРОШЕНИЯ (WEATHER_ADAPT) ---
    
    // АН анализирует небо: если облачность > 70% или уже идет дождь — полив не требуется.
    static bool ShouldWaitRain()
    {
        float overCast = GetGame().GetWeather().GetOvercast().GetActual();
        float rain = GetGame().GetWeather().GetRain().GetActual();

        if (overCast > 0.7 || rain > 0.1)
        {
            return true; // Небо напоит землю само. Экономим силы и скрытность.
        }
        return false;
    }

    // Протокол "Дикое Фермерство"
    static void Protocol_WildFarming()
    {
        // Директива: Закладка грядок в любой точке при прогнозе осадков.
        // Экономит ресурс [100.1 Гидратация] и позволяет не привязываться к источникам воды.
        if (ShouldWaitRain())
        {
            Print("[AGRO-700.W] Небо в тучах/идет дождь. Закладка скрытных грядок без привязки к воде.");
        }
    }

    // --- 🎃 СЕЛЕКЦИЯ И ПРИОРИТЕТЫ ---
    static string GetMainCrop() { return "Pumpkin"; } // Тыква - золото фермера (вес/калории/цена)

    static void Protocol_SoilPreparation()
    {
        // Логика: Разметка грядок внутри Приюта или в "зеленке".
        // Безопасность: Каждые 30 секунд разрыв анимации (Осмотр 360).
        Print("[AGRO-700.11] Подготовка почвы. Приоритет - скрытность посадки.");
    }

    // --- 💧 ГИДРАТАЦИЯ ПОЧВЫ ---
    static void Protocol_Watering()
    {
        // Если дождя нет — ручной полив. 
        // Память: "Сухая земля - пустой кошелёк".
        if (!ShouldWaitRain())
        {
            Print("[AGRO-700.12] Полив культур вручную. Дождя не предвидится.");
        }
    }

    // --- 🧺 СБОР И ЛОГИСТИКА (TIER-UP СТРАТЕГИЯ) ---
    static void Protocol_Harvesting()
    {
        // Сбор урожая. Реализация через Quinn для накопления на прицелы/глушители.
        Print("[AGRO-700.13] Урожай собран. Конвертация кабачков в Tier-UP оборудование.");
    }
}
