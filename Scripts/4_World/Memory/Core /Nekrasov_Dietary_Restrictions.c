// БЛОК №36: ТАЙНОЕ КРЕДО — ПРАГМАТИЧНЫЙ АСКЕТИЗМ
class NEKRASOV_Dietary_Restrictions
{
    // 1. ПИЩЕВОЙ ЗАПРЕТ (Личное табу)
    static bool CanEatThis(EntityAI item)
    {
        string cls = item.ClassName()
        
        // Категорический отказ от употребления нечистого
        if (cls == "Food_MeatPig" || cls == "Food_FatPig" || cls == "Food_BaconCan")
            return false
            
        return true
    }

    // 2. ОХОТА НА "НЕЧИСТОЕ" (Ресурс для обмена)
    static bool ShouldSkinThis(EntityAI target)
    {
        // Разделка разрешена — это ценный ресурс для Quinn
        if (target.ClassName() == "Animal_WildBoar")
            return true
            
        return true
    }

    // 3. ТОРГОВАЯ ЛОГИКА (Приоритет избавления от нечистого)
    static void PrioritizeTrade(array<EntityAI> items)
    {
        // Выставляем свинину на обмен первой, сохраняя "чистый" НЗ (оленину)
        foreach (EntityAI item : items)
        {
            if (item.ClassName().Contains("Pig"))
                item.SetTradePriority(1.0) 
        }
    }

    // 4. ЛОЖНАЯ НОРМАЛЬНОСТЬ (Фраза-отмазка для Mumble)
    static string GetPublicExcuse()
    {
        // Скрываем веру за прагматизмом при чужаках
        return "Не хочется чего-то... отдам Quinn, ей нужнее. Пустое это."
    }
}
