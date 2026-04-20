/*
    УЗЕЛ 77.F: ПОЛЕВОЕ ОБСЛУЖИВАНИЕ И СТАБИЛИЗАЦИЯ
    Файл: NEKRASOV_Agro_Memory_14.c
    Связь: field_maintenance.md
    Назначение: Временный ремонт и поддержка оборудования вне Хаба.
*/

modded class NEKRASOV_Agro_Memory
{
    // Множитель деградации при полевом ремонте
    protected float m_NEKRASOV_FieldRepairQuality;

    override void Init()
    {
        super.Init();
        m_NEKRASOV_FieldRepairQuality = 0.6; // Полевой ремонт менее эффективен, чем в мастерской
    }

    // Логика: Быстрая стабилизация (изолента, проволока)
    // Согласно field_maintenance.md: это временная мера, износ ускорится
    void NEKRASOV_ApplyFieldFix(ItemBase item, ItemBase repairKit)
    {
        if (!item || !repairKit) return;

        // Полевой ремонт возможен для кабелей, антенн и раций
        if (item.IsInherited(Transmitter_Base) || item.IsInherited(ItemTransmitter))
        {
            float boost = 15.0 * m_NEKRASOV_FieldRepairQuality;
            item.AddHealth("", "Health", boost);
            
            // Штраф: ускорение будущей деградации (программная метка "Полевой ремонт")
            NEKRASOV_MarkAsFieldRepaired(item);
        }
    }

    // Рефлекс: Проверка пригодности инструмента для полевых нужд
    // Нож из Узла 11 может быть использован для зачистки проводов
    bool NEKRASOV_CanUseKnifeForTech(ItemBase knife)
    {
        // Только UtilityKnives разрешены для тех-работ согласно иерархии
        return m_NEKRASOV_UtilityKnives.Find(knife.GetType()) != -1;
    }

    protected void NEKRASOV_MarkAsFieldRepaired(ItemBase item)
    {
        // Логика пометки предмета для последующей дефектовки в Мастерской (_5.c)
    }
}
