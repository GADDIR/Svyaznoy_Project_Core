class FishingNetSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Плетение сети (нужно 2 мотка веревки / или много тряпок)
        if (NeedsNet(bot) && HasRopes(bot))
        {
            CraftNet(bot);
        }

        // 2. Установка (если сеть готова и бот у воды)
        if (HasNet(bot) && IsNearWater(bot))
        {
            PlaceNet(bot);
        }
    }

    private void CraftNet(ExpansionAIBase bot)
    {
        ItemBase rope1 = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rope"));
        // Плетение сети из веревок
        bot.StartAction(ActionCreateFishingNet);
        Print("[AN_NEKRASOV_82] Плету рыболовную сеть из запасов веревки.");
    }

    private void PlaceNet(ExpansionAIBase bot)
    {
        // Установка сети на мелководье
        bot.StartAction(ActionPlaceFishingNet);
        Print("[AN_NEKRASOV_82] Установил сеть. Приду проверять улов утром.");
    }

    private bool NeedsNet(ExpansionAIBase bot) { return !HasNet(bot); }
    private bool HasRopes(ExpansionAIBase bot) { return bot.GetInventory().CountItemsWithPrefix("Rope") >= 2; }
    private bool HasNet(ExpansionAIBase bot) { return bot.GetInventory().FindEntityInInventory("FishingNet") != null; }
    private bool IsNearWater(ExpansionAIBase bot) { return GetGame().GetWaterDepth(bot.GetPosition()) > 0.5; }
}

