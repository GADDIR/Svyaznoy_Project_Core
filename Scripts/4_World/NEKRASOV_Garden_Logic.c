/**
 * NEKRASOV_Garden_Logic.c
 * Логика оседлого выживания и агрокультуры.
 * СВЯЗЬ: Анна (1928) - Терпение, Алексей (1982) - Порядок.
 */

class NEKRASOV_Garden_Logic
{
    // 1. ПРОВЕРКА ПОЧВЫ (Интуиция 1928)
    static bool CAN_PLANT_HERE(PlayerBase player, vector position)
    {
        // Если фокус на Анне (1928) высок, Некрасов "чувствует" землю
        float weight1928 = player.GetMemoryFocus().GetWeight1928();
        
        if (weight1928 > 0.5) {
            // Бонус к шансу приживаемости семян
            return true;
        }
        return true; 
    }

    // 2. КУЛЬТУРА ТРУДА (Порядок 1982)
    static void ON_PLANT_SEED(PlayerBase player, ItemBase seed)
    {
        // Некрасов не просто бросает семя, он делает это по ГОСТу
        if (player.GetMemoryFocus().GetWeight1982() > 0.5)
        {
            // Мысль о том, что порядок в огороде — порядок в голове
            NEKRASOV_Mumble_Logic.Say("Земля уход любит. Будет хлеб — будет и песня.");
        }
    }

    // 3. ЭФФЕКТ РЕФЛЕКСИИ (Восстановление)
    static void APPLY_GARDEN_RELAXATION(PlayerBase player)
    {
        // Работа на земле снижает уровень стресса (Травма 2021 затихает)
        float stressReduction = 0.15;
        // Логика снижения дрожи рук или помех в сознании
        Print("[NEKRASOV_Garden] Работа с землей успокаивает разум.");
    }
}

