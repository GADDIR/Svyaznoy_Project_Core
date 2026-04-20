/*
    УЗЕЛ 75.К3: ЭКОНОМИЧЕСКИЙ ФИЛЬТР КУХНИ (PRT-ECON)
    Файл: NEKRASOV_FOOD_TABOO_3.c
    Назначение: Контроль лимитов хранения и правил перемещения активов NEKRASOV.
    Связь: PRT-ECON-REGISTRY.md
*/

modded class NEKRASOV_FOOD_TABOO
{
    // Реестр допустимых объемов (согласно лимитам PRT-ECON)
    protected int m_NEKRASOV_MaxFoodVolume;
    protected ref array<string> m_NEKRASOV_LogisticsRestricted;

    override void Init()
    {
        super.Init();
        
        m_NEKRASOV_MaxFoodVolume = 100; // Пример лимита из реестра
        m_NEKRASOV_LogisticsRestricted = new array<string>;
        
        NEKRASOV_LoadEconProtocols();
    }

    // Загрузка правил из PRT-ECON-REGISTRY.md
    protected void NEKRASOV_LoadEconProtocols()
    {
        // Предметы, которые запрещено перемещать в больших количествах (протокол скрытности)
        m_NEKRASOV_LogisticsRestricted.Insert("WoodenLog");
        m_NEKRASOV_LogisticsRestricted.Insert("Barrel_ColorBase");
    }

    // Проверка логистического узла: можно ли хранить здесь еду?
    bool NEKRASOV_AuditEconStorage(EntityAI container)
    {
        if (!container) return false;

        // Если контейнер — технический ящик (запрещенный реестром)
        if (m_NEKRASOV_LogisticsRestricted.Find(container.GetType()) != -1)
        {
            return false; // Нарушение: Еда в логистическом мусоре
        }

        return true;
    }

    // Интеграция с Агро-Хабом: отчет о пригодности запасов
    float NEKRASOV_GetEconHealthFactor()
    {
        // Возвращает коэффициент "чистоты" экономики кухни для Агро-модуля
        // Если кругом запрещенная тара — коэффициент падает
        return 1.0; 
    }
}

