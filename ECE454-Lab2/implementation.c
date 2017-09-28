#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "utilities.h"  // DO NOT REMOVE this line
#include "implementation_reference.h"   // DO NOT REMOVE this line

//#define PRINTS 0

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
    return processMoveUpReference(buffer_frame, width, height, offset);
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
    return processMoveRightReference(buffer_frame, width, height, offset);
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
    return processMoveDownReference(buffer_frame, width, height, offset);
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
    return processMoveLeftReference(buffer_frame, width, height, offset);
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
    return processRotateCWReference(buffer_frame, width, height, rotate_iteration);
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
    return processMirrorXReference(buffer_frame, width, height, _unused);
}

/***********************************************************************************************************************
 * @param buffer_frame - pointer pointing to a buffer storing the imported 24-bit bitmap image
 * @param width - width of the imported 24-bit bitmap image
 * @param height - height of the imported 24-bit bitmap image
 * @param _unused - this field is unused
 * @return
 **********************************************************************************************************************/
unsigned char *processMirrorY(unsigned char *buffer_frame, unsigned width, unsigned height, int _unused) {
    return processMirrorYReference(buffer_frame, width, height, _unused);
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
void print_frame_buffer_to_terminal(unsigned char *frame_buffer, unsigned int width, unsigned int height) {
	for (int col = 0; col < width; col++) printf("=");
	printf("\n");
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if(frame_buffer[row * width * 3 + col * 3] == 255) {
				printf("-");
			} else {
				printf("O");
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

// Function that compounds 25 sensor values into up to 3 transformations
unsigned char *compound_sensor_values(unsigned char *frame_buffer, struct kv *sensor_values,
									  int startingSensorValueIdx, unsigned int width, unsigned int height) {
    // Variables to keep track of current accumulated state
    int currentRotation = ROTATION_UPRIGHT;
    bool isFlippedAcrossXAxis = false;
    bool isFlippedAcrossYAxis = false;
    int accumulatedXTranslation = 0;
    int accumulatedYTranslation = 0;
    
    // Iterate over every sensor value
    for (int sensorValueIdx = startingSensorValueIdx; sensorValueIdx < startingSensorValueIdx + 25; sensorValueIdx++) {
    	// If sensor value is negative, use the opposite sensor motion
    	char *effectiveKey = sensor_values[sensorValueIdx].key;
    	int effectiveValue = sensor_values[sensorValueIdx].value;
		if (sensor_values[sensorValueIdx].value < 0) {
			if (!strcmp(sensor_values[sensorValueIdx].key, "CW")) {
				effectiveKey = "CCW";
			} else if (!strcmp(sensor_values[sensorValueIdx].key, "CCW")) {
				effectiveKey = "CW";
			} else if (!strcmp(sensor_values[sensorValueIdx].key, "W")) { // Up
				effectiveKey = "S";
			} else if (!strcmp(sensor_values[sensorValueIdx].key, "S")) { // Down
				effectiveKey = "W";
			} else if (!strcmp(sensor_values[sensorValueIdx].key, "D")) { // Right
				effectiveKey = "A";
			} else if (!strcmp(sensor_values[sensorValueIdx].key, "A")) { // Left
				effectiveKey = "D";
			}
			effectiveValue = -1 * sensor_values[sensorValueIdx].value;
		}
    	
		// Rotations affect rotation state
		if (!strcmp(effectiveKey, "CW")) {
			currentRotation = (currentRotation + effectiveValue) % 4;
		} else if (!strcmp(effectiveKey, "CCW")) {
			currentRotation = (currentRotation - effectiveValue) % 4;
			if(currentRotation < 0) {
				currentRotation = 4 + currentRotation;
			}
		}
		
		// Flips affect flip state
		else if (!strcmp(effectiveKey, "MX")) {
			if(currentRotation == ROTATION_UPRIGHT) {
				isFlippedAcrossXAxis = !isFlippedAcrossXAxis;
			} else if(currentRotation == ROTATION_RIGHT) {
				isFlippedAcrossYAxis = !isFlippedAcrossYAxis;
			} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
				isFlippedAcrossXAxis = !isFlippedAcrossXAxis;
			} else /* ROTATION_LEFT */ {
				isFlippedAcrossYAxis = !isFlippedAcrossYAxis;
			}
		} else if (!strcmp(effectiveKey, "MY")) {
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
		else if (!strcmp(effectiveKey, "W")) { // Up
			if(currentRotation == ROTATION_UPRIGHT) {
				// The motion here should be the motion in the rotated space, but the translation in the og space
				accumulatedYTranslation += (isFlippedAcrossXAxis ? -1 : 1) * effectiveValue;
			} else if(currentRotation == ROTATION_RIGHT) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? 1 : -1) * effectiveValue;
			} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? 1 : -1) * effectiveValue;
			} else /* ROTATION_LEFT */ {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? -1 : 1) * effectiveValue;
			}
		} else if (!strcmp(effectiveKey, "S")) { // Down
			if(currentRotation == ROTATION_UPRIGHT) {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? 1 : -1) * effectiveValue;
			} else if(currentRotation == ROTATION_RIGHT) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? -1 : 1) * effectiveValue;
			} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? -1 : 1) * effectiveValue;
			} else /* ROTATION_LEFT */ {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? 1 : -1) * effectiveValue;
			}
		} else if (!strcmp(effectiveKey, "D")) { // Right
			if(currentRotation == ROTATION_UPRIGHT) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? -1 : 1) * effectiveValue;
			} else if(currentRotation == ROTATION_RIGHT) {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? -1 : 1) * effectiveValue;
			} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? 1 : -1) * effectiveValue;
			} else /* ROTATION_LEFT */ {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? 1 : -1) * effectiveValue;
			}
		} else if (!strcmp(effectiveKey, "A")) { // Left
			if(currentRotation == ROTATION_UPRIGHT) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? 1 : -1) * effectiveValue;
			} else if(currentRotation == ROTATION_RIGHT) {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? 1 : -1) * effectiveValue;
			} else if(currentRotation == ROTATION_UPSIDE_DOWN) {
				accumulatedXTranslation += (isFlippedAcrossYAxis ? -1 : 1) * effectiveValue;
			} else /* ROTATION_LEFT */ {
				accumulatedYTranslation += (isFlippedAcrossXAxis ? 1 : -1) * effectiveValue;
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

