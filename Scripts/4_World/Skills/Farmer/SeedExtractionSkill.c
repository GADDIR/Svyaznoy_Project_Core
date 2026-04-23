class SeedExtractionSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Нужны семена для следующей посадки
        if (NeedsSeeds(bot))
        {
            ExtractSeedsFromCrops(bot);
        }
    }

    private void ExtractSeedsFromCrops(ExpansionAIBase bot)
    {
        // Ищем нож
        ItemBase knife = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Knife_Base"));
        if (!knife) return;

        // Ищем овощ (Томат, Кабачок, Тыква, Перец)
        // Бот может добыть семена даже из подпорченных (Damaged) овощей
        Edible_Base crop = FindSuitableCrop(bot);
        
        if (crop && knife)
        {
            bot.TakeItemToHands(knife);
            // Действие: Разрезать овощ для получения семян
            bot.StartAction(ActionPrepareSeeds); 
            Print("[AN_NEKRASOV_82] Добываю семена из собственного урожая для следующего цикла.");
        }
    }

    private bool NeedsSeeds(ExpansionAIBase bot)
    {
        // Если в рюкзаке осталось меньше 2-х пачек семян любого типа
        return bot.GetInventory().CountItemsWithPrefix("SeedsPack") < 2;
    }

    private Edible_Base FindSuitableCrop(ExpansionAIBase bot)
    {
        string[] seedSources = {"Tomato", "Zucchini", "Pumpkin", "GreenBellPepper"};
        foreach (string s : seedSources)
        {
            Edible_Base item = Edible_Base.Cast(bot.GetInventory().FindEntityInInventory(s));
            if (item && !item.IsRuined()) return item;
        }
        return null;
    }
}

