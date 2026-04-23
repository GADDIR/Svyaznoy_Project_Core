class CrateCrafting
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть доски (8 шт) + гвозди (16 шт) + молоток/топор
        if (CanCraftCrate(bot))
        {
            StartCrafting(bot);
        }
    }

    private bool CanCraftCrate(ExpansionAIBase bot)
    {
        ItemBase planks = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Plank"));
        ItemBase nails = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Nails"));
        
        // Для ящика нужно 8 досок и 16 гвоздей
        return (planks && planks.GetQuantity() >= 8 && nails && nails.GetQuantity() >= 16);
    }

    private void StartCrafting(ExpansionAIBase bot)
    {
        // Ищем инструмент (молоток, топорик или даже разводной ключ)
        ItemBase tool = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Hammer"));
        if (!tool) tool = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Hatchet"));

        if (tool)
        {
            bot.TakeItemToHands(tool);
            // Действие: Сколотить деревянный ящик
            bot.StartAction(ActionCraftWoodenCrate);
            Print("[AN_NEKRASOV_82] Сколачиваю ящик для хранения запасов.");
        }
    }
}

