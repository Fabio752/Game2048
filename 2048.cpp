
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <ctime>

bool merge_num(std::vector<int>& v, int bi, int ei);
void rotate_anti_clock(std::vector<int>& v);
bool game_over(const std::vector<int>& v);
void print_grid(const std::vector<int>& v);
int row_col_toindex(int row, int col, int rowlen);
bool checkpossiblemoves(std::vector<int> v, int ind);
int setinputgrid(std::vector<int>& v, char move);
void random_place2(std::vector<int>& v);




int main() {
    
    srand(time(NULL));
    bool gameover = false;
    std::vector<int> confgrid;
    std::string inputgrid;
    
    std::cout << "please enter name of file containing the input configuration of the grid: " << std::endl;
    std::cin >> inputgrid;
    
    std::ifstream inputfile;
    inputfile.open(inputgrid.c_str());
    
    // if inputfile is not valid
    if(!inputfile.is_open()){
        std::cout << "error, file not found, using default start configuration: " << std::endl;
        
        //setting vector "confgrid"
        for (int i = 0; i < 15; i++)
            confgrid.push_back(0);
        
        
        confgrid.push_back(2);
    }
    
    //if inputfile is valid
    else {
        int tmp;

        while(inputfile >> tmp)
            confgrid.push_back(tmp);
        
        
    }
    
    print_grid(confgrid); //print on the screen intial configuration
    
    int size = sqrt(confgrid.size());
    gameover = game_over(confgrid); //check whether initial configuration is valid
    
    while (!gameover){
        char move;
        std::cout << "enter a move: " <<std::endl <<"'a' = left" <<std::endl <<"'s' = down" <<std::endl <<"'d' = right" <<std::endl <<"'w' = up" <<std::endl;
        
        std::cin >> move;
        
        while (move != 'a' && move != 's' && move != 'd' && move != 'a'){
            std::cout << "enter a valid move: " <<std::endl <<"'a' = left" <<std::endl <<"'s' = down" <<std::endl <<"'d' = right" <<std::endl <<"'w' = up" <<std::endl;
            std::cin >> move;
        }
        // moves can be:
        // a = merge everything left
        // s = merge everything down
        // d = merge everything right
        // w = merge everything up
        
        int afterrotations = setinputgrid(confgrid, move); //after rotations is the number of rotation the grid has to do in order not to alterate the game
        bool changeinconf = false;

        for (int bi = 0; bi < confgrid.size(); bi = bi + size){
            int ei = bi + size;
            bool tmpbool = merge_num(confgrid, bi, ei);
            
            if (tmpbool)
                changeinconf = true;
            
        }
        
        //reorganize the grid in the right setting
        for (int i = 0; i < afterrotations; i++)
            rotate_anti_clock(confgrid);
        
        
        if (changeinconf){
            random_place2(confgrid);
            print_grid(confgrid); //print on the screen current configuration
            gameover = game_over(confgrid);
        }
        
    }
    
    std::cout <<"GAME OVER" <<std::endl;
    
    return 0;
}



// merging numbers as in the game specification and return a bool on whether the configuration has changed or not
bool merge_num(std::vector<int>& v, int bi, int ei){
    
    bool mergehappened = false;
    std::vector<int> tmpvector;
    int numofzeros = 0;

    for (int i = bi; i < ei; i++){
        
        //vector tmpvector stores the non-zeros values only
        if (v[i] != 0){
            tmpvector.push_back(v[i]);
            
            //if there is a non zero-number and at least a zero has been already counted, the merge happened
            if(numofzeros > 0)
                mergehappened = true;

        }
        else
            numofzeros = numofzeros + 1;
    
    }
    int offset = 0;
    
    //merging operation modifies v that is passed by reference
    for (int i = 0; i < tmpvector.size(); i++){
        
        if (tmpvector[i] == tmpvector[i + 1] && i != tmpvector.size() - 1){
            
            v[bi + offset] = tmpvector[i] * 2;
            i = i + 1;
            mergehappened = true;
            numofzeros = numofzeros + 1;
            
        }
        else
            v[bi + offset] = tmpvector[i];
        
        
        offset = offset + 1;
    }
    
    //filling the merged vector at the end with 0s
    for (int i = 0; i < numofzeros ; i++)
        v[ei - i - 1] = 0;
    
    return mergehappened;
}


//rotates the grid anticlockwise in order to perform the merging with just mergenum function
void rotate_anti_clock(std::vector<int>& v){
    int size = sqrt(v.size());
    std::vector<int> tmpvector;
    
    for (int i = size - 1; i >= 0; i--){
        for (int j = 0; j < size; j++){
            
            int index = row_col_toindex(j, i, size);
            tmpvector.push_back(v[index]);
            
        }
    }
    
    for (int i = 0; i < tmpvector.size(); i++)
        v[i] = tmpvector[i];
    
}


//returns a bool about whether or not the game is over
bool game_over(const std::vector<int>& v){
    int size = sqrt(v.size());
    
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            
            int index = row_col_toindex(i, j, size);
            
            if (checkpossiblemoves(v, index) == false)
                return false;
        
        }
    }
    
    return true;
}



//prints on the screen the current configuration of the grid
void print_grid(const std::vector<int>& v){
    int size = sqrt(v.size());
   
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            
            int index = row_col_toindex(i, j, size);
            std::cout << v[index] << "\t";
            
        }
        std::cout << std::endl;
    }
    
}


//gives as output the index of the item in a one dimention vector
int row_col_toindex(int row, int col, int rowlen){
    return row * rowlen + col;
}



//take in input a vector and the index of a number and tell us if that number can be moved;
bool checkpossiblemoves(std::vector<int> v, int ind){
    
    int size = sqrt(v.size());
    
    //special condition: if the grid has one or more zeros the game is never over
    for (int i = 0; i < v.size(); i++){
        
        if (v[i] == 0)
            return false;
        
    }
    //everything but the top row
    if (ind > size){
        
        if (v[ind] == v[ind-size])
            return false;
        
    }
    //everything but the bottom row
    if (ind < v.size() - size){
        
        if (v[ind] == v[ind + size])
            return false;
        
    }
    //everything but the left column
        if (ind % size != 0 || ind != 0){
            
            if (v[ind] == v[ind - 1])
                return false;
            
        }
    //everything but the right column
    if (ind % (size + 1) != 0){
        
        if (v[ind] == v[ind + 1])
            return false;
        
    }
    
    return true;
}


//because merge_num performs only shifts left, we need a setinputgrid function that, based on the input command, rotates the grid the appropriate number of times and returns the number or rotations left in order to complete the 4 rotations (going back to normal shape)
int setinputgrid(std::vector<int>& v, char move){
    
    if (move == 'w'){
        rotate_anti_clock(v);
        return 3;
    }
    
    if (move == 'd'){
        rotate_anti_clock(v);
        rotate_anti_clock(v);
        return 2;
    }
    
    if (move == 's'){
        rotate_anti_clock(v);
        rotate_anti_clock(v);
        rotate_anti_clock(v);
        return 1;
    }
    
    return 0;
}



//generates a 2 in a random '0' position
void random_place2(std::vector<int>& v){
    std::vector<int> storingpositions;
    
    for (int i = 0; i < v.size(); i++){
        
        if (v[i] == 0)
            storingpositions.push_back(i);
        
    }
    
    int randomindex = rand() % storingpositions.size();
    v[storingpositions[randomindex]] = 2;
}

