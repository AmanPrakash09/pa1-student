/**
 * File: block.cpp
 * Description: student implementation for Block functions
 *              for CPSC 221 2023S PA1
 *
 *              THIS FILE WILL BE SUBMITTED.
 */

#include "block.h"

/**
 * Creates a square Block that is dimension x dimension pixels in size,
 * starting at (x, y) on img. Assumes that the requested
 * Block fits on the image (inputs are feasible)
 */
void Block::Build(PNG& img, unsigned int x, unsigned int y, unsigned int dimension) {
	// complete your implementation below
    cout << "Build, x: " << x << " " << "y: " << y << endl;
    data.resize(dimension);

    for (unsigned int i = 0; i < dimension; i++) {
        data[i].resize(dimension);
    }

    int dataX = 0;      // ++ when j++
    int dataY = 0;      // ++ when i++

    // Loop over each pixel in the new image
    for (unsigned int i = x; i < dimension + x; i++) {
        dataX = 0;
        // cout << "1" << endl;
        // cout << "i:" << i << endl;
        // cout << "dataY:" << dataY << endl;
        for (unsigned int j = y; j < dimension + y; j++) {
            // cout << "j:" << j << endl;
            // cout << "dataX:" << dataX << endl;
            // cout << "2" << endl;
            // copy the pixel from the original image to the block image
			HSLAPixel *pixel = img.getPixel(i, j);
            // cout << "ERROR?" << endl;
			data[dataX][dataY] = *pixel;
            // cout << "4" << endl;
            // data[j][i] because we get columns through each iteration of j --> need to fill up first spot of all columns
            dataX++;
        }
        dataY++;
    }
    cout << "DONE BOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOM" << endl;

}

/**
 * Renders this Block onto img with its upper-left corner at (x, y).
 * Assumes block fits on the image.
 */
void Block::Render(PNG& img, unsigned int x, unsigned int y) const {
	// complete your implementation below
    cout << "Render" << endl;

    int dataX = 0;      // ++ when j++
    int dataY = 0;      // ++ when i++

    cout << data.size() << endl;
    
    int dimension = data.size();
    cout << "A" << endl;

    for (unsigned int i = x; i < dimension + x; i++) {
        // cout << "i:" << i << endl;
        dataX = 0;
        // cout << "B" << endl;
        for (unsigned int j = y; j < dimension + y; j++) {
            // cout << "j:" << j << endl;
            // copy the pixel from the original image to the block image
            HSLAPixel *pixel = img.getPixel(i, j);
            // cout << "C" << endl;
            *pixel = data[dataX][dataY];
            // cout << "D" << endl;
            // collect pixel from data[j][i] because img.getPixel(x + i, y + j) increments by pixels in column first then rows
            dataX++;
        }
        dataY++;
    }
}

/**
 * Flips the Block's pixel data horizontally by a simple reflection
 * across the vertical axis through its middle.
 */
void Block::FlipHorizontal() {
	// complete your implementation below
    unsigned int dimension = data.size();

    // for (unsigned int i = 0; i < dimension / 2; i++) {
    //     for (unsigned int j = 0; j < dimension; j++) {
    //         HSLAPixel pixel = data[i][j];
    //         data[i][j] = data[(dimension - 1 - i)][j];
    //         data[(dimension - 1 - i)][j] = pixel;
    //     }
    // }

    for (unsigned int i = 0; i < dimension; i++) {
        for (unsigned int j = 0; j < dimension / 2; j++) {
            HSLAPixel pixel = data[i][j];
            data[i][j] = data[i][(dimension - 1 - j)];
            data[i][(dimension - 1 - j)] = pixel;
        }
    }
}

/**
 * Rotates the Block's pixel data 90 degrees counter-clockwise.
 */
void Block::RotateCCW() {
	// complete your implementation below

    // 90 CCW: 
    
    // algorithm to rotate 90 CCW: 
    // transpose --> flip vertically    OR     flip horizontally --> transpose

    int dimension = data.size();

    FlipHorizontal();

    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < i; j++) {
            HSLAPixel pixel = data[i][j];
            data[i][j] = data[j][i];
            data[j][i] = pixel;
        }
    }
}

/**
 * Returns the dimension of the block (its width or height).
 */
unsigned int Block::Dimension() const {
	// replace the statement below with your implementation
	return data.size( );
}