class FuelExtractionSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        ItemBase container = GetAnyContainer(bot);
        if (!container || container.GetQuantity() == container.GetQuantityMax()) return;

        // 1. ЛОГИКА АЗС (Бензоколонка)
        Object gasStation = bot.GetNearestObject("Land_FuelStation_Feed", 3.0);
        if (gasStation)
        {
            bot.TakeItemToHands(container);
            bot.StartAction(ActionFillBottleBase); 
            Print("[AN_NEKRASOV_82] Наполняю " + container.GetType() + " на заправке.");
            return;
        }

        // 2. ЛОГИКА СИФОНА (Слив шлангом из авто)
        ItemBase hose = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("CanisterGasoline")); // Условно шланг
        CarScript targetCar = CarScript.Cast(bot.GetNearestObject("CarScript", 3.0));
        
        if (targetCar && hose && targetCar.GetFluidFraction(CarFluid.FUEL) > 0)
        {
            bot.TakeItemToHands(hose);
            // Логика DayZ: Слить топливо шлангом в тару
            bot.StartAction(ActionDrainFuel); 
            Print("[AN_NEKRASOV_82] Сливаю остатки бензина из бака шлангом.");
        }
    }

    private ItemBase GetAnyContainer(ExpansionAIBase bot)
    {
        string[] types = {"CanisterGasoline", "WaterBottle", "Pot", "Canteen"};
        foreach (string t : types)
        {
            ItemBase item = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(t));
            if (item) return item;
        }
        return null;
    }
}

