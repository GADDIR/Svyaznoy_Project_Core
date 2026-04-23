class RuinedDisposalSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive() || bot.IsFighting()) return;

        // Регулярная проверка инвентаря на наличие "красного" брака
        PurgeRuinedItems(bot);
    }

    private void PurgeRuinedItems(ExpansionAIBase bot)
    {
        array<EntityAI> items = new array<EntityAI>;
        bot.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

        foreach (EntityAI item : items)
        {
            // Проверка на статус Ruined (HealthLevel == 4)
            if (item.GetHealthLevel() >= 4 || item.IsRuined())
            {
                // Исключение: Не выбрасываем квестовые вещи или паспорт, если они есть
                if (item.IsInherited(Passport_Base)) continue;

                Print("[AN_NEKRASOV_82] Обнаружен брак: " + item.GetType() + ". Выбрасываю.");
                
                // Если это магазин - вынимаем его из оружия перед сбросом
                if (item.IsInherited(Magazine)) {
                    bot.PredictiveDropEntity(item);
                } else {
                    bot.PredictiveDropEntity(item);
                }
            }
        }
    }
}

