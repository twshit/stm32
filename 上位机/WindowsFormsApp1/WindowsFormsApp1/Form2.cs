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
    public partial class Form2 : Form
    {
        int count1 = 0;
        int count2 = 0;
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_FormClosing(object sender, FormClosingEventArgs e)
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

        private void button2_Click(object sender, EventArgs e)
        {
                if (serialPort1.IsOpen)
            {
                byte[] sendData = null;
                string str = "AA 01 04 00 00 0D";
                sendData = strToHexByte(str.Trim());
                serialPort1.Write(sendData, 0, sendData.Length);//发送数据
            }
            else
            {
                MessageBox.Show("串口未打开", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void dianzuzhi_input_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                byte[] sendData = null;
                string str = "AA 01 05 00 00 0D";
                sendData = strToHexByte(str.Trim());
                serialPort1.Write(sendData, 0, sendData.Length);//发送数据
            }
            else
            {
                MessageBox.Show("串口未打开", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void Form2_FormClosed(object sender, FormClosedEventArgs e)
        {
            serialPort1.Close();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            byte[] sendData = null;
            string tte = textBox1.Text;
            double zu=double.Parse(tte);
            double temp = zu * 4096 / 3.3;
            if(temp==4096)
            {
                temp -= 1;
            }
            int DAC = (int)Math.Floor(temp);
            string strd = DAC.ToString("X");
            byte[] sendDatad = null;
            sendDatad = strToHexByte(strd.Trim());
            byte[] sendData1 = null;
            byte[] sendData2 = null;
            string str1 = "AA 01 02 ";
            string str2 = "0D";
            string strt = "00";
            sendData = null;
            sendData1 = strToHexByte(str1.Trim());
            sendData2 = strToHexByte(str2.Trim());
            byte[] sendDatat = strToHexByte(strt.Trim());
            if(sendDatad.Length==1)
            {
                sendData = new byte[sendData1.Length + sendDatad.Length + sendData2.Length+sendDatat.Length];
                sendData1.CopyTo(sendData, 0);
                sendDatat.CopyTo(sendData, sendData1.Length);
                sendDatad.CopyTo(sendData, sendData1.Length+sendDatat.Length);
                sendData2.CopyTo(sendData, sendDatad.Length + sendData1.Length+sendDatat.Length);
            }
            else
            {
                sendData= new byte[sendData1.Length + sendDatad.Length+ sendData2.Length];
                sendData1.CopyTo(sendData, 0);
                sendDatad.CopyTo(sendData, sendData1.Length);
                sendData2.CopyTo(sendData, sendDatad.Length+ sendData1.Length);
            }
            serialPort1.Write(sendData, 0, sendData.Length);//发送数据
        }

        private void serialPort1_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            byte[] ReDatas = new byte[serialPort1.BytesToRead];
            serialPort1.Read(ReDatas, 0, ReDatas.Length);//读取数据
            string recv="";
            if (ReDatas.Length == 6)
            {
                if (ReDatas[2] == 04)
                {
                    string str1 = ReDatas[3].ToString();
                    string str2 = ReDatas[4].ToString();
                    if (int.Parse(str1) != 0)
                    {
                        int temp = int.Parse(str1) * 256 + int.Parse(str2);
                        temp = temp * 10;
                        recv = temp.ToString();
                    }
                    else
                    {
                        int temp = int.Parse(str2);
                        temp = temp * 10;
                        recv = temp.ToString();
                    }
                    AddContent2(recv);
                    Addlist1(recv);
                }

                else if (ReDatas[2] == 05)
                {
                    string str1 = ReDatas[3].ToString();
                    string str2 = ReDatas[4].ToString();
                    if (int.Parse(str1) != 0)
                    {
                        int temp = int.Parse(str1) * 256 + int.Parse(str2);
                        temp = temp * 10;
                        recv = temp.ToString();
                    }
                    else
                    {
                        int temp = int.Parse(str2);
                        temp = temp * 10;
                        recv = temp.ToString();
                    }
                    AddContent1(recv);
                    Addlist2(recv);
                }
                else if (ReDatas[2] == 07)
                {
                    string str1 = ReDatas[3].ToString();
                    string str2 = ReDatas[4].ToString();
                    if (int.Parse(str1) != 0)
                    {
                        int temp = int.Parse(str1) * 256 + int.Parse(str2);
                        recv = temp.ToString();
                    }
                    else
                    {
                        int temp = int.Parse(str2);
                        recv = temp.ToString();
                    }
                    AddContent3(recv);
                }
            }
            
        }
        private void AddContent1(string content)
        {
            this.BeginInvoke(new MethodInvoker(delegate
            {
                listBox1.Items.Insert(0,content);
            }));
        }
        private void AddContent2(string content)
        {
            this.BeginInvoke(new MethodInvoker(delegate
            {
                listBox2.Items.Insert(0, content);
            }));
        }
        private void AddContent3(string content)
        {
            this.BeginInvoke(new MethodInvoker(delegate
            {
                listBox3.Items.Insert(0, content);
            }));
        }
        private void Addlist1(string content)
        {
            this.BeginInvoke(new MethodInvoker(delegate
            {
                int index = this.dataGridView1.Rows.Add();
                this.dataGridView1.Rows[index].Cells[0].Value = count1++;
                this.dataGridView1.Rows[index].Cells[1].Value = content;
            }));
        }
        private void Addlist2(string content)
        {
            this.BeginInvoke(new MethodInvoker(delegate
            {
                int index = this.dataGridView3.Rows.Add();
                this.dataGridView3.Rows[index].Cells[0].Value = count2++;
                this.dataGridView3.Rows[index].Cells[3].Value = content;
                this.dataGridView3.Rows[index].Cells[2].Value = this.listBox3.Items[0];
                this.dataGridView3.Rows[index].Cells[1].Value = this.comboBox3.Text;
            }));
        }
        private void button7_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                byte[] sendData = null;
                string str = "AA 01 07 00 00 0D";
                sendData = strToHexByte(str.Trim());
                serialPort1.Write(sendData, 0, sendData.Length);//发送数据
            }
            else
            {
                MessageBox.Show("串口未打开", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }


        private void Form2_Load_1(object sender, EventArgs e)
        {
            dataGridView1.ReadOnly = true;
            dataGridView3.ReadOnly = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (DataTableToTxt(dataGridView1, "暗电阻.txt",' '))
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
                for (int i = 0; i < gridview.Rows.Count-1; i++)
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

        private void button5_Click(object sender, EventArgs e)
        {
            if (DataTableToTxt(dataGridView3, "亮电阻.txt", ' '))
            {
                MessageBox.Show("导出成功");
            }
            else
            {
                MessageBox.Show("导出失败");
            }
        }
    }
}
