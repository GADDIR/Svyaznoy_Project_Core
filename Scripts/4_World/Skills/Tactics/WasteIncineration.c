class WasteIncineration
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Есть активный огонь и в инвентаре есть мусор
        Object fireplace = bot.GetNearestObject("FireplaceBase", 2.0);
        if (fireplace && IsIgnited(fireplace))
        {
            BurnTrash(bot, fireplace);
        }
    }

    private void BurnTrash(ExpansionAIBase bot, Object source)
    {
        array<EntityAI> items = new array<EntityAI>;
        bot.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            if (IsTrash(item))
            {
                // Закидываем мусор в топку
                bot.TakeItemToHands(item);
                bot.StartAction(ActionAttach); 
                Print("[AN_NEKRASOV_82] Сжигаю улики (" + item.GetType() + ") в огне.");
                
                // В DayZ вещи в огне быстро уничтожаются
            }
        }
    }

    private bool IsTrash(EntityAI item)
    {
        string type = item.GetType();
        // Список сжигаемого мусора: пустые банки, кости, бумага, руины одежды, кочерыжки
        return type.Contains("FoodCan_Empty") || type == "Bone" || type == "Paper" || 
               item.IsRuined() || type.Contains("AppleCore");
    }

    private bool IsIgnited(Object source) { /* Проверка наличия пламени */ return true; }
}

