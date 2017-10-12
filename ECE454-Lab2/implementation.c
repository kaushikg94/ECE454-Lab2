#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h> // TODO remove
#include "utilities.h"  // DO NOT REMOVE this line
#include "implementation_reference.h"   // DO NOT REMOVE this line

// Declarations
void print_frame_buffer_to_terminal(unsigned char *frame_buffer, unsigned int width, unsigned int height);

// Structure representing a non-white pixel in the image
typedef struct  {
	short row, col;
	unsigned char r, g, b;
} Pixel;

// Image dimensions
int width, height;

// Number of non-white pixels in the image (lengths of below arrays)
int nNonWhitePixels;

// Temporary image buffer for use by some transformations
Pixel *nonWhitePixels;

// Function to detect all non-white pixels
void detectNonWhitePixels(unsigned char *image) {
	// Allocate memory for first buffer to be bigger than how many non-white pixels we expect to see
	int nPixels = width * height;
	int initialSize = (int) (0.03 * nPixels);
	if(width < 200) initialSize = nPixels;
#ifdef PRINT_DEBUG_INFO
	printf("nPixels: %d\n", initialSize);
#endif
	nonWhitePixels = (Pixel *) malloc(initialSize * sizeof(Pixel));
	
	// Iterate through array of pixels
	int nPixelColours = nPixels * 3;
	int row = 0, col = 0;
	for(int i = 0; i < nPixelColours; i += 3) {
		unsigned char r = image[i];
		unsigned char g = image[i + 1];
		unsigned char b = image[i + 2];
		if(r + g + b < 765) {
			// Found a new non-white pixel
			nonWhitePixels[nNonWhitePixels].row = row;
			nonWhitePixels[nNonWhitePixels].col = col;
			nonWhitePixels[nNonWhitePixels].r = r;
			nonWhitePixels[nNonWhitePixels].g = g;
			nonWhitePixels[nNonWhitePixels].b = b;
			nNonWhitePixels++;
		}
		col++;
		if(col == width) {
			row++;
			col = 0;
		}
	}
#ifdef PRINT_DEBUG_INFO
	printf("nNonWhitePixels: %d\n", nNonWhitePixels);
#endif
}

// Applies an array of Pixels onto an image, filling the rest with white
void applyPixels(Pixel *pixels, unsigned char *frame_buffer) {
	// Bleach our image
	memset(frame_buffer, 255, width * height * 3);
	
	// Apply each non-white pixel
	for(int i = 0; i < nNonWhitePixels; i++) {
		Pixel pixel = pixels[i];
		frame_buffer[pixel.row * width * 3 + pixel.col * 3] = pixel.r;
		frame_buffer[pixel.row * width * 3 + pixel.col * 3 + 1] = pixel.g;
		frame_buffer[pixel.row * width * 3 + pixel.col * 3 + 2] = pixel.b;
	}
}

/***********************************************************************************************************************
 * WARNING: Do not modify the implementation_driver and team info prototype (name, parameter, return value) !!!
 *          Do not forget to modify the team_name and team member information !!!
 **********************************************************************************************************************/
void print_team_info(){
    // Please modify this field with something interesting
    char team_name[] = "sponsored-by-Popeyes";

    // Please fill in your information
    char student1_first_name[] = "Rifdhan";
    char student1_last_name[] = "Nazeer";
    char student1_student_number[] = "1000761767";

    // Please fill in your partner's information
    // If yon't have partner, do not modify this
    char student2_first_name[] = "Gokul";
    char student2_last_name[] = "Kaushik";
    char student2_student_number[] = "999878191";

    // Printing out team information
    printf("*******************************************************************************************************\n");
    printf("Team Information:\n");
    printf("\tteam_name: %s\n", team_name);
    printf("\tstudent1_first_name: %s\n", student1_first_name);
    printf("\tstudent1_last_name: %s\n", student1_last_name);
    printf("\tstudent1_student_number: %s\n", student1_student_number);
    printf("\tstudent2_first_name: %s\n", student2_first_name);
    printf("\tstudent2_last_name: %s\n", student2_last_name);
    printf("\tstudent2_student_number: %s\n", student2_student_number);
}

