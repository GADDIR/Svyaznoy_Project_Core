class NEKRASOV_TaskBase
{
    protected PlayerBase m_NPC;        // Ссылка на самого бота
    protected bool m_IsActive;        // Статус: выполняется ли задача сейчас
    protected float m_Timeout;        // Таймер, чтобы бот не «завис» навсегда

    void NEKRASOV_TaskBase(PlayerBase npc)
    {
        m_NPC = npc;
        m_IsActive = false;
    }

    // Метод, который вызывает Нейросеть (через посредника)
    void OnStart(string params = "")
    {
        m_IsActive = true;
        m_Timeout = 0;
        Print("[NEKRASOV AI] Задача запущена: " + this.ClassName());
    }

    // Основной цикл задачи (срабатывает каждый тик сервера)
    void OnUpdate(float timeslice)
    {
        if (!m_IsActive) return;

        m_Timeout += timeslice;
        
        // Предохранитель: если задача длится больше 5 минут — отменяем
        if (m_Timeout > 300) 
        {
            OnCancel();
        }
    }

    // Что делать, если задачу нужно прервать
    void OnCancel()
    {
        m_IsActive = false;
        Print("[NEKRASOV AI] Задача прервана: " + this.ClassName());
    }

    // Что делать, когда всё успешно выполнено
    void OnComplete()
    {
        m_IsActive = false;
        Print("[NEKRASOV AI] Задача завершена: " + this.ClassName());
    }

    bool IsActive() { return m_IsActive; }
}
