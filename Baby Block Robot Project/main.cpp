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
char switch_blocks(char robot, unsigned int position, char array[], unsigned int & switch_count);
bool test_empty(unsigned int position, char array[]);
unsigned int findMid(char *blocks);
void printBlockLayout(char *blocks);
char *sort(char *blocks, unsigned int index, char current_block, int increment, unsigned int switch_count);
unsigned int search(char &current_block, char *blocks, unsigned int increment_coefficient, int &increment, unsigned int switch_count);

int main(void){
    char *blocks, current_block;
    unsigned int start_pos = 0, increment_coefficient = 1, switch_count = 0;
    int increment = 1;
    
    blocks = new char[20];
    for(int i = 0; i < 20; i++)
        blocks[i] = 0; //Initialize all of the elements in our block array to zero.
    cout << "Blocks = " << blocks << endl;
    
    cout << "Hello, I am the Baby Block 270 Robot. Please specify the starting slot (0-19):" << endl;
    cin >> start_pos;
    
    cout << left << "Your starting position is " << start_pos << "." << endl;
    
    cout << "Please enter character for the first block." << endl;
    blocks[start_pos] = get_block();
    
    printBlockLayout(blocks);
    
    for(int j = 1; j <= 20; j++){
        cout << "Please enter a character for the next block" << endl;
        if(j > 10)
            increment_coefficient = 2;
        blocks = sort(blocks, search(current_block, blocks, increment_coefficient, increment, switch_count), current_block, increment, switch_count);
        
        printBlockLayout(blocks);
    }
    
    
    return 0;
}

void printBlockLayout(char *blocks){
    cout << endl << "Current block layout: " << endl;
        for (int i = 0; i < 20; i++) {
            if (blocks[i] != 0)
                cout << setw(3) << blocks[i];
            else
                cout << setw(3) << "-";
        }
    cout << endl;
}
unsigned int findMid(char *blocks){ //Function used to find the index of the current middle baby block.
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

unsigned int search(char &current_block, char *blocks, unsigned int increment_coefficient, int &increment, unsigned int switch_count){
    unsigned int index = 0;
    
    index = findMid(blocks);
    if(current_block > blocks[index])
        increment = 1*increment_coefficient;
    else if(current_block < blocks[index])
        increment = -1*increment_coefficient;
    else
        return index;
    
    do
        index += increment;
    while(!(index >= 19 || index <= 0 
            || test_empty(index,blocks) 
            || (current_block > blocks[index] && increment < 0)
            || (current_block < blocks[index] && increment > 0)
            || (current_block == blocks[index])));

    if(test_empty(index,blocks))
        return index;
    else if(index > 19){ //If we're to the right of the max index
        current_block = switch_blocks(current_block, 19, blocks, switch_count); //We'll need switch the current block with the last block in the array, at index 19.
        return index -= increment; //Then we can take a step backwards so that we 
    }
    else if(index < 0){ //Then if we're to the left of the min index
        current_block = switch_blocks(current_block, 0, blocks, switch_count); //We'll need switch the current block with the first block in the array, index 0.
        return index -= increment;
    }
    else{ //if it's out of our index
        current_block = switch_blocks(current_block, index, blocks, switch_count); //We'll switch the blocks.
        return index += increment; //then we need to send our new current block into the sorting function with the net index
    }
        
}

char *sort(char *blocks, unsigned int index, char current_block, int increment, unsigned int switch_count){
    if(index < 19 && index > 0){ //if we're not outside of the array..
        if(test_empty(index, blocks) == true) //see if the slot is empty
            put_block(current_block, index, blocks); //if it is, put the block there and be done.
        
        else //if it's not empty
		do {
                    switch_blocks()
                    shift_right;
                    switch_blocks;
                    count++;
		}while (blocks[index] !> 19 && !(test_empty == true));
		put_block(current_block, index, blocks);
    }
    index += increment;

    if (index > 19 && index < 0)
	{
		do {
		shift_left;
		switch_blocks;
		count++;
		}while(!(test_empty == true));
		put_block(current_block, [index], blocks);
	}
    return blocks;
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

unsigned int put_block(char block, unsigned int position, char *blocks)
{
	blocks[position] = block;
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

char switch_blocks(char robot, unsigned int position, char *blocks, unsigned int &switch_count)
{
	char temp_hold;

	cout << "Switching blocks " << robot << " with " << blocks[position] << endl;
	temp_hold = robot;
	robot = blocks[position];
	blocks[position] = temp_hold;
        switch_count++;
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