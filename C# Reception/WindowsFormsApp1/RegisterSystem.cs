using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public class RegisterSystem
    {
        private ReceptionForm Form;
        public  List<string> IDs = new List<string>();
        private List<string> FirstNames = new List<string>();
        private List<string> LastNames = new List<string>();
        public  List<string> Rooms = new List<string>();

        public string ID;
        public string FirstName;
        public string LastName;
        public string Room;
        public bool RoomAvailable;
        bool ElementInList;
        public int IndexOfElement;


        public RegisterSystem(ReceptionForm form) 
        {
            this.Form = form;
        }
        public void CheckIfRegisterd(string Message, int AvailableRooms) //Starts remove or add mode depending if the Tag has already been registerd and if there is a room available.
        {
            ElementInList = IDs.Contains(Message);
            IndexOfElement = IDs.IndexOf(Message); 
            if (ElementInList == true)
            { 
                ID = IDs[IndexOfElement];
                FirstName = FirstNames[IndexOfElement];  
                LastName = LastNames[IndexOfElement];              
                Room = Rooms[IndexOfElement];
                Form.EnableRemove(ID, FirstName, LastName, Room);
            }
            else if (AvailableRooms == 0)
            {
                RoomAvailable = false;   
            }
            else 
            {
                ID = Message;
                Form.EnableAdd(ID);
                RoomAvailable = true;
            }
        }
        public bool CheckIfClaimed(string Message) //Checks if the Room has been claimed.
        {
            ElementInList = Rooms.Contains(Message);
            IndexOfElement = Rooms.IndexOf(Message);
            return ElementInList;
        }
        public void AddToLists() //Add the filled in information to the lists.
        {
            IDs.Add(ID);
            Rooms.Add(Room);
            FirstNames.Add(FirstName);
            LastNames.Add(LastName);
        }
        public void RemoveMode(int Index) // Starts remove mode when a guest has been selected.
        {
            IndexOfElement = Index;
            ID = IDs[Index];
            FirstName = FirstNames[Index];
            LastName = LastNames[Index];
            Room = Rooms[Index];
            Form.EnableRemove(ID, FirstName, LastName, Room);
        }
        public void RemoveFromLists()  // Removes the information in all the lists on a sertain index.
        {
            IDs.RemoveAt(IndexOfElement);
            FirstNames.RemoveAt(IndexOfElement);
            LastNames.RemoveAt(IndexOfElement);
            Rooms.RemoveAt(IndexOfElement);
            Form.Disable();
        }
    }
}
