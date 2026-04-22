class NEKRASOV_TaskManager
{
    protected PlayerBase m_NPC;
    protected ref NEKRASOV_TaskBase m_CurrentTask;
    protected ref map<string, ref NEKRASOV_TaskBase> m_AvailableTasks;

    void NEKRASOV_TaskManager(PlayerBase npc)
    {
        m_NPC = npc;
        m_AvailableTasks = new map<string, ref NEKRASOV_TaskBase>;
        RegisterTasks();
    }

    // Здесь мы регистрируем все файлы задач из твоего репозитория
    void RegisterTasks()
    {
        m_AvailableTasks.Insert("HARVEST", new NEKRASOV_TaskHarvest(m_NPC));
        m_AvailableTasks.Insert("FOLLOW", new NEKRASOV_TaskFollow(m_NPC));
        // Сюда будешь дописывать новые задачи по мере их создания
    }

    // Главная функция: запуск задачи по текстовому коду
    void Execute(string taskName, string params = "")
    {
        if (m_CurrentTask && m_CurrentTask.IsActive())
        {
            m_CurrentTask.OnCancel(); // Останавливаем старую задачу
        }

        NEKRASOV_TaskBase task = m_AvailableTasks.Get(taskName);
        if (task)
        {
            m_CurrentTask = task;
            m_CurrentTask.OnStart(params);
        }
        else
        {
            Print("[NEKRASOV] Ошибка: Задача " + taskName + " не найдена!");
        }
    }

    // Тик менеджера (вызывается из OnUpdate бота)
    void OnUpdate(float timeslice)
    {
        if (m_CurrentTask && m_CurrentTask.IsActive())
        {
            m_CurrentTask.OnUpdate(timeslice);
        }
    }
}
