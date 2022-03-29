using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Test_Doorlock_System
{
    public partial class Form1 : Form
    {
        List<string> CardIDs = new List<string>();

        public Form1()
        {
            InitializeComponent();

            CardIDs.Add("2729144348");
        }


        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            serialPort.Open();
            timer1.Start();
        }
        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            serialPort.Close();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (serialPort.BytesToRead > 0)
            {
                string input = serialPort.ReadLine();
                input = input.Trim();
                for (int i = 0; i < CardIDs.Count; i++)
                {
                    if (input == CardIDs[i])
                    {
                        string message = "AccesGranted";
                        listBox1.Items.Add("Acces granted");
                        serialPort.WriteLine(message);
                    }
                    else
                    {
                        string message = "AccesDenied";
                        listBox1.Items.Add("Acces Denied");
                        serialPort.WriteLine(message);
                    }
                }
            }
        }


    }
}
