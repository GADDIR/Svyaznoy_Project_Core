class UniversalFluidTransfer
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        CarScript car = CarScript.Cast(bot.GetNearestObject("CarScript", 4.0));
        if (!car) return;

        // Поиск любой тары с жидкостью в руках или инвентаре
        ItemBase container = GetFluidContainer(bot);
        if (container && container.GetQuantity() > 0)
        {
            RefillVehicle(bot, car, container);
        }
    }

    private void RefillVehicle(ExpansionAIBase bot, CarScript car, ItemBase container)
    {
        // 1. ЗАПРАВКА РАДИАТОРА (ВОДА)
        if (container.GetLiquidType() == LiquidType.WATER && NeedsCoolant(car))
        {
            bot.TakeItemToHands(container);
            bot.StartAction(ActionFillCoolant);
            Print("[AN_NEKRASOV_82] Заливаю воду в радиатор из " + container.GetType());
        }
        // 2. ЗАПРАВКА БАКА (БЕНЗИН)
        else if (container.GetLiquidType() == LiquidType.GASOLINE && NeedsFuel(car))
        {
            bot.TakeItemToHands(container);
            bot.StartAction(ActionFillFuel);
            Print("[AN_NEKRASOV_82] Доливаю топливо в бак из " + container.GetType());
        }
    }

    private ItemBase GetFluidContainer(ExpansionAIBase bot)
    {
        string[] types = {"CanisterGasoline", "Pot", "WaterBottle", "Canteen"};
        foreach (string t : types)
        {
            ItemBase item = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(t));
            if (item) return item;
        }
        return null;
    }

    private bool NeedsCoolant(CarScript car) { return car.GetFluidFraction(CarFluid.COOLANT) < 0.95; }
    private bool NeedsFuel(CarScript car) { return car.GetFluidFraction(CarFluid.FUEL) < 0.95; }
}

