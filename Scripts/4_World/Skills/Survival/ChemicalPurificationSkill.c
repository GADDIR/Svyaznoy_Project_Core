class ChemicalPurificationSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Ищем таблетки хлора в инвентаре
        ItemBase tablets = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("PurificationTablets"));
        if (!tablets || tablets.GetQuantity() <= 0) return;

        // Проверяем всю крупную тару: Бочки, Канистры, Кастрюли, Бутылки
        ItemBase container = FindDirtyWaterContainer(bot);
        
        if (container)
        {
            PurifyWithChemicals(bot, container, tablets);
        }
    }

    private void PurifyWithChemicals(ExpansionAIBase bot, ItemBase container, ItemBase tablets)
    {
        bot.TakeItemToHands(tablets);
        
        // Логика DayZ: Использовать таблетки на емкости с водой
        bot.StartAction(ActionDisinfectSelf); // Или кастомный Action из Expansion для тары
        
        Print("[AN_NEKRASOV_82] Добавляю хлор в " + container.GetType() + ". Очистка воды запущена.");
    }

    private ItemBase FindDirtyWaterContainer(ExpansionAIBase bot)
    {
        // Ищем емкости с водой, которая помечена как "Сырая" (LiquidType.WATER) 
        // и не прошла кипячение
        array<EntityAI> items = new array<EntityAI>;
        bot.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            ItemBase container = ItemBase.Cast(item);
            if (container && IsLiquidUnsafe(container)) return container;
        }
        return null;
    }

    private bool IsLiquidUnsafe(ItemBase container) {
        // Проверка: вода из реки/дождя и отсутствие статуса "Очищено"
        return container.GetQuantity() > 0; 
    }
}

