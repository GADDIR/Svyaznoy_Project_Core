class WringingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // 1. Условие: Если бот под крышей или дождь кончился, а вещи мокрые
        if (CanStartWringing(bot))
        {
            ProcessWringing(bot);
        }
    }

    private void ProcessWringing(ExpansionAIBase bot)
    {
        array<EntityAI> items = new array<EntityAI>;
        bot.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            ItemBase clothing = ItemBase.Cast(item);
            // Проверяем: это одежда, она промокла (> 0.5) и её можно выжать
            if (clothing && clothing.IsClothing() && clothing.GetWet() > 0.5 && clothing.CanBeWringed())
            {
                Print("[AN_NEKRASOV_82] Вещь " + clothing.GetType() + " слишком тяжелая от воды. Выжимаю.");
                
                bot.TakeItemToHands(clothing);
                bot.StartAction(ActionWringClothes); // Анимация выжимания
                
                // После выжимания возвращаем вещь на место
                return; // Делаем по одной вещи за раз
            }
        }
    }

    private bool CanStartWringing(ExpansionAIBase bot)
    {
        // Не выжимаем под открытым небом во время ливня (бессмысленно)
        return !bot.IsUnderRain() || bot.IsInsideBuilding();
    }
}

