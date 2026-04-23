class RecoverySkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. САМОПОМОЩЬ: Если шок критический (пред-обморок)
        if (bot.GetStatShock().Get() < 300.0 && HasEpinephrine(bot))
        {
            ApplyEpinephrine(bot);
        }

        // 2. ПОМОЩЬ ДРУГИМ: Поиск тел в обмороке рядом
        CheckNearbyUnconscious(bot);
    }

    private void CheckNearbyUnconscious(ExpansionAIBase bot)
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man player : players)
        {
            if (player != bot && player.IsUnconscious() && vector.Distance(bot.GetPosition(), player.GetPosition()) < 2.0)
            {
                PerformResuscitation(bot, player);
                return;
            }
        }
    }

    private void PerformResuscitation(ExpansionAIBase bot, Man target)
    {
        ItemBase epi = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Epinephrine"));
        if (epi)
        {
            bot.TakeItemToHands(epi);
            bot.StartAction(ActionInjectTarget); // Укол адреналина цели
            Print("[AN_NEKRASOV_82] Привожу человека в чувство адреналином.");
        }
        else
        {
            bot.StartAction(ActionWakeUpTarget); // Приведение в чувство руками
            Print("[AN_NEKRASOV_82] Привожу в чувство руками (хлопки по щекам).");
        }
    }
}

