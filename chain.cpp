/**
 * File: chain.cpp
 * Description: student implementation for Chain functions
 *              for CPSC 221 2023S PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
 */

#include <math.h>

#include "chain.h"

/**
 * Constructs a Chain from an input image
 * Each Node will cover a nodedimension x nodedimension (in pixels)
 * region in the source image.
 * @param img the input image
 * @param nodedimension number of pixels along the width and height of the Block region
 * @pre input image's width and height are evenly divisible by nodedimension
 */
Chain::Chain(PNG& img, unsigned int nodedimension) {
	cout << "Chain" << endl;
	// complete your implementation below
	// int rowHeight = img.height() / nodedimension;
	// int columnWidth = img.width() / nodedimension;

	// Clear();

	// Chain();

	unsigned int numNodes = 0;

	NW = NULL;
	SE = NULL;

	length_ = 0;

	cout << Length() << endl;

	// if (NW == NULL) {
	// 	cout << "GOOD" << endl;
	// }
	// else {
	// 	cout << "BAD" << endl;
	// 	Clear();
	// }

	Node* curr = NW;

	cout << img.width() << endl;
	cout << img.height() << endl;

	for (unsigned int y = 0; y < img.height(); y += nodedimension) {
        for (unsigned int x = 0; x < img.width(); x += nodedimension) {
			Block block;
			block.Build(img, x, y, nodedimension);

			Node* newNode = new Node(block);
			cout << "A" << endl;

			if (NW == NULL) {
				cout << "B" << endl;
				NW = newNode;
				curr = NW;
			}
			else {
				cout << "C" << endl;
				curr->next = newNode;
				cout << "D" << endl;
				newNode->prev = curr;
				cout << "C" << endl;
				curr = newNode;
			}
			length_++;
			numNodes++;
        }
    }

	curr->next = NULL;

	SE = curr;

	cout << "SE = " << SE->data.Dimension() << endl;
	cout << "NUMBER OF NODES = " << numNodes << endl;

	cout << "LENGTH IS ========================================" << Length() << endl;
}

/**
 * Renders the Chain's pixel data into an output PNG.
 * The PNG should be sized according to the number of nodes
 * specified by the cols parameter.
 * It is possible that there may not be enough nodes to fill
 * the bottom row of the PNG. If this happens, just render
 * as many nodes as there are, from left to right, and leave
 * the rest of the row as opaque white pixels.
 * @pre this Chain is not empty
 * @param cols the number of Blocks to use for the width of the image
 */
PNG Chain::Render(unsigned int cols) {
	cout << "Render Chain" << endl;
	cout << "LENGTH IS ========================================" << Length() << endl;
	// replace the line below with your implementation
	// chain --> Node (data) ---> img

	// cols is actually number of rows
	// columns is actually number of columns
	
	// unsigned int numNodes = 0;
    // Node* curr = NW;
    // while (curr != SE) {
	// 	numNodes++;
	// 	curr = curr->next;
	// }								// now we have number of nodes

	// set curr back to NW
	Node* curr = NW;

	unsigned int numNodes = Length();

	unsigned int rows;
	if (numNodes % cols != 0) {
		// rows = floor(numNodes / cols) + 1;
		rows = ceil(numNodes / cols) + 1;
	}
	else {
		rows = numNodes / cols;
	}

	cout << "columns: " << cols << " " << "rows: " << rows << endl;

	unsigned int blockDimension = curr->data.Dimension();

	unsigned int imgWidth = blockDimension * cols;
	unsigned int imgHeight = blockDimension * rows;

	PNG img(imgWidth, imgHeight);

	cout << "imgWidth: " << imgWidth << " " << "imgHeight: " << imgHeight << endl;

	unsigned int x;
	unsigned int y;

	// for (unsigned int x = 0; x < imgWidth; x += blockDimension) {
    //     for (unsigned int y = 0; y < imgHeight; y += blockDimension) {
	for (y = 0; y < imgHeight; y += blockDimension) {
        for (x = 0; x < imgWidth; x += blockDimension) {
			cout << "Rendering: x =  " << x << " " << "y = " << y << endl;
			if (curr->next != NULL) {
				curr->data.Render(img, x, y);
				curr = curr->next;
			}
			else {
				curr->data.Render(img, x, y);
				break;
			}
        }
    }

	cout << "GYYYYYYYYYYYYYYAT x: " << x << " " << "y: " << y << endl;
	// cols = 4, rows = 2 --> x = 40, y = 

	return img;
}

