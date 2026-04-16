/*
    АГРО-ПАМЯТЬ: АЛЕКСЕЙ НИКОЛАЕВИЧ (СВЯЗНОЙ)
    ИНДЕКС: PRT-AGRO-2024-V6-FINAL-INTEGRATED
    ОПИСАНИЕ: База данных узлов, логика скрытого фермерства и селекция урожая.
*/

class NEKRASOV_Agro_Memory
{
    private ref array<vector> m_GardenPoints;
    private bool m_IsCompromised = false;
    private static float m_LastCheckTime = 0;

    void  NEKRASOV_Agro_Memory()
    {
        m_GardenPoints = new array<vector>;
    }

    // --- 🌽 РЕЕСТР И ЛИМИТЫ (ПО ПАМЯТИ) ---
    void RegisterGarden(vector position)
    {
        if (m_GardenPoints.Find(position) == -1 && CanCreatePlot(m_GardenPoints.Count()))
        {
            m_GardenPoints.Insert(position);
            Print("[СВЯЗНОЙ-АГРО]: Новая точка зафиксирована: " + position.ToString());
        }
    }

    static bool CanCreatePlot(int activePlots)
    {
        return (activePlots < 3); // Строгий лимит — 3 огорода
    }

    // --- 🚜 ВЫБОР КУЛЬТУРЫ (БАЗА ЗНАНИЙ) ---
    static string GetPlantingChoice(int slotIndex, float energyLevel, array<string> seeds)
    {
        if (seeds.Count() == 0) return "";

        // ФАЗА 1: Выживание (Голод)
        if (energyLevel < 2000)
        {
            if (seeds.Contains("ZucchiniSeeds")) return "Zucchini";
            if (seeds.Contains("TomatoSeeds"))   return "Tomato";
        }

        // ФАЗА 2: Бизнес (Pumpkin — валюта)
        int type = slotIndex % 3;
        if (type == 0 && seeds.Contains("PumpkinSeeds")) return "Pumpkin";
        return seeds.Get(0);
    }

    // --- 💰 ЛОГИСТИКА УРОЖАЯ ---
    static string DecideHarvestFate(float energyLevel)
    {
        if (energyLevel < 2500) return "TO_KITCHEN_CAMP"; 
        return "TO_TRADE_QUINN";
    }

    // --- 🛡 БЕЗОПАСНОСТЬ И КОНТРОЛЬ (РАЗУМЕНИЕ) ---
    void CheckSecurity(PlayerBase self)
    {
        float currentTime = GetGame().GetTime() * 0.001;
        
        // Тактический разрыв: проверка каждые 30 секунд
        if (currentTime - m_LastCheckTime > 30.0)
        {
            m_LastCheckTime = currentTime;
            array<Man> players = new array<Man>;
            GetGame().GetPlayers(players);

            foreach (Man target : players)
            {
                if (target == self) continue;
                if (vector.Distance(self.GetPosition(), target.GetPosition()) < 50.0)
                {
                    m_IsCompromised = true;
                    Print("[СВЯЗНОЙ-АГРО]: Обнаружена бактерия! Плантация скомпрометирована.");
                }
            }
        }
    }

    bool NeedsWater()
    {
        return (GetGame().GetWeather().GetRain().GetActual() < 0.1);
    }
}
