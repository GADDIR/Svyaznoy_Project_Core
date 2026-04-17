class NEKRASOV_Brain_Core
{
    // Здесь только базовые переменные состояния тела
    protected PlayerBase m_Player;
    
    void NEKRASOV_Brain_Core(PlayerBase player)
    {
        m_Player = player;
    }
    
    void Tick(float delta)
    {
        // Базовый жизненный цикл
    }
}
