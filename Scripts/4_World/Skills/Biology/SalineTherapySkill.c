class SalineTherapySkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. САМОПОМОЩЬ: Если вода в "красной" зоне или шок высокий
        if (bot.GetStatWater().Get() < 1000.0 || bot.GetStatShock().Get() < 500.0)
        {
            ApplySaline(bot, bot);
        }

        // 2. ПОМОЩЬ ДРУГИМ: Если рядом игрок в обмороке
        LookForPatients(bot);
    }

    private void ApplySaline(ExpansionAIBase bot, Man target)
    {
        ItemBase salineIV = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("SalineBagIV"));
        if (salineIV)
        {
            bot.TakeItemToHands(salineIV);
            if (target == bot)
                bot.StartAction(ActionGiveSalineSelf);
            else
                bot.StartAction(ActionGiveSalineTarget);
            
            Print("[AN_NEKRASOV_82] Ввожу физраствор для стабилизации состояния.");
        }
    }

    private void LookForPatients(ExpansionAIBase bot)
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        foreach (Man p : players)
        {
            if (p != bot && p.IsUnconscious() && vector.Distance(bot.GetPosition(), p.GetPosition()) < 2.0)
            {
                ApplySaline(bot, p);
            }
        }
    }
}

