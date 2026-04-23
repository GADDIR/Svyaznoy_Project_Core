class UniversalWaterRefill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // Ищем ближайшую колонку (Well)
        Object well = bot.GetNearestObject("StaticObj_RoadCone", 2.0); // ID колонки в движке
        if (well)
        {
            RefillAllContainers(bot, well);
        }
    }

    private void RefillAllContainers(ExpansionAIBase bot, Object well)
    {
        // Список всей возможной тары для воды
        string[] types = {"CanisterGasoline", "Pot", "WaterBottle", "Canteen", "BeerBottle"};
        
        foreach (string t : types)
        {
            ItemBase container = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(t));
            
            // Если тара не полная и не содержит бензин
            if (container && container.GetQuantity() < container.GetQuantityMax() && container.GetLiquidType() != LiquidType.GASOLINE)
            {
                bot.TakeItemToHands(container);
                bot.StartAction(ActionFillBottleBase); 
                Print("[AN_NEKRASOV_82] Набираю чистую воду в " + t + " из колонки.");
                return; // Набираем по очереди
            }
        }
    }
}

