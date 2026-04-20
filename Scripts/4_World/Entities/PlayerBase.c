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
            // Здесь мы можем идентифицировать Маверика. 
            // Например, по пресету персонажа или специальному флагу.
            // Пока сделаем проверку, что это не обычный игрок-человек
            if ( !GetIdentity() ) 
            {
                InitNekrasovAI();
            }
        }
    }

    // Метод активации "Чипа сознания"
    void InitNekrasovAI()
    {
        Print("NEKRASOV AI: Обнаружена биологическая оболочка. Подключение контроллера...");
        m_NekrasovController = new NEKRASOV_MaverickController(this);
    }

    // Главный тик жизни
    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        // Если мозг подключен — передаем ему управление в каждом кадре
        if (m_NekrasovController)
        {
            m_NekrasovController.OnUpdate(timeslice);
        }
    }
    
    // Важно: удаляем контроллер при смерти тела
    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
        if (m_NekrasovController)
        {
            Print("NEKRASOV AI: Биологическая смерть носителя. Отключение...");
            m_NekrasovController = null; 
        }
    }
}