/**
 * Inserts a new Node containing ndata at the back of the Chain
 */
void Chain::InsertBack(const Block& ndata) {
	// complete your implementation below

	Node* newNode = new Node(ndata);

	if (NW == NULL) {
		NW = newNode;
		SE = newNode;
	}
	else {
		SE->next = newNode;
		newNode->prev = SE;
		newNode->next = NULL;
		SE = newNode;
	}

	length_++;

}

/**
 * Reverses the structure of the list. This must be done by
 * pointer assignments. You may not deallocate or allocate any Nodes.
 * Example:
 *	before:	NW -> A <-> B <-> C <-> D <-> E <-> F <-> G <-> H <- SE
 *  
 *  after:	NW -> H <-> G <-> F <-> E <-> D <-> C <-> B <-> A <- SE
 */
void Chain::Reverse() {
	// complete your implementation below

	cout << "reverse LENGTH IS ========================================" << Length() << endl;

	Node* front = NW->next;
	Node* back = NW;

	back->next = NULL;
	back->prev = front;

	SE = back;

	while (front != NULL) {
		front->prev = front->next;
		front->next = back;
		back = front;
		front = front->prev;
	}

	NW = back;

	cout << "reverse LENGTH IS ========================================" << Length() << endl;
	
}

/**
 * Rearranges the Node structure and internal pixel data to be flipped over a vertical axis.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *  before, flipping with 3 columns (2 rows):
 *
 *		NW -> A> <-> B> <-> C> <->
 *            D> <-> E> <-> F> <- SE
 * 
 *  after, visualized with 3 columns (2 rows):
 * 
 *		NW -> <C <-> <B <-> <A <->
 *            <F <-> <E <-> <D <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
 */
