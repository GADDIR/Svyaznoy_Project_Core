class StethoscopeSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Поиск человека без сознания в радиусе 2 метров
        CheckPulse(bot);
    }

    private void CheckPulse(ExpansionAIBase bot)
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man player : players)
        {
            if (player != bot && player.IsUnconscious() && vector.Distance(bot.GetPosition(), player.GetPosition()) < 2.0)
            {
                ItemBase stetho = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Stethoscope"));
                if (stetho)
                {
                    bot.TakeItemToHands(stetho);
                    bot.StartAction(ActionInspectBody);
                    Print("[AN_NEKRASOV_82] Проверяю пульс стетоскопом. Оцениваю шансы на спасение.");
                }
            }
        }
    }
}

