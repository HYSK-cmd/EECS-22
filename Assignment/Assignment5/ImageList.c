/*********************************************************************/
/* Homework Assignment 5, for EECS 22, Winter 2024                   */
/* ImageList.c: source file for image list manipulations             */
/*********************************************************************/

#include <stdlib.h>
#include <assert.h>
#include "ImageList.h"
#include <stdio.h>
/* Create a new image list */
ILIST *CreateImageList(void)
{
	ILIST *image_list;
	image_list = malloc(sizeof(ILIST));
	if(!image_list){
		perror("Out of Memory. Aborting..");
		exit(10);
	}
	image_list->Length = 0;
	image_list->First = NULL;
	image_list->Last = NULL;
	return image_list;
}

/* Delete an image list (and all entries) */
void DeleteImageList(ILIST *list)
{
    IENTRY *e, *n;
    assert(list);
    e = list->First;
    while (e) {
        n = e->Next;
        if (e->image) {
			if (e->image == (void *)((YUVImage *)(e->image))) {
				DeleteYUVImage((YUVImage *)(e->image));
			} else {
				DeleteImage((Image *)(e->image));
			}
			e->image = NULL;
        }
        free(e);  // Free the list entry itself
        e = n;
    }
	list->First = NULL;
    list->Last = NULL;
    list->Length = 0;
    free(list);
}

/* Insert a RGB image to the image list at the end */
void AppendRGBImage(ILIST *list, Image *RGBimage)
{
	assert(list);
	assert(RGBimage);

	IENTRY *rgbimg = malloc(sizeof(IENTRY));

	rgbimg->image = RGBimage;
	rgbimg->List = list;

	if(list->Last){
		rgbimg->Next = NULL;			// last element is null
		rgbimg->Prev = list->Last; 		// prev element is last element in the list;
		list->Last->Next = rgbimg; 		// next element is rgbimg
		list->Last = rgbimg; 			// last element in the list should be rgbimg
	} else { 							// the list is empty
		rgbimg->Prev = NULL; 			// prev element is null
		rgbimg->Next = NULL;			// last element is null
		list->First = rgbimg; 			// first and last element in the list is rgbimg
		list->Last = rgbimg;
	}
	list->Length++;
}

/* Insert a YUV image to the image list at the end */
void AppendYUVImage(ILIST *list, YUVImage *YUVimage)
{
	assert(list);
	assert(YUVimage);

	IENTRY *yuvimg = malloc(sizeof(IENTRY));

	yuvimg->image = YUVimage;
	yuvimg->List = list;

	if(list->Last){
		yuvimg->Next = NULL;			// last element is null
		yuvimg->Prev = list->Last; 		// prev element is last element in the list;
		list->Last->Next = yuvimg; 		// next element is yuvimg
		list->Last = yuvimg; 			// last element in the list should be yuvimg
	} else { 							// the list is empty
		yuvimg->Prev = NULL; 			// prev element is null
		yuvimg->Next = NULL;			// last element is null
		list->First = yuvimg; 			// first and last element in the list is yuvimg
		list->Last = yuvimg;
	}
	list->Length++;
}

/* Crop an image list */
void CropImageList(ILIST *list, unsigned int start, unsigned int end)
{
	assert(list);
	assert(start < end);
	assert(end <= list->Length);

	unsigned int n = 0;
	IENTRY *ENTRY = list->First;
	IENTRY *nextENTRY;
	while(ENTRY){
		nextENTRY = ENTRY->Next;
		//crop any images before and after
		if(n < start || n > end){
			if(ENTRY->image){
				if (list->First->image) {
                    DeleteYUVImage((YUVImage *)(ENTRY->image));
                } else {
                    DeleteImage((Image *)(ENTRY->image));
                }
                ENTRY->image = NULL;
			}
			if(ENTRY->Prev){
				ENTRY->Prev->Next = ENTRY->Next;
			} else {
				list->First = ENTRY->Next;
			}
			if(ENTRY->Next){
				ENTRY->Next->Prev = ENTRY->Prev;
			} else {
				list->Last = ENTRY->Prev;
			}
			free(ENTRY);
			list->Length--;
		}
		ENTRY = nextENTRY;		
		n++;
	}
}

/* Fast forward an image list */
void FastImageList(ILIST *list, unsigned int factor)
{
	assert(list);
	assert(factor);
	unsigned int n = 0, nLength = 0;
	IENTRY *ENTRY = list->First;
	IENTRY *nextENTRY;
	while (ENTRY)
	{
		nextENTRY = ENTRY->Next;
		if(n % factor != 0){
			if(ENTRY->image){
				if (list->First->image) {
                    DeleteYUVImage((YUVImage *)(ENTRY->image));
                } else {
                    DeleteImage((Image *)(ENTRY->image));
                }
                ENTRY->image = NULL;
			}
			if(ENTRY->Prev){
				ENTRY->Prev->Next = ENTRY->Next;
			} else {
				list->First = ENTRY->Next;
			}
			if(ENTRY->Next){
				ENTRY->Next->Prev = ENTRY->Prev;
			} else {
				list->Last = ENTRY->Prev;
			}
			free(ENTRY);
		} else {
			nLength++;
		}
		ENTRY = nextENTRY;
		n++;
	}
	list->Length = nLength; //updated length
}

/* Reverse an image list */
void ReverseImageList(ILIST *list)
{
	assert(list);
	IENTRY *ENTRY = list->First;
	while(ENTRY && ENTRY->Next) //traverse to the last node
	{
		ENTRY = ENTRY->Next;
	}
	list->Last = list->First; //swap first and last headers
	list->First = ENTRY;
	// play backwards
	while(ENTRY){ 
		IENTRY *tmp = ENTRY->Next;
		ENTRY->Next = ENTRY->Prev;
		ENTRY->Prev = tmp;

		ENTRY = ENTRY->Next;
	}
}

/* Insert a RGB image to the image list in the front */
void PrependRGBImage(ILIST *list, Image *RGBimage)
{
	assert(list);
	assert(RGBimage);

	IENTRY *rgbimg = malloc(sizeof(IENTRY));
	assert(rgbimg);
	rgbimg->image = RGBimage;
	rgbimg->List = list;

	if(list->First){
		rgbimg->Prev = NULL;			// prev element is null
		rgbimg->Next = list->First;		// next element is orignally first element in the list;
		list->First->Prev = rgbimg;		// prev element is rgbimg
		list->First = rgbimg;			// first element in the list should be rgbimg
	} else {	//if the list is emty
		rgbimg->Prev = NULL;			// prev element is null
		rgbimg->Next = NULL;			// last element is null
		list->First = rgbimg;			// first and last element in the list is yuvimg
		list->Last = rgbimg;	
	}
	list->Length++;
}
/* EOF */