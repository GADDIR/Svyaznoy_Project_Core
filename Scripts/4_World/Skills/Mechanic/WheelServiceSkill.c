class WheelServiceSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        CarScript car = CarScript.Cast(bot.GetNearestObject("CarScript", 4.0));
        if (!car) return;

        // Ищем колесо в инвентаре (от легковушки или грузовика)
        EntityAI wheel = bot.GetInventory().FindEntityInInventory("CarWheel");
        if (wheel && !wheel.IsRuined())
        {
            InstallAndTighten(bot, car, wheel);
        }
    }

    private void InstallAndTighten(ExpansionAIBase bot, CarScript car, EntityAI wheel)
    {
        // 1. Накинуть колесо
        bot.TakeItemToHands(wheel);
        bot.StartAction(ActionAttach);
        Print("[AN_NEKRASOV_82] Накидываю колесо на ось.");

        // 2. Подтянуть болты (нужен баллонный ключ)
        ItemBase wrench = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("LugWrench"));
        if (wrench)
        {
            bot.TakeItemToHands(wrench);
            bot.StartAction(ActionTuneCarWheel); // Затяжка болтов
            Print("[AN_NEKRASOV_82] Затягиваю болты баллонным ключом. Теперь не отвалится.");
        }
    }
}

