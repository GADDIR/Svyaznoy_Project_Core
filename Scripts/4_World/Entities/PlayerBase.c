modded class PlayerBase
{
    // Ссылка на контроллер разума NEKRASOV
    protected ref NEKRASOV_MaverickController m_NekrasovController;

    override void Init()
    {
        super.Init();

        // Работаем только на стороне сервера
        if (GetGame().IsServer())
        {
            // У NPC обычно нет Identity. Это хороший способ отличить их от игроков.
            if ( !GetIdentity() ) 
            {
                InitNekrasovAI();
            }
        }
    }

    void InitNekrasovAI()
    {
        Print("NEKRASOV AI: Подключение контроллера к телу...");
        m_NekrasovController = new NEKRASOV_MaverickController(this);
    }

    // Метод, который вызывается из чата (MissionServer)
    void ReceiveNekrasovCommand(string message)
    {
        if (m_NekrasovController)
        {
            m_NekrasovController.ProcessText(message);
        }
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);
        if (m_NekrasovController)
        {
            m_NekrasovController.OnUpdate(timeslice);
        }
    }
    
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
        if (m_NekrasovController)
        {
            Print("NEKRASOV AI: Связь разорвана. Носитель мертв.");
            m_NekrasovController = null; 
        }
    }
}
