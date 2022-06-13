using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btn_dianzu_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form2 f2 = new Form2();
            f2.Owner = this;
            f2.Show();
        }

        private void btn_guangzhao_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form3 f3 = new Form3();
            f3.Owner = this;
            f3.Show();
        }

      

        private void btn_shijian_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form5 f5 = new Form5();
            f5.Owner = this;
            f5.Show();
        }

        private void label2_Click(object sender, EventArgs e)
        {
            MessageBox.Show("这是光电系统集成课程的上位机程序" + "\r\n" + "仅适用于本课题的光敏电阻特性测量" + "\r\n");
        }
    }
}
