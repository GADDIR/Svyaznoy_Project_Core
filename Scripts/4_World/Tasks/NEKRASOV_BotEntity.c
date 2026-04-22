class NEKRASOV_BotEntity : PlayerBase
{
    // Тот самый менеджер, который мы написали
    protected ref NEKRASOV_TaskManager m_NekrasovManager;

    // Вызывается при создании бота на сервере
    override void DeferredInit()
    {
        super.DeferredInit();

        // Инициализируем мозги
        m_NekrasovManager = new NEKRASOV_TaskManager(this);
        
        Print("[NEKRASOV] Бот инициализирован и готов к командам.");
    }

    // Главный цикл обновлений бота
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        // Передаем управление менеджеру задач
        if (m_NekrasovManager)
        {
            m_NekrasovManager.OnUpdate(timeslice);
        }
    }

    // Функция, которую мы будем вызывать из чат-обработчика
    void RemoteControl(string command, string args = "")
    {
        Print("[NEKRASOV] Получена внешняя команда: " + command);
        m_NekrasovManager.Execute(command, args);
    }
}

