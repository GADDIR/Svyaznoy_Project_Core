class EconomySkill
{
    // Список приоритетных покупок (по порядку)
    private ref array<string> m_ShoppingList = {"Belt_Leather", "PistolHolster", "MKII_Pistol", "Mag_MKII_10Rnd", "Box_22LR_50Rnd"};
    
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot) return;

        // 1. Проверяем наполненность рюкзака урожаем
        if (IsInventoryFullOfCrops(bot))
        {
            GoToTrader(bot);
        }

        // 2. Если мы у торговца — запускаем логику обмена
        if (IsNearTrader(bot))
        {
            TradeCycle(bot);
        }
    }

    private bool IsInventoryFullOfCrops(ExpansionAIBase bot)
    {
        // Проверяем наличие томатов, тыкв и т.д. в рюкзаке
        // Если овощей больше 5 штук — пора идти продавать
        return bot.GetInventory().CountItemsWithPrefix("Tomato") > 5;
    }

    private void GoToTrader(ExpansionAIBase bot)
    {
        // Координаты торговца из CentralTraders.map
        vector traderPos = "300.0 283.0 250.0"; // Уточнить реальные координаты торговца
        bot.GetNavigation().SetTarget(traderPos, ExpansionHAL_Mode.WALK);
    }

    private void TradeCycle(ExpansionAIBase bot)
    {
        // Логика:
        // 1. Продать все овощи (заменить овощи на валюту в инвентаре)
        // 2. Оценить текущий бюджет
        // 3. Сравнить бюджет со списком m_ShoppingList
        // 4. Если хватает на следующую вещь — "купить" и надеть
        
        float cash = bot.GetInventory().GetMoneyAmount();
        string nextItem = GetNextNeededItem(bot);

        if (cash >= GetPrice(nextItem))
        {
            bot.BuyAndEquip(nextItem);
            Print("[AN_NEKRASOV_82] Куплено: " + nextItem);
        }
    }

    private string GetNextNeededItem(ExpansionAIBase bot)
    {
        foreach (string item : m_ShoppingList)
        {
            if (!bot.GetInventory().FindEntityInInventory(item))
                return item;
        }
        return "";
    }
}

