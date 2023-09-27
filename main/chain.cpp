
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
	// complete your implementation below
	  NW = NULL;
      SE = NULL;
      length_ = 0;

	int imgArea = img.height() * img.width();
	int nodeArea = nodedimension * nodedimension;
	int numberOfNodes = imgArea / nodeArea;

	int numberOfNodesAlongWidth = img.width() / nodedimension;
	int numberOfNodesAlongHeight = img.height() / nodedimension;

	for (int y = 0; y < numberOfNodesAlongHeight; y++){
		for (int x = 0; x < numberOfNodesAlongWidth; x++){
     		Block block;
			block.Build(img, x * nodedimension , y * nodedimension, nodedimension);
			InsertBack(block);
		}
	}

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
	// replace the line below with your implementation

	unsigned int dimension = NW->data.Dimension();
	unsigned int pngWidth = cols * dimension;
	int numRows = static_cast<int>(ceil(length_ / static_cast<double>(cols)));
	unsigned int pngHeight = numRows * dimension;

	Node * temp = NW;
	PNG image(pngWidth, pngHeight);
	for (unsigned int y = 0; y < pngHeight; y+= dimension){
		for (unsigned int x = 0; x < pngWidth; x+= dimension){
			if (temp != NULL){
				temp->data.Render(image, x , y);
				temp = temp->next;
			}
		}
	}

	return image;
	
}



/**
 * Inserts a new Node containing ndata at the back of the Chain
 */
void Chain::InsertBack(const Block& ndata) {
	// complete your implementation below
 
 	Node* newNode = new Node(ndata);

		if (SE == NULL) {
            NW = newNode;
            SE = newNode;
            newNode->prev = NULL;
            newNode->next = NULL;
        } else {
			newNode->next = NULL;
			newNode->prev = SE;
            SE->next = newNode;
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

	Node* current = NW;
    Node* prev = nullptr;

    while (current != nullptr) {
        Node* next = current->next;
        current->next = prev;
        current->prev = next;
        prev = current;
        current = next;
    }

    // Swap NW and SE pointers
    Node* temp = NW;
    NW = SE;
    SE = temp;
	
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
    int rows = length_ / cols;
    vector<Node*> flippedNodes;

    for (int i = cols; i <= length_; i += cols) {
        for (int j = i; j > i - cols; j--) {
            Node* current = searchByIdx(j);
            current->data.FlipHorizontal();
            flippedNodes.push_back(current);
        }
    }

    // Update the pointers
    if (!flippedNodes.empty()) {
        flippedNodes[0]->prev = nullptr;
        NW = flippedNodes[0];

        for (size_t i = 0; i < flippedNodes.size() - 1; i++) {
            flippedNodes[i]->next = flippedNodes[i + 1];
            flippedNodes[i + 1]->prev = flippedNodes[i];
        }

        SE = flippedNodes.back();
        SE->next = nullptr;
    }
}



Node* Chain::searchByIdx(int index) {
    Node* currentNode = NW;

    int i = 0;
    while (currentNode != nullptr && i < index - 1) {
        currentNode = currentNode->next;
        i++;
    }

    return currentNode;
}

void Chain::RotateCCW(unsigned int cols) {
    vector<Node*> rotatedNodes;

    for (int i = cols; i > 0; i--) {
        Node* current = searchByIdx(i);
        current->data.RotateCCW();
        rotatedNodes.push_back(current);

        for (int j = i + cols; j <= length_; j += cols) {
            Node* next = searchByIdx(j);
            next->data.RotateCCW();
            rotatedNodes.push_back(next);
        }
    }

    // Update the pointers
    if (!rotatedNodes.empty()) {
        rotatedNodes[0]->prev = nullptr;
        NW = rotatedNodes[0];

        for (size_t i = 0; i < rotatedNodes.size() - 1; i++) {
            rotatedNodes[i]->next = rotatedNodes[i + 1];
            rotatedNodes[i + 1]->prev = rotatedNodes[i];
        }

        SE = rotatedNodes.back();
        SE->next = nullptr;
    }
}


/**
 * Destroys all dynamically allocated memory associated with
 * this Chain object. Called by destructor and operator=.
 * You must complete its implementation for PA1.
 */
void Chain::Clear() {
	// complete your implementation below

	 Node* temp = NW;
    while(temp != NULL){
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    NW = NULL;
    SE = NULL;
    length_ =0;


}

/**
 * Copies the parameter other Chain into the temp Chain.
 * Does not free any memory. Called by copy constructor and
 * operator=.
 * You must complete its implementation for PA1.
 * @param other The Chain to be copied.
 */
void Chain::Copy(const Chain& other) {
	// complete your implementation below
    if (other.IsEmpty()) {
    NW = nullptr;SE = nullptr; length_ = 0;
    return;
    }
NW = new Node(other.NW->data);
Node* currentOther = other.NW->next;
Node* currentNew = NW;

while (currentOther != nullptr) {
    Node* newNode = new Node(currentOther->data);
    currentNew->next = newNode;
    newNode->prev = currentNew;
    currentNew = newNode;
    currentOther = currentOther->next;
}

SE = currentNew;
SE->next = nullptr;
length_ = other.length_;
}
/**
 * If you have declared any private helper functions in chain_private.h,
 * add your completed implementations below.
 */
