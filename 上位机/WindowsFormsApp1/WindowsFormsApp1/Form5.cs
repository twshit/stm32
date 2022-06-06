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
    public partial class Form5 : Form
    {
        public Form5()
        {
            InitializeComponent();
        }

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void chart1_Click(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Form5_FormClosing(object sender, FormClosingEventArgs e)
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
        private void btn_setcolor_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                byte[] sendData = null;
                string str;
                string temp = comboBox3.Text;
                switch (temp)
                {
                    case ("关闭"):
                        {
                            str = "AA 01 01 00 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            break;
                        }
                    case ("紫灯"):
                        {
                            str = "AA 01 01 01 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            break;
                        }
                    case ("蓝灯"):
                        {
                            str = "AA 01 01 02 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            break;
                        }
                    case ("绿灯"):
                        {
                            str = "AA 01 01 03 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            break;
                        }
                    case ("黄绿灯"):
                        {
                            str = "AA 01 01 04 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            break;
                        }
                    case ("黄灯"):
                        {
                            str = "AA 01 01 05 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            break;
                        }
                    case ("橘灯"):
                        {
                            str = "AA 01 01 06 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            break;
                        }
                    case ("红灯"):
                        {
                            str = "AA 01 01 07 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            break;
                        }
                    case ("白灯"):
                        {
                            str = "AA 01 01 08 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            break;
                        }
                    default:
                        break;

                }
            }
            else
            {
                MessageBox.Show("串口未打开", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Form5_FormClosed(object sender, FormClosedEventArgs e)
        {
            serialPort1.Close();
        }
    }
}
