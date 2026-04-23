class UniversalPotCooking
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        ItemBase pot = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Pot"));
        if (!pot || pot.GetQuantity() == 0) return; // Кастрюля должна быть с водой/едой

        Object stove = FindNearestStove(bot);
        if (stove && IsIgnited(stove))
        {
            AttachPotToSource(bot, pot, stove);
        }
    }

    private void AttachPotToSource(ExpansionAIBase bot, ItemBase pot, Object source)
    {
        // 1. Если это домашняя печь или камин
        if (source.GetType().Contains("Oven") || source.GetType().Contains("Fireplace_Indoor"))
        {
            bot.TakeItemToHands(pot);
            bot.StartAction(ActionAttach); 
            Print("[AN_NEKRASOV_82] Ставлю кастрюлю на домашнюю печь.");
        }
        // 2. Если это бочка-печь
        else if (source.IsInherited(BarrelHoles_ColorBase))
        {
            bot.StartAction(ActionAttach);
            Print("[AN_NEKRASOV_82] Использую бочку как плиту.");
        }
        // 3. Если это костер с треногой
        else if (source.IsInherited(Fireplace) && HasTripod(source))
        {
            bot.StartAction(ActionAttach);
            Print("[AN_NEKRASOV_82] Вешаю кастрюлю на треногу над костром.");
        }
    }

    private Object FindNearestStove(ExpansionAIBase bot)
    {
        // Поиск: Печь (в доме) > Бочка > Костер с треногой
        return bot.GetNearestObject("HouseWithFireplace", 3.0); 
    }
}

