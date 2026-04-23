class BottleTechRefill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        CarScript car = CarScript.Cast(bot.GetNearestObject("CarScript", 4.0));
        if (!car) return;

        // Ищем именно пластиковую бутылку с жидкостью
        ItemBase bottle = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WaterBottle"));
        
        if (bottle && bottle.GetQuantity() > 0)
        {
            ProcessBottleRefill(bot, car, bottle);
        }
    }

    private void ProcessBottleRefill(ExpansionAIBase bot, CarScript car, ItemBase bottle)
    {
        float fuelLevel = car.GetFluidFraction(CarFluid.FUEL);
        float coolantLevel = car.GetFluidFraction(CarFluid.COOLANT);

        // 1. БЕНЗИН В БАК
        if (bottle.GetLiquidType() == LiquidType.GASOLINE && fuelLevel < 1.0)
        {
            bot.TakeItemToHands(bottle);
            bot.StartAction(ActionFillFuel);
            Print("[AN_NEKRASOV_82] Доливаю топливо бутылкой. Капля камень точит.");
        }
        // 2. ВОДА В РАДИАТОР
        else if (bottle.GetLiquidType() == LiquidType.WATER && coolantLevel < 1.0)
        {
            bot.TakeItemToHands(bottle);
            bot.StartAction(ActionFillCoolant);
            Print("[AN_NEKRASOV_82] Наполняю радиатор бутылкой воды.");
        }
    }
}

