using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace WindowsFormsApp1
{
    public partial class Form3 : Form
    {
        int count = 0;
        int led = 0;
        public Form3()
        {
            InitializeComponent();
        }

        private void splitContainer1_Panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void splitContainer1_Panel2_Paint(object sender, PaintEventArgs e)
        {

        }

        private void dianzuzhi_input_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                byte[] sendData = null;
                string str = "AA 01 08 00 00 0D";
                sendData = strToHexByte(str.Trim());
                serialPort1.Write(sendData, 0, sendData.Length);//发送信息
            }
            else
            {
                MessageBox.Show("串口未打开", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Form3_FormClosing(object sender, FormClosingEventArgs e)
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
                            led = 0;
                            break;
                        }
                    case ("蓝灯"):
                        {
                            str = "AA 01 01 02 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            led = 1;
                            break;
                        }
                    case ("绿灯"):
                        {
                            str = "AA 01 01 03 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            led = 2;
                            break;
                        }
                    case ("黄绿灯"):
                        {
                            str = "AA 01 01 04 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            led = 3;
                            break;
                        }
                    case ("黄灯"):
                        {
                            str = "AA 01 01 05 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            led = 4;
                            break;
                        }
                    case ("橘灯"):
                        {
                            str = "AA 01 01 06 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            led = 5;
                            break;
                        }
                    case ("红灯"):
                        {
                            str = "AA 01 01 07 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            led = 6;
                            break;
                        }
                    case ("白灯"):
                        {
                            str = "AA 01 01 08 00 0D";
                            sendData = strToHexByte(str.Trim());
                            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
                            led = 7;
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

        private void Form3_FormClosed(object sender, FormClosedEventArgs e)
        {
            serialPort1.Close();
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
        
            byte[] ReDatas = new byte[serialPort1.BytesToRead];
            serialPort1.Read(ReDatas, 0, ReDatas.Length);//读取数据
            string recv1 = "";
            string recv2 = "";
            if (ReDatas.Length == 8)
            {
                string str1 = ReDatas[0].ToString();
                string str2 = ReDatas[1].ToString();
                if (int.Parse(str1) != 0)
                {
                    int temp = int.Parse(str1) * 256 + int.Parse(str2);
                    recv1 = temp.ToString();
                }
                else
                {
                    int temp = int.Parse(str2);
                    recv1 = temp.ToString();
                }
                string str3 = ReDatas[4].ToString();
                string str4 = ReDatas[5].ToString();
                if (int.Parse(str3) != 0)
                {
                    int temp = int.Parse(str3) * 256 + int.Parse(str4);
                    temp = temp * 10;
                    recv2 = temp.ToString();
                }
                else
                {
                    int temp = int.Parse(str4);
                    temp = temp * 10;
                    recv2 = temp.ToString();
                }
                Addlist(recv1, recv2,led);
            }
           
        }
        private void Addlist(string content1,string content2,int n)
        {
            this.BeginInvoke(new MethodInvoker(delegate
            {
                int index = this.dataGridView1.Rows.Add();
                this.dataGridView1.Rows[index].Cells[0].Value = count++;
                this.dataGridView1.Rows[index].Cells[3].Value = content2;
                this.dataGridView1.Rows[index].Cells[2].Value = content1;
                this.dataGridView1.Rows[index].Cells[1].Value = this.comboBox3.Text;
                this.chart1.Series[n].Points.AddXY(int.Parse(content1), int.Parse(content2));
            }));
        }
        static string GetBytesString(byte[] bytes, int index, int count, string sep)
        {
            var sb = new StringBuilder();
            for (int i = index; i < count - 1; i++)
            {
                sb.Append(bytes[i].ToString("X2") + sep);
            }
            sb.Append(bytes[index + count - 1].ToString("X2"));
            return sb.ToString();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            if (DataTableToTxt(dataGridView1, "光照特性.txt", ' '))
            {
                MessageBox.Show("导出成功");
            }
            else
            {
                MessageBox.Show("导出失败");
            }
        }
        #region 方法--dgv导出到txt
        //导出到txt
        //strFileName文件名，strSplit文件中数据间的分隔符
        public static bool DataTableToTxt(DataGridView gridview, string strFileName, char strSplit)
        {
            if (gridview == null || gridview.Rows.Count == 0)
                return false;

            FileStream fileStream = new FileStream(strFileName, FileMode.OpenOrCreate);
            StreamWriter streamWriter = new StreamWriter(fileStream, System.Text.Encoding.UTF8);

            StringBuilder strBuilder = new StringBuilder();

            try
            {
                for (int i = 0; i < gridview.Rows.Count - 1; i++)
                {
                    strBuilder = new StringBuilder();
                    for (int j = 0; j < gridview.Columns.Count; j++)
                    {
                        strBuilder.Append(gridview.Rows[i].Cells[j].Value.ToString() + strSplit);
                    }
                    strBuilder.Remove(strBuilder.Length - 1, 1); // 将最后添加的一个strSplit删除掉
                    streamWriter.WriteLine(strBuilder.ToString());
                }
            }
            catch (Exception ex)
            {
                string strErrorMessage = ex.Message;
                return false;
            }
            finally
            {
                streamWriter.Close();
                fileStream.Close();
            }

            return true;
        }
        #endregion

    }
}