// Function that prints the given frame buffer to terminal in a ledgible format
// usage: print_frame_buffer_to_terminal(buffer_frame, width, height);
void print_frame_buffer_to_terminal(unsigned char *frame_buffer, unsigned int width, unsigned int height) {
	for (int col = 0; col < width; col++) printf("=");
	printf("\n");
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if(frame_buffer[row * width * 3 + col * 3] != 255 ||
				frame_buffer[row * width * 3 + col * 3 + 1] != 255 ||
				frame_buffer[row * width * 3 + col * 3 + 2] != 255) {
				printf("O");
			} else {
				printf("-");
			}
		}
		printf("\n");
	}
	for (int col = 0; col < width; col++) printf("=");
	printf("\n");
}

// Orientation constants (in CW order)
#define ROTATION_UPRIGHT     0
#define ROTATION_RIGHT       1
#define ROTATION_UPSIDE_DOWN 2
#define ROTATION_LEFT        3

// Sensor keys
#define SENSOR_CW  0b000 // 0
#define SENSOR_CCW 0b111 // 7
#define SENSOR_MX  0b001 // 1
#define SENSOR_MY  0b110 // 6
#define SENSOR_W   0b010 // 2
#define SENSOR_S   0b101 // 5
#define SENSOR_D   0b100 // 4
#define SENSOR_A   0b011 // 3

// Applies a set of transformations to a given list of pixels
void transformPixels(Pixel *pixels, int accumulatedXTranslation, int accumulatedYTranslation,
					 bool isFlippedAcrossXAxis, bool isFlippedAcrossYAxis, int currentRotation) {
	// Apply transformation to each pixel
	int sizeOver2 = width / 2;
	for(int i = 0; i < nNonWhitePixels; i++) {
		// Transform from row,col space to x,y space
		short x = pixels[i].col;
		short y = height - 1 - pixels[i].row;
		//printf("Before: x: %d, y: %d\n", x, y);
		
		// Apply transformations in x,y space
		x += accumulatedXTranslation;
		y += accumulatedYTranslation;
		
		if(isFlippedAcrossXAxis) y = height - 1 - y;
		if(isFlippedAcrossYAxis) x = width - 1 - x;
		
		if(currentRotation == ROTATION_UPRIGHT) {
			// Do nothing
		} else if(currentRotation == ROTATION_RIGHT) {
			x -= sizeOver2;
			y -= sizeOver2;
			short temp = x;
			x = y;
			y = -temp - 1;
			x += sizeOver2;
			y += sizeOver2;
		} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
			x -= sizeOver2;
			y -= sizeOver2;
			x = -x - 1;
			y = -y - 1;
			x += sizeOver2;
			y += sizeOver2;
		} else /* ROTATION_LEFT */ {
			x -= sizeOver2;
			y -= sizeOver2;
			short temp = x;
			x = -y - 1;
			y = temp;
			x += sizeOver2;
			y += sizeOver2;
		}
		
		// Transform from x,y space to row,col space
		//printf("After:  x: %d, y: %d\n", x, y);
		pixels[i].col = x;
		pixels[i].row = height - 1 - y;
	}
}

