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
    public partial class Form4 : Form
    {
        public Form4()
        {
            InitializeComponent();
        }

        private void Form4_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.Owner.Show();
        }

        private void comboBox1_MouseClick(object sender, MouseEventArgs e)
        {
            string[] ports = System.IO.Ports.SerialPort.GetPortNames();
            comboBox1.DataSource = ports;
        }

        private void port_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen == false)
            {
                this.serialPort1.PortName = comboBox1.Text;
                this.serialPort1.BaudRate = int.Parse(comboBox2.Text);
                serialPort1.Open();
                this.port.Text = "关闭串口";
            }
            else
            {
                serialPort1.Close();
                this.port.Text = "打开串口";
            }
        }

        private void fanhui_Click(object sender, EventArgs e)
        {
            this.Owner.Show();
            this.Close();
        }
        private byte[] strToHexByte(string hexString)
        {
            string temp = " ";
            hexString = hexString.Replace(" ", "");
            if ((hexString.Length % 2) != 0)
            {
                hexString = temp + hexString;
            }
            byte[] returnBytes = new byte[hexString.Length / 2];
            for (int i = 0; i < returnBytes.Length; i++)
                returnBytes[i] = Convert.ToByte(hexString.Substring(i * 2, 2).Replace(" ", ""), 16);
            return returnBytes;
        }

        private void Form4_FormClosed(object sender, FormClosedEventArgs e)
        {
            serialPort1.Close();
        }
    }
}
