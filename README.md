# ADT_01_singly_linked_list

Author: Mahdi Aouchiche (https://github.com/mahdi-aouchiche/ADT_01_singly_linked_list)

* Implementation of Singly Linked List in an example.
* The example is to create a song playlist which holds records of data.
* A new node is created for each song which holds the song data.
* A playlist of songs is represented by a singly linked list of all the song nodes.
* Google unit testing "Gtest" is added to verify the functionality of the class functions. 
* The user interface allows to:
    1. ***Create new song.***
    2. ***Delete a song.***
    3. ***Move a song position in the list.***
    4. ***Display the full playlist.***
    5. ***Display all the songs by a given artist name.***
    6. ***Output total playlist time.***  

### To run the project nicely run the following commands ###
```c++
mkdir build
cd build
cmake ..
make 
```
### 2 executables are created, use the following commands to run an executable: ###
```c++
// run the unit tests
./playlist_test

// run the code
./playlist
```