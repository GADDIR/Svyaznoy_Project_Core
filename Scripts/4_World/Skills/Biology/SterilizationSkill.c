class SterilizationSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // Ищем нестерильные тряпки
        ItemBase rags = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rag"));
        if (rags && !rags.IsDisinfected())
        {
            ProcessSterilization(bot, rags);
        }
    }

    private void ProcessSterilization(ExpansionAIBase bot, ItemBase rags)
    {
        // 1. ХИМИЯ (Спрей, Спирт, Йод)
        ItemBase cleaner = FindLiquidDisinfectant(bot);
        if (cleaner)
        {
            bot.TakeItemToHands(cleaner);
            // Действие: Продезинфицировать тряпки
            bot.StartAction(ActionDisinfectTarget); 
            Print("[AN_NEKRASOV_82] Стерилизую тряпки с помощью " + cleaner.GetType());
            return;
        }

        // 2. КИПЯЧЕНИЕ (Если есть кастрюля на огне)
        ItemBase pot = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Pot"));
        if (pot && pot.GetTemperature() >= 100)
        {
            bot.TakeItemToHands(rags);
            bot.StartAction(ActionAttach); // Поместить в кипяток
            Print("[AN_NEKRASOV_82] Кипячу бинты в кастрюле для стерильности.");
        }
    }

    private ItemBase FindLiquidDisinfectant(ExpansionAIBase bot)
    {
        string[] types = {"DisinfectantSpray", "AlcoholPreps", "IodineTincture"};
        foreach (string t : types)
        {
            ItemBase item = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(t));
            if (item && item.GetQuantity() > 0) return item;
        }
        return null;
    }
}

