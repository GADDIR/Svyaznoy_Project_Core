class BroomRecycling
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Если в руках или рядом есть метла, а нам нужны палки
        ItemBase broom = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Broom"));
        if (broom && NeedsSticks(bot))
        {
            DismantleBroom(bot, broom);
        }
    }

    private void DismantleBroom(ExpansionAIBase bot, ItemBase broom)
    {
        ItemBase knife = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Knife_Base"));
        if (knife)
        {
            bot.TakeItemToHands(knife);
            // Действие: Разобрать метлу на палки
            bot.StartAction(ActionDetachedBroom); 
            Print("[AN_NEKRASOV_82] Разбираю метлу на полезные ветки и палки.");
        }
    }

    private bool NeedsSticks(ExpansionAIBase bot)
    {
        // Если нет длинной палки для крафта копья или удочки
        return bot.GetInventory().FindEntityInInventory("LongWoodenStick") == null;
    }
}

