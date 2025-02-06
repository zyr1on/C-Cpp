public  class MainForm  : Form
{
    private int x = 400;
    private int y = 300; 
    private int speedX = -9;
    private int speedY = -9;
    private const int circleRadius = 25;
	
    public MainForm ()
    {
        this.Text = "Bounce Ball";
        this.ClientSize = new Size(800, 600);
        this.BackColor = Color.FromArgb(51, 77, 77);
		
        this.Paint += (sender, e) =>
        {
            Graphics g = e.Graphics;
            
            Brush brush = new SolidBrush(Color.Red);
            g.FillEllipse(brush, x, y, circleRadius * 2, circleRadius * 2);
        };

        System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
        timer.Interval = 30;
        timer.Tick += (sender, e) =>
        {
		
            x += speedX;
            y += speedY;
            if (x + circleRadius * 2 > this.ClientSize.Width || x < 0)
                speedX = -speedX; 
            if (y + circleRadius * 2 > this.ClientSize.Height || y < 0)
                speedY = -speedY; 
            
            this.Invalidate();
        };
        timer.Start();
    }
}
static class Program
{
    [STAThread]
    static void Main()
    {
        ApplicationConfiguration.Initialize();
        Application.Run(new MainForm());
    }    
}
// total 43 lines
