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
    public partial class ReceptionForm : Form
    {
        RegisterSystem Register;
        bool AlarmSystemOn;
        string Input;
        
        public ReceptionForm()
        {
            InitializeComponent();
            Register = new RegisterSystem(this);
        }
        
        private void Form1_Load(object sender, EventArgs e) //Opens all the comports and starts up the register and alarm system.
        {
            spRFID.Open();
            spAlarm.Open();
            spDoorSystem.Open();
            spLightSystem.Open();
            AlarmSystemOn = true;
            Disable();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e) //Closes all the com ports.
        {
            spRFID.Close();
            spAlarm.Close();
            spDoorSystem.Close();
            spLightSystem.Close();

        }
        public void EnableAdd(string id) // Changes the Form design to Add mode.
        {
            tbxFirstName.Enabled = true;
            tbxLastName.Enabled = true;
            cbxRooms.Enabled = true;
            tbxFirstName.BackColor = Color.White;
            tbxLastName.BackColor = Color.White;
            btnAdd.Visible = true;
            btnAdd.Enabled = true;
            btnCancel.Visible = true;
            btnCancel.Enabled = true;
            btnRemove.Visible = false;
            btnRemove.Enabled = false;
            tbxFirstName.Clear();
            tbxLastName.Clear();
            cbxRooms.Text = "";
            lblMessage.Text = " Fill in the Information for ID: " +  id + ".";
        }
        public void EnableRemove(string ID, string fName, string LName, string RoomNMR) // Changes the Form design to remove mode.
        {
            tbxFirstName.Enabled = false;
            tbxLastName.Enabled = false;
            cbxRooms.Enabled = false;
            tbxFirstName.BackColor = Color.White;
            tbxLastName.BackColor = Color.White;
            btnAdd.Visible = false;
            btnAdd.Enabled = false;
            btnCancel.Visible = true;
            btnCancel.Enabled = true;
            btnRemove.Visible = true;
            btnRemove.Enabled = true;
            tbxFirstName.Text = fName;
            tbxLastName.Text = LName;
            cbxRooms.Text = RoomNMR;
            lblMessage.Text = "Remove ID: " + ID + ".";
        }

        public void Disable() //Disables add/remove mode.
        {
            tbxFirstName.Enabled = false;
            tbxFirstName.Clear();
            tbxLastName.Enabled = false;
            tbxLastName.Clear();
            cbxRooms.Enabled = false;
            cbxRooms.Text = " ";
            tbxFirstName.BackColor = Color.LightCoral;
            tbxLastName.BackColor = Color.LightCoral;
            btnAdd.Visible = false;
            btnAdd.Enabled = false;
            btnCancel.Visible = false;
            btnCancel.Enabled = false;
            btnRemove.Visible = false;
            btnRemove.Enabled = false;
            lblMessage.Text = "Scan a card or select a guest to register/deregister.";
        }

        
        void SelectGuest() //When a person has been selected starts remove mode
        {
            if (lbxRegisterd.SelectedItems.Count > 0) 
            {
                Register.RemoveMode(lbxRegisterd.SelectedIndex);
            }
        }

        void RegisterID() // Checks if a tag has been scanned and if it has been registerd.
        {
            if (spRFID.BytesToRead > 0) 
            {
                lbxRegisterd.ClearSelected();
                Input = spRFID.ReadLine(); // Receives ID.
                Input = Input.Trim();
                Register.CheckIfRegisterd(Input, cbxRooms.Items.Count);
                if (Register.RoomAvailable == false) // Shows a message when no more rooms are availablr. 
                {
                    lblMessage.Text = "No room is Available.";
                }
            }
        }

        void UnlockDoor()
        {
            if (spDoorSystem.BytesToRead > 0) // Checks if a tag has been scanned and sends the command to open the door depending if the room belongs to that guest.
            {
                Input = spDoorSystem.ReadLine(); // Receives Room number.
                Input = Input.Trim();
                bool RoomClaimed = Register.CheckIfClaimed(Input);
                int Index = Register.IndexOfElement;
                Input = spDoorSystem.ReadLine(); // Receives ID.
                Input = Input.Trim();
                if (RoomClaimed == true && Input == Register.IDs[Index]) 
                {
                    spDoorSystem.WriteLine("AccesGranted");                   
                }
                else
                {
                    spDoorSystem.WriteLine("AccesDenied");
                }
            }
        }

        void BurglarAlarm() // Checks if a possible burglary is happening and sounds the alarm depending if the alarmsystem is on.
        {
            if (spLightSystem.BytesToRead > 0)
            {
                Input = spLightSystem.ReadLine(); // receives Room number.
                Input = Input.Trim();
                if (Register.CheckIfClaimed(Input) == false)
                {
                    if (AlarmSystemOn == true) 
                    {
                        spLightSystem.Write("AlarmOn");
                        spAlarm.Write("killBurglar");
                        btnAlarm.BackColor = Color.Red; 
                    }
                    else
                    {
                        btnAlarm.BackColor = Color.Gray;
                    }
                }
            }
        }

        void FireAlarm() // Checks if a possible fire is happening and sounds the alarm depending if the alarmsystem is on.
        {
            if (spAlarm.BytesToRead > 0)
            {
                Input = spAlarm.ReadLine();
                Input = Input.Trim();
                if (Input == "AlarmOn") 
                {
                    if (AlarmSystemOn == true)
                    {
                        btnAlarm.BackColor = Color.Red;
                        spLightSystem.WriteLine(Input);
                    }
                    else
                    {
                        btnAlarm.BackColor = Color.Gray;
                    }
                }
                else if (Input == "AlarmOff")
                {
                    spLightSystem.WriteLine(Input);
                    if (AlarmSystemOn == true)
                    {
                        btnAlarm.BackColor = Color.LightGreen;
                    }
                    else
                    {
                        btnAlarm.BackColor = Color.Gray;
                    }
                }
            }
        }

        private void timer_Tick(object sender, EventArgs e) // loops all the methods that need to bee looped
        {
            SelectGuest();
            RegisterID();
            UnlockDoor();
            FireAlarm();
            BurglarAlarm();
        } 

        private void btnCancel_Click(object sender, EventArgs e) // Stops add or remove mode by activating Disable mode.
        {
            Disable();
            lbxRegisterd.ClearSelected();
        }
        private void btnAdd_Click(object sender, EventArgs e) // Adds guest to the database
        {
            Register.FirstName = tbxFirstName.Text;
            Register.LastName = tbxLastName.Text;
            Register.Room = cbxRooms.Text;
            if (Register.FirstName == "" || Register.LastName == "" || Register.Room == "") // Checks if every field has been filled in correctly
            {
                MessageBox.Show("All information must be given", "Error");
            }
            else
            {
                cbxRooms.Items.Remove(Register.Room);
                Register.AddToLists();
                lbxRegisterd.Items.Add("Registed: " + Register.FirstName + " " + Register.LastName + ", " + "ID: " + Register.ID + ", " + " room: " + Register.Room + ".");
                Disable();
            }
        }
        private void btnRemove_Click(object sender, EventArgs e) // Removes selected or scanned card.
        {
            string FreeRoom = Register.Rooms[Register.IndexOfElement];
            cbxRooms.Items.Add(FreeRoom);
            lbxRegisterd.Items.RemoveAt(Register.IndexOfElement);
            Register.RemoveFromLists();
            Disable();
        }
        private void btnAlarm_Click(object sender, EventArgs e) // Toggles the alarm system 
        {
            if (AlarmSystemOn == true)
            {
                AlarmSystemOn = false;
                btnAlarm.Text = "Alarm-system off";
                spAlarm.Write("R- Alarm off");
                spLightSystem.Write("R- Alarm off");
                btnAlarm.BackColor = Color.Gray;
            }
            else
            {
                btnAlarm.Text = "Alarm-system on";
                spAlarm.Write("R- Alarm on");
                spLightSystem.Write("R- Alarm on");
                btnAlarm.BackColor = Color.LightGreen;
                AlarmSystemOn = true;
            }
        }
    }
}

