// NEKRASOV_LIFESTYLE_MODULE.C — БЫТОВОЙ УЗЕЛ (ГИГИЕНА И АГРОНОМИЯ)
// Интеграция: Блок №30 (Анна), Блок №31 (Николай), Блок №35 (Адвентизм)

class Nekrasov_Lifestyle_Module
{
    // ГЛАВНЫЙ ЦИКЛ ЖИЗНЕОБЕСПЕЧЕНИЯ
    static void OnLifestyleUpdate(PlayerBase player, float hour)
    {
        // 1. ГИГИЕНИЧЕСКИЙ ТЕРРОР (Анна Петровна - Блок №30)
        if (player.GetStatDirtyHands().Get() > 0 || player.HasBloodyHands())
            ExecuteHygieneProtocol(player)

        // 2. ДЕДОВСКИЙ ПРОМЫСЕЛ (Николай - Блок №31)
        // Рыбалка в сумерках (18:00 - 06:00)
        if (hour >= 18.0 || hour <= 6.0)
            if (player.IsNearWater())
                ApplyFishingBonus(player)

        // 3. АГРОНОМИЯ (Гатчинские огороды - Блок №6)
        if (player.IsAtGarden())
            MaintainGardenDiscipline(player)
    }

    // ЛОГИКА СТЕРИЛЬНОСТИ
    private static void ExecuteHygieneProtocol(PlayerBase player)
    {
        // Блокировка приема пищи и крафта до умывания
        player.BlockAction("ActionEat")
        player.BlockAction("ActionCraft")
        
        if (player.IsIdle())
            Nekrasov_Mumble_Logic.Say(player, "Грязь — союзник смерти. Сначала мойся.")
    }

    // ГАТЧИНСКИЕ ГРЯДКИ (Порядок и расчет)
    private static void MaintainGardenDiscipline(PlayerBase player)
    {
        // Приоритет овощей (Адвентизм - Блок №35)
        // Скорость ухода +30% из Блока №6
        float skill = Nekrasov_Genesis_Registry.Get(6)
        
        if (player.IsPlanting())
            player.SetPlantingPrecision(1.0) // Грядки "по линейке"
            player.SetActionSpeedMultiplier(1.3 * skill)
    }

    // ПИЩЕВОЙ ФИЛЬТР (Синхронизация с Уставом Чистого Сигнала)
    static bool CanEatThis(PlayerBase player, EntityAI food)
    {
        // Блок №35: Свинина — табу
        if (food.ClassName().Contains("Pig") || food.ClassName().Contains("Bacon"))
            Nekrasov_Mumble_Logic.Say(player, "Дед свинины в дом не вносил, и я не стану.")
            return false

        return true
    }
}
