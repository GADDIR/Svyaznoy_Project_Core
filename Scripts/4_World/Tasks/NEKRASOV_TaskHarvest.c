class NEKRASOV_TaskHarvest : NEKRASOV_TaskBase
{
    protected Object m_TargetPlot;

    override void OnStart(string params = "")
    {
        super.OnStart(params);
        
        // 1. Ищем ближайший огород в радиусе 30 метров
        m_TargetPlot = GetNearestGardenPlot();

        if (m_TargetPlot)
        {
            Print("[NEKRASOV] Огород найден! Иду к цели.");
            // 2. Даем команду ИИ двигаться к объекту
            // Используем навигацию (предполагаем наличие базового AI компонента)
            m_NPC.GetInputController().OverrideMovementSpeed(true, 2.0); // Бег
            m_NPC.GetCommand_Move().SetTargetLocation(m_TargetPlot.GetPosition()); 
        }
        else
        {
            Print("[NEKRASOV] Огородов поблизости нет.");
            OnCancel();
        }
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        if (!m_IsActive || !m_TargetPlot) return;

        float distance = vector.Distance(m_NPC.GetPosition(), m_TargetPlot.GetPosition());

        // 3. Если подошли вплотную (менее 1.5 метров)
        if (distance < 1.5)
        {
            PerformHarvest();
        }
    }

    protected void PerformHarvest()
    {
        Print("[NEKRASOV] Начинаю сбор урожая...");
        
        // Запуск анимации (например, приседание или сбор)
        m_NPC.StartCommand_Action(DayZPlayerConstants.CMD_ACTIONFB_INTERACT, DayZPlayerConstants.STANCEMASK_CROUCH);
        
        // Здесь логика удаления объектов с грядки
        // GetGame().ObjectDelete(m_TargetPlot); // Самый простой вариант - "сожрать" весь огород
        
        OnComplete();
    }

    protected Object GetNearestGardenPlot()
    {
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition(m_NPC.GetPosition(), 30.0, objects, null);

        for (int i = 0; i < objects.Count(); i++)
        {
            if (objects[i].IsInherited(GardenPlot)) return objects[i];
        }
        return null;
    }
}
