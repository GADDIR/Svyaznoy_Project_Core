class BaseProtectionSkill
{
    private string MAVERICK_PASS = "625224"; // Личный код Алексея Николаевича

    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Поиск развернутой палатки рядом
        TentBase tent = TentBase.Cast(bot.GetNearestObject("TentBase", 5.0));
        if (!tent) return;

        // 2. Логика Маскировки
        ApplyCamoNet(bot, tent);

        // 3. Логика Замка (CodeLock)
        ApplyCodeLock(bot, tent);
    }

    private void ApplyCamoNet(ExpansionAIBase bot, TentBase tent)
    {
        // Ищем маскировочную сеть в инвентаре
        ItemBase net = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("CamoNet"));
        
        // Если у палатки есть слот под сеть и он пуст
        if (net && tent.GetInventory().CanAddAttachment(net))
        {
            bot.TakeItemToHands(net);
            bot.StartAction(ActionAttach); 
            Print("[AN_NEKRASOV_82] Маскирую палатку сетью. Теперь она незаметна.");
        }
    }

    private void ApplyCodeLock(ExpansionAIBase bot, TentBase tent)
    {
        // Ищем CodeLock (из твоего списка модов)
        ItemBase lock = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("CodeLock"));
        
        // Проверяем, можно ли повесить замок на эту палатку/ворота
        if (lock && tent.CanAddCodeLock()) 
        {
            bot.TakeItemToHands(lock);
            
            // Установка замка с вводом конкретного пароля
            bot.SetActionCode(MAVERICK_PASS); 
            bot.StartAction(ActionAttachCodeLock);
            
            Print("[AN_NEKRASOV_82] Устанавливаю кодовый замок. Пароль забит в память.");
        }
    }
}

