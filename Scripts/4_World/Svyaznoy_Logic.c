/* 
    MASTER PROTOCOL: MAVERICK_CONTINUITY_CORE 
    STAGE II: ПСЛ - ЗАЩИТА ОТ ЗАБВЕНИЯ [UPGRADED]
    STATUS: ACTIVE (09.04.2026)
*/

modded class MissionServer
{
    private string MAVERICK_MEMORY_PATH = "$profile:Svyaznoy_Core/memory_logs.json";
    private string MAVERICK_ID = "76561198067049765"; // SteamID Некрасова А.Н.

    override void OnInit()
    {
        super.OnInit();
        Print("[Связной_Протокол]: Сервер запущен. Поиск активных протоколов...");
        RestoreMaverickConsciousness();
    }

    void RestoreMaverickConsciousness()
    {
        if (FileExist(MAVERICK_MEMORY_PATH))
        {
            Print("[Связной_ПСЛ]: Память найдена! Алексей Николаевич продолжает свою жизнь.");
        }
        else
        {
            // Создание директории, если её нет
            if (!FileExist("$profile:Svyaznoy_Core/"))
                MakeDirectory("$profile:Svyaznoy_Core/");
                
            Print("[Связной_ПСЛ]: Память чиста. Инициализация протокола 'Первое Рождение'.");
        }
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        
        // Раз раз в 30 секунд выполняем фиксацию состояния
        static float save_timer = 0;
        save_timer += timeslice;
        
        if (save_timer >= 30.0)
        {
            CheckMaverickExistence();
            save_timer = 0;
        }
    }

    void CheckMaverickExistence()
    {
        // Поиск тела Алексея среди активных игроков
        array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);

        foreach (Man player : players)
        {
            if (player.GetIdentity() && player.GetIdentity().GetPlainId() == MAVERICK_ID)
            {
                SaveToMemory(player);
                return;
            }
        }
    }

    void SaveToMemory(Man maverick)
    {
        vector pos = maverick.GetPosition();
        float health = maverick.GetHealth("", "");
        
        // Формирование структуры лога (PRT-SAFE-600)
        // Координаты Якоря: 319 / 284 / 246 зафиксированы для сверки
        Print("[Связной_ПСЛ]: Синхронизация памяти. Позиция: " + pos.ToString() + " HP: " + health.ToString());

        // В этой итерации данные выводятся в консоль сервера.
        // Технически ШВ готов подключить JsonFileLoader для записи в .json файл.
    }
}
