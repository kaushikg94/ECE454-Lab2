#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "utilities.h"  // DO NOT REMOVE this line
#include "implementation_reference.h"   // DO NOT REMOVE this line

//#define PRINTS 0

// Declarations
unsigned char *processMoveUp(unsigned char *buffer_frame, unsigned width, unsigned height, int offset);
unsigned char *processMoveLeft(unsigned char *buffer_frame, unsigned width, unsigned height, int offset);
unsigned char *processMoveDown(unsigned char *buffer_frame, unsigned width, unsigned height, int offset);
unsigned char *processMoveRight(unsigned char *buffer_frame, unsigned width, unsigned height, int offset);
unsigned char *processRotateCW(unsigned char *buffer_frame, unsigned width, unsigned height,
                                        int rotate_iteration);
unsigned char *processRotateCCW(unsigned char *buffer_frame, unsigned width, unsigned height,
                                        int rotate_iteration);
void print_frame_buffer_to_terminal(unsigned char *frame_buffer, unsigned int width, unsigned int height);

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image up
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveUp(unsigned char *buffer_frame, unsigned width, unsigned height, int offset) {
    // handle negative offsets
    if (offset < 0) {
        return processMoveDown(buffer_frame, width, height, offset * -1);
    }
    
    // store shifted pixels to temporary buffer
    for (int row = 0; row < (height - offset); row++) {
        for (int column = 0; column < width * 3; column++) {
            int position_above = row * width * 3 + column;
            int position_below = (row + offset) * width * 3 + column;
            buffer_frame[position_above] = buffer_frame[position_below];
        }
    }

    // fill left over pixels with white pixels
    for (int row = (height - offset); row < height; row++) {
        for (int column = 0; column < width * 3; column++) {
            int position_rendered_frame = row * width * 3 + column;
            buffer_frame[position_rendered_frame] = 255;
        }
    }

    // return a pointer to the updated image buffer
    return buffer_frame;
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image up
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveDown(unsigned char *buffer_frame, unsigned width, unsigned height, int offset) {
    // handle negative offsets
    if (offset < 0) {
        return processMoveUp(buffer_frame, width, height, offset * -1);
    }

    // store shifted pixels to temporary buffer
    for (int row = height - 1; row > offset - 1; row--) {
        for (int column = 0; column < width * 3; column++) {
            int position_below = row * width * 3 + column;
            int position_above = (row - offset) * width * 3 + column;
            buffer_frame[position_below] = buffer_frame[position_above];
        }
    }

    // fill left over pixels with white pixels
    for (int row = 0; row < offset; row++) {
        for (int column = 0; column < width * 3; column++) {
            int position_rendered_frame = row * width * 3 + column;
            buffer_frame[position_rendered_frame] = 255;
        }
    }
    
    // return a pointer to the updated image buffer
    return buffer_frame;
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image left
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveRight(unsigned char *buffer_frame, unsigned width, unsigned height, int offset) {
    // handle negative offsets
    if (offset < 0) {
        return processMoveLeft(buffer_frame, width, height, offset * -1);
    }

    // store shifted pixels to temporary buffer
    for (int row = 0; row < height; row++) {
        for (int column = width * 3 - 1; column > offset * 3 - 1; column--) {
            int position_right = row * width * 3 + column;
            int position_left = row * width * 3 + (column - 3 * offset);
            buffer_frame[position_right] = buffer_frame[position_left];
        }
    }

    // fill left over pixels with white pixels
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < offset * 3; column++) {
            int position_rendered_frame = row * width * 3 + column;
            buffer_frame[position_rendered_frame] = 255;
        }
    }

    // return a pointer to the updated image buffer
    return buffer_frame;
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param offset - number of pixels to shift the object in bitmap image right
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note1: White pixels RGB(255,255,255) are treated as background. Object in the image refers to non-white pixels.
 * Note2: You can assume the object will never be moved off the screen
 **********************************************************************************************************************/
unsigned char *processMoveLeft(unsigned char *buffer_frame, unsigned width, unsigned height, int offset) {
    // handle negative offsets
    if (offset < 0) {
        return processMoveRight(buffer_frame, width, height, offset * -1);
    }

    // store shifted pixels to temporary buffer
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < (width - offset) * 3; column++) {
            int position_left = row * width * 3 + column;
            int position_right = row * width * 3 + column + offset * 3;
            buffer_frame[position_left] = buffer_frame[position_right];
        }
    }

    // fill left over pixels with white pixels
    for (int row = 0; row < height; row++) {
        for (int column = (width - offset) * 3 - 1; column < width * 3; column++) {
            int position_rendered_frame = row * width * 3 + column;
            buffer_frame[position_rendered_frame] = 255;
        }
    }

    // return a pointer to the updated image buffer
    return buffer_frame;
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param rotate_iteration - rotate object inside frame buffer clockwise by 90 degrees, <iteration> times
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note: You can assume the frame will always be square and you will be rotating the entire image
 **********************************************************************************************************************/
