class HygieneSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Проверка: Грязные ли руки/перчатки?
        if (bot.HasBloodyHands()) 
        {
            WashHandsLogic(bot);
        }
    }

    private void WashHandsLogic(ExpansionAIBase bot)
    {
        // Приоритет 1: Использовать воду из бутылки (если она есть)
        ItemBase bottle = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("WaterBottle"));
        if (bottle && bottle.GetQuantity() > 0)
        {
            bot.TakeItemToHands(bottle);
            bot.StartAction(ActionWashHandsItem);
            Print("[AN_NEKRASOV_82] Мою руки водой из бутылки после разделки.");
            return;
        }

        // Приоритет 2: Искать природный источник (водоем или колонку)
        if (IsNearWaterSource(bot))
        {
            bot.StartAction(ActionWashHandsWell);
            Print("[AN_NEKRASOV_82] Мою руки в природном источнике.");
        }
    }

    private bool IsNearWaterSource(ExpansionAIBase bot)
    {
        // Проверка на близость к колонке или открытой воде
        return bot.IsNearObject("StaticObj_RoadCone", 2.0) || GetGame().GetWaterDepth(bot.GetPosition()) > 0;
    }
}

