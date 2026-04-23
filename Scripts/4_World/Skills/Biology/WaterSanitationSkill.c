class WaterSanitationSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // 1. КИПЯЧЕНИЕ: Если есть кастрюля с сырой водой на огне
        ItemBase pot = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Pot"));
        if (pot && pot.GetQuantity() > 0 && IsNearFire(bot))
        {
            if (pot.GetTemperature() >= 100) // Вода вскипела
            {
                DistributeCleanWater(bot, pot);
            }
        }

        // 2. ХЛОРИРОВАНИЕ: Если есть таблетки и сырая вода в таре (бутылка/канистра)
        ItemBase tablets = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("PurificationTablets"));
        if (tablets && tablets.GetQuantity() > 0)
        {
            PurifyWithChemicals(bot, tablets);
        }
    }

    private void DistributeCleanWater(ExpansionAIBase bot, ItemBase source)
    {
        // Ищем пустую или грязную тару (которую мы слили ранее)
        ItemBase target = FindEmptyContainer(bot);
        if (target)
        {
            bot.TakeItemToHands(source);
            bot.StartAction(ActionTransferLiquid);
            Print("[AN_NEKRASOV_82] Заготавливаю стерильную воду: переливаю из кастрюли в " + target.GetType());
        }
    }

    private void PurifyWithChemicals(ExpansionAIBase bot, ItemBase tablets)
    {
        // Очищаем любую тару (включая канистры и бочки)
        ItemBase container = bot.GetInventory().FindEntityInInventory("Bottle_Base"); // Условный фильтр
        if (container && IsUnsafe(container))
        {
            bot.TakeItemToHands(tablets);
            bot.StartAction(ActionDisinfectTarget);
            Print("[AN_NEKRASOV_82] Очищаю воду в " + container.GetType() + " таблетками хлора.");
        }
    }

    private bool IsNearFire(ExpansionAIBase bot) { return bot.IsNearObject("FireplaceBase", 2.0); }
    private bool IsUnsafe(ItemBase item) { return item.GetLiquidType() == LiquidType.WATER && !item.IsItemClean(); }
    private ItemBase FindEmptyContainer(ExpansionAIBase bot) { /* Поиск пустых бутылок/фляг */ return null; }
}