unsigned char *processRotateCW(unsigned char *buffer_frame, unsigned width, unsigned height,
                               int rotate_iteration) {
    // handle negative offsets
    if (rotate_iteration < 0){
        return processRotateCCW(buffer_frame, width, height, rotate_iteration * -1);
    }

    // allocate memory for temporary image buffer
    unsigned char *rendered_frame = allocateFrame(width, height);

    // store shifted pixels to temporary buffer
    for (int iteration = 0; iteration < rotate_iteration; iteration++) {
        int render_column = width - 1;
        int render_row = 0;
        for (int row = 0; row < width; row++) {
            for (int column = 0; column < height; column++) {
                int position_frame_buffer = row * width * 3 + column * 3;
                rendered_frame[render_row * width * 3 + render_column * 3] = buffer_frame[position_frame_buffer];
                rendered_frame[render_row * width * 3 + render_column * 3 + 1] = buffer_frame[position_frame_buffer + 1];
                rendered_frame[render_row * width * 3 + render_column * 3 + 2] = buffer_frame[position_frame_buffer + 2];
                render_row += 1;
            }
            render_row = 0;
            render_column -= 1;
        }

        // copy the temporary buffer back to original frame buffer
        buffer_frame = copyFrame(rendered_frame, buffer_frame, width, height);
    }

    // free temporary image buffer
    deallocateFrame(rendered_frame);

    // return a pointer to the updated image buffer
    return buffer_frame;
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param rotate_iteration - rotate object inside frame buffer counter clockwise by 90 degrees, <iteration> times
 * @return - pointer pointing a buffer storing a modified 24-bit bitmap image
 * Note: You can assume the frame will always be square and you will be rotating the entire image
 **********************************************************************************************************************/
unsigned char *processRotateCCW(unsigned char *buffer_frame, unsigned width, unsigned height,
                                int rotate_iteration) {
    printf("WARNING: Not implemented\n");
    return processRotateCCWReference(buffer_frame, width, height, rotate_iteration);
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param _unused - this field is unused
 * @return
 **********************************************************************************************************************/
unsigned char *processMirrorX(unsigned char *buffer_frame, unsigned int width, unsigned int height, int _unused) {
    // Flip the pixels in place
    for (int row = 0; row < height / 2; row++) {
        for (int column = 0; column < width * 3; column++) {
        	int position_top = row * width * 3 + column;
        	int position_bottom = (height - row - 1) * width * 3 + column;
        	unsigned char temp = buffer_frame[position_top];
        	buffer_frame[position_top] = buffer_frame[position_bottom];
        	buffer_frame[position_bottom] = temp;
        }
    }

    return buffer_frame;
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param _unused - this field is unused
 * @return
 **********************************************************************************************************************/
unsigned char *processMirrorY(unsigned char *buffer_frame, unsigned width, unsigned height, int _unused) {
    // Flip the pixels in place
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < (width / 2); column++) {
        	int position_left = row * height * 3 + column * 3;
        	int position_right = row * height * 3 + (width - column - 1) * 3;
        	unsigned char temp = buffer_frame[position_left];
        	buffer_frame[position_left] = buffer_frame[position_right];
        	buffer_frame[position_right] = temp;
        	temp = buffer_frame[position_left + 1];
        	buffer_frame[position_left + 1] = buffer_frame[position_right + 1];
        	buffer_frame[position_right + 1] = temp;
        	temp = buffer_frame[position_left + 2];
        	buffer_frame[position_left + 2] = buffer_frame[position_right + 2];
        	buffer_frame[position_right + 2] = temp;
        }
    }

    return buffer_frame;
}

/***********************************************************************************************************************
 * WARNING: Do not modify the implementation_driver and team info prototype (name, parameter, return value) !!!
 *          Do not forget to modify the team_name and team member information !!!
 **********************************************************************************************************************/
void print_team_info(){
    // Please modify this field with something interesting
    char team_name[] = "sponsored-by-Popeyes-Louisiana-Kitchen-for-optimized-chicken";

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

// Function that compounds 25 sensor values into up to 3 transformations
static inline unsigned char *compound_sensor_values(unsigned char *frame_buffer, struct kv *sensor_values,
									  int startingSensorValueIdx, unsigned int width, unsigned int height) {
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
    	int sensorValue;
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
			sensorValue = sensor_values[sensorValueIdx].value;
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
				accumulatedYTranslation += (isFlippedAcrossXAxis ? 1 : -1) * sensorValue;
			}
		}
    }
    
#ifdef PRINTS
	// DEBUG: print state
    printf("xTranslate: %d, yTranslate: %d\n", accumulatedXTranslation, accumulatedYTranslation);
    printf("flipped across x: %d, flipped across y: %d\n", isFlippedAcrossXAxis, isFlippedAcrossYAxis);
    printf("rotation: %d\n", currentRotation);
