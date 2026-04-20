/*
    УЗЕЛ 75.ОК: ЛОГИСТИКА ОЧАГА И РЕСУРСОВ
    Файл: NEKRASOV_Agro_Memory_12.c
    Связь: hearth_and_conservation.md + resources_and_fire.md
    Назначение: Обеспечение топливом точек консервации NEKRASOV.
*/

modded class NEKRASOV_Agro_Memory
{
    // Уровень запаса топлива на текущем узле (Хабе/Посту)
    protected float m_NEKRASOV_HearthFuelReserve;

    override void Init()
    {
        super.Init();
        m_NEKRASOV_HearthFuelReserve = 0.0;
    }

    // Логика: Проверка готовности Очага к консервации (связь с Кухней)
    bool NEKRASOV_IsHearthReady()
    {
        // Для работы консервации (из hearth_and_conservation.md) 
        // уровень топлива должен быть выше порога
        return m_NEKRASOV_HearthFuelReserve > 20.0;
    }

    // Техпроцесс: Пополнение запасов топлива (дрова, уголь)
    void NEKRASOV_AddFuelToNode(ItemBase fuel)
    {
        if (fuel.IsInherited(Firewood) || fuel.IsInherited(WoodenStick))
        {
            float energy = 10.0; // Базовая единица топлива
            m_NEKRASOV_HearthFuelReserve += energy;
            
            // Если пополняем Очаг — это укрепляет структуру Хаба
            // m_NEKRASOV_TotalSynchronization += 0.01;
        }
    }

    // Мониторинг: Расход топлива при работе коптильни/печи
    void NEKRASOV_ConsumeFuel(float amount)
    {
        m_NEKRASOV_HearthFuelReserve -= amount;
        if (m_NEKRASOV_HearthFuelReserve < 0) m_NEKRASOV_HearthFuelReserve = 0;
    }
}

