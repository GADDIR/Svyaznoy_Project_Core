class SharpenedStickSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть сырое мясо/рыба + есть длинная палка, но нет заточенной палки
        if (HasRawFood(bot) && HasLongStick(bot) && !HasSharpenedStick(bot))
        {
            PrepareCookingStick(bot);
        }
    }

    private void PrepareCookingStick(ExpansionAIBase bot)
    {
        ItemBase knife = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Knife_Base"));
        ItemBase longStick = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("LongWoodenStick"));

        if (knife && longStick)
        {
            bot.TakeItemToHands(knife);
            // Действие: Заточить длинную палку ножом
            bot.StartAction(ActionSharpenStick);
            Print("[AN_NEKRASOV_82] Затачиваю палку для жарки мяса.");
        }
    }

    private bool HasRawFood(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("Meat_Base") != null || bot.GetInventory().FindEntityInInventory("CarpFillet") != null;
    }

    private bool HasLongStick(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("LongWoodenStick") != null;
    }

    private bool HasSharpenedStick(ExpansionAIBase bot)
    {
        return bot.GetInventory().FindEntityInInventory("SharpenedStick") != null;
    }
}

