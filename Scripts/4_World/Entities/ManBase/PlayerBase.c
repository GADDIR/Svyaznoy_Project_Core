/**
 * ОБЪЕКТ: Алексей Николаевич Некрасов
 * СТАНДАРТ: NEKRASOV (MONOLITH 74/74)
 * ОПИСАНИЕ: Центральный узел связи биологии и памяти.
 */

modded class PlayerBase
{
    // --- СЕКТОР II: АРХИТЕКТУРА РАЗУМА ---
    ref NEKRASOV_Brain_Core m_NEKRASOV_Brain;
    ref NEKRASOV_Memory_Focus m_NEKRASOV_Focus;

    // --- ИНИЦИАЛИЗАЦИЯ СИСТЕМЫ ---
    override void Init()
    {
        super.Init();

        // Запуск биологического BIOS (Модуль №11)
        m_NEKRASOV_Brain = new NEKRASOV_Brain_Core(this);
        
        // Запуск Линзы Внимания (Модуль №13)
        m_NEKRASOV_Focus = new NEKRASOV_Memory_Focus(this);

        Print("[NEKRASOV] Синхронизация слоёв сознания завершена на 85%");
    }

    // --- СЕКТОР VII: РЕФЛЕКСИЯ (БОЙ - Модуль №73) ---
    override bool EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int componentIdx, string dmgZone, string skeletonComponent, float speedCoef)
    {
        bool result = super.EEHitBy(damageResult, damageType, source, componentIdx, skeletonComponent, speedCoef);

        // Вызов боевой рефлексии (Николай 1923 / Банов 2021)
        if (GetGame().IsServer() && m_NEKRASOV_Focus)
        {
            NEKRASOV_Combat_Trigger(damageResult);
        }

        return result;
    }

    // --- СЕКТОР VII: РЕФЛЕКСИЯ (МЕДИЦИНА И АГРО - Модули №72, №74) ---
    override void OnActionEndServer(ActionData action_data)
    {
        super.OnActionEndServer(action_data);

        if (!action_data || !action_data.m_Action) return;

        // Проверка на медицинское действие (Голос Анны 1928)
        if (action_data.m_Action.IsMedicalAction())
        {
            NEKRASOV_Medical_Trigger();
        }
        
        // Проверка на работу с землёй (Голос Анны 1928)
        if (action_data.m_Action.IsAgroAction()) // Метод IsAgroAction должен быть в базовом классе действий
        {
            NEKRASOV_Agro_Trigger();
        }
    }

    // --- СЛУЖЕБНЫЕ МЕТОДЫ МОНОЛИТА ---
    
    void NEKRASOV_Combat_Trigger(TotalDamageResult damage)
    {
        // Логика из NEKRASOV_Mumble_Combat.c
        // Здесь происходит переключение весов между 1923 и 2021
    }

    void NEKRASOV_Medical_Trigger()
    {
        // Логика из NEKRASOV_Mumble_Medical.c
        // Активация милосердия 1928
    }

    void NEKRASOV_Agro_Trigger()
    {
        // Логика из NEKRASOV_Mumble_Agro.c
        // Связь с почвой 1928
    }

    // Геттеры для связи с другими модулями из 74 позиций
    NEKRASOV_Memory_Focus NEKRASOV_GetFocus()
    {
        return m_NEKRASOV_Focus;
    }
}
