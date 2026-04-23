class UniversalIrrigationSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Проверка: Нужно ли полить огород?
        if (NeedsWatering(bot))
        {
            UseAnyWaterContainer(bot);
        }
    }

    private void UseAnyWaterContainer(ExpansionAIBase bot)
    {
        // Список приоритетов тары для полива
        string[] containers = {"CanisterGasoline", "Pot", "WaterBottle", "Canteen"};
        
        foreach (string type : containers)
        {
            ItemBase container = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(type));
            
            // Если в таре есть ЛЮБАЯ вода (не обязательно чистая)
            if (container && container.GetQuantity() > 0)
            {
                bot.TakeItemToHands(container);
                bot.StartAction(ActionWaterPlant); // Полив растения
                bot.StartAction(ActionWaterGardenPlot); // Полив всей грядки
                Print("[AN_NEKRASOV_82] Полив огорода из " + type);
                return;
            }
        }
    }

    private bool NeedsWatering(ExpansionAIBase bot)
    {
        // Логика: поиск сухой грядки (GardenPlot) в радиусе 10м
        return bot.IsNearObject("GardenPlot", 10.0); 
    }
}

