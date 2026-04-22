modded class MissionServer
{
    override void OnChatMessage(int channel, string sender_name, string text)
    {
        super.OnChatMessage(channel, sender_name, text);

        string tmp = text;
        tmp.ToLower();

        // Если в чате упомянули ИИ
        if (tmp.Contains("некрасов"))
        {
            array<Man> players = new array<Man>;
            GetGame().GetPlayers(players);

            foreach (Man p : players)
            {
                PlayerBase pb = PlayerBase.Cast(p);
                if (pb)
                {
                    // Отправляем команду в PlayerBase
                    pb.ReceiveNekrasovCommand(text);
                }
            }
        }
    }
}
