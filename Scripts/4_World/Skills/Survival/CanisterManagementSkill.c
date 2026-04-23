class CanisterManagementSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        ItemBase canister = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("CanisterGasoline"));
        if (!canister) return;

        // ЛОГИКА 1: Очистка найденного
        if (IsNewFound(canister) && canister.GetQuantity() > 0)
        {
            bot.TakeItemToHands(canister);
            bot.StartAction(ActionEmptyCanister); 
            Print("[AN_NEKRASOV_82] Очищаю найденную канистру для своих нужд.");
        }

        // ЛОГИКА 2: Стратегическое хранение
        if (bot.IsInSafeZone())
        {
            // Бот прячет канистру с водой в палатку или ящик (схрон)
            StoreCanister(bot, canister);
        }
    }

    private void StoreCanister(ExpansionAIBase bot, ItemBase canister)
    {
        // Поиск места в палатке или ящике
        EntityAI storage = bot.GetNearestObject("WoodenCrate", 2.0);
        if (storage && bot.GetInventory().CanAddEntityToTargetInventory(storage, canister))
        {
            bot.TakeEntityToTargetInventory(InventoryMode.PREDICTIVE, storage, canister);
            Print("[AN_NEKRASOV_82] Убираю канистру в схрон. Это ценный ресурс.");
        }
    }
}

