class FuelWaterLogistics
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        ItemBase canister = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("CanisterGasoline"));
        if (!canister) return;

        CarScript car = CarScript.Cast(bot.GetNearestObject("CarScript", 4.0));
        
        // 1. ЗАПРАВКА ТОПЛИВОМ (В бак)
        if (car && NeedsFuel(car) && IsGasoline(canister))
        {
            bot.TakeItemToHands(canister);
            bot.StartAction(ActionFillFuel);
            Print("[AN_NEKRASOV_82] Заправляю машину бензином из канистры.");
        }

        // 2. ЗАПРАВКА РАДИАТОРА (Водой)
        if (car && NeedsCoolant(car) && IsWater(canister))
        {
            bot.TakeItemToHands(canister);
            bot.StartAction(ActionFillCoolant);
            Print("[AN_NEKRASOV_82] Заливаю воду в радиатор. Перегрев не нужен.");
        }
    }

    private bool NeedsFuel(CarScript car) {
        return car.GetFluidFraction(CarFluid.FUEL) < 0.9; // Если бак не полон
    }

    private bool NeedsCoolant(CarScript car) {
        return car.GetFluidFraction(CarFluid.COOLANT) < 0.9; // Если радиатор не полон
    }

    private bool IsGasoline(ItemBase item) { return item.GetLiquidType() == LiquidType.GASOLINE; }
    private bool IsWater(ItemBase item) { return item.GetLiquidType() == LiquidType.WATER; }
}

