#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H
#include <vector>
#include <iostream>

using std::vector;
using namespace std;
class Queue {
	struct Node {
	int data;
	struct Node* next;
};
// Two glboal variables to store address of front and rear nodes. 
struct Node* front = NULL;
struct Node* rear = NULL;

public:
~Queue () {
		Node *p = front;
    Node *pnext;

    while (p != nullptr)
    {
      pnext = p->next;
      delete p;
      p = pnext;
    }
	}
		
	
// To Enqueue an integer
void Enqueue(int x) {
	struct Node* temp = new Node;
	//	(struct Node*)malloc(sizeof(struct Node));
	temp->data =x; 
	temp->next = NULL;
	if(front == NULL && rear == NULL){
		front = rear = temp;
		return;
	}
	rear->next = temp;
	rear = temp;
}

// To Dequeue an integer.
int Dequeue() {
	int deathID=0;
	struct Node* temp = front;
	if(front == NULL) {
		return -1;
	}
	if(front == rear) {
		deathID = temp->data;
		front = rear = NULL;
		return deathID;
	}
	else {
		deathID = temp->data;
		front = front->next;
		return deathID;
	}
	free(temp);
}
};

class GridWorld {

  private:
    // private stuff goes here!
    //   typedefs
    //   data members
    //   private helper functions
    //   etc.
	int worldPopulation = 0;
	int numRows = 0;
	int numCols= 0 ;
	int vectorSize =0;
  public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districtcs) in which all 
    *    districtricts are empty (a wasteland!).
    */
        
    struct ddlNode { 
    int data; 
    struct ddlNode* next; // Pointer to next node in DLL 
    struct ddlNode* prev; // Pointer to previous node in DLL 
    	ddlNode() {
  			next = prev = nullptr; 
			data =0; 	
		}
	};
    
    struct district {
    	
    	ddlNode *front;
    	ddlNode *back;
		int row;
    	int col;
    	int districtPopulation;
    		district() {
    			front = back = nullptr;
    			row = col = districtPopulation = 0;
    			
			}
    	
	};
	
	struct Person {
		int row;
		int col;
		int personID;
		bool alive;
		ddlNode*ddlperson;
			Person () {
				row = col = personID =0;
				alive = false;
				ddlperson = nullptr;
		}
	};
	
	vector<Person*> myPerson_vec;
	district** districtArray;
	Queue deadpool;
	
    GridWorld(unsigned nrows, unsigned ncols)   {

      // your constructor code here!
      this->numRows = nrows;
      this->numCols = nrows; 
      
      districtArray = new district*[numRows];
		for(int i = 0; i < numRows; ++i)
    		districtArray[i] = new district[numCols];
    	
    }
    ~GridWorld(){
       // your destructor code here.
      for (int i=0 ; i < numRows; i++) {
      	for (int j=0 ; j< numCols; j++){
		      	ddlNode *p = districtArray[i][j].front;
				    ddlNode *pnext;
				
				    while (p != nullptr)
				    {
				      pnext = p->next;
				      delete p;
				      p = pnext;
				    }
		      }
      	delete districtArray [i];
	  }
	  delete [] districtArray [numRows];
	  
	  
	  for (int k = 0; k < vectorSize; k++) {
	  	delete myPerson_vec[k];
	  }
    
    
    }

    /*
     * function: birth
     * description:  if row/col is valid, a new person is created
     *   with an ID according to rules in handout.  New person is
     *   placed in district (row, col)
     *
     * return:  indicates success/failure
     */
    //Person myPerson;
    
    bool birth(int row, int col, int &id){
    	if(row <= numRows && col <= numCols) {
    		Person *myPerson = new Person;
    			
    		int valDequeue = deadpool.Dequeue();
    		// Check if deadpool is empty
    		if ( valDequeue == -1) {
    			// If the district is empty
    			if (districtArray[row][col].front == nullptr) {
    				ddlNode *temp = new ddlNode;
    				districtArray[row][col].front = temp;
    				districtArray[row][col].back = temp;
    				temp->prev = nullptr;
    				temp->next = nullptr;
    				temp->data = vectorSize;
    				myPerson->ddlperson = temp;
    				
				}
				// If the district has one node
				else if (districtArray[row][col].front == districtArray[row][col].back) {
					ddlNode * temp = new ddlNode;
					districtArray[row][col].back = temp;
					districtArray[row][col].front->next  = temp;
					temp->prev = districtArray[row][col].front;
					temp->next = nullptr;
					temp->data = vectorSize;
					myPerson->ddlperson = temp;
				}
				// If the district has more than 1 node
				else {
					ddlNode *temp = new ddlNode;
					districtArray[row][col].back->next = temp;
					temp->prev = districtArray[row][col].back;
					districtArray[row][col].back = temp;
					temp->next = nullptr;
					temp->data = vectorSize;
					myPerson->ddlperson = temp;
				}
				districtArray[row][col].row = row;
				districtArray[row][col].col = col;
				
				myPerson_vec.push_back(myPerson);
				myPerson->row = row;
				myPerson->col = col;
				myPerson->personID = vectorSize;
				id = vectorSize;
				myPerson->alive = true;
				vectorSize++;
				districtArray[row][col].districtPopulation++;
				worldPopulation++;
    			return true;
				
			}
			// If deadpool is not empty
			else {
				int recycleID =0;
				recycleID = valDequeue;
				// If the district is empty
    			if (districtArray[row][col].front == nullptr) {
    				ddlNode *temp = new ddlNode;
    				districtArray[row][col].front = temp;
    				districtArray[row][col].back = temp;
    				//cout << "reached" << endl;
    				temp->prev = nullptr;
    				temp->next = nullptr;
    				temp->data = recycleID;
    				myPerson->ddlperson = temp;
				}
				// If the district has one node
				else if (districtArray[row][col].front == districtArray[row][col].back) {
					ddlNode * temp = new ddlNode;
					districtArray[row][col].back = temp;
					districtArray[row][col].front->next  = temp;
					temp->prev = districtArray[row][col].front;
					temp->next = nullptr;
					temp->data = recycleID;
					myPerson->ddlperson = temp;
				}
				// If the district has more than 1 node
				else {
					
					ddlNode *temp = new ddlNode;
					districtArray[row][col].back->next = temp;
					temp->prev = districtArray[row][col].back;
					districtArray[row][col].back = temp;
					temp->next = nullptr;
					temp->data = recycleID;
					myPerson->ddlperson = temp;
				}
				districtArray[row][col].row = row;
				districtArray[row][col].col = col;
				myPerson_vec[recycleID]->row = row;
				myPerson_vec[recycleID]->col = col;
				myPerson_vec[recycleID]->personID = recycleID;
				id = recycleID;
				myPerson_vec[recycleID]->alive = true;
				//vectorSize++;
				districtArray[row][col].districtPopulation++;
				worldPopulation++;
    			return true;
				
				
			}
			
		}
    	else {
    		return false;
		}
      
    }

    /*
     * function: death 
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     *
     * return:  indicates success/failure
     */
    bool death(int personID){
    	int deadPersonRow;
    	int deadPersonCol;
    	if(personID < vectorSize) {
    		deadPersonRow = myPerson_vec[personID]->row;
    		deadPersonCol = myPerson_vec[personID]->col;
			deadpool.Enqueue(personID);
    		//myPerson_vec[personID]->ddlperson = nullptr;				// <<<<<<<<<<<<<<<<Make it null when death function is completed
			myPerson_vec[personID]->alive = false;
			districtArray[deadPersonRow][deadPersonCol].districtPopulation--;
			worldPopulation--;
			
			
			if (districtArray[deadPersonRow][deadPersonCol].front == districtArray[deadPersonRow][deadPersonCol].back) {
				delete districtArray[deadPersonRow][deadPersonCol].front;
				districtArray[deadPersonRow][deadPersonCol].front = nullptr;
				districtArray[deadPersonRow][deadPersonCol].back = nullptr;
				return true;
			}
			else if (myPerson_vec[personID]->ddlperson == districtArray[deadPersonRow][deadPersonCol].front) {
				districtArray[deadPersonRow][deadPersonCol].front = districtArray[deadPersonRow][deadPersonCol].front->next;
				delete districtArray[deadPersonRow][deadPersonCol].front->prev;
				districtArray[deadPersonRow][deadPersonCol].front->prev = nullptr;
				return true;
			}
			else if (myPerson_vec[personID]->ddlperson == districtArray[deadPersonRow][deadPersonCol].back) {
				districtArray[deadPersonRow][deadPersonCol].back = districtArray[deadPersonRow][deadPersonCol].back->prev;
				delete districtArray[deadPersonRow][deadPersonCol].back->next;
				districtArray[deadPersonRow][deadPersonCol].back->next = nullptr;
				return true;
			}
			else {
				myPerson_vec[personID]->ddlperson->prev->next = myPerson_vec[personID]->ddlperson->next;
				myPerson_vec[personID]->ddlperson->next->prev = myPerson_vec[personID]->ddlperson->prev;
				delete myPerson_vec[personID]->ddlperson;
				return true;
			}
			myPerson_vec[personID]->ddlperson = nullptr;
		}
		else {
			return false;
		}

      return false;
    }

    /*
     * function: whereis
     * description:  if given person is alive, his/her current residence
     *   is reported via reference parameters row and col.
     *
     * return:  indicates success/failure
     */
    bool whereis(int id, int &row, int &col)const{
    	if (id< vectorSize){
    		if (myPerson_vec[id]->alive == true) {
    			row = myPerson_vec[id]->row;
    			col = myPerson_vec[id]->col;
    		
    		return true;
		}
      	else {
      		return false;
		  }
		}
		else{
			return false;
		}
	  
    }

    /*
     * function: move
     * description:  if given person is alive, and specified target-row
     *   and column are valid, person is moved to specified district and
     *   data structures updated accordingly.
     *
     * return:  indicates success/failure
     *
     * comment/note:  the specified person becomes the 'newest' member
     *   of target district (least seniority) --  see requirements of members().
     */
    bool move(int id, int targetRow, int targetCol){
    	if (targetRow <= numRows && targetCol <=numCols) {
    		if (myPerson_vec[id]->alive == true) {
    			ddlNode* temp2;
				if (districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].front == districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].back) {
					temp2 = districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].front;
					districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].front = nullptr;
					districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].back = nullptr;	
					districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].districtPopulation--;			
					
				}
				else if (myPerson_vec[id]->ddlperson == districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].front) {
					districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].front = districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].front->next;
					temp2 =  districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].front->prev;
					districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].front->prev = nullptr;
					districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].districtPopulation--;
					
				}
				else if (myPerson_vec[id]->ddlperson == districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].back) {
					districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].back = districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].back->prev;
					temp2 =  districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].back->next;
					districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].back->next = nullptr;
					districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].districtPopulation--;
					
				}
				else {
					myPerson_vec[id]->ddlperson->prev->next = myPerson_vec[id]->ddlperson->next;
					myPerson_vec[id]->ddlperson->next->prev = myPerson_vec[id]->ddlperson->prev;
					temp2 = myPerson_vec[id]->ddlperson;
					districtArray[myPerson_vec[id]->row][myPerson_vec[id]->col].districtPopulation--;
					
				}
					
				temp2->next = nullptr;
				temp2->prev = nullptr;	
					
				// If the district is empty
    			if (districtArray[targetRow][targetCol].front == nullptr) {
    				districtArray[targetRow][targetCol].front = temp2;
    				districtArray[targetRow][targetCol].back = temp2;
    				temp2->prev = nullptr;
    				temp2->next = nullptr;
    				temp2->data = id;
    				myPerson_vec[id]->ddlperson = temp2;
    				districtArray[targetRow][targetCol].districtPopulation++;
    				
				}
				// If the district has one node
				else if (districtArray[targetRow][targetCol].front == districtArray[targetRow][targetCol].back) {
					
					districtArray[targetRow][targetCol].back = temp2;
					districtArray[targetRow][targetCol].front->next  = temp2;
					temp2->prev = districtArray[targetRow][targetCol].front;
					temp2->next = nullptr;
					temp2->data = id;
					myPerson_vec[id]->ddlperson = temp2;
					districtArray[targetRow][targetCol].districtPopulation++;
				}
				// If the district has more than 1 node
				else {
					
					districtArray[targetRow][targetCol].back->next = temp2;
					temp2->prev = districtArray[targetRow][targetCol].back;
					districtArray[targetRow][targetCol].back = temp2;
					temp2->next = nullptr;
					temp2->data = id;
					myPerson_vec[id]->ddlperson = temp2;
					districtArray[targetRow][targetCol].districtPopulation++;
				}
				myPerson_vec[id]->row = targetRow;
				myPerson_vec[id]->col = targetCol;
				return true;
    			
			}
			else {
				return false;
			}
    		
		}
		else {
			return false;
		}
      return false;
    }
	
    std::vector<int>  *members(int row, int col)const{
    	vector <int> *member_vect = new vector <int>;
    	if (row < numRows && col < numCols) {
    		struct ddlNode*temp;
			temp = districtArray[row][col].front;
			
    		for (int i=0; i<districtArray[row][col].districtPopulation; i++) {
    		
    		member_vect->push_back(temp->data);
    		temp = temp->next;
			
    		
			 
    		
    	
			}
			return member_vect;
		}
		else {
			return member_vect;	
		}
      
    }

    /*
     * function: population
     * description:  returns the current (living) population of the world.
     */
    int population()const{
      return worldPopulation;
    }
    
    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row, int col)const{
      return districtArray[row][col].districtPopulation;
    }

    /*
     * function: num_rows
     * description:  returns number of rows in world
     */
    int num_rows()const {
      return numRows;
    }

    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const {
      return numCols;
    }



};

#endif
