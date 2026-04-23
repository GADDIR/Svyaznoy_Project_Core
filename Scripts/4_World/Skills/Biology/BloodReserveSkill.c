class BloodReserveSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. ЗАГОТОВКА: Если бот в идеальном состоянии и есть инвентарь для забора
        if (IsPerfectCondition(bot) && HasCollectionKit(bot))
        {
            CreateBloodReserve(bot);
        }

        // 2. ИСПОЛЬЗОВАНИЕ: Если критическая потеря крови (экран серый)
        if (bot.GetStatBlood().Get() < 3000.0 && HasFullBloodBag(bot))
        {
            UseBloodReserve(bot);
        }
    }

    private void CreateBloodReserve(ExpansionAIBase bot)
    {
        ItemBase kit = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("BloodBagEmpty"));
        if (kit)
        {
            bot.TakeItemToHands(kit);
            bot.StartAction(ActionCollectBloodSelf);
            Print("[AN_NEKRASOV_82] Заготавливаю пакет собственной крови на черный день.");
        }
    }

    private void UseBloodReserve(ExpansionAIBase bot)
    {
        ItemBase fullBag = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("BloodBagFull"));
        ItemBase ivKit = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("IVBloodBag")); // Готовый к вводу

        if (fullBag || ivKit)
        {
            bot.TakeItemToHands(ivKit);
            bot.StartAction(ActionGiveBloodSelf);
            Print("[AN_NEKRASOV_82] Критическая потеря крови! Провожу экстренное переливание.");
        }
    }

    private bool IsPerfectCondition(ExpansionAIBase bot) {
        return bot.GetStatHealth().Get() > 4500.0 && bot.GetStatBlood().Get() > 4900.0;
    }

    private bool HasCollectionKit(ExpansionAIBase bot) {
        return bot.GetInventory().FindEntityInInventory("BloodBagEmpty") != null;
    }

    private bool HasFullBloodBag(ExpansionAIBase bot) {
        return bot.GetInventory().FindEntityInInventory("BloodBagFull") != null || bot.GetInventory().FindEntityInInventory("IVBloodBag") != null;
    }
}

