class ItemSalvageSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        CheckForSalvage(bot);
    }

    private void CheckForSalvage(ExpansionAIBase bot)
    {
        array<EntityAI> items = new array<EntityAI>;
        bot.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            if (item.IsRuined() && item.GetInventory())
            {
                // 1. Спасаем вложения (обвесы, магазины, батарейки)
                SalvageAttachments(bot, item);
                
                // 2. Опустошаем карманы (Cargo)
                SalvageCargo(bot, item);

                // 3. Только если вещь пуста - разрешаем навыку RuinedDisposal её выкинуть
                Print("[AN_NEKRASOV_82] Разбираю сломанную вещь " + item.GetType() + " перед утилизацией.");
            }
        }
    }

    private void SalvageAttachments(ExpansionAIBase bot, EntityAI ruinedItem)
    {
        for (int i = 0; i < ruinedItem.GetInventory().AttachmentCount(); i++)
        {
            EntityAI attachment = ruinedItem.GetInventory().GetAttachmentFromIndex(i);
            if (attachment && !attachment.IsRuined())
            {
                bot.TakeEntityToInventory(InventoryMode.PREDICTIVE, attachment);
                Print("[AN_NEKRASOV_82] Спас модуль: " + attachment.GetType());
            }
        }
    }

    private void SalvageCargo(ExpansionAIBase bot, EntityAI ruinedItem)
    {
        // Перенос всех вещей из внутреннего хранилища в основной инвентарь бота
    }
    }

