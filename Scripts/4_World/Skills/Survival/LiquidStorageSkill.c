class LiquidStorageSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Цикл перелива: из кастрюли (после готовки) в бутылки
        EntityAI cookingPot = bot.GetInventory().FindEntityInInventory("Pot");
        if (cookingPot && IsPotReady(cookingPot))
        {
            DistributeLiquids(bot, cookingPot);
        }
    }

    private void DistributeLiquids(ExpansionAIBase bot, EntityAI source)
    {
        // Бот ищет пустую тару для хранения
        ItemBase container = GetEmptyBottle(bot);
        if (!container) return;

        bot.TakeItemToHands(source);
        
        // Логика выбора типа жидкости:
        if (IsTea(source)) {
            Print("[AN_NEKRASOV_82] Переливаю целебный чай в бутылку про запас.");
        } else if (IsSoup(source)) {
            Print("[AN_NEKRASOV_82] Сохраняю питательный суп на завтра.");
        } else {
            Print("[AN_NEKRASOV_82] Заготавливаю кипяченую воду.");
        }

        bot.StartAction(ActionTransferLiquid); // Перелив
    }

    private bool IsPotReady(EntityAI pot) { return pot.GetTemperature() > 40 && pot.GetTemperature() < 90; }
    private bool IsTea(EntityAI pot) { return pot.GetInventory().FindAttachment(InventorySlots.DIRECT_COOKING_SLOT_1).IsInherited(CaninaBerry); }
    private bool IsSoup(EntityAI pot) { return pot.GetInventory().FindAttachment(InventorySlots.DIRECT_COOKING_SLOT_1).IsInherited(Meat_Base); }
}