void Chain::FlipHorizontal(unsigned int cols) {
	// complete your implementation below

	// Node* curr = NW;

	// unsigned int numNodes = 0;
	// while (curr != NULL) {
	// 	curr->data.FlipHorizontal();
	// 	curr = curr->next;
	// 	numNodes++;
	// }

	// Node* front = NW->next;
	// Node* back = NW;
	// Node* oldHead = back;

	// unsigned int nodeCounter = 1;
	// unsigned int rowsCompleted = 0;

	// while (rowsCompleted < (numNodes / cols)) {
	// 	cout << "Flipping: rowsCompleted =  " << rowsCompleted << endl;
	// 	back->next = NULL;
	// 	back->prev = front;
	// 	while (nodeCounter < cols) {
	// 		cout << "test 1" << endl;
	// 		front->prev = front->next;
	// 		cout << "test 2" << endl;
	// 		front->next = back;
	// 		cout << "test 3" << endl;
	// 		back = front;
	// 		cout << "test 4" << endl;
	// 		front = front->prev;
	// 		cout << "test 5" << endl;
	// 		nodeCounter++;
	// 	}
	// 	// <C <-> <B <-> <A <->
	// 	// front is D, back is C, oldHead is A, nodeCounter = 3
	// 	// reset nodeCounter
	// 	nodeCounter = 1;
	// 	rowsCompleted++;

	// 	// set C->prev to NULL, connect A to F, and make NW point to C
	// 	if  (rowsCompleted == 1) {
	// 		cout << "test 6" << endl;
	// 		back->prev = NULL;
	// 		cout << "test 7" << endl;
	// 		oldHead->next = SE;
	// 		// SE->prev = oldHead;
	// 		NW = back;
	// 	}

	// 	// connect F to A
	// 	if (rowsCompleted == (numNodes / cols)) {
	// 		cout << "test 8" << endl;
	// 		back->prev = oldHead;
	// 	}

	// 	// move front to E and back to D and repeated reverse
	// 	if (rowsCompleted < (numNodes / cols) && front->next != NULL) {
	// 		cout << "test 9" << endl;
	// 		back = front;
	// 		cout << "test 10" << endl;
	// 		front = front->next;
	// 	}

	// }

	// for (unsigned int i = 0; i < cols - 1; i++) {
	// 	SE = back->next;
	// }

	Node* curr = NW;

	while (curr != NULL) {
		curr->data.FlipHorizontal();
		curr = curr->next;
	}

	vector<vector<Node*>> doubleArray;

	unsigned int rows = (Length() / cols);

	doubleArray.resize(rows);

    for (unsigned int i = 0; i < rows; i++) {
        doubleArray[i].resize(cols);
    }

	// we have a 2D array that we are going to populate with Node addresses

	curr = NW;

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			doubleArray[i][j] = curr;
			curr = curr->next;
		}
		// curr = curr->next;
	}

	// now 2D array has <<A, B, C> , <D, E, F>>
	// need to swap elements in inner array

	for (unsigned int i = 0; i < rows; i++) {
		unsigned int first = 0;
		unsigned int last = cols - 1;

		while (first < last){
			Node* temp = doubleArray[i][first];
			doubleArray[i][first] = doubleArray[i][last];
			doubleArray[i][last] = temp;
			first++;
			last--;
		}
	}

	// now 2D array has <<C, B, A> , <F, E, D>>
	// we convert 2D array to 1D array

	vector<Node*> singleArray;
	unsigned int k = 0;

	singleArray.resize(Length());

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			singleArray[k] = doubleArray[i][j];
			k++;
		}
	}

	// now we connect the 1D array and make it a doubly linked list

	NW = singleArray[0];		// NW = C
	curr = singleArray[1];		// curr = B

	NW->prev = NULL;
	NW->next = curr;
	curr->prev = NW;

	k = 2;

	while (k < Length()) {
		Node* tail = curr;
		curr = singleArray[k];		// curr = A
		tail->next = curr;
		curr->prev = tail;

		k++;
	}

	// curr is singleArray[5] which is D
	curr->next = NULL;
	SE = curr;

}

/**
 * Rearranges the Node structure and internal pixel data to be rotated counter-clockwise.
 * This must be done using pointer assignments.
 * You may not deallocate or allocate any Nodes.
 * Example, length = 6:
 *	before, rotating with 3 columns (2 rows):
 *            ^     ^     ^
 *      NW -> A <-> B <-> C <->
 *            ^     ^     ^
 *            D <-> E <-> F <- SE
 * 
 *  after, visualized with 2 columns (3 rows):
 * 
 *      NW -> <C <-> <F <->
 *            <B <-> <E <->
 *            <A <-> <D <- SE
 * 
 * @param cols number of Blocks to use for the initial width of the image
 * @pre length_ is divisible by cols (i.e. no "partially-filled" rows)
 */
