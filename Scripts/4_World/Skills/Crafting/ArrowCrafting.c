class ArrowCraftingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть нож и короткие палки, но мало стрел
        if (NeedsArrows(bot) && CanCraftBasicArrow(bot))
        {
            CraftSimpleArrow(bot);
        }

        // 2. Условие: Есть кости и перья — делаем усиленные стрелы
        if (CanCraftBoneArrow(bot))
        {
            CraftBoneArrow(bot);
        }
    }

    private void CraftSimpleArrow(ExpansionAIBase bot)
    {
        ItemBase knife = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Knife_Base"));
        ItemBase stick = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WoodenStick"));

        if (knife && stick)
        {
            bot.TakeItemToHands(knife);
            // Логика DayZ: Заточить палку в стрелу
            bot.StartAction(ActionCreateArrow); 
            Print("[AN_NEKRASOV_82] Вытачиваю простую стрелу из ветки.");
        }
    }

    private void CraftBoneArrow(ExpansionAIBase bot)
    {
        // Усложненный крафт: палка + перо + костяной наконечник
        Print("[AN_NEKRASOV_82] Изготавливаю усиленную стрелу с костяным наконечником.");
    }

    private bool NeedsArrows(ExpansionAIBase bot)
    {
        return bot.GetInventory().CountItemsWithPrefix("Ammo_Arrow") < 5;
    }

    private bool CanCraftBasicArrow(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("Knife_Base") && bot.GetInventory().FindEntityInInventory("WoodenStick");
    }
}

