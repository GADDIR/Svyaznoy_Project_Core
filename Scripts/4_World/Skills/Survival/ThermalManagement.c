class ThermalManagementSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Бот промок (Wetness > 0.2) и рядом есть активный огонь
        if (IsWet(bot) && IsFireActive(bot))
        {
            TacticalDrying(bot);
        }
    }

    private void TacticalDrying(ExpansionAIBase bot)
    {
        // 2. Снимаем мокрые вещи и выжимаем их
        array<EntityAI> items = new array<EntityAI>;
        bot.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            if (item.IsClothing() && item.GetWet() > 0.1)
            {
                // Выжимаем, если это возможно
                bot.StartAction(ActionWringClothes); 
                
                // Снимаем и кладем у костра/печи
                bot.PredictiveDropEntity(item); 
                Print("[AN_NEKRASOV_82] Снял мокрую вещь " + item.GetType() + " для быстрой сушки.");
            }
        }

        // 3. Греем руки у огня, сохраняя бдительность
        if (!bot.IsActionRunning())
        {
            bot.StartAction(ActionWarmUp);
            Print("[AN_NEKRASOV_82] Греюсь у огня. Оружие наготове.");
        }
    }

    private bool IsFireActive(ExpansionAIBase bot)
    {
        // Бот видит любой источник: Костер, Печь, Камин, Бочка
        return bot.IsNearObject("FireplaceBase", 3.0) || bot.IsNearObject("BarrelHoles_ColorBase", 3.0);
    }

    private bool IsWet(ExpansionAIBase bot)
    {
        return bot.GetStatWet().Get() > 0.2;
    }
}