void Chain::RotateCCW(unsigned int cols) {
	// complete your implementation below

	// Node* curr = NW;

	// unsigned int numNodes = 0;
	// while (curr != NULL) {
	// 	curr->data.RotateCCW();
	// 	curr = curr->next;
	// 	numNodes++;
	// }

	// curr = NW;

	// for (unsigned int i = 1; i < cols; i++) {
	// 	curr = curr->next;
	// }

	// // curr = C

	// while (curr != NULL) {
	// 	curr->next = SE;
	// 	curr = curr->prev;
	// 	SE->next = curr;
	// 	SE = SE->prev;
	// }
	
	// // SE = C
	// NW = SE;
	// SE->prev = NULL;
	// Node* tail;

	// while (SE != NULL) {
	// 	tail = SE;
	// 	SE = SE->next;
	// 	if (SE == NULL) {
	// 		break;
	// 	}
	// 	else {
	// 		SE->prev = tail;
	// 	}
	// }

	// // tail = D
	// SE = tail;
	// Node* curr = NW;
	
	// while (curr != NULL) {
	// 	curr->data.RotateCCW();
	// 	curr = curr->next;
	// }


	// curr = NW;
	// vector<Node*> arrayOriginal;

	// arrayOriginal.resize(Length());

	// // populate array with Blocks from Chain
	// for (unsigned int i = 0; i < Length(); i++) {
	// 	arrayOriginal[i] = curr;
	// 	curr = curr->next;
	// }

	// // array now has <A, B, C, D, E, F>
	// cout << arrayOriginal[0] << " " << arrayOriginal[1] << " " << arrayOriginal[2] << " "  << arrayOriginal[3] << " " << arrayOriginal[4] << " " << arrayOriginal[5] <<  endl;
	// // if cols = 3, need to copy every 3rs element then decrement
	
	// vector<Node*> arraySwap;
	// arraySwap.resize(Length());

	// int swapFactor = cols - 1;
	// unsigned int index = 0;
	// unsigned int rows = Length() / cols;
	
	// // unsigned int innerIndex = 0;
	// while (index < Length()) {
	// 	unsigned int innerIndex = 0;
	// 	for (unsigned int i = 0; innerIndex < rows; i += cols) {
	// 		if (index % 2 == 0) {
	// 			arraySwap[index] = arrayOriginal[swapFactor];
	// 		}
	// 		else {
	// 			arraySwap[index] = arrayOriginal[i + swapFactor];
	// 		}
	// 		index++;
	// 		innerIndex++;
	// 	}
	// 	// index++;
	// 	swapFactor--;
	// }

	// // unsigned int first = cols - 1;
	// // unsigned int last = Length() - 1;
	// // unsigned int i = 0;

	// // while (first < Length()) {
	// // 	arraySwap[i] = arrayOriginal[first];
	// // 	i++;
	// // 	arraySwap[i] = arrayOriginal[last];
	// // 	i++;
	// // 	first--;
	// // 	last--;
	// // }


	// // arraySwap is now <C, F, B, E, A, D>
	// cout << arraySwap[0] << " " << arraySwap[1] << " " << arraySwap[2] << " "  << arraySwap[3] << " " << arraySwap[4] << " " << arraySwap[5] <<  endl;
	// // connect to doubly linked list

	// NW = arraySwap[0];		// NW = C
	// curr = arraySwap[1];	// curr = F
	
	// NW->prev = NULL;
	// NW->next = curr;
	// curr->prev = NW;
	
	// unsigned int k = 2;

	// while (k < Length()) {
	// 	Node* tail = curr;
	// 	curr = arraySwap[k];		// curr = B
	// 	tail->next = curr;
	// 	curr->prev = tail;

	// 	k++;
	// }
	
	// // curr is singleArray[5] which is D
	// curr->next = NULL;
	// SE = curr;

	Node* curr = NW;
	
	while (curr != NULL) {
		curr->data.RotateCCW();
		curr = curr->next;
	}

	vector<vector<Node*>> doubleArray;

	unsigned int rows = (Length() / cols);

	doubleArray.resize(rows);

    for (unsigned int i = 0; i < rows; i++) {
        doubleArray[i].resize(cols);
    }

	// we have a 2D array that we are going to populate with Node addresses

	curr = NW;

	for (unsigned int i = 0; i < rows; i++) {
		for (unsigned int j = 0; j < cols; j++) {
			doubleArray[i][j] = curr;
			curr = curr->next;
		}
		// curr = curr->next;
	}

	// now 2D array has <<A, B, C> , <D, E, F>>
	// we convert 2D array to 1D array but in reverse

	vector<Node*> singleArray;
	unsigned int k = 0;

	singleArray.resize(Length());

	for (int j = cols - 1; j >= 0; j--) {
		for (unsigned int i = 0; i < rows; i++) {
			singleArray[k] = doubleArray[i][j];
			k++;
		}
	}

	// 1D array is now <C, F, B, E, A, D>
	// now we connect the 1D array and make it a doubly linked list

	NW = singleArray[0];		// NW = C
	curr = singleArray[1];		// curr = F

	NW->prev = NULL;
	NW->next = curr;
	curr->prev = NW;

	k = 2;

	while (k < Length()) {
		Node* tail = curr;
		curr = singleArray[k];		// curr = B
		tail->next = curr;
		curr->prev = tail;

		k++;
	}

	// curr is singleArray[5] which is D
	curr->next = NULL;
	SE = curr;

}

