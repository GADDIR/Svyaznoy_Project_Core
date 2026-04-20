/*
    УЗЕЛ 71.К: ИЕРАРХИЯ НОЖЕЙ
    Файл: NEKRASOV_Agro_Memory_11.c
    Связь: knives_hierarchy.md
    Назначение: Контроль использования колюще-режущего инструмента согласно рангам.
*/

modded class NEKRASOV_Agro_Memory
{
    // Ранги ножей из knives_hierarchy.md
    protected ref array<string> m_NEKRASOV_EliteKnives; // Ножи Чести
    protected ref array<string> m_NEKRASOV_UtilityKnives; // Рабочие ножи

    override void Init()
    {
        super.Init();
        m_NEKRASOV_EliteKnives = new array<string>;
        m_NEKRASOV_UtilityKnives = new array<string>;
        
        NEKRASOV_LoadKnifeHierarchy();
    }

    protected void NEKRASOV_LoadKnifeHierarchy()
    {
        // Ранг: Высший (Только для защиты или особых ритуалов)
        m_NEKRASOV_EliteKnives.Insert("CombatKnife");
        m_NEKRASOV_EliteKnives.Insert("HuntingKnife");

        // Ранг: Низший (Для быта и "грязи")
        m_NEKRASOV_UtilityKnives.Insert("KitchenKnife");
        m_NEKRASOV_UtilityKnives.Insert("StoneKnife");
    }

    // Логика: Проверка целевого использования (из knives_hierarchy.md)
    // Если элитный нож используется для вскрытия банок — штраф к Синхронизации
    void NEKRASOV_AuditKnifeUsage(ItemBase knife, string actionType)
    {
        if (m_NEKRASOV_EliteKnives.Find(knife.GetType()) != -1)
        {
            if (actionType == "OpenCan" || actionType == "Skinning")
            {
                // Нарушение иерархии ножей
                NEKRASOV_ReduceSyncByViolation("KNIFE_MISUSE");
            }
        }
    }

    // Рефлекс: Элитный нож нельзя принести в жертву (в отличие от Узла 7)
    override void NEKRASOV_EvaluateSacrifice(ItemBase sacrificeItem, string targetNode)
    {
        if (m_NEKRASOV_EliteKnives.Find(sacrificeItem.GetType()) != -1)
        {
            // Блокировка жертвы: Честь выше структуры
            return; 
        }
        
        super.NEKRASOV_EvaluateSacrifice(sacrificeItem, targetNode);
    }
}
