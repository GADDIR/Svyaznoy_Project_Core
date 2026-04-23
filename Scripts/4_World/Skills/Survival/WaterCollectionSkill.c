class WaterCollectionSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Поиск пустой или неполной тары в инвентаре
        ItemBase container = GetEmptyContainer(bot);
        if (container && NeedsWaterRefill(bot))
        {
            FindWaterAndFill(bot, container);
        }
    }

    private void FindWaterAndFill(ExpansionAIBase bot, ItemBase container)
    {
        // Логика приоритетов источников:
        // 1. Колонка (чистая вода)
        // 2. Река/Озеро (требует последующей очистки/кипячения)
        // 3. Дождь (если открыта бочка - навык BarrelUsage)

        if (IsNearWell(bot)) // У колонки
        {
            bot.TakeItemToHands(container);
            bot.StartAction(ActionFillBottleBase); 
            Print("[AN_NEKRASOV_82] Набираю чистую воду в " + container.GetType());
        }
        else if (IsNearPond(bot)) // У водоема
        {
            bot.TakeItemToHands(container);
            bot.StartAction(ActionFillBottleBase);
            Print("[AN_NEKRASOV_82] Набираю речную воду. Потребуется очистка.");
        }
    }

    private ItemBase GetEmptyContainer(ExpansionAIBase bot)
    {
        // Бот проверяет ВСЮ возможную тару:
        // Бутылки, Фляги, Кастрюли, Канистры (для полива), Бензобаки (если будет авто)
        string[] types = {"WaterBottle", "Pot", "Canteen", "CanisterGasoline"};
        foreach (string t : types)
        {
            ItemBase item = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(t));
            if (item && item.GetQuantity() < item.GetQuantityMax()) return item;
        }
        return null;
    }

    private bool IsNearWell(ExpansionAIBase bot) { return bot.IsNearObject("StaticObj_RoadCone", 2.0); }
    private bool IsNearPond(ExpansionAIBase bot) { return GetGame().GetWaterDepth(bot.GetPosition()) > 0; }
    private bool NeedsWaterRefill(ExpansionAIBase bot) { return true; }
}

