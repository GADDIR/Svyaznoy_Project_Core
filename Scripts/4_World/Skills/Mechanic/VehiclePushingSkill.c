class VehiclePushingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        CarScript car = CarScript.Cast(bot.GetNearestObject("CarScript", 2.0));
        if (car && ShouldPush(bot, car))
        {
            PerformPush(bot, car);
        }
    }

    private void PerformPush(ExpansionAIBase bot, CarScript car)
    {
        // 1. Проверка передачи (нужна Нейтралка)
        if (car.GetGear() != CarGear.NEUTRAL)
        {
            bot.StartAction(ActionSwitchSeats); // Садится и переключает
            Print("[AN_NEKRASOV_82] Ставлю на нейтралку, чтобы толкнуть.");
            return;
        }

        // 2. Силовое действие (Push)
        if (bot.GetStatStamina().Get() > 20.0)
        {
            bot.StartAction(ActionPushCar); 
            Print("[AN_NEKRASOV_82] Толкаю машину. Налегай!");
        }
    }

    private bool ShouldPush(ExpansionAIBase bot, CarScript car)
    {
        // Толкаем если: застряли, нет бензина или нужно тихо переместить
        return car.IsCarStuck() || car.GetFluidFraction(CarFluid.FUEL) <= 0;
    }
}

