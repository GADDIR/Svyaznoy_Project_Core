class CamoNetExpert
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Ищем масксеть в инвентаре
        ItemBase net = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("CamoNet"));
        if (!net) return;

        // 2. Ищем ближайшую палатку или навес (Shelter), где нет сетки
        TentBase tent = TentBase.Cast(bot.GetNearestObject("TentBase", 5.0));
        if (!tent) tent = TentBase.Cast(bot.GetNearestObject("ShelterBase", 5.0));

        if (tent && CanAttachNet(tent))
        {
            ApplyCamo(bot, tent, net);
        }
    }

    private void ApplyCamo(ExpansionAIBase bot, TentBase target, ItemBase net)
    {
        bot.TakeItemToHands(net);
        // Действие: Закрепить маскировочную сеть
        bot.StartAction(ActionAttach); 
        Print("[AN_NEKRASOV_82] Маскирую вход и стены. Теперь базу не найдут с воздуха.");
    }

    private bool CanAttachNet(TentBase tent)
    {
        // Проверяем, пуст ли слот под масксеть
        return tent.GetInventory().FindAttachment(InventorySlots.CAMONET) == null;
    }
}

