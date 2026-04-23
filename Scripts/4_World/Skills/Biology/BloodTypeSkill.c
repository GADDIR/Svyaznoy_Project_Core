class BloodTypeSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Узнать свою группу крови (если еще не знает)
        if (bot.GetBloodType() == 0) 
        {
            DetermineOwnBloodType(bot);
        }
    }

    private void DetermineOwnBloodType(ExpansionAIBase bot)
    {
        ItemBase testKit = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("BloodTestKit"));
        if (testKit)
        {
            bot.TakeItemToHands(testKit);
            bot.StartAction(ActionTestBloodSelf);
            Print("[AN_NEKRASOV_82] Провожу анализ крови. Нужно знать свою группу.");
        }
    }

    // Логика сбора любой крови у цели (если есть набор)
    void CollectAnyBlood(ExpansionAIBase bot, Man target)
    {
        ItemBase kit = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("BloodBagEmpty"));
        if (kit)
        {
            bot.TakeItemToHands(kit);
            bot.StartAction(ActionCollectBloodTarget);
            Print("[AN_NEKRASOV_82] Забираю кровь у донора. Группа будет определена позже.");
        }
    }
}

