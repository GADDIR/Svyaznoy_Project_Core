class TacticalPrepSkill
{
    private const float SCAN_RANGE = 200.0; // Дистанция обнаружения угрозы

    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // Если бот готов начать "опасное" действие (разделку, установку сети, крафт укрытия)
        if (bot.IsPlanningAction())
        {
            PerformTacticalScan(bot);
        }
    }

    private void PerformTacticalScan(ExpansionAIBase bot)
    {
        // 1. Принять скрытную позу (Prone / Корточки)
        bot.StartCommand_Action(DayZPlayerConstants.CMD_ACTIONFB_PRONE, DayZPlayerConstants.STANCE_PRONE);
        Print("[AN_NEKRASOV_82] Ложусь для скрытного осмотра перед работой.");

        // 2. Осмотр на 360 градусов (сканирование на игроков и зомби)
        if (IsAreaSafe(bot))
        {
            Print("[AN_NEKRASOV_82] Чисто. Приступаю к работе.");
            bot.OnTacticalScanComplete(); // Разрешение на выполнение основного действия
        }
        else
        {
            Print("[AN_NEKRASOV_82] Обнаружена угроза! Отмена работ, ухожу в укрытие.");
            bot.CancelAllActions();
            bot.GetNavigation().SetTarget(bot.GetSafeZonePos(), ExpansionHAL_Mode.SPRINT);
        }
    }

    private bool IsAreaSafe(ExpansionAIBase bot)
    {
        // Поиск угроз в радиусе SCAN_RANGE
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        foreach (Man p : players)
        {
            if (p != bot && vector.Distance(bot.GetPosition(), p.GetPosition()) < SCAN_RANGE)
                return false; // Игрок рядом
        }
        return true;
    }
}