// Function that compounds 25 sensor values into up to 3 transformations
static inline void compound_sensor_values(Pixel *pixels, struct kv *sensor_values, int startingSensorValueIdx) {
    // Variables to keep track of current accumulated state
    int currentRotation = ROTATION_UPRIGHT;
    bool isFlippedAcrossXAxis = false;
    bool isFlippedAcrossYAxis = false;
    int accumulatedXTranslation = 0;
    int accumulatedYTranslation = 0;
    
    // Iterate over every sensor value
    for (int sensorValueIdx = startingSensorValueIdx; sensorValueIdx < startingSensorValueIdx + 25; sensorValueIdx++) {
    	// Determine the current sensor key and value
    	int sensorKey;
    	int sensorValue = sensor_values[sensorValueIdx].value;
    	if(sensorValue == 0) continue;
    	{
    		// Map the current sensor key to a sensor key int
			char firstLetter = sensor_values[sensorValueIdx].key[0];
			if(firstLetter == 'C') {
				char secondLetter = sensor_values[sensorValueIdx].key[1];
				if(secondLetter == 'W') sensorKey = SENSOR_CW;
				else /* secondLetter == C */ sensorKey = SENSOR_CCW;
			} else if(firstLetter == 'M') {
				char secondLetter = sensor_values[sensorValueIdx].key[1];
				if(secondLetter == 'X') sensorKey = SENSOR_MX;
				else /* secondLetter == Y */ sensorKey = SENSOR_MY;
			} else if(firstLetter == 'W') {
				sensorKey = SENSOR_W;
			} else if(firstLetter == 'S') {
				sensorKey = SENSOR_S;
			} else if(firstLetter == 'D') {
				sensorKey = SENSOR_D;
			} else /* firstLetter == A */ {
				sensorKey = SENSOR_A;
			}
			
			// If the sensor value is negative, use the opposite operation
			if(sensorValue < 0 && (sensorKey != SENSOR_MX && sensorKey != SENSOR_MY)) {
				sensorKey = ~sensorKey & 0b0111;
				sensorValue = 0 - sensorValue;
			}
    	}
    	
		// Rotations affect rotation state
		if (sensorKey == SENSOR_CW) {
			currentRotation = (currentRotation + sensorValue) % 4;
		} else if (sensorKey == SENSOR_CCW) {
			currentRotation = (currentRotation - sensorValue) % 4;
			if(currentRotation < 0) {
				currentRotation = 4 + currentRotation;
			}
		}
		
		// Flips affect flip state
		else if (sensorKey == SENSOR_MX) {
			if(currentRotation == ROTATION_UPRIGHT) {
				isFlippedAcrossXAxis = !isFlippedAcrossXAxis;
			} else if(currentRotation == ROTATION_RIGHT) {
				isFlippedAcrossYAxis = !isFlippedAcrossYAxis;
			} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
				isFlippedAcrossXAxis = !isFlippedAcrossXAxis;
			} else /* ROTATION_LEFT */ {
				isFlippedAcrossYAxis = !isFlippedAcrossYAxis;
			}
		} else if (sensorKey == SENSOR_MY) {
			if(currentRotation == ROTATION_UPRIGHT) {
				isFlippedAcrossYAxis = !isFlippedAcrossYAxis;
			} else if(currentRotation == ROTATION_RIGHT) {
				isFlippedAcrossXAxis = !isFlippedAcrossXAxis;
			} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
				isFlippedAcrossYAxis = !isFlippedAcrossYAxis;
			} else /* ROTATION_LEFT */ {
				isFlippedAcrossXAxis = !isFlippedAcrossXAxis;
			}
		}
		
		// Compute translation state based on current rotation and flip state
		else if (sensorKey == SENSOR_W) { // Up
			if(currentRotation == ROTATION_UPRIGHT) {
				// The motion here should be the motion in the rotated space, but the translation in the og space
				accumulatedYTranslation += (isFlippedAcrossXAxis ? -1 : 1) * sensorValue;
			} else if(currentRotation == ROTATION_RIGHT) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? 1 : -1) * sensorValue;
			} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? 1 : -1) * sensorValue;
			} else /* ROTATION_LEFT */ {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? -1 : 1) * sensorValue;
			}
		} else if (sensorKey == SENSOR_S) { // Down
			if(currentRotation == ROTATION_UPRIGHT) {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? 1 : -1) * sensorValue;
			} else if(currentRotation == ROTATION_RIGHT) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? -1 : 1) * sensorValue;
			} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? -1 : 1) * sensorValue;
			} else /* ROTATION_LEFT */ {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? 1 : -1) * sensorValue;
			}
		} else if (sensorKey == SENSOR_D) { // Right
			if(currentRotation == ROTATION_UPRIGHT) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? -1 : 1) * sensorValue;
			} else if(currentRotation == ROTATION_RIGHT) {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? -1 : 1) * sensorValue;
			} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? 1 : -1) * sensorValue;
			} else /* ROTATION_LEFT */ {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? 1 : -1) * sensorValue;
			}
		} else if (sensorKey == SENSOR_A) { // Left
			if(currentRotation == ROTATION_UPRIGHT) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? 1 : -1) * sensorValue;
			} else if(currentRotation == ROTATION_RIGHT) {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? 1 : -1) * sensorValue;
			} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? -1 : 1) * sensorValue;
			} else /* ROTATION_LEFT */ {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? -1 : 1) * sensorValue;
			}
		}
    }
    
