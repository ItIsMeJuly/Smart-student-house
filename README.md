# Smart-student-house
An arduino project for a smart student house. It consists of 5 arduino subsystems and two Windows Forms applications to monitor the information from the boards. 
They communicate with a serial connection (USB) and the boards send information to the Laptop/PC. It is a very basic system where we have a couple files: </br> 
<ul>
  <li> C# Reception that is the main form of connection between the boards and the Desktop App. 🧾</li>
  <li> Student Bathroom which is an automated bathroom with simulated sink and toilet. 🛁</li>
  <li> Door locking system which's reason is the lock a door and the only way to open it is with an access card. It also ahs a burglar alarm and when it is triggered, a message is sent to the reception. 🔒 </li>
  <li> Fire Alarm system that check whether the CO2 sensor's readings are above a threshold and sounds an alarm sending messages to the reception. 🚒</li>
  <li> Lighting system with a few modes for 🔦:
    <ol>
      <li> Party 🎊</li>
      <li> Studying 📖</li>
      <li> Manual 🔑</li>
    </ol>
  <li> Vending Machine and a Microwave are both integrated on one chip with a seperate software for a Laptop, PC. You could either get a beverage or a snack from the vending machine while heating something in the microwave. 🎰
</ul>

