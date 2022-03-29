using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace vending_microwave
{
    public partial class Form1 : Form
    {
        vending_microwave.VendingMachine v = new VendingMachine();
        int count = 0;
        public Form1()
        {
            //initial state of the program
            InitializeComponent();
            serialPort1.Open();
            timer3.Start();
            panel1.Visible = false;
            panel2.Visible = false;
            button1.Visible = false;
            label4.Visible = false;
            listView1.View = View.Details;
            for(int i = 0; i < v.getList().Count; i++)
            {
                var row = new string[] { v.getList()[i].getName(), Convert.ToString(v.getList()[i].getCount())};
                var lvi = new ListViewItem(row);
                listView1.Items.Add(lvi);
            }
        }

        /*public class AutoClosingMessageBox
        {
            System.Threading.Timer _timeoutTimer;
            string _caption;
            AutoClosingMessageBox(string text, string caption, int timeout)
            {
                _caption = caption;
                _timeoutTimer = new System.Threading.Timer(OnTimerElapsed,
                    null, timeout, System.Threading.Timeout.Infinite);
                using (_timeoutTimer)
                    MessageBox.Show(text, caption);
            }
            public static void Show(string text, string caption, int timeout)
            {
                new AutoClosingMessageBox(text, caption, timeout);
            }
            void OnTimerElapsed(object state)
            {
                IntPtr mbWnd = FindWindow("#32770", _caption); // lpClassName is #32770 for MessageBox
                if (mbWnd != IntPtr.Zero)
                    SendMessage(mbWnd, WM_CLOSE, IntPtr.Zero, IntPtr.Zero);
                _timeoutTimer.Dispose();
            }
            const int WM_CLOSE = 0x0010;
            [System.Runtime.InteropServices.DllImport("user32.dll", SetLastError = true)]
            static extern IntPtr FindWindow(string lpClassName, string lpWindowName);
            [System.Runtime.InteropServices.DllImport("user32.dll", CharSet = System.Runtime.InteropServices.CharSet.Auto)]
            static extern IntPtr SendMessage(IntPtr hWnd, UInt32 Msg, IntPtr wParam, IntPtr lParam);
        }*/

        private void label1_Click(object sender, EventArgs e)
        {
            
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void timer1_Tick_1(object sender, EventArgs e)
        {
            timer3.Stop();
            List<Product> cpy = v.getList();
            string message = "";
            if (serialPort1.BytesToRead > 0)
            {
                message = serialPort1.ReadLine();
                message = message.Trim();
                if (message.Contains("no"))
                {
                    message = message.Remove(0, 2);
                    message = message.Remove(message.Length - 2);
                    int number = Convert.ToInt32(message);
                    Label:
                    //if the number corresponds to the number of a product, the background of the line becomes aqua
                    if (number >= 0 && number <= cpy.Count - 1)
                    {
                        foreach(ListViewItem item in listView1.Items)
                        {
                            if(item.BackColor == Color.Aqua)
                            {
                                item.BackColor = Color.Transparent;
                                break;
                            }
                        }
                        ListViewItem lst = listView1.FindItemWithText(cpy[number].getName());
                        lst.BackColor = Color.Aqua;
                    }
                    else
                    {
                        number = cpy.Count - 1;
                        goto Label;
                    }
                    
                }
                //if a button for pick action is pressed, we remove one from the quantity of the product
                else if(Char.IsDigit(message[0]))
                {
                    int number = Convert.ToInt32(message);
                label2:
                    if (number >= 0 && number <= v.getList().Count)
                    {
                        if (v.getProduct(number + 1))
                        {
                            serialPort1.Write("true");
                            string text = $"You bought: {v.getList()[int.Parse(message)].getName()}";
                        }
                        else
                        {
                            serialPort1.Write("false");
                        }
                        listView1.Items.Clear();
                        for (int i = 0; i < v.getList().Count; i++)
                        {
                            var row = new string[] { v.getList()[i].getName(), Convert.ToString(v.getList()[i].getCount()) };
                            var lvi = new ListViewItem(row);
                            listView1.Items.Add(lvi);
                        }
                        listView1.Items[number].BackColor = Color.Aqua;
                    }
                    else
                    {
                        number = cpy.Count - 1;
                        message = Convert.ToString(number);
                        goto label2;
                    }
                }
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            //separates and processes each data for the microwave
            if(serialPort1.BytesToRead > 0)
            {
                string text = serialPort1.ReadLine();
                if (text.StartsWith("temp"))
                {
                    text = text.Remove(0, 4);
                    text = text.Remove(text.Length - 5);
                    textBox4.Text = text;
                    if (Convert.ToInt16(text) > 800)
                    {
                        label4.Visible = true;
                    }
                    else
                        label4.Visible = false;
                }
                else if (text.StartsWith("time"))
                {
                    text = text.Remove(0, 4);
                    text = text.Remove(text.Length - 5);
                    textBox5.Text = text;
                }
                else if (text.StartsWith("dur"))
                {
                    text = text.Remove(0, 3);
                    text = text.Remove(text.Length - 4);
                    textBox6.Text = text;
                    if(Convert.ToInt16(text) >= 1)
                    {
                        button1.Enabled = false;
                    }
                    else
                    {
                        button1.Enabled = true;
                    }
                }
            }
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            // if the arduino sends an open signal, that means we got authorized access
            string text;
            if (serialPort1.BytesToRead > 0)
            {
                text = serialPort1.ReadLine();
                if (text.Contains("o"))
                {
                    panel1.Visible = true;
                    panel2.Visible = true;
                    button1.Visible = true;
                    timer2.Start();
                    timer1.Start();
                    label3.Visible = false;
                    label3.Text = "Approximate card";
                }
                else
                {
                    label3.Text = "Access denied";
                }
            }
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            //if you press an item twice, we remove one from the count of the item
            if (listView1.SelectedItems.Count == 1)
            {
                ListView.SelectedListViewItemCollection items = listView1.SelectedItems;
                ++count;
                ListViewItem lvItem = items[0];
                if (count == 2)
                {
                    v.getProduct(lvItem.Index + 1);
                    listView1.Items.Clear();
                    for (int i = 0; i < v.getList().Count; i++)
                    {
                        var row = new string[] { v.getList()[i].getName(), Convert.ToString(v.getList()[i].getCount()) };
                        var lvi = new ListViewItem(row);
                        listView1.Items.Add(lvi);
                    }
                    count = 0;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label3.Visible = true;
            serialPort1.Write("close");
            panel1.Visible = false;
            panel2.Visible = false;
            button1.Visible = false;
            timer1.Stop();
            timer2.Stop();
            timer3.Start();
        }
    }
}