#endif
    
    // Apply the translations
    if(accumulatedXTranslation > 0) {
		frame_buffer = processMoveRight(frame_buffer, width, height, accumulatedXTranslation);
	} else if(accumulatedXTranslation < 0) {
		frame_buffer = processMoveLeft(frame_buffer, width, height, accumulatedXTranslation * -1);
	}
    if(accumulatedYTranslation > 0) {
		frame_buffer = processMoveUp(frame_buffer, width, height, accumulatedYTranslation);
	} else if(accumulatedYTranslation < 0) {
		frame_buffer = processMoveDown(frame_buffer, width, height, accumulatedYTranslation * -1);
	}
    
    // Apply the flips
    if(isFlippedAcrossXAxis) {
    	frame_buffer = processMirrorX(frame_buffer, width, height, 1);
    }
    if(isFlippedAcrossYAxis) {
    	frame_buffer = processMirrorY(frame_buffer, width, height, 1);
    }
    
    // Apply the rotations
    if(currentRotation != ROTATION_UPRIGHT) {
    	frame_buffer = processRotateCW(frame_buffer, width, height, currentRotation);
    }
    
    return frame_buffer;
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
// DEBUG: reference implementation driver for comparison
void implementation_driver_ref(struct kv *sensor_values, int sensor_values_count, unsigned char *frame_buffer,
                           unsigned int width, unsigned int height, bool grading_mode) {   
    for (int sensorValueIdx = 0; sensorValueIdx < sensor_values_count; sensorValueIdx++) {
        if (!strcmp(sensor_values[sensorValueIdx].key, "W")) {
            frame_buffer = processMoveUp(frame_buffer, width, height, sensor_values[sensorValueIdx].value);
        } else if (!strcmp(sensor_values[sensorValueIdx].key, "A")) {
            frame_buffer = processMoveLeft(frame_buffer, width, height, sensor_values[sensorValueIdx].value);
        } else if (!strcmp(sensor_values[sensorValueIdx].key, "S")) {
            frame_buffer = processMoveDown(frame_buffer, width, height, sensor_values[sensorValueIdx].value);
        } else if (!strcmp(sensor_values[sensorValueIdx].key, "D")) {
            frame_buffer = processMoveRight(frame_buffer, width, height, sensor_values[sensorValueIdx].value);
        } else if (!strcmp(sensor_values[sensorValueIdx].key, "CW")) {
            frame_buffer = processRotateCW(frame_buffer, width, height, sensor_values[sensorValueIdx].value);
        } else if (!strcmp(sensor_values[sensorValueIdx].key, "CCW")) {
            frame_buffer = processRotateCCW(frame_buffer, width, height, sensor_values[sensorValueIdx].value);
        } else if (!strcmp(sensor_values[sensorValueIdx].key, "MX")) {
            frame_buffer = processMirrorX(frame_buffer, width, height, sensor_values[sensorValueIdx].value);
        } else if (!strcmp(sensor_values[sensorValueIdx].key, "MY")) {
            frame_buffer = processMirrorY(frame_buffer, width, height, sensor_values[sensorValueIdx].value);
        }
    }
}


void implementation_driver(struct kv *sensor_values, int sensor_values_count, unsigned char *frame_buffer,
                           unsigned int width, unsigned int height, bool grading_mode) {
    // DEBUG: make a copy of the original frame
    //unsigned char *reference_frame = allocateFrame(width, height);
    //reference_frame = copyFrame(frame_buffer, reference_frame, width, height);
    //implementation_driver_ref(sensor_values, sensor_values_count, reference_frame, width, height, grading_mode);
    
    // DEBUG: print original and ref frame
	//printf("Original:\n");
    //print_frame_buffer_to_terminal(frame_buffer, width, height);
	//printf("Reference:\n");
	//print_frame_buffer_to_terminal(reference_frame, width, height);
    
    // Iterate over every group of 25 sensor values
    for (int sensorValueIdx = 0; sensorValueIdx < sensor_values_count; sensorValueIdx += 25) {
    	// Check if this group has fewer than 25 sensor values
    	if(sensorValueIdx + 25 > sensor_values_count) {
    		// If so, we are not required to output a frame for this group
    		break;
    	}
    	
    	// Process this group of 25 sensor values
    	frame_buffer = compound_sensor_values(frame_buffer, sensor_values, sensorValueIdx, width, height);
    	
    	// DEBUG: print processed frame
		//printf("After %d iterations:\n", (sensorValueIdx + 1) * 25);
		//print_frame_buffer_to_terminal(frame_buffer, width, height);
    	
    	// Verify the new frame
        verifyFrame(frame_buffer, width, height, grading_mode);
    }
}

