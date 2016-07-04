//
//	ICS 51, Lab #2
//
//	-----------------------------------------------------------------
// 
//	IMPORTATNT NOTES:
//	
//	- To test your code use the tests in lab2-testing.cpp
//	
//	- Write your assembly code only in the marked blocks.
//	
//	- Do NOT change anything outside the marked blocks.
//
//	- Remember to fill in your name, student ID below.
// 
//	- This lab has to be done individually.
//
//  - Use lodepng.h and lodepng.cpp to read/write png files.
//
//  - Two test images are provided to you.
//	
//	- Submit ONLY lab2.cpp file for grading.
// 

char *yourName = "Maximillian Kirchgesner";
char *yourStudentID = "27238431";

//
// This function should takes in a square sized grayscale image and applies thresholding on each pixel.
// Width and height of the image are equal to dim.
// NOTE: you can't define additional variables.
//
void imageThresholding(unsigned char* image, int dim) {

	__asm {

		// YOUR CODE STARTS HERE
		//General purpose register: eax, ebx, ecx, edx, esi, edi
		mov esi, 0 // row counter
		mov ebx, image
	//Loop through each row of the image
	ROWLOOP:
		cmp esi, dim
		jae ROWDONE // if the register is greater than the dimension, then we are done with all the rows
		and edi, 0 // otherwise, we move on and compare the columns
	//Loop through each column of the image
	COLLOOP:
		cmp edi, dim
		jae COLDONE // if the register is greater than the dimension, then we are done with this certain column
		and eax, 0
		and edx, 0
	
	// Offset Formula = (row_index * num_of_col) + col_index
	// Element_address = base_address + (element_size_in_bytes * offset)
	// Each element is 1 byte

	LABEL1:
		cmp edx, dim
		jae LABEL1DONE // if greater, then exit loop
		add eax, esi // #of rows
		add edx, 1
		jmp LABEL1
	LABEL1DONE:
		add eax, edi
		and edx, 0
		mov cl, [ebx+eax]
		and cl, 0x80
		cmp cl, 0x00 // if the intensity of the pixel is greater than 0x80, then replace pixel with 0xFF
		jne LABEL2
		and edx, 0
		jmp LABEL3
	LABEL2:
		or edx, 0xFF
	LABEL3:
		mov[ebx+eax], dl
		add edi, 1
		jmp COLLOOP
	COLDONE:
		add esi, 1
		jmp ROWLOOP
	ROWDONE:
		mov image, ebx
		// YOUR CODE ENDS HERE
	}

}


// This function flips an square iamge of given dimension horizontally/vertically.
// Width and height of the image are equal to dim.
// if direction is 0, image should be flipped horizontally
// otherwise image should be flipped vertically.
//
//
// Two variables are definde to help you with implemetanion.
// NOTE: you can't define additional variables.
//
void imageFlip(unsigned int* image, int dim, int direction) {

	unsigned int a_p, a_p_m;

	__asm {
		// YOUR CODE STARTS HERE
		//# parameters: image, dim, dir = 0
		//for row from 0 to dim - 1 :
		// for col from 0 to dim / 2 :

		//  # calculate the address of the current pixel
		//  a_p = image + (row * dim + col) * 4

		//  # calculate the address of the mirrored pixel
		//  row_m = # I leave this one for you to figure out!
		//  col_m = # I leave this one for you to figure out!
		//  a_p_m = image + (row_m * dim + col_m) * 4

		//  # swap the pixels
		//  temp = Mem[a_p]
		//  Mem[a_p] = Mem[a_p_m]
		//  Mem[a_p_m] = temp

		// General purpose registers: eax, ebx, ecx, edx, esi, edi
		// Can also use a_p and a_p_m
		mov eax, image
		mov ecx, 0 // row number
		mov edx, 0
		FORLOOP1: // for row from 0 to dim - 1
			mov esi, dim
			dec esi
			cmp ecx, esi
			jae ENDFORLOOP1
			mov edi, 0 // col number
			FORLOOP2 : // for col from 0 to dim/2. Since we are flipping, only need to iterate over half of the image
				mov esi, dim
				shr esi, 1 // 1 bit shifted right divides by 2
				cmp edi, esi
				jae ENDFORLOOP2
				mov ebx, 0

				//calculate address of current pixel
				//a_p = (image + (row * dim + col) * 4)
				mov esi, dim
				mul esi
				add esi, edi
				shl esi, 2 // 1 bit shifted left by 2 multiples by 4
				add esi, eax
				mov eax, image
				mov a_p, esi

				//calculate address of mirrored pixel
				//row_m = same row
				//col_m = (dim - col_idx) - 1
				mov esi, dim
				sub esi, edi
				sub esi, 1
				mov ebx, esi
				//a_p_m = (image + (row_m * dim + col_m) * 4
				//mov edx, ebx
				mov esi, dim
				mul esi
				add esi, ebx
				shl esi, 2
				add esi, eax
				mov eax, image
				mov a_p_m, esi

				//swap the pixels 
				// (calculate offset = (row_index * num_of_col) + col_index)
				// element_address = (base_address + element_size_in_bytes * offset)
				//  temp = Mem[a_p]
				//  Mem[a_p] = Mem[a_p_m]
				//  Mem[a_p_m] = temp

				//Can't figure out why it keeps crashing at mov ebx, [edx]
				
				//mov edx, a_p
				//mov ebx, [edx]
				//mov eax, a_p_m
				//mov esi, [eax]
				//mov [eax], ebx
				//mov [edx], esi
				
				mov eax, image
				add edi, 1
				jmp FORLOOP2

			ENDFORLOOP2 :
				add ecx, 1
				jmp FORLOOP1

		ENDFORLOOP1 :
			mov image, eax
			// YOUR CODE ENDS HERE

	}

}