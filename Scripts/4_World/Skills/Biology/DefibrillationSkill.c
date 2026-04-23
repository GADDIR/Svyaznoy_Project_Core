class DefibrillationSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Поиск человека в глубоком обмороке в радиусе 2 метров
        CheckForCardiacArrest(bot);
    }

    private void CheckForCardiacArrest(ExpansionAIBase bot)
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man player : players)
        {
            if (player != bot && player.IsUnconscious() && vector.Distance(bot.GetPosition(), player.GetPosition()) < 2.0)
            {
                ItemBase defib = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Defibrillator"));
                if (defib && HasBattery(defib))
                {
                    UseDefibrillator(bot, player, defib);
                }
            }
        }
    }

    private void UseDefibrillator(ExpansionAIBase bot, Man target, ItemBase defib)
    {
        bot.TakeItemToHands(defib);
        
        // 1. Включить прибор
        if (!defib.GetCompEM().IsSwitchedOn())
        {
            bot.StartAction(ActionTurnOnWeaponLight); // Универсальное действие включения
        }

        // 2. Произвести разряд
        bot.StartAction(ActionDefibrilateTarget);
        Print("[AN_NEKRASOV_82] РАЗРЯД! Попытка запустить сердце выжившего.");
    }

    private bool HasBattery(ItemBase item)
    {
        return item.GetInventory().FindAttachment(InventorySlots.BATTERY) != null;
    }
}

