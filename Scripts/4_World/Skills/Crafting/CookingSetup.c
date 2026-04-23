void SetupCookingEquipment(ExpansionAIBase bot, EntityAI targetFireplace)
{
    // Приоритет 1: Металлическая тренога из рюкзака
    ItemBase metalTripod = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("CookingStand"));
    if (metalTripod)
    {
        bot.TakeItemToHands(metalTripod);
        bot.StartAction(ActionAttach); // Прикрепить к костру
        Print("[AN_NEKRASOV_82] Устанавливаю надежную металлическую треногу.");
        return;
    }

    // Приоритет 2: Использование самодельной, если металла нет
    ItemBase stickTripod = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("ImprovisedCookingStand"));
    if (stickTripod)
    {
        bot.StartAction(ActionPlaceObject);
        Print("[AN_NEKRASOV_82] Ставлю временную треногу из веток.");
    }
}

