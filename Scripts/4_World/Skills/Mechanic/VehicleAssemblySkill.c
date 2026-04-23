class VehicleAssemblySkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        CarScript car = CarScript.Cast(bot.GetNearestObject("CarScript", 4.0));
        if (car)
        {
            AssembleCar(bot, car);
        }
    }

    private void AssembleCar(ExpansionAIBase bot, CarScript car)
    {
        // 1. УСТАНОВКА СВЕЧИ (SparkPlug)
        EntityAI plug = bot.GetInventory().FindEntityInInventory("SparkPlug");
        if (plug && !car.GetInventory().FindAttachment(InventorySlots.SPARKPLUG))
        {
            bot.TakeItemToHands(plug);
            bot.StartAction(ActionAttach);
            Print("[AN_NEKRASOV_82] Вкручиваю свечу зажигания.");
            return;
        }

        // 2. УСТАНОВКА АККУМУЛЯТОРА (CarBattery)
        EntityAI battery = bot.GetInventory().FindEntityInInventory("CarBattery");
        if (battery && !car.GetInventory().FindAttachment(InventorySlots.BATTERY))
        {
            bot.TakeItemToHands(battery);
            bot.StartAction(ActionAttach);
            Print("[AN_NEKRASOV_82] Ставлю аккумулятор. Проверяю клеммы.");
            return;
        }

        // 3. УСТАНОВКА РАДИАТОРА (CarRadiator)
        EntityAI radiator = bot.GetInventory().FindEntityInInventory("CarRadiator");
        if (radiator && !car.GetInventory().FindAttachment(InventorySlots.RADIATOR))
        {
            bot.TakeItemToHands(radiator);
            bot.StartAction(ActionAttach);
            Print("[AN_NEKRASOV_82] Монтирую радиатор. Сейчас нужна будет вода.");
        }
    }
}

