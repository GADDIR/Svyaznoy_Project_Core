class GateManagementSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Поиск ближайших ворот или калитки (Expansion Barrier/Gate или Fence)
        Object target = bot.GetNearestObject("Fence", 3.5);
        if (!target) target = bot.GetNearestObject("ExpansionBarrier", 3.5);

        if (target)
        {
            HandleGateLogic(bot, target);
        }
    }

    private void HandleGateLogic(ExpansionAIBase bot, Object gate)
    {
        Fence fence = Fence.Cast(gate);
        if (!fence) return;

        // ДИСЦИПЛИНА: Закрывать ворота сразу после прохода
        if (fence.IsOpened())
        {
            bot.StartAction(ActionCloseFence);
            Print("[AN_NEKRASOV_82] Закрываю ворота/калитку. Территория должна быть замкнута.");
        }

        // БЕЗОПАСНОСТЬ: Если на воротах есть замок (CodeLock) - проверить, закрыт ли он
        if (!fence.IsOpened() && !fence.IsLocked())
        {
            // Бот использует свой пароль 625224 для активации замка
            bot.StartAction(ActionLockFence); 
            Print("[AN_NEKRASOV_82] Проверил замок на воротах. Закрыто.");
        }
    }
}

