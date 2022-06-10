
namespace WindowsFormsApp1
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.btn_guangzhao = new System.Windows.Forms.Button();
            this.btn_shijian = new System.Windows.Forms.Button();
            this.btn_dianzu = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.panel1.SuspendLayout();
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
            this.splitContainer1.Panel1.Controls.Add(this.panel1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.btn_guangzhao);
            this.splitContainer1.Panel2.Controls.Add(this.btn_shijian);
            this.splitContainer1.Panel2.Controls.Add(this.btn_dianzu);
            this.splitContainer1.Size = new System.Drawing.Size(577, 505);
            this.splitContainer1.SplitterDistance = 103;
            this.splitContainer1.TabIndex = 0;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.ActiveCaption;
            this.panel1.Controls.Add(this.label1);
            this.panel1.Location = new System.Drawing.Point(-4, 1);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(585, 107);
            this.panel1.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 18F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label1.ForeColor = System.Drawing.SystemColors.ButtonHighlight;
            this.label1.Location = new System.Drawing.Point(4, -1);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(577, 103);
            this.label1.TabIndex = 1;
            this.label1.Text = "光敏电阻特性测量实验";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // btn_guangzhao
            // 
            this.btn_guangzhao.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_guangzhao.Location = new System.Drawing.Point(139, 133);
            this.btn_guangzhao.Name = "btn_guangzhao";
            this.btn_guangzhao.Size = new System.Drawing.Size(270, 53);
            this.btn_guangzhao.TabIndex = 2;
            this.btn_guangzhao.Text = "光照特性";
            this.btn_guangzhao.UseVisualStyleBackColor = true;
            this.btn_guangzhao.Click += new System.EventHandler(this.btn_guangzhao_Click);
            // 
            // btn_shijian
            // 
            this.btn_shijian.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_shijian.Location = new System.Drawing.Point(139, 289);
            this.btn_shijian.Name = "btn_shijian";
            this.btn_shijian.Size = new System.Drawing.Size(270, 53);
            this.btn_shijian.TabIndex = 1;
            this.btn_shijian.Text = "时间响应特性";
            this.btn_shijian.UseVisualStyleBackColor = true;
            this.btn_shijian.Click += new System.EventHandler(this.btn_shijian_Click);
            // 
            // btn_dianzu
            // 
            this.btn_dianzu.Font = new System.Drawing.Font("微软雅黑", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_dianzu.Location = new System.Drawing.Point(139, 55);
            this.btn_dianzu.Name = "btn_dianzu";
            this.btn_dianzu.Size = new System.Drawing.Size(270, 53);
            this.btn_dianzu.TabIndex = 0;
            this.btn_dianzu.Text = "亮暗电阻";
            this.btn_dianzu.UseVisualStyleBackColor = true;
            this.btn_dianzu.Click += new System.EventHandler(this.btn_dianzu_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(577, 505);
            this.Controls.Add(this.splitContainer1);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.Text = "光敏电阻特性测量实验";
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn_guangzhao;
        private System.Windows.Forms.Button btn_shijian;
        private System.Windows.Forms.Button btn_dianzu;
    }
}

