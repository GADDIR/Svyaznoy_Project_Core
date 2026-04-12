/*
    АГРО-ПАМЯТЬ: АЛЕКСЕЙ НИКОЛАЕВИЧ (СВЯЗНОЙ)
    ИНДЕКС: PRT-AGRO-2024-V6-FINAL
    ОПИСАНИЕ: Профессиональное управление плантациями (лимит 3), селекция и маркировка урожая.
*/

class Svyaznoy_Agro_Memory
{
    private static float m_LastCheckTime = 0;
    
    // --- 🚜 ГЛАВНЫЙ АЛГОРИТМ ПОСАДКИ (СМЕШАННЫЙ ЦИКЛ) ---
    static string GetPlantingChoice(int slotIndex, float energyLevel, array<string> seeds)
    {
        if (seeds.Count() == 0) return "";

        // ФАЗА 1: "БИТВА ЗА КАЛОРИИ" (Энергия < 2000)
        if (energyLevel < 2000)
        {
            if (seeds.Contains("ZucchiniSeeds")) return "Zucchini";
            if (seeds.Contains("TomatoSeeds"))   return "Tomato";
        }

        // ФАЗА 2: "БИЗНЕС-ПЛАН" (Смешанный тип для реализма)
        int type = slotIndex % 3;
        if (type == 0 && seeds.Contains("PumpkinSeeds"))  return "Pumpkin";
        if (type == 1 && seeds.Contains("PotatoSeed"))    return "Potato";
        if (type == 2 && seeds.Contains("ZucchiniSeeds")) return "Zucchini";

        return seeds.Get(0);
    }

    // --- 💰 ЛОГИСТИКА УРОЖАЯ (МАРКИРОВКА) ---
    static string DecideHarvestFate(string cropClass, float energyLevel)
    {
        // Только решение о направлении: в Лагерь или на Рынок
        if (energyLevel < 2500) return "TO_KITCHEN_CAMP"; 
        return "TO_TRADE_QUINN";
    }

    // --- ♻️ СЕМЕННОЙ РЕЗЕРВ (СЕЛЕКЦИЯ) ---
    static bool ShouldHarvestForSeeds(string crop, int currentSeedStock)
    {
        // Алексей всегда держит фонд. Если семян вида < 10 — на разделку.
        return (currentSeedStock < 10);
    }

    // --- 🚜 ЛИМИТ ПЛАНТАЦИЙ (ЗАЩИТА СЕРВЕРА) ---
    static bool CanCreatePlot(int activePlots)
    {
        // Строго 2-3 огорода.
        return (activePlots < 3);
    }

    // --- 🛡 ТАКТИЧЕСКИЙ РАЗРЫВ (БЕЗОПАСНОСТЬ 360°) ---
    static void Protocol_FieldSecurity()
    {
        float currentTime = GetGame().GetTime() * 0.001; 
        if (currentTime - m_LastCheckTime > 30.0)
        {
            Print("[СВЯЗНОЙ-АГРО] А. Николаевич: Осмотр периметра плантации.");
            m_LastCheckTime = currentTime;
        }
    }
}
