class SocialSkill
{
    private float m_UpdateTimer = 0;
    private const float SCAN_INTERVAL = 2.0; // Сканируем окружение каждые 2 секунды

    void OnUpdate(ExpansionAIBase bot)
    {
        if (!bot) return;

        m_UpdateTimer += 0.1; // Условный шаг времени
        if (m_UpdateTimer < SCAN_INTERVAL) return;
        m_UpdateTimer = 0;

        PlayerBase nearestPlayer = GetNearestPlayer(bot, 15.0);
        if (nearestPlayer)
        {
            HandlePlayerEncounter(bot, nearestPlayer);
        }
    }

    private PlayerBase GetNearestPlayer(ExpansionAIBase bot, float range)
    {
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        
        foreach (Man man : players)
        {
            PlayerBase player = PlayerBase.Cast(man);
            if (player && player != bot && vector.Distance(bot.GetPosition(), player.GetPosition()) < range)
            {
                return player;
            }
        }
        return null;
    }

    private void HandlePlayerEncounter(ExpansionAIBase bot, PlayerBase player)
    {
        EntityAI itemInHands = player.GetHumanInventory().GetEntityInHands();

        // 1. Оценка угрозы: Оружие в руках игрока
        if (itemInHands && (itemInHands.IsInherited(Weapon) || itemInHands.IsInherited(MeleeWeapon_Base)))
        {
            // Некрасов пугается, перестает работать и пятится к Safe Zone
            bot.StartCommand_Action(DayZPlayerConstants.CMD_ACTIONFB_WALKBACK, DayZPlayerConstants.STANCE_ERECT);
            Print("[AN_NEKRASOV_82] Опасается вооруженного человека.");
        }
        // 2. Мирное приветствие
        else
        {
            // Если игрок близко (5м) и без оружия — машем рукой
            if (vector.Distance(bot.GetPosition(), player.GetPosition()) < 5.0)
            {
                bot.StartCommand_Action(DayZPlayerConstants.CMD_GESTUREFB_GREETING, DayZPlayerConstants.STANCE_ERECT);
            }
        }
    }
}

