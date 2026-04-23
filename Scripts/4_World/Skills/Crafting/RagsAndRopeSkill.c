class RagsAndRopeSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Проверка: Нужна ли веревка для крафта удочки/копья/рюкзака
        if (NeedsRope(bot) && HasEnoughRags(bot))
        {
            CraftRope(bot);
        }
    }

    private void CraftRope(ExpansionAIBase bot)
    {
        // Ищем тряпки в инвентаре
        ItemBase rags = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rag"));
        
        if (rags)
        {
            // ВАРИАНТ 1: В стаке ровно 12 или больше
            if (rags.GetQuantity() >= 12)
            {
                bot.TakeItemToHands(rags);
                bot.StartAction(ActionCreateRope); 
                Print("[AN_NEKRASOV_82] Плету веревку из целого стака (12 шт).");
            }
            // ВАРИАНТ 2: Ищем вторую пачку тряпок, чтобы совместить (6+6)
            else
            {
                ItemBase rags2 = FindAnotherRagStack(bot, rags);
                if (rags2 && (rags.GetQuantity() + rags2.GetQuantity() >= 12))
                {
                    bot.TakeItemToHands(rags);
                    // Совмещаем две стопки
                    bot.StartAction(ActionCreateRope); 
                    Print("[AN_NEKRASOV_82] Плету веревку, соединяя две стопки тряпок.");
                }
            }
        }
    }

    private bool HasEnoughRags(ExpansionAIBase bot)
    {
        int total = bot.GetInventory().CountItemsWithPrefix("Rag");
        return total >= 12;
    }

    private bool NeedsRope(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("Rope") == null;
    }

    private ItemBase FindAnotherRagStack(ExpansionAIBase bot, ItemBase firstStack)
    {
        // Логика поиска второй пачки тряпок в инвентаре, исключая первую
        return null; // В реальности здесь поиск по ID объекта
    }
}

