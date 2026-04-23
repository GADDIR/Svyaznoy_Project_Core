class ImprovisedClothingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Для любого крафта одежды из тряпок нужно минимум 1-2 тряпки
        ItemBase rags = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rag"));
        if (!rags || rags.GetQuantity() < 1) return;

        // Приоритет 1: Ноги (защита от грибка и порезов)
        if (!bot.GetInventory().FindAttachment(InventorySlots.FEET))
            CraftAndEquip(bot, "Feet", 2); // Обмотки на ноги (2 тряпки)

        // Приоритет 2: Руки (гигиена при разделке и сборе камней)
        else if (!bot.GetInventory().FindAttachment(InventorySlots.GLOVES))
            CraftAndEquip(bot, "Gloves", 2); // Перчатки (2 тряпки)

        // Приоритет 3: Маска (фильтрация и тепло)
        else if (!bot.GetInventory().FindAttachment(InventorySlots.MASK))
            CraftAndEquip(bot, "Mask", 1); // Маска (1 тряпка)

        // Приоритет 4: Голова (защита от солнца и холода)
        else if (!bot.GetInventory().FindAttachment(InventorySlots.HEADGEAR))
            CraftAndEquip(bot, "Head", 1); // Платок/бандана (1 тряпка)

        // Приоритет 5: Повязка на руку (идентификация личности AN_NEKRASOV_82)
        else if (!bot.GetInventory().FindAttachment(InventorySlots.ARMBAND))
            CraftAndEquip(bot, "Armband", 1); // Повязка (1 тряпка)
    }

    private void CraftAndEquip(ExpansionAIBase bot, string type, int cost)
    {
        ItemBase rags = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Rag"));
        if (rags && rags.GetQuantity() >= cost)
        {
            bot.TakeItemToHands(rags);
            // Логика DayZ: Создать и сразу надеть предмет
            bot.StartAction(ActionCreateAndEquipImprovised); 
            Print("[AN_NEKRASOV_82] Изготавливаю элемент одежды: " + type);
        }
    }
}

