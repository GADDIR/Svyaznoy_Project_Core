class AmmoUnboxingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // 1. Ищем любую запечатанную коробку патронов (Box_...)
        ItemBase ammoBox = GetAmmoBoxInInventory(bot);
        
        if (ammoBox)
        {
            UnpackAmmo(bot, ammoBox);
        }
    }

    private void UnpackAmmo(ExpansionAIBase bot, ItemBase box)
    {
        // Для распаковки руки должны быть свободны или в них должна быть коробка
        if (bot.GetHumanInventory().CanAddEntityInHands(box))
        {
            bot.TakeItemToHands(box);
            // Логика DayZ: Распаковать коробку (ActionUnpackBox)
            bot.StartAction(ActionUnpackBox); 
            Print("[AN_NEKRASOV_82] Распаковываю коробку: " + box.GetType() + ". Готовлю БК.");
        }
    }

    private ItemBase GetAmmoBoxInInventory(ExpansionAIBase bot)
    {
        // Поиск предметов с префиксом "AmmoBox_" или "Box_" (22LR, 9x19, 380 и т.д.)
        return ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Ammostack_Base")); 
        // В реальности — фильтр по типам коробок
    }
}

