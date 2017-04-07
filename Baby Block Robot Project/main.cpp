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
char switch_blocks(char robot, unsigned int position, char array[], unsigned int &switch_count);
bool test_empty(unsigned int position, char array[]);
unsigned int findMid(char *blocks);
void printBlockLayout(char *blocks);
char *sort(char *blocks, unsigned int index, char &current_block, int &increment, unsigned int &switch_count, unsigned int sort_iteration);
unsigned int search(char &current_block, char *blocks, unsigned int increment_coefficient, int &increment, unsigned int &switch_count);

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
    
    for(int j = 0; j < 19; j++){
        cout << "Please enter a character for the next block" << endl;
        
        if(j < 9)
            increment_coefficient = 2;
        else
            increment_coefficient = 1;
        
        current_block = get_block();
        blocks = sort(blocks, search(current_block, blocks, increment_coefficient, increment, switch_count), current_block, increment, switch_count, 0);
        
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

unsigned int search(char &current_block, char *blocks, unsigned int increment_coefficient, int &increment, unsigned int &switch_count){
    unsigned int index = 0;
    
    index = findMid(blocks);
    if(current_block > blocks[index])
        increment = 1*increment_coefficient;
    else if(current_block < blocks[index]){
        //cout << current_block << "<" << blocks[index] << endl; //TEST
        increment = -1*increment_coefficient;
    }
    else
        return index;
    //cout << "current increment after first set is: " << increment << endl; //TEST
    do{
        index += increment;
        cout << "incremented to index" << index << endl;
    }
    while(!(index >= 19 || index <= 0 
            || (current_block > blocks[index] && current_block > blocks[index+2] && increment < 0)
            || (current_block < blocks[index] && current_block < blocks[index+2] && increment > 0)
            || (current_block == blocks[index])));

    if(test_empty(index,blocks))
        return index;
    if(index < 19 && index > 0){ //if we're not outside of the array..
        current_block = switch_blocks(current_block, index, blocks, switch_count); //We'll switch the blocks.
        return index += increment; //then we need to send our new current block into the sorting function with the next index
    }\

    else{ //But if we ARE outside of the array
        if (index >= 19) { //then if we're to the right of the max index
            index = 19;
            if(test_empty(index,blocks)) //We now need to see if it's empty. If it is, we will just put the block down
                put_block(current_block, index, blocks);
            else{
                current_block = switch_blocks(current_block, index, blocks, switch_count); //If not, we'll need switch the current block with the last block in the array, at index 19.
                increment *= -1;
                return index + increment; //Then we can take a step forwards or backwards from the first or last index before we send it to the sorting function.
            }
        }
        else{ //If we're to the left of the min index
            index = 0;
            if(test_empty(index,blocks)) //We now need to see if it's empty. If it is, we will just put the block down
                put_block(current_block, index, blocks);
            else{
                current_block = switch_blocks(current_block, index, blocks, switch_count); //We'll need switch the current block with the first block in the array, index 0.
                increment *= -1;
                return index + increment; //Then we can take a step forwards or backwards from the first or last index before we send it to the sorting function.
            }
        }
    }
        
}

char *sort(char *blocks, unsigned int index, char &current_block, int &increment, unsigned int &switch_count, unsigned int eoa_count){
    cout << "index: " << index << endl;
    if(index < 19 && index > 0){ //if we're not outside of the array..
        if(test_empty(index, blocks) == true) //see if the slot is empty
            put_block(current_block, index, blocks); //if it is, put the block there and be done.
        
        else{ //if it's not empty
            current_block = switch_blocks(current_block, index, blocks, switch_count); //we'll switch the blocks
            index += increment; //Then we can step to the next index.
            blocks = sort(blocks, index, current_block, increment, switch_count, eoa_count); //And use recursion to sort our new current_block!
        }
    }
    else{ //but if we ARE outside of the array..
        if(index >= 19) { //If we're to the right of the max index
            index = 19;
            if(test_empty(index,blocks)) //See if it's empty and if we can just put the block down
                put_block(current_block, index, blocks);
            else{ //If it's not empty
                current_block = switch_blocks(current_block, index, blocks, switch_count); //We'll need switch the current block with the last block in the array, at index 19. 
                if(eoa_count == 0) ///If we reach the end of the array in our first iteration, we need to switch the way that we're stepping.
                    increment *= -1; //But if it's not in the first iteration, we don't want to keep switching the way that we're going.
                index += increment; //So now we will be stepping backwards to sort.
                eoa_count++; //Increment the end of array count.
                blocks = sort(blocks, index, current_block, increment, switch_count, eoa_count); //And we can use recursion to sort the rest.
            }
        }
        
        if (index < 0) { //Then if we're to the left of the min index
            index = 0;
            if(test_empty(index,blocks)) //See if it's empty and if we can just put the block down
                put_block(current_block, index, blocks);
            else{ //if it's not empty..
                current_block = switch_blocks(current_block, index, blocks, switch_count); //We'll need switch the current block with the first block in the array, index 0.
                if(eoa_count == 0) ///If we reach the end of the array in our first iteration, we need to switch the way that we're stepping.
                    increment *= -1; //But if it's not in the first iteration, we don't want to keep switching the way that we're going.
                index += increment; //So now we will be stepping backwards to sort.
                eoa_count++;
                blocks = sort(blocks, index, current_block, increment, switch_count, eoa_count); //And we can use recursion to sort the rest.
            }
        }
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
        cout << "Current switch count: " << switch_count << endl;
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
	if  (array[position] == 0)
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