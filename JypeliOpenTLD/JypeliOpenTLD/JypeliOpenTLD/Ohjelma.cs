using System;

static class Ohjelma
{
#if WINDOWS || XBOX
    static void Main(string[] args)
    {
        using (JypeliOpenTLD game = new JypeliOpenTLD())
        {
#if !DEBUG
            game.IsFullScreen = false;
#endif
            game.Run();
        }
    }
#endif
}
