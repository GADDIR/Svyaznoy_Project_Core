class BarkMiningSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Нужна кора (для розжига костра или крафта)
        if (NeedsBark(bot))
        {
            ExtractBark(bot);
        }
    }

    private bool NeedsBark(ExpansionAIBase bot)
    {
        // Проверяем: есть ли в инвентаре кора? Если нет - надо добыть.
        return bot.GetInventory().FindEntityInInventory("Bark_Oak") == null;
    }

    private void ExtractBark(ExpansionAIBase bot)
    {
        // 2. Поиск ножа
        ItemBase knife = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Knife_Base"));
        if (!knife) return;

        // 3. Поиск подходящего дерева
        Object tree = GetNearestTree(bot, 3.0);
        if (tree)
        {
            bot.TakeItemToHands(knife);
            // Запуск действия "Срезать кору"
            bot.StartAction(ActionCutBark);
            Print("[AN_NEKRASOV_82] Срезаю кору для розжига...");
        }
    }

    private Object GetNearestTree(ExpansionAIBase bot, float range)
    {
        // Поиск ближайшего дерева в радиусе
        return null; // В реальности здесь поиск объектов типа "Tree"
    }
}
