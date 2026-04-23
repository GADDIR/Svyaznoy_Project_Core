class CanOpeningSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // Ищем закрытую банку в инвентаре
        ItemBase can = FindClosedCan(bot);
        if (can)
        {
            OpenCanLogic(bot, can);
        }
    }

    private void OpenCanLogic(ExpansionAIBase bot, ItemBase can)
    {
        // Выбор лучшего инструмента из имеющихся
        ItemBase tool = FindBestOpener(bot);

        if (tool)
        {
            bot.TakeItemToHands(tool);
            // Логика DayZ: Открыть банку выбранным инструментом
            bot.StartAction(ActionOpenCan); 
            Print("[AN_NEKRASOV_82] Открываю " + can.GetType() + " используя " + tool.GetType());
        }
    }

    private ItemBase FindBestOpener(ExpansionAIBase bot)
    {
        // Иерархия инструментов Мэверика
        string[] openers = {"CanOpener", "Knife_Base", "Screwdriver", "Hatchet", "Hammer", "SmallStone"};
        foreach (string t : openers)
        {
            ItemBase item = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(t));
            if (item && !item.IsRuined()) return item;
        }
        return null;
    }

    private ItemBase FindClosedCan(ExpansionAIBase bot) {
        // Поиск запечатанных консервов (PeachesCan, TacticalBaconCan и т.д.)
        return ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Can_Base")); 
    }
}

