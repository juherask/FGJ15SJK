using System;
using System.Collections.Generic;
using Jypeli;
using Microsoft.Xna.Framework.Graphics;
using clrmotld;
using Jypeli.Widgets;

public class JypeliOpenTLD : PhysicsGame
{
    const bool DO_CAPTURE = true;
    const int BOX_SIZE = 80;
    // Processing accuracy: 1 for full resolution (640,480), 2 for half resolution (320x240), 4 for quarter resiolution (160x120)
    const int SIZE_DIVISOR = 4; 
    const double FPS_TARGET = 10; // how high can you go depends on your hardware.

    VideoCapture webcam;
    MOTLD tracker;

    GameObject preview;    
    GameObject crosshair;
    bool tracking = false;

    DoubleMeter fps;
    int processedFrames;
    Time lastTick;


    public override void Begin()
    {
        SetWindowSize(800, 600);

        PhoneBackButton.Listen(ConfirmExit, "Lopeta peli");
        Keyboard.Listen(Key.Escape, ButtonState.Pressed, ConfirmExit, "Lopeta peli");
        Keyboard.Listen(Key.I, ButtonState.Pressed, InitTracker, "Lopeta peli");

        if (DO_CAPTURE)
        {
            InitCamera();
        }

        preview = new GameObject(VideoCapture.Width, VideoCapture.Height);
        preview.Color = Color.Black;
        Add(preview);

        int[][] boxpieces = 
        {
            new int[] {1,BOX_SIZE,BOX_SIZE/2,0},
            new int[] {1,BOX_SIZE,-BOX_SIZE/2,0},
            new int[] {BOX_SIZE,1,0, BOX_SIZE/2},
            new int[] {BOX_SIZE,1,0, -BOX_SIZE/2}
        };
        crosshair = new GameObject(BOX_SIZE, BOX_SIZE);
        crosshair.Color = Color.Transparent;
        foreach (var bp in boxpieces)
	    {
		    GameObject bbox = new GameObject(bp[0], bp[1]);
            bbox.Position = new Vector(bp[2], bp[3]);
            bbox.Color = Color.Red;
            crosshair.Add(bbox);
	    }
        Add(crosshair, 1);

        CreateFpsIndicator();
    }

    void CreateFpsIndicator()
    {
        lastTick = Game.Time;
        fps = new DoubleMeter(0.0);
        Label timeDisplay = new Label("fps");
        timeDisplay.TextColor = Color.White;
        timeDisplay.DecimalPlaces = 1;
        timeDisplay.Y = Screen.Height/2 - 80;
        timeDisplay.BindTo(fps);
        Add(timeDisplay);
    }

    private void InitCamera()
    {
        Image buffer = new Image(VideoCapture.Width, VideoCapture.Height, Color.Black);
        webcam = new VideoCapture(Game.GraphicsDevice);

        Timer.SingleShot(3.0, () =>
        {
            Timer updateFrame = new Timer();
            updateFrame.Interval = 1.0 / FPS_TARGET;
            updateFrame.Timeout += ProcessFrame;
            updateFrame.Start();
        });
    }

    protected override void OnExiting(object sender, EventArgs args)
    {
        base.OnExiting(sender, args);
        preview.Destroy();
        if (DO_CAPTURE)
        {
            webcam.Dispose();
        }
    }
    protected override void Update(Time time)
    {
        base.Update(time);

        double elapsed = time.SinceStartOfGame.TotalSeconds-lastTick.SinceStartOfGame.TotalSeconds;
        if (elapsed > 3.0)
        {
            fps.Value = processedFrames / elapsed;
            processedFrames = 0;
            lastTick = time;
        }
    }

    void ProcessFrame()
    {
        if (!preview.IsDestroyed)
        {
            Image jypeliBuffer = new Image(webcam.Frame);
            preview.Image = jypeliBuffer;

            if (tracking)
            {
                byte[] buffer = null;
                if (SIZE_DIVISOR == 1)
                    buffer = webcam.Grayscale;
                else if (SIZE_DIVISOR==2)
                    buffer = webcam.HalfGrayscale;
                else if (SIZE_DIVISOR == 4)
                    buffer = webcam.QuarterGrayscale;

                tracker.ProcessFrame(buffer, false);
                if (tracker.IsTrackingOk())
                {
                    crosshair.IsVisible = true;
                    int cx, cy;
                    tracker.GetObjectPosition(out cx, out cy);
                    // TODO: Write using preview and crosshair and their position and size
                    crosshair.Position = new Vector(-VideoCapture.Width / 2 + cx * SIZE_DIVISOR, VideoCapture.Height / 2 - cy * SIZE_DIVISOR);
                }
                else
                {
                    crosshair.IsVisible = false;
                }
            }
            processedFrames++;
        }
    }

    void InitTracker()
    {
        if (!tracking && DO_CAPTURE)
        {
            tracker = new MOTLD();
            tracker.Init(640 / SIZE_DIVISOR, 480 / SIZE_DIVISOR);

            byte[] buffer = null;
            if (SIZE_DIVISOR == 1)
                buffer = webcam.Grayscale;
            else if (SIZE_DIVISOR == 2)
                buffer = webcam.HalfGrayscale;
            else if (SIZE_DIVISOR == 4)
                buffer = webcam.QuarterGrayscale;
            tracker.ProcessFrame(buffer, false);

            // This set the tracked object
            tracker.AddObjectBox(
                // TODO: Write using preview and crosshair and their position and size
                (VideoCapture.Width / 2 - BOX_SIZE / 2) / SIZE_DIVISOR,
                (VideoCapture.Height / 2 - BOX_SIZE / 2) / SIZE_DIVISOR,
                (VideoCapture.Width / 2 + BOX_SIZE / 2) / SIZE_DIVISOR,
                (VideoCapture.Height / 2 + BOX_SIZE / 2) / SIZE_DIVISOR);

            crosshair.Destroy();
            crosshair = new GameObject(20, 20, Shape.Circle);
            crosshair.Color = Color.Red;
            crosshair.IsVisible = false;
            Add(crosshair, 1);
            
            tracking = true;
        }
    }
}
