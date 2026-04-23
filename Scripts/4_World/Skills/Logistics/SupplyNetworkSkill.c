class SupplyNetworkSkill
{
    private const float CHECK_RADIUS = 3.0;

    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Ищем свою маленькую палатку (Shelter) в радиусе маршрута
        TentBase shelter = TentBase.Cast(bot.GetNearestObject("ShelterBase", CHECK_RADIUS));
        
        if (shelter && shelter.IsOpened())
        {
            MaintainCheckpoint(bot, shelter);
        }
    }

    private void MaintainCheckpoint(ExpansionAIBase bot, TentBase shelter)
    {
        // Протокол комплектации "Минимум"
        CheckAndRefill(bot, shelter, "Hoes", 1);           // Мотыга
        CheckAndRefill(bot, shelter, "SeedsPack", 2);      // Семена
        CheckAndRefill(bot, shelter, "WaterBottle", 1);    // Вода
        CheckAndRefill(bot, shelter, "BandageDressing", 2);// Медицина
        CheckAndRefill(bot, shelter, "SalineBagIV", 1);    // Физраствор
        CheckAndRefill(bot, shelter, "Matchbox", 1);       // Огонь
        CheckAndRefill(bot, shelter, "Knife_Base", 1);     // Нож
    }

    private void CheckAndRefill(ExpansionAIBase bot, TentBase storage, string itemType, int count)
    {
        int currentCount = storage.GetInventory().CountItemsWithPrefix(itemType);
        if (currentCount < count)
        {
            ItemBase resource = ItemBase.Cast(bot.GetInventory().FindEntityInInventory(itemType));
            if (resource)
            {
                bot.TakeEntityToTargetInventory(InventoryMode.PREDICTIVE, storage, resource);
                Print("[AN_NEKRASOV_82] Пополняю аванпост: добавил " + itemType);
            }
        }
    }
}

