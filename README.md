# Baby-Block-Robot-Project
CS 121 Project written in C++.
The full project requirements can be found here:

  CS 121 Class Project

Thank you for your purchase of the Baby Block 270 Robot (BB270). In order to use the BB270 you must write a program using the basic robot operations stated below:

Get Block – Removes and holds one block from the chute

Put Block – Inserts the block currently held by the robot into an empty slot.

Switch Blocks – Removes a block currently in a slot and replaces it with the block being held by the robot. When finished the robot is holding the block it just removed from the slot.

Compare Blocks – Compares the value of the block (letter) being held by the robot to that of a block in a slot. (If the block held by the robot is less than or equal to the block in the slot the result of the compare is TRUE. If the block held by the robot is greater than the block in the slot the result of the compare is FALSE)

Shift Left – Shift the robotic arm one slot to the left. (Cannot go to the left of slot 1)

Shift Right – Shift the robotic arm one slot to the right. (Cannot go to the right of slot 20)

Test Empty – Determines if a slot is empty. (Returns True if empty or False if the slot contains a block.)

Included with the robot are functions for each of the above operations coded in the C++ Programming Language.  The code may be downloaded from the assignments tab in Canvas. You will need to write another function that will print out the contents of all 20 slots in order to see how the block placement progresses and to show the final arrangement.

To test your robot write a program that will place a series of blocks into 20 slots in alphabetic order.  Specifically the robot must be able to accomplish this task according to the following requirements:

To begin with all slots must be empty.

The robot must be able to start at any of the 20 slots. (Specified at program start.)

Blocks will enter the chute in random order. 

Blocks entering the chute will have a value from  ‘A’  through ‘Z ‘. (Uppercase alphabetic characters.)

Blocks may repeat. (e.g. there may be two or more blocks with  the same letter value.)

The robot can take only one block from the chute at a time. 

The robot can switch the block it is holding with a block in a given slot. 

The robot can only shift (left or right) one slot at a time. (If you want to shift more than one position you will need to use a loop.)

As blocks are placed into the slots they must be in alphabetic order. (You are not allowed to randomly place all the blocks and then sort them. )

The robot cannot go to the left of slot 1 or to the right of slot 20. (This means that you will have to allow for movement of 
multiple blocks to the left or right in order to stay within the 20 slots.)

You must use the functions provided. However, if you have a better implementation for any of the functions then you may use yours after approval from the instructor.

You may (and you will need to ) write additional functions which are composed of calls to the provided functions. For example, to shuffle multiple blocks left or right to open a slot for a new block.
