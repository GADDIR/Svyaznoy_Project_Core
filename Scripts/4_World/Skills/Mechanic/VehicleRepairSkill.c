class VehicleRepairSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // Ищем машину в радиусе 3 метров
        CarScript car = CarScript.Cast(bot.GetNearestObject("CarScript", 3.0));
        if (car && NeedsRepair(car))
        {
            PerformAutoRepair(bot, car);
        }
    }

    private void PerformAutoRepair(ExpansionAIBase bot, CarScript car)
    {
        // 1. РЕМОНТ ДВИГАТЕЛЯ (Приоритет №1)
        ItemBase wrench = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("PipeWrench"));
        if (wrench && car.GetHealth("Engine", "") < car.GetMaxHealth("Engine", ""))
        {
            bot.TakeItemToHands(wrench);
            bot.StartAction(ActionRepairCarEngine);
            Print("[AN_NEKRASOV_82] Чиню двигатель трубочным ключом.");
            return;
        }

        // 2. РЕМОНТ КУЗОВА И БАКОВ
        ItemBase epoxy = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("EpoxyPutty"));
        if (epoxy && car.GetHealth("Chassis", "") < car.GetMaxHealth("Chassis", ""))
        {
            bot.TakeItemToHands(epoxy);
            bot.StartAction(ActionRepairCarChassis);
            Print("[AN_NEKRASOV_82] Латаю кузов эпоксидкой.");
        }
    }

    private bool NeedsRepair(CarScript car) {
        return car.GetHealthLevel("") > 0; // Если состояние ниже Pristine
    }
}

