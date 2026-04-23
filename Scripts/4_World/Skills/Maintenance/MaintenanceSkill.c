class MaintenanceSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Ремонт одежды (Набор для шитья / Кожаный набор)
        MaintainClothing(bot);

        // 2. Ремонт оружия и инструментов (Набор для чистки оружия / Точильный камень)
        MaintainTools(bot);
    }

    private void MaintainClothing(ExpansionAIBase bot)
    {
        ItemBase sewingKit = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("SewingKit"));
        if (!sewingKit) return;

        // Бот проверяет всё на себе: куртку, штаны, рюкзак
        array<EntityAI> items = new array<EntityAI>;
        bot.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            if (item.IsClothing() && item.GetHealthLevel() >= 2) // Если состояние "Damaged" и хуже
            {
                bot.TakeItemToHands(sewingKit);
                bot.StartAction(ActionRepairInsideTarget); 
                return;
            }
        }
    }

    private void MaintainTools(ExpansionAIBase bot)
    {
        ItemBase whetstone = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Whetstone"));
        ItemBase gunKit = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WeaponCleaningKit"));

        // Проверка Мотыги (Hoe) - ремонт точильным камнем
        EntityAI hoe = bot.GetInventory().FindEntityInInventory("Hoe");
        if (hoe && hoe.GetHealthLevel() >= 2 && whetstone)
        {
            bot.TakeItemToHands(whetstone);
            bot.StartAction(ActionRepairTarget);
            return;
        }

        // Проверка оружия - ремонт набором для чистки
        Weapon weapon = Weapon.Cast(bot.GetHumanInventory().GetEntityInHands());
        if (weapon && weapon.GetHealthLevel() >= 2 && gunKit)
        {
            bot.TakeItemToHands(gunKit);
            bot.StartAction(ActionRepairTarget);
        }
    }
}

