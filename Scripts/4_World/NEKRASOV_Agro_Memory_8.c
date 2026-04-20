/*
    УЗЕЛ 80: СТАНДАРТИЗАЦИЯ И СОВМЕСТИМОСТЬ
    Файл: NEKRASOV_Agro_Memory_8.c
    Связь: mod_set_standard.md
    Назначение: Обеспечение работы ядра с внешними активами (Expansion, CF и др.)
*/

modded class NEKRASOV_Agro_Memory
{
    // Реестр одобренных модовых префиксов и классов
    protected ref array<string> m_NEKRASOV_StandardAssets;

    override void Init()
    {
        super.Init();
        m_NEKRASOV_StandardAssets = new array<string>;
        
        NEKRASOV_LoadStandardProtocols();
    }

    // Регистрация активов согласно mod_set_standard.md
    protected void NEKRASOV_LoadStandardProtocols()
    {
        // Прописываем классы из "Золотого состава" (Expansion, Dabs и т.д.)
        m_NEKRASOV_StandardAssets.Insert("ExpansionBaseBuilding"); 
        m_NEKRASOV_StandardAssets.Insert("StaticObj_Radio_Tower"); // Для Пути Связиста
    }

    // Логика: Валидация модового предмета на соответствие стандарту
    bool NEKRASOV_IsAssetStandard(EntityAI item)
    {
        if (!item) return false;
        
        string type = item.GetType();
        
        // Проверка: входит ли предмет в разрешенный "Мод-Сет"
        foreach (string standard : m_NEKRASOV_StandardAssets)
        {
            if (type.Contains(standard)) return true;
        }

        return false;
    }

    // Адаптация ресурсов (связь с resources_and_fire.md)
    // Повтор: Мы уже делали это в Кухне_5, но здесь — уровень Инфраструктуры
    float NEKRASOV_GetFuelEfficiency(ItemBase fuel)
    {
        // Если это дрова из Expansion или другого стандартного мода
        if (NEKRASOV_IsAssetStandard(fuel)) return 1.5; 
        return 1.0;
    }
}
