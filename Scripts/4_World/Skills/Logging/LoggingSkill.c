class LoggingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Нужны дрова для "Базы" (склада) или костра
        if (IsStockLow(bot) && bot.GetStatEnergy().Get() > 3000)
        {
            PerformLogging(bot);
        }
    }

    private void PerformLogging(ExpansionAIBase bot)
    {
        // 2. Поиск инструмента (Топор или Топорик)
        ItemBase tool = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Axe_Base"));
        if (!tool) tool = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Hatchet"));

        if (tool)
        {
            Object tree = GetNearestTree(bot, 15.0);
            if (tree)
            {
                bot.TakeItemToHands(tool);
                bot.StartAction(ActionChopTree);
                // После рубки - собрать дрова (Firewood) и отнести к костру/складу
                Print("[AN_NEKRASOV_82] Валю дерево для долгого огня...");
            }
        }
    }

    private bool IsStockLow(ExpansionAIBase bot)
    {
        // Проверяем количество дров рядом с точкой дома
        return bot.GetInventory().CountItemsWithPrefix("Firewood") < 5;
    }
}

