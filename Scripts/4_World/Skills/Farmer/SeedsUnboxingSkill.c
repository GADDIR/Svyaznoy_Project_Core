class SeedsUnboxingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // Ищем любой запечатанный пакетик семян
        ItemBase seedsPack = GetSeedsPack(bot);
        
        if (seedsPack)
        {
            UnpackSeeds(bot, seedsPack);
        }
    }

    private void UnpackSeeds(ExpansionAIBase bot, ItemBase pack)
    {
        if (bot.GetHumanInventory().CanAddEntityInHands(pack))
        {
            bot.TakeItemToHands(pack);
            // Логика DayZ: Распаковать пакетик (ActionUnpackBox)
            bot.StartAction(ActionUnpackBox); 
            Print("[AN_NEKRASOV_82] Распаковываю семена: " + pack.GetType() + ". Готовлюсь к посевной.");
        }
    }

    private ItemBase GetSeedsPack(ExpansionAIBase bot)
    {
        // Поиск предметов, являющихся упаковками семян
        return ItemBase.Cast(bot.GetInventory().FindEntityInInventory("SeedsPack_Base"));
    }
}

