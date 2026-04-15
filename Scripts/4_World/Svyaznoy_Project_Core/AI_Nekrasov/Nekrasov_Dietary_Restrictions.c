// NEKRASOV_DIETARY_RESTRICTIONS.C — ПРАГМАТИЧНЫЙ АСКЕТИЗМ (ТАЙНОЕ КРЕДО)
// Интеграция: Блок №35 (Адвентизм) и Блок №36 (Ложная нормальность)

class Nekrasov_Dietary_Restrictions
{
    // 1. ПИЩЕВОЙ ЗАПРЕТ (Личное табу)
    static bool IsActionAllowed(PlayerBase player, EntityAI item)
    {
        string cls = item.ClassName()
        
        // Категорический отказ от употребления "нечистого" (Блок №35)
        if (cls == "Food_MeatPig" || cls == "Food_FatPig" || cls == "Food_BaconCan")
            return false
        
        // Запрет на алкоголь (Ясность ума - Блок №35)
        if (cls.Contains("Vodka") || cls.Contains("Beer"))
            return false
            
        return true
    }

    // 2. ЛОГИКА СКРЫТНОСТИ (Ложная нормальность - Блок №36)
    static string GetPublicExcuse(string itemType)
    {
        // Некрасов не говорит о вере чужакам, он находит прагматичный предлог
        if (itemType == "PORK")
            return "Не хочется чего-то... Изжога замучает. Отдам Quinn, ей нужнее."

        if (itemType == "ALCOHOL")
            return "Ясность ума — оружие связиста. Оставь себе, мне лишний шум в голове не нужен."
            
        return "Не сейчас."
    }

    // 3. ПРИОРИТЕТ РЕСУРСА (Охота разрешена - Блок №36)
    static bool ShouldProcessCarcass(string animalType)
    {
        // Он убивает свиней, потому что это ресурс (Дед Николай учил: "Все в дело")
        if (animalType == "Animal_WildBoar")
            return true
            
        return true
    }
}
