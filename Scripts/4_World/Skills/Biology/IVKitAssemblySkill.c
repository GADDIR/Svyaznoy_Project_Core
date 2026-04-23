class IVKitAssemblySkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // 1. Сборка системы с физраствором
        AssembleIVKit(bot, "SalineBag", "SalineBagIV");

        // 2. Сборка системы с кровью
        AssembleIVKit(bot, "BloodBagFull", "BloodBagIV");
    }

    private void AssembleIVKit(ExpansionAIBase bot, string bagType, string resultType)
    {
        ItemBase bag = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(bagType));
        ItemBase ivStartKit = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("IVStartKit"));

        // Если есть пакет и игла, но нет готовой системы в инвентаре
        if (bag && ivStartKit && !HasReadyIV(bot, resultType))
        {
            bot.TakeItemToHands(ivStartKit);
            // Логика DayZ: Соединить иглу с пакетом
            bot.StartAction(ActionAttach); 
            Print("[AN_NEKRASOV_82] Собираю медицинскую систему: " + resultType);
        }
    }

    private bool HasReadyIV(ExpansionAIBase bot, string type)
    {
        return bot.GetInventory().FindEntityInInventory(type) != null;
    }
}

