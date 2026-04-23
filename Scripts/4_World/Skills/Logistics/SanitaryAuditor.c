class SanitaryAuditor
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || !bot.IsInSafeZone()) return;

        // Раз в час или при возвращении домой бот делает обход
        PerformStorageAudit(bot);
    }

    private void PerformStorageAudit(ExpansionAIBase bot)
    {
        // Список объектов для проверки
        array<Object> storageObjects = new array<Object>;
        GetGame().GetObjectsAtPosition3D(bot.GetPosition(), 5.0, storageObjects, null);

        foreach (Object obj : storageObjects)
        {
            EntityAI storage = EntityAI.Cast(obj);
            if (storage && IsStorage(storage))
            {
                CleanContainer(bot, storage);
            }
        }
    }

    private void CleanContainer(ExpansionAIBase bot, EntityAI container)
    {
        array<EntityAI> contents = new array<EntityAI>;
        container.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, contents);

        foreach (EntityAI item : contents)
        {
            // Условие удаления: Гниль, Разрушено (Ruined) или пустая бумага/коробки
            if (item.GetHealthLevel() >= 4 || item.IsRuined() || IsTrash(item))
            {
                bot.TakeEntityToHands(item);
                // Выносим мусор подальше от центра базы
                bot.PredictiveDropEntity(item); 
                Print("[AN_NEKRASOV_82] Выбросил мусор из хранилища: " + item.GetType());
            }
        }
    }

    private bool IsStorage(EntityAI obj) {
        return obj.IsInherited(TentBase) || obj.IsInherited(Barrel_ColorBase) || 
               obj.IsInherited(WoodenCrate) || obj.IsInherited(SeaChest) || 
               obj.GetType().Contains("Rack");
    }

    private bool IsTrash(EntityAI item) {
        return item.GetType() == "Paper" && !NeedsPaper(item); // Лишняя бумага - мусор
    }
}

