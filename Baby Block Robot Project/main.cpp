/* 
 * File:   main.cpp
 * Author: Sean Widmier, Jennifer Miller
 *
 * Created on April 4th, 2017, 12:37 PM
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>

using namespace std;

char get_block(void);
unsigned int put_block(char block, unsigned int position, char array[]);
unsigned int shift_right(unsigned int position);
unsigned int shift_left(unsigned int position);
bool compare_blocks(char robot, char in_slot);
char switch_blocks(char robot, unsigned int position, char array[]);
bool test_empty(unsigned int position, char array[]);
unsigned int compSeq(char current_block, char blocks[20], unsigned int N);
unsigned int findMid(char blocks[20]);
void printBlockLayout(char blocks[20]);

int main(void){
    char blocks[20] = {0}, current_block, index;
    unsigned int start_pos = 0, N = 1;
    
    cout << "Hello, I am the Baby Block 270 Robot. Please specify the starting slot (0-19):" << endl;
    cin >> start_pos;
    
    cout << left << "Your starting position is " << start_pos << "." << endl;
    
    cout << "Please enter character for the first block." << endl;
    blocks[start_pos] = get_block();
    
    printBlockLayout(blocks);
    
    for(int j = 1; j <= 20; j++){
        cout << "Please enter a character for the next block" << endl;
        if(j > 10)
            N = 2;
        index = compSeq(get_block(), blocks, N);
        
        printBlockLayout(blocks);
    }
    
    
    return 0;
}

void printBlockLayout(char blocks[20]){
    cout << endl << "Current block layout: " << endl;
        for (int i = 0; i < 20; i++) {
            if (blocks[i] != 0)
                cout << setw(3) << blocks[i];
            else
                cout << setw(3) << "-";
        }
    cout << endl;
}
unsigned int findMid(char blocks[20]){ //Function used to find the index of the current middle baby block.
    unsigned int N = 0, mid = 0, index = 0;
    
    for(int i = 0; i < 20; i++){
        if(blocks[i] != 0)
            N++;
    }
    //cout << "N = " << N << endl; 
    if(N % 2 == 0)
        mid = N/2;
    else
        mid = (N/2)+1;
    //cout << "mid = " << mid << endl;
    
    for(int i = 0; i < 20; i++){
        if(blocks[i] != 0)
            index++;

        if(index == mid)
            return i;
    }
}

unsigned int compSeq(char current_block, char blocks[20], unsigned int N){
    unsigned int index = 0;
    int increment = 1;
    
    index = findMid(blocks);
    if(current_block > blocks[index])
        increment = 1*N;
    else if(current_block < blocks[index])
        increment = -1*N;
    else
        return index;
    
    do
        index += increment;
    while(!(index >= 19 || index <= 0 
            || test_empty(index,blocks) 
            || (current_block > blocks[index] && increment < 0)
            || (current_block < blocks[index] && increment > 0)
            || (current_block == blocks[index])));

    if(index > 19 || index < 0)
        return index-1;
    else
        return index;
}

// ------------------------------------------------------------------------ //
//																			//
//																			//
//				Functions for the seven robot operations					//
//																			//
//																			//
// ------------------------------------------------------------------------ //

//
// Function get_block
// Reads in a single character value from the keyboard 
// This is the input from the chute
// Returns: a single character
//
// Example function call: 	block = get_block();

char get_block(void)
{
	char block;
	cin >> block;
        block = toupper(block);
	return block;
}

// Function put_block
// This function stores a character into the character array representing the slots
//
// Inputs: 
// block - type char - The character to be inerted into a slot
// position - type unsigned int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// position - type unsigned int - the index of the slot where the block was placed
//
// Example function call: 	put_block(block, position, slots);

unsigned int put_block(char block, unsigned int position, char array[])
{
	array[position] = block;
	cout << "Block " << block << " inserted into slot " << position << endl;
	return position;
}

// Function shift_right
// This function increments the index simulating a movement of the robot 
// to the next higher slot (index) of the array
// 
// Inputs:
// position - type unsigned int - current slot position
//
// Returns:
// position - type unsigned int - The updated position which is input position + 1
//
// Example function call:  position = shift_right(position)
//

unsigned int shift_right(unsigned int position)
{
	position++;
	cout << "Position right shifted to " << position << endl;
	return position;
}

// Function shift_left
// This function decrements the index simulating a movement of the robot 
// to the next lower slot (index) of the array
// 
// Inputs:
// position - type unsigned int - current slot position
//
// Returns:
// position - type unsigned int - The updated position which is input position - 1
//
// Example function call: position = shift_left(position)
//

unsigned int shift_left(unsigned int position)
{
	position--;
	cout << "Position left shifted to " << position << endl;
	return position;
}

// Function compare_blocks
// This function compares the value of the block held by the robot 
// with the value of the block in a slot 
// 
// Inputs:
// robot - type char - value of block held by robot
// in_slot - type char - value of block in the slot
//
// Returns:
// true or false
// TRUE if block held by robot is LESS than or equal to the block in slot
// FALSE if block held by robot is GREATER than block in slot
//
// Example function call: if ( compare_blocks(robot_block, slot_block) )
//
bool compare_blocks(char robot, char in_slot)
{
	
	cout << endl <<  "Comparing robot block " << robot << " with block in slot " << in_slot << endl;
	if (robot <= in_slot)
	{
		cout << "returning true. Robot block LESS than or EQUAL to block in slot. " << endl;
		return true;
	}
	else
	{
		cout << "returning false. Robot block GREATER than block in slot. " << endl;
		return false;
	}
}
// Function switch_blocks
// This function switches the block held by the robot with a block in a slot. 
// After the switch the robot is holding the block removed from the slot.
// 
// Inputs: 
// robot - type char - The block to be inserted into a slot
// position - type unsigned int - index of the slot where the block will go
// array - type char - array of slots containing the blocks
//
// Returns:
// robot - type char. The value of the block removed from the slot.
//
// Example function call: block = switch_blocks(block,  position, array);
//

char switch_blocks(char robot, unsigned int position, char array[])
{
	char temp_hold;

	cout << "Switching blocks " << robot << " with " << array[position] << endl;
	temp_hold = robot;
	robot = array[position];
	array[position] = temp_hold;
	return robot;
}
// Function test_empty
// This function tests the array to determine if a slot is empty (NULL) 
// 
// Inputs:
// position - type unsigned int - index of slot to be tested
//
// Returns:
// true or false as value o function
// TRUE if slot is empty
// FALSE if the slot contains a block
//
// Example function call: if ( test_empty(index, array) )
//
bool test_empty(unsigned int position, char array[])
{
	if  (array[position] == NULL)
	{
		cout << "Slot " << position << " empty. " << endl;
		return true;
	}
	else
	{
		cout << "Slot " << position << " contains a block " << endl;
		return false;
	}

}