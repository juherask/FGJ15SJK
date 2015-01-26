using System;
using System.Collections.Generic;
using Jypeli;
using Microsoft.Xna.Framework.Graphics;


public class JypeliOpenTLD : PhysicsGame
{
    VideoCapture webcam;
    GameObject preview;

    public override void Begin()
    {
        // TODO: Kirjoita ohjelmakoodisi tähän

        PhoneBackButton.Listen(ConfirmExit, "Lopeta peli");
        Keyboard.Listen(Key.Escape, ButtonState.Pressed, ConfirmExit, "Lopeta peli");

        Image buffer = new Image(640, 480, Color.Black);
        webcam = new VideoCapture(Game.GraphicsDevice);

        Timer.SingleShot(5.0, () =>
        {
            Timer updateFrame = new Timer();
            updateFrame.Interval = 0.1;
            updateFrame.Timeout += UpdatePreview;
            updateFrame.Start();
        });

        preview = new GameObject(640, 480);
        Add(preview);
    }

    protected override void Update(Time time)
    {
        base.Update(time);

        preview.Position = Mouse.PositionOnScreen;
    }

    void UpdatePreview()
    {
        Image buffer = new Image(webcam.Frame);
        preview.Image = buffer;
    }
    
}
