class TorchDryingSkill
{
    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot || !bot.IsAlive()) return;

        // 1. Условие: Низкая температура тела или сильная влажность одежды
        if (NeedsThermalSupport(bot))
        {
            HandleTorchThermal(bot);
        }
    }

    private void HandleTorchThermal(ExpansionAIBase bot)
    {
        ItemBase torch = ItemBase.Cast(bot.GetInventory().FindEntityInInventory("Torch"));
        if (!torch) return;

        // 2. Логика розжига, если факел в инвентаре потушен
        if (!torch.IsIgnited() && !bot.IsNearObject("FireplaceBase", 5.0))
        {
            PrepareAndLightTorch(bot, torch);
        }

        // 3. ЭФФЕКТ "ТЕПЛОВОГО КОКОНА" ПРИ БЕГЕ
        if (torch.IsIgnited())
        {
            if (bot.GetHumanInventory().GetEntityInHands() != torch)
            {
                bot.TakeItemToHands(torch);
            }

            // Бот понимает: пока он бежит с огнем, его HeatComfort не падает в критическую зону
            if (bot.GetNavigation().IsMoving())
            {
                Print("[AN_NEKRASOV_82] Бегу с факелом. Сохраняю тепло тела в движении.");
            }
        }
    }

    private bool NeedsThermalSupport(ExpansionAIBase bot)
    {
        // Срабатывает, если индикатор температуры стал синим или одежда мокрая > 30%
        return bot.GetStatHeatComfort().Get() < 0 || bot.GetStatWet().Get() > 0.3;
    }
}

