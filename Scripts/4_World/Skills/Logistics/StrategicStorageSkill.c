class StrategicStorageSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Проверка режима "Турист" перед выходом из Safe Zone
        if (bot.IsLeavingSafeZone())
        {
            PrepareTouristKit(bot);
        }

        // 2. Логика "Схрона" - наполнение ресурсов в ящики
        if (bot.IsInSafeZone())
        {
            RefillBuriedReserves(bot);
        }
    }

    private void PrepareTouristKit(ExpansionAIBase bot)
    {
        // Бот проверяет, чтобы в инвентаре была минимум одна ПОЛНАЯ фляга
        ItemBase flask = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Canteen"));
        if (flask && flask.GetQuantity() < flask.GetQuantityMax())
        {
            bot.StartAction(ActionFillBottleBase); // Долить перед выходом
            Print("[AN_NEKRASOV_82] Подготовка режима ТУРИСТ: наполняю походную флягу.");
        }
    }
}