/**
 * Destroys all dynamically allocated memory associated with
 * this Chain object. Called by destructor and operator=.
 * You must complete its implementation for PA1.
 */
void Chain::Clear() {
	// complete your implementation below

	// 	Node* curr;

	// 	while(NW != NULL) {
	//     curr = NW;
	//     NW = NW->next;
	//     free(curr);
	//   }

	cout << "LENGTH IS ========================================" << Length() << endl;

	Node* curr = NW;

	if (NW == NULL) {
		cout << "NULL NW" << endl;
	}
	else {
		cout << "hello NW" << endl;
	}

	if (SE == NULL) {
		cout << "NULL SE" << endl;
	}
	else {
		cout << "hello SE" << endl;
	}

	while(NW != NULL) {
		cout << "yo" << endl;
		curr = NW;
		cout << "yoyo" << endl;
		if (NW->next == NULL) {
			// cout << "AH" << endl;
			break;
		}
		else {
			cout << "AHHHHHHH" << endl;
			NW = NW->next;
		}
		cout << "yoyoyo" << endl;
		delete curr;
		cout << "yoyoyoyo" << endl;
		curr = NULL;
	}

	if (NW == NULL) {
		cout << "yea it's NULL" << endl;
	}
	else {
		cout << "sike" << endl;
		// NW = NW->next;
	}

	// NW is the last Block
	cout << "delete" << endl;
	delete NW;
	cout << "NW = NULL" << endl;
	NW = NULL;
	cout << "NW = NULL" << endl;
	cout << "SE = NULL" << endl;
	SE = NULL;
	cout << "SE = NULL" << endl;

	// set length to 0
	length_ = 0;

	cout << "LENGTH IS ========================================" << Length() << endl;

}

/**
 * Copies the parameter other Chain into the current Chain.
 * Does not free any memory. Called by copy constructor and
 * operator=.
 * You must complete its implementation for PA1.
 * @param other The Chain to be copied.
 */
void Chain::Copy(const Chain& other) {
	// complete your implementation below
	
	cout << "I AM CALLED HELLOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO" << endl;

	// Node* curr = other.NW;
	// Node* head = curr;

	// while (curr != NULL) {
	// 	curr = curr->next;
	// }

	// NW = head;

	NW = NULL;
	SE = NULL;
	length_ = 0;

	Node* currOther = other.NW;

	// create first node and assign NW and SE to it
	// Node* newNode = new Node(currOther->data);
	// NW = newNode;
	// SE = newNode;
	// currOther = currOther->next;

	while (currOther->next != NULL) {
		InsertBack(currOther->data);
		currOther = currOther->next;
	}

	// currOther is the last Block in other
	// need to get data for last Block
	InsertBack(currOther->data);

}

/**
 * If you have declared any private helper functions in chain_private.h,
 * add your completed implementations below.
 */