#ifdef PRINT_DEBUG_INFO
	// DEBUG: print state
    printf("xTranslate: %d, yTranslate: %d\n", accumulatedXTranslation, accumulatedYTranslation);
    printf("flipped across x: %d, flipped across y: %d\n", isFlippedAcrossXAxis, isFlippedAcrossYAxis);
    printf("rotation: %d\n", currentRotation);
#endif

	// Apply all transformations
	transformPixels(pixels, accumulatedXTranslation, accumulatedYTranslation,
		isFlippedAcrossXAxis, isFlippedAcrossYAxis, currentRotation);
}


/***********************************************************************************************************************
 * WARNING: Do not modify the implementation_driver and team info prototype (name, parameter, return value) !!!
 *          You can modify anything else in this file
 ***********************************************************************************************************************
 * @param sensor_values - structure stores parsed key value pairs of program instructions
 * @param sensor_values_count - number of valid sensor values parsed from sensor log file or commandline console
 * @param frame_buffer - pointer pointing to a buffer storing the imported  24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param grading_mode - turns off verification and turn on instrumentation
 ***********************************************************************************************************************
 *
 **********************************************************************************************************************/
void implementation_driver(struct kv *sensor_values, int sensor_values_count, unsigned char *frame_buffer,
                           unsigned int _width, unsigned int _height, bool grading_mode) {
    // Reset temporary frame buffers
    nNonWhitePixels = 0;
    nonWhitePixels = NULL;
    width = _width;
    height = _height;
    
    // Find all non-white pixels in the image
    detectNonWhitePixels(frame_buffer);
	
#ifdef DISPLAY_IMAGE_IN_TERMINAL
	printf("Starting frame:\n");
	print_frame_buffer_to_terminal(frame_buffer, width, height);
#endif
    
    // Iterate over every group of 25 sensor values
    for (int sensorValueIdx = 0; sensorValueIdx < sensor_values_count; sensorValueIdx += 25) {
    	// Check if this group has fewer than 25 sensor values
    	if(sensorValueIdx + 25 > sensor_values_count) {
    		// If so, we are not required to output a frame for this group
    		break;
    	}
    	
    	// Process this group of 25 sensor values
    	compound_sensor_values(nonWhitePixels, sensor_values, sensorValueIdx);
		applyPixels(nonWhitePixels, frame_buffer);
#ifdef DISPLAY_IMAGE_IN_TERMINAL
		printf("Frame %d:\n", (sensorValueIdx / 25 + 1));
    	print_frame_buffer_to_terminal(frame_buffer, width, height);
#endif
    	
    	// Verify the new frame
#ifndef SKIP_VERIFICATION
        verifyFrame(frame_buffer, width, height, grading_mode);
#endif
    }
    
    // Free temporary buffers
    free(nonWhitePixels);
}

