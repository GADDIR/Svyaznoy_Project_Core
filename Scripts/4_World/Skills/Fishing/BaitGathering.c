class BaitGathering
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть нож + есть крючок, но нет червяка
        if (HasFishingGear(bot) && !HasBait(bot))
        {
            DigForWorms(bot);
        }
    }

    private void DigForWorms(ExpansionAIBase bot)
    {
        ItemBase knife = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Knife_Base"));
        if (knife)
        {
            bot.TakeItemToHands(knife);
            // Команда: Использовать нож на почве для поиска червей
            bot.StartAction(ActionDigWorms);
            Print("[AN_NEKRASOV_82] Копаю червей для наживки.");
        }
    }

    private bool HasFishingGear(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("BoneHook") != null || bot.GetInventory().FindEntityInInventory("FishingRod_Base") != null;
    }

    private bool HasBait(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("Food_Worm") != null;
    }
}

