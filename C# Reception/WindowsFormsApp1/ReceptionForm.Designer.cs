
namespace WindowsFormsApp1
{
    partial class ReceptionForm
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
            this.btnCancel = new System.Windows.Forms.Button();
            this.cbxRooms = new System.Windows.Forms.ComboBox();
            this.gbRegistration = new System.Windows.Forms.GroupBox();
            this.btnRemove = new System.Windows.Forms.Button();
            this.lblFirstName = new System.Windows.Forms.Label();
            this.lblLastName = new System.Windows.Forms.Label();
            this.lblRoom = new System.Windows.Forms.Label();
            this.btnAdd = new System.Windows.Forms.Button();
            this.tbxFirstName = new System.Windows.Forms.TextBox();
            this.tbxLastName = new System.Windows.Forms.TextBox();
            this.Timer = new System.Windows.Forms.Timer(this.components);
            this.spAlarm = new System.IO.Ports.SerialPort(this.components);
            this.lblReception = new System.Windows.Forms.Label();
            this.lblRegisted = new System.Windows.Forms.Label();
            this.lbxRegisterd = new System.Windows.Forms.ListBox();
            this.btnAlarm = new System.Windows.Forms.Button();
            this.lblMessage = new System.Windows.Forms.Label();
            this.spRFID = new System.IO.Ports.SerialPort(this.components);
            this.spDoorSystem = new System.IO.Ports.SerialPort(this.components);
            this.spLightSystem = new System.IO.Ports.SerialPort(this.components);
            this.gbRegistration.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnCancel
            // 
            this.btnCancel.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
            this.btnCancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnCancel.Location = new System.Drawing.Point(9, 252);
            this.btnCancel.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.btnCancel.Name = "btnCancel";
            this.btnCancel.Size = new System.Drawing.Size(138, 42);
            this.btnCancel.TabIndex = 0;
            this.btnCancel.Text = "Cancel";
            this.btnCancel.UseVisualStyleBackColor = false;
            this.btnCancel.Click += new System.EventHandler(this.btnCancel_Click);
            // 
            // cbxRooms
            // 
            this.cbxRooms.FormattingEnabled = true;
            this.cbxRooms.Items.AddRange(new object[] {
            "1",
            "2",
            "3",
            "4",
            "5",
            "6"});
            this.cbxRooms.Location = new System.Drawing.Point(141, 161);
            this.cbxRooms.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cbxRooms.Name = "cbxRooms";
            this.cbxRooms.Size = new System.Drawing.Size(148, 45);
            this.cbxRooms.Sorted = true;
            this.cbxRooms.TabIndex = 1;
            // 
            // gbRegistration
            // 
            this.gbRegistration.BackColor = System.Drawing.SystemColors.ButtonShadow;
            this.gbRegistration.Controls.Add(this.btnRemove);
            this.gbRegistration.Controls.Add(this.lblFirstName);
            this.gbRegistration.Controls.Add(this.lblLastName);
            this.gbRegistration.Controls.Add(this.lblRoom);
            this.gbRegistration.Controls.Add(this.btnAdd);
            this.gbRegistration.Controls.Add(this.tbxFirstName);
            this.gbRegistration.Controls.Add(this.tbxLastName);
            this.gbRegistration.Controls.Add(this.btnCancel);
            this.gbRegistration.Controls.Add(this.cbxRooms);
            this.gbRegistration.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.gbRegistration.Location = new System.Drawing.Point(68, 159);
            this.gbRegistration.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.gbRegistration.Name = "gbRegistration";
            this.gbRegistration.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.gbRegistration.Size = new System.Drawing.Size(300, 312);
            this.gbRegistration.TabIndex = 2;
            this.gbRegistration.TabStop = false;
            this.gbRegistration.Text = "Registration";
            // 
            // btnRemove
            // 
            this.btnRemove.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(0)))));
            this.btnRemove.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnRemove.Location = new System.Drawing.Point(156, 252);
            this.btnRemove.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.btnRemove.Name = "btnRemove";
            this.btnRemove.Size = new System.Drawing.Size(135, 42);
            this.btnRemove.TabIndex = 8;
            this.btnRemove.Text = "Remove";
            this.btnRemove.UseVisualStyleBackColor = false;
            this.btnRemove.Click += new System.EventHandler(this.btnRemove_Click);
            // 
            // lblFirstName
            // 
            this.lblFirstName.AutoSize = true;
            this.lblFirstName.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblFirstName.Location = new System.Drawing.Point(8, 61);
            this.lblFirstName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblFirstName.Name = "lblFirstName";
            this.lblFirstName.Size = new System.Drawing.Size(109, 25);
            this.lblFirstName.TabIndex = 3;
            this.lblFirstName.Text = "First name:";
            // 
            // lblLastName
            // 
            this.lblLastName.AutoSize = true;
            this.lblLastName.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblLastName.Location = new System.Drawing.Point(8, 119);
            this.lblLastName.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblLastName.Name = "lblLastName";
            this.lblLastName.Size = new System.Drawing.Size(109, 25);
            this.lblLastName.TabIndex = 4;
            this.lblLastName.Text = "Last name:";
            // 
            // lblRoom
            // 
            this.lblRoom.AutoSize = true;
            this.lblRoom.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblRoom.Location = new System.Drawing.Point(45, 178);
            this.lblRoom.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblRoom.Name = "lblRoom";
            this.lblRoom.Size = new System.Drawing.Size(69, 25);
            this.lblRoom.TabIndex = 3;
            this.lblRoom.Text = "Room:";
            // 
            // btnAdd
            // 
            this.btnAdd.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
            this.btnAdd.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnAdd.Location = new System.Drawing.Point(156, 252);
            this.btnAdd.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.btnAdd.Name = "btnAdd";
            this.btnAdd.Size = new System.Drawing.Size(135, 42);
            this.btnAdd.TabIndex = 3;
            this.btnAdd.Text = "Add";
            this.btnAdd.UseVisualStyleBackColor = false;
            this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
            // 
            // tbxFirstName
            // 
            this.tbxFirstName.Location = new System.Drawing.Point(141, 46);
            this.tbxFirstName.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.tbxFirstName.Name = "tbxFirstName";
            this.tbxFirstName.Size = new System.Drawing.Size(148, 43);
            this.tbxFirstName.TabIndex = 3;
            // 
            // tbxLastName
            // 
            this.tbxLastName.BackColor = System.Drawing.Color.WhiteSmoke;
            this.tbxLastName.ForeColor = System.Drawing.SystemColors.WindowText;
            this.tbxLastName.Location = new System.Drawing.Point(141, 105);
            this.tbxLastName.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.tbxLastName.Name = "tbxLastName";
            this.tbxLastName.Size = new System.Drawing.Size(148, 43);
            this.tbxLastName.TabIndex = 3;
            // 
            // Timer
            // 
            this.Timer.Enabled = true;
            this.Timer.Interval = 50;
            this.Timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // spAlarm
            // 
            this.spAlarm.PortName = "COM5";
            // 
            // lblReception
            // 
            this.lblReception.AutoSize = true;
            this.lblReception.BackColor = System.Drawing.Color.DarkGray;
            this.lblReception.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblReception.Location = new System.Drawing.Point(76, 14);
            this.lblReception.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblReception.Name = "lblReception";
            this.lblReception.Size = new System.Drawing.Size(216, 47);
            this.lblReception.TabIndex = 3;
            this.lblReception.Text = "Reception";
            // 
            // lblRegisted
            // 
            this.lblRegisted.AutoSize = true;
            this.lblRegisted.Location = new System.Drawing.Point(498, 134);
            this.lblRegisted.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblRegisted.Name = "lblRegisted";
            this.lblRegisted.Size = new System.Drawing.Size(105, 20);
            this.lblRegisted.TabIndex = 4;
            this.lblRegisted.Text = "Registerd list:";
            // 
            // lbxRegisterd
            // 
            this.lbxRegisterd.Font = new System.Drawing.Font("Microsoft Sans Serif", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lbxRegisterd.FormattingEnabled = true;
            this.lbxRegisterd.ItemHeight = 26;
            this.lbxRegisterd.Location = new System.Drawing.Point(502, 159);
            this.lbxRegisterd.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.lbxRegisterd.Name = "lbxRegisterd";
            this.lbxRegisterd.Size = new System.Drawing.Size(513, 472);
            this.lbxRegisterd.TabIndex = 6;
            // 
            // btnAlarm
            // 
            this.btnAlarm.BackColor = System.Drawing.Color.LightGreen;
            this.btnAlarm.Font = new System.Drawing.Font("Microsoft Sans Serif", 13F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnAlarm.Location = new System.Drawing.Point(77, 504);
            this.btnAlarm.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.btnAlarm.Name = "btnAlarm";
            this.btnAlarm.Size = new System.Drawing.Size(282, 66);
            this.btnAlarm.TabIndex = 7;
            this.btnAlarm.Text = "Alarm-system on";
            this.btnAlarm.UseVisualStyleBackColor = false;
            this.btnAlarm.Click += new System.EventHandler(this.btnAlarm_Click);
            // 
            // lblMessage
            // 
            this.lblMessage.AutoSize = true;
            this.lblMessage.Location = new System.Drawing.Point(63, 134);
            this.lblMessage.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.lblMessage.Name = "lblMessage";
            this.lblMessage.Size = new System.Drawing.Size(248, 20);
            this.lblMessage.TabIndex = 8;
            this.lblMessage.Text = "Scan a card to register/deregister.";
            // 
            // spRFID
            // 
            this.spRFID.PortName = "COM4";
            // 
            // spDoorSystem
            // 
            this.spDoorSystem.PortName = "COM6";
            // 
            // spLightSystem
            // 
            this.spLightSystem.PortName = "COM7";
            // 
            // ReceptionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.LightSteelBlue;
            this.ClientSize = new System.Drawing.Size(1200, 692);
            this.Controls.Add(this.lblMessage);
            this.Controls.Add(this.btnAlarm);
            this.Controls.Add(this.lbxRegisterd);
            this.Controls.Add(this.lblRegisted);
            this.Controls.Add(this.lblReception);
            this.Controls.Add(this.gbRegistration);
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Name = "ReceptionForm";
            this.Text = "Reception";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.gbRegistration.ResumeLayout(false);
            this.gbRegistration.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnCancel;
        private System.Windows.Forms.ComboBox cbxRooms;
        private System.Windows.Forms.GroupBox gbRegistration;
        private System.Windows.Forms.Label lblFirstName;
        private System.Windows.Forms.Label lblLastName;
        private System.Windows.Forms.Label lblRoom;
        private System.Windows.Forms.Button btnAdd;
        private System.Windows.Forms.TextBox tbxFirstName;
        private System.Windows.Forms.TextBox tbxLastName;
        private System.Windows.Forms.Timer Timer;
        private System.IO.Ports.SerialPort spAlarm;
        private System.Windows.Forms.Label lblReception;
        private System.Windows.Forms.Label lblRegisted;
        private System.Windows.Forms.ListBox lbxRegisterd;
        private System.Windows.Forms.Button btnAlarm;
        private System.Windows.Forms.Button btnRemove;
        private System.Windows.Forms.Label lblMessage;
        private System.IO.Ports.SerialPort spRFID;
        private System.IO.Ports.SerialPort spDoorSystem;
        private System.IO.Ports.SerialPort spLightSystem;
    }
}

