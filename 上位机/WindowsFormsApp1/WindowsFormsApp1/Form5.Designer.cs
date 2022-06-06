
namespace WindowsFormsApp1
{
    partial class Form5
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.fanhui = new System.Windows.Forms.Button();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            this.port = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.button2 = new System.Windows.Forms.Button();
            this.button5 = new System.Windows.Forms.Button();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.listBox2 = new System.Windows.Forms.ListBox();
            this.dianzuzhi_input = new System.Windows.Forms.Button();
            this.btn_setlight = new System.Windows.Forms.Button();
            this.btn_setcolor = new System.Windows.Forms.Button();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.comboBox3 = new System.Windows.Forms.ComboBox();
            this.LED_zhaodu = new System.Windows.Forms.Label();
            this.LED_color = new System.Windows.Forms.Label();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.SuspendLayout();
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 0);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.fanhui);
            this.splitContainer1.Panel1.Controls.Add(this.comboBox2);
            this.splitContainer1.Panel1.Controls.Add(this.port);
            this.splitContainer1.Panel1.Controls.Add(this.label1);
            this.splitContainer1.Panel1.Controls.Add(this.comboBox1);
            this.splitContainer1.Panel1.Controls.Add(this.label2);
            this.splitContainer1.Panel1.Paint += new System.Windows.Forms.PaintEventHandler(this.splitContainer1_Panel1_Paint);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.button2);
            this.splitContainer1.Panel2.Controls.Add(this.button5);
            this.splitContainer1.Panel2.Controls.Add(this.chart1);
            this.splitContainer1.Panel2.Controls.Add(this.listBox2);
            this.splitContainer1.Panel2.Controls.Add(this.dianzuzhi_input);
            this.splitContainer1.Panel2.Controls.Add(this.btn_setlight);
            this.splitContainer1.Panel2.Controls.Add(this.btn_setcolor);
            this.splitContainer1.Panel2.Controls.Add(this.numericUpDown1);
            this.splitContainer1.Panel2.Controls.Add(this.comboBox3);
            this.splitContainer1.Panel2.Controls.Add(this.LED_zhaodu);
            this.splitContainer1.Panel2.Controls.Add(this.LED_color);
            this.splitContainer1.Size = new System.Drawing.Size(790, 667);
            this.splitContainer1.SplitterDistance = 84;
            this.splitContainer1.TabIndex = 0;
            // 
            // fanhui
            // 
            this.fanhui.Location = new System.Drawing.Point(651, 29);
            this.fanhui.Name = "fanhui";
            this.fanhui.Size = new System.Drawing.Size(106, 29);
            this.fanhui.TabIndex = 30;
            this.fanhui.Text = "返回主页";
            this.fanhui.UseVisualStyleBackColor = true;
            this.fanhui.Click += new System.EventHandler(this.fanhui_Click);
            // 
            // comboBox2
            // 
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "115200"});
            this.comboBox2.Location = new System.Drawing.Point(320, 32);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(137, 23);
            this.comboBox2.TabIndex = 28;
            // 
            // port
            // 
            this.port.Location = new System.Drawing.Point(514, 29);
            this.port.Name = "port";
            this.port.Size = new System.Drawing.Size(105, 29);
            this.port.TabIndex = 29;
            this.port.Text = "打开串口";
            this.port.UseVisualStyleBackColor = true;
            this.port.Click += new System.EventHandler(this.port_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(17, 36);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(52, 15);
            this.label1.TabIndex = 25;
            this.label1.Text = "串口号";
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(84, 32);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(131, 23);
            this.comboBox1.TabIndex = 26;
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.comboBox1_SelectedIndexChanged);
            this.comboBox1.MouseClick += new System.Windows.Forms.MouseEventHandler(this.comboBox1_MouseClick);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(252, 36);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(52, 15);
            this.label2.TabIndex = 27;
            this.label2.Text = "波特率";
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(72, 523);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(106, 27);
            this.button2.TabIndex = 47;
            this.button2.Text = "导入数据库";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(291, 523);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(106, 27);
            this.button5.TabIndex = 46;
            this.button5.Text = "导出EXCEL";
            this.button5.UseVisualStyleBackColor = true;
            // 
            // chart1
            // 
            chartArea1.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea1);
            this.chart1.Location = new System.Drawing.Point(26, 160);
            this.chart1.Name = "chart1";
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series1.Name = "Series1";
            this.chart1.Series.Add(series1);
            this.chart1.Size = new System.Drawing.Size(380, 337);
            this.chart1.TabIndex = 45;
            this.chart1.Text = "chart1";
            this.chart1.Click += new System.EventHandler(this.chart1_Click);
            // 
            // listBox2
            // 
            this.listBox2.FormattingEnabled = true;
            this.listBox2.ItemHeight = 15;
            this.listBox2.Location = new System.Drawing.Point(442, 21);
            this.listBox2.Name = "listBox2";
            this.listBox2.Size = new System.Drawing.Size(324, 529);
            this.listBox2.TabIndex = 44;
            // 
            // dianzuzhi_input
            // 
            this.dianzuzhi_input.Location = new System.Drawing.Point(126, 117);
            this.dianzuzhi_input.Name = "dianzuzhi_input";
            this.dianzuzhi_input.Size = new System.Drawing.Size(151, 23);
            this.dianzuzhi_input.TabIndex = 43;
            this.dianzuzhi_input.Text = "开始测量";
            this.dianzuzhi_input.UseVisualStyleBackColor = true;
            // 
            // btn_setlight
            // 
            this.btn_setlight.Location = new System.Drawing.Point(305, 72);
            this.btn_setlight.Name = "btn_setlight";
            this.btn_setlight.Size = new System.Drawing.Size(92, 23);
            this.btn_setlight.TabIndex = 42;
            this.btn_setlight.Text = "设置";
            this.btn_setlight.UseVisualStyleBackColor = true;
            // 
            // btn_setcolor
            // 
            this.btn_setcolor.Location = new System.Drawing.Point(305, 32);
            this.btn_setcolor.Name = "btn_setcolor";
            this.btn_setcolor.Size = new System.Drawing.Size(92, 23);
            this.btn_setcolor.TabIndex = 41;
            this.btn_setcolor.Text = "设置";
            this.btn_setcolor.UseVisualStyleBackColor = true;
            this.btn_setcolor.Click += new System.EventHandler(this.btn_setcolor_Click);
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(90, 67);
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(201, 25);
            this.numericUpDown1.TabIndex = 39;
            // 
            // comboBox3
            // 
            this.comboBox3.FormattingEnabled = true;
            this.comboBox3.Items.AddRange(new object[] {
            "关闭",
            "紫灯",
            "蓝灯",
            "绿灯",
            "黄绿灯",
            "黄灯",
            "橘灯",
            "红灯",
            "白灯"});
            this.comboBox3.Location = new System.Drawing.Point(90, 31);
            this.comboBox3.Name = "comboBox3";
            this.comboBox3.Size = new System.Drawing.Size(201, 23);
            this.comboBox3.TabIndex = 38;
            this.comboBox3.Text = "关闭";
            // 
            // LED_zhaodu
            // 
            this.LED_zhaodu.AutoSize = true;
            this.LED_zhaodu.Location = new System.Drawing.Point(23, 72);
            this.LED_zhaodu.Name = "LED_zhaodu";
            this.LED_zhaodu.Size = new System.Drawing.Size(52, 15);
            this.LED_zhaodu.TabIndex = 36;
            this.LED_zhaodu.Text = "光照度";
            // 
            // LED_color
            // 
            this.LED_color.AutoSize = true;
            this.LED_color.Location = new System.Drawing.Point(14, 35);
            this.LED_color.Name = "LED_color";
            this.LED_color.Size = new System.Drawing.Size(61, 15);
            this.LED_color.TabIndex = 35;
            this.LED_color.Text = "LED颜色";
            // 
            // Form5
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(790, 667);
            this.Controls.Add(this.splitContainer1);
            this.Name = "Form5";
            this.Text = "时间响应特性";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form5_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form5_FormClosed);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel1.PerformLayout();
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Button fanhui;
        private System.Windows.Forms.ComboBox comboBox2;
        private System.Windows.Forms.Button port;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button5;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.ListBox listBox2;
        private System.Windows.Forms.Button dianzuzhi_input;
        private System.Windows.Forms.Button btn_setlight;
        private System.Windows.Forms.Button btn_setcolor;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.ComboBox comboBox3;
        private System.Windows.Forms.Label LED_zhaodu;
        private System.Windows.Forms.Label LED_color;
        private System.IO.Ports.SerialPort serialPort1;
    }
}