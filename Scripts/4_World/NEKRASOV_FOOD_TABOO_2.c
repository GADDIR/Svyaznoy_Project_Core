/*
    УЗЕЛ 75.К2: ТЕХНОЛОГИЧЕСКИЙ ЦИКЛ ПРИГОТОВЛЕНИЯ
    Файл: NEKRASOV_FOOD_TABOO_2.c
    Связь: agro_hub.md + PRT-ECON-REGISTRY.md
    Назначение: Логика обработки продуктов (ферментация, хранение, крафт).
*/

modded class NEKRASOV_FOOD_TABOO
{
    // Параметры техпроцесса "Умных бочек"
    protected float m_NEKRASOV_FermentationSpeed;
    protected int m_NEKRASOV_ActiveBarrelsCount;

    override void Init()
    {
        super.Init();
        m_NEKRASOV_FermentationSpeed = 1.0;
        m_NEKRASOV_ActiveBarrelsCount = 0;
    }

    // Логика: Контроль техпроцесса в радиусе Агро-Хаба
    // Если объект (бочка) находится в зоне Хаба, процесс идет быстрее/чище
    void NEKRASOV_UpdateFermentation(ItemBase barrel, float deltaT)
    {
        if (barrel.IsInherited(Barrel_ColorBase))
        {
            // Проверка условий из agro_hub.md: температура, закрыта ли крышка
            if (barrel.GetAnimationPhase("Lid") == 1) // Крышка закрыта
            {
                NEKRASOV_ProcessFerment(barrel, deltaT);
            }
        }
    }

    // Исполнение протокола: превращение "сырого" в "чистое" (по PRT-ECON)
    protected void NEKRASOV_ProcessFerment(ItemBase item, float deltaT)
    {
        // Здесь логика изменения состояния еды внутри бочки
        // Например: превращение овощей в "Квашеную капусту (Чисто)"
    }

    // Проверка пригодности тары для длительного хранения (Запрет ящиков)
    bool NEKRASOV_IsStorageCompliant(EntityAI container)
    {
        // Согласно PRT-ECON: запрет на хранение еды в определенных типах ящиков
        if (container.IsKindOf("WoodenLog")) return false;
        
        return true;
    }
}
