class TripodCrafting
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть кастрюля (Pot), но нет треноги для костра
        if (HasPot(bot) && !HasTripod(bot))
        {
            CraftImprovisedTripod(bot);
        }
    }

    private void CraftImprovisedTripod(ExpansionAIBase bot)
    {
        // Для самодельной треноги нужны 3 длинные палки (Long Wooden Sticks) + Веревка
        ItemBase sticks = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("LongWoodenStick"));
        ItemBase rope = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rope"));

        if (sticks && sticks.GetQuantity() >= 3 && rope)
        {
            bot.TakeItemToHands(rope);
            // Логика DayZ: Соединить 3 палки и веревку
            bot.StartAction(ActionCreateCookingStand); 
            Print("[AN_NEKRASOV_82] Сооружаю треногу. Теперь готовить будет проще.");
        }
    }

    private bool HasPot(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("Pot") != null;
    }

    private bool HasTripod(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("CookingStand") != null;
    }
}

