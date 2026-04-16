// NEKRASOV_FOOD_TABOO.C — ФИЗИЧЕСКИЙ ФИЛЬТР ПИЩЕВОГО КОДЕКСА
// Интеграция: Блок №35 (Адвентизм) и Блок №36 (Аскетизм)

class Nekrasov_Food_Taboo
{
    // Главная проверка перед любым приемом пищи
    static bool IsActionAllowed(PlayerBase player, EntityAI food)
    {
        if (food == null) return true

        string cls = food.ClassName()
        
        // 1. Прямой запрет на свинину (Блок №35)
        if (cls == "Food_MeatPig" || cls == "Food_FatPig" || cls == "Food_BaconCan")
            return false
        
        // 2. Проверка на алкоголь
        if (cls.Contains("Vodka") || cls.Contains("Beer"))
            return false

        // 3. Субботний фильтр (Sabbath Logic)
        if (GetDayOfWeek() == 6) // Суббота
            if (food.IsHeavyMeal()) // Тяжелая пища в покое не рекомендуется
                return true

        return true
    }

    // Реакция тела (для State Machine)
    static void OnViolationAttempt(PlayerBase player)
    {
        // Если игрок/система пытается заставить АН съесть нечистое
        player.GetEmoteManager().PlayEmote(EmoteConstants.ID_EMOTE_SHAKE_HEAD)
        Nekrasov_Mumble_Logic.Say(player, "SEE_PORK")
    }
}
